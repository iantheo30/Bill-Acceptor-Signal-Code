#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
//WIRE CONFIGURATION
/*
 * LCD 20X4 OR LCD 16X2
 * SDA - SDA
 * SCL - SCL
 * VCC - 5V
 * GND - GND
 * 
 * BILL ACCEPTOR
 * RED WIRE - 12V
 * ORANGE WIRE - GND OF ARDUINO
 * PURPLE WIRE - GND OF ARDUINO
 * BLUE WIRE - COMMON OF RELAY THEN IT WILL COME OUT OF NO OF RELAY, THEN FROM NO GO TO PIN2
 * 
 * 1 CHANNEL RELAY
 * VCC - VCC
 * SIGNAL - PIN3 ARDUINO
 * GND - GND
 * 
 * OUTPUT SIDE OF RELAY(WHERE NC NO CAN BE SEEN)
 * COMMON - CONNECTED TO BLUE WIRE OF BILL ACCEPTOR
 * NO - TO PIN2 OF ARDUINO
 * 
 */

//PIN DECLARATIONS
int billacceptorpin = 2;
int relaybill = 3;
//PIN DECLARATIONS

//PARAMETERS DECLARATION
volatile int pulses = 0;
int prevpulses = 0;
int creditinc = 0;
int creditmoney = 0;
int resetc = 0;
//PARAMETERS DECLARATION


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin();
  
  //PINMODES
  pinMode(2, INPUT_PULLUP);
  pinMode(relaybill, OUTPUT);
  //PINMODES

  //INTERRUPT PIN DECLARATION
  attachInterrupt(digitalPinToInterrupt(2), countPulses, FALLING);  // On digital pin 2
  //INTERRUPT PIN DECLARATION
}

//PULSE COUNTER FOR BILL ACCEPTOR
void countPulses() {
  int val = digitalRead(2);
  if (val == LOW) {
    pulses += 1;
  }
  prevpulses = pulses;
}
//PULSE COUNTER FOR BILL ACCEPTOR

//PULSE TO CREDIT CONVERTER
void creditcounter() {
    Serial.println("Pulses:"+String(prevpulses));
    if(prevpulses)
    {
      lcd.clear();
      lcd.print("Inserted");
      delay(3000);
    }
    //FOR 100 PESO
    if (pulses==10) 
    {
      lcd.clear();
      lcd.print("P100");
          Serial.println("You inserted 100 pesos");
          creditinc = 100;
          pulses = 0;
          prevpulses = 0;
          digitalWrite(relaybill, HIGH);
          delay(4200);
          digitalWrite(relaybill, LOW);
          lcd.clear();
    }
    //FOR 100 PESO

    //FOR 20 PESO
      else if (pulses==2) 
      {
        lcd.clear();
        lcd.print("P20");
        Serial.println("You inserted 20 pesos");
        creditinc = 20;
        pulses = 0;
        prevpulses = 0;
        digitalWrite(relaybill, HIGH);
        delay(4200);
        digitalWrite(relaybill, LOW);
        lcd.clear();
      }
     //FOR 20 PESO

        //FOR 50 PESO
        else if (pulses==5) 
        {
          lcd.clear();
          lcd.print("P50");
          Serial.println("You inserted 50 pesos");
          creditinc = 50;
          pulses = 0;
          prevpulses = 0;
          digitalWrite(relaybill, HIGH);
          delay(4200);
          digitalWrite(relaybill, LOW);
          lcd.clear();
        } 
        //FOR 50 PESO

          //FOR 200 PESO
          else if (pulses==20) {
            lcd.clear();
            lcd.print("P200");
            Serial.println("You inserted 200 pesos");
            creditinc = 200;
            pulses = 0;
            prevpulses = 0;
            digitalWrite(relaybill, HIGH);
            delay(4200);
            digitalWrite(relaybill, LOW);
            lcd.clear();
          }
          //FOR 200 PESO

            //EXCESS PULSE CLEANER
            else
            {
                lcd.clear();
              digitalWrite(relaybill,LOW);
              delay(300);
              creditinc = 0;
            }
            //EXCESS PULSE CLEANER
      
  Serial.println("Pulse:" + String(pulses));
  creditmoney = creditmoney + creditinc;
  Serial.println("Current Bill Inserted:" + String(creditmoney));
  if(creditmoney==0)
  {
    lcd.print("Please Insert");
  }
    else
    {
      lcd.print("Inserted:" + String(creditinc));
    }
 
  delay(1000);
  lcd.clear();
}
//PULSE TO CREDIT CONVERTER

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relaybill, HIGH);
  delay(8000);
  delay(1000);
  resetc = 0;
  do {
      if (prevpulses != 0) {
        prevpulses--;
      }
  
        if (pulses != 0) {
          pulses--;
        }
  
          if (creditinc != 0) {
            creditinc--;
          }
          resetc++;
    } while (resetc != 1000);

    creditmoney = 0;
    pulses = 0;
    lcd.clear();
  //PULSE MONITORING
    do
    {
      creditcounter();
    }while(1);
  //PULSE MONITORING
}
