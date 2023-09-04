#include <Servo.h>
#include <Key.h>
#include <Keypad.h>

const byte ROWS=4;
const byte COLS=4;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};
byte rowPins[ROWS]={A0,A1,A2,A3};
byte colsPins[COLS]={5,4,3,2};


Keypad magdy = Keypad(makeKeymap(hexaKeys),rowPins,colsPins,ROWS,COLS);


byte echopin =11 ,trigpin =10;
long duration ,distance ;


Servo myservo ;


void setup() {
  Serial.begin(9600);
  pinMode(echopin, INPUT);
  pinMode(trigpin, OUTPUT);
  myservo.attach(9);
}
void loop(){
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
 digitalWrite(trigpin,HIGH);
 delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  
  duration=pulseIn(echopin,HIGH);
  distance= duration/58.2 ;
  Serial.print("distance =");
  Serial.println(distance);
  char custemkey = magdy.getKey();
  if((distance <= 8) && (custemkey == 'A' || custemkey=='B' || custemkey=='C'))
  {
    myservo.write(90);
    delay(7000);
    myservo.write(0);
    
  }
  else
  { 
    myservo.write(0);
  }
  }
  
