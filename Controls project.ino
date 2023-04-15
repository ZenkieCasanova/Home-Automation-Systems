// Motor Two
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include <Servo.h> 

LiquidCrystal_I2C lcd(0x27,16,2);

const int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

int L1 = 11;//LIGHTS
int L2 = 12;

int enB = 5; //FAN1
int IN33 = 13;
int IN44 = 4;

int enA = 6; //FAN2
int IN1 = 7;
int IN2 = 8;

int LOCK = 9; //DOORLOCK
Servo LOCK1;

void setup (){
Serial.begin(9600);
irrecv.enableIRIn();
irrecv.blink13(true);
// Set all the motor contol pins as outputs
pinMode (enB, OUTPUT);
pinMode (IN33, OUTPUT);
pinMode (IN44, OUTPUT);
pinMode (enA, OUTPUT);
pinMode (IN1, OUTPUT);
pinMode (IN2, OUTPUT);
digitalWrite(enA,HIGH);// Activer moteur A
digitalWrite(enB,HIGH);// Activer moteur B
//LIGHTS
pinMode (L1, OUTPUT);
pinMode (L2, OUTPUT);
//LOCK
LOCK1.attach(LOCK);
}
void motorOne(){
/* This function will run the motor in both directions
at a fixed speed
*/
analogWrite(enB, 100);
// Turn ON Motor Two
digitalWrite (IN33, HIGH);
digitalWrite (IN44, LOW);
// Set speed to 200 out of possible range (0 - 255)
}
void motorOneOFF(){
/* This function will run the motor in both directions
at a fixed speed
*/
analogWrite(enB, 0);
// Turn ON Motor Two
digitalWrite (IN33, LOW);
digitalWrite (IN44, LOW);
// Set speed to 200 out of possible range (0 - 255)
}
void motorTwo(){
/* This function will run the motor in both directions
at a fixed speed
*/
analogWrite(enA, 120);
analogWrite(enB, 100);
// Turn ON Motor Two
digitalWrite (IN1, HIGH);

// Turn ON Motor Two
digitalWrite (IN44, HIGH);


// Set speed to 200 out of possible range (0 - 255)
}
void motorTwoOFF(){
/* This function will run the motor in both directions
at a fixed speed
*/
analogWrite(enA, 0);
// Turn ON Motor Two
digitalWrite (IN1, LOW);
digitalWrite (IN2, LOW);
digitalWrite (IN44, LOW);
// Set speed to 200 out of possible range (0 - 255)
}
void LCDTEST(){
  // Print a message on both lines of the LCD.
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("Hello world!");
  
  lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
  lcd.print("LCD Tutorial");
}

void loop(){
  lcd.init();
  lcd.clear();
  lcd.setCursor(1,0);   //Set cursor to character 2 on line 0        
  lcd.backlight();      // Make sure backlight is on
  if (irrecv.decode(&results)){
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
          //LIVING ROOM LIGHT
          case 0xFFA25D:
          lcd.clear();
          lcd.setCursor(1,0);   //Set cursor to character 2 on line 0
          lcd.print("LIVINGRM LIGHT");
          lcd.setCursor(1,1);   //Move cursor to character 2 on line 1
          lcd.print("STATUS: ON");
          Serial.println("1");
          digitalWrite (L2, HIGH);
          break ;
          case 0xFF629D:
          lcd.clear();
          lcd.setCursor(1,0);   //Set cursor to character 2 on line 0
          lcd.print("LIVINGRM LIGHT");
          lcd.setCursor(1,1);   //Move cursor to character 2 on line 1
          lcd.print("STATUS: OFF");
          Serial.println("2");
          digitalWrite (L2, LOW);
          break ;


          //LIVING ROOM FAN
          case 0xFFE21D:
          lcd.clear();
          lcd.setCursor(1,0);   //Set cursor to character 2 on line 0
          lcd.print("LIVING ROOM FAN");
          lcd.setCursor(1,1);   //Move cursor to character 2 on line 1
          lcd.print("STATUS: ON");
          Serial.println("3");
          motorTwo();
          break ;
          case 0xFF22DD:
          lcd.clear();
          lcd.setCursor(1,0);   //Set cursor to character 2 on line 0
          lcd.print("LIVING ROOM FAN");
          lcd.setCursor(1,1);   //Move cursor to character 2 on line 1
          lcd.print("STATUS: OFF");
          Serial.println("4");
          motorTwoOFF();
          break ;
          

          case 0xFF02FD:
          lcd.clear();
          lcd.setCursor(3,0);   //Set cursor to character 2 on line 0
          lcd.print("HOUSE LOCK");
          lcd.setCursor(3,1);   //Move cursor to character 2 on line 1
          lcd.print("STATUS: OPEN");
          Serial.println("5");
          LOCK1.write(30);
          break;
          case 0xFFC23D:
          lcd.clear();
          lcd.setCursor(3,0);   //Set cursor to character 2 on line 0
          lcd.print("HOUSE LOCK");
          lcd.setCursor(3,1);   //Move cursor to character 2 on line 1
          lcd.print("STATUS: CLOSED");
          Serial.println("6");
          LOCK1.write(130);
          break ;


          case 0xFFE01F:
          lcd.clear();
          lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
          lcd.print("KITCHEN FAN&LIGHT");
          lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
          lcd.print("STATUS: ON");
          Serial.println("7");
          digitalWrite (L1, HIGH);
          motorOne();
          break ;
          case 0xFFA857:
          lcd.clear();
          lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
          lcd.print("KITCHEN FAN&LIGHT");
          lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
          lcd.print("STATUS: OFF");
          Serial.println("8");
          digitalWrite (L1, LOW);
          motorOneOFF();
          break ;
          case 0xFF6897:
          Serial.println("9");
          break ;      
        }
        key_value = results.value;
        irrecv.resume(); 
  }
}