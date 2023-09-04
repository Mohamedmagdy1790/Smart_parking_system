/*
 * A Program to demonstrate data logging 
 * using the ESP8266 and ThingSpeak.
 */

// The ESP8266 WiFi Library.
#include <ESP8266WiFi.h>

// Local Network Settings.
char ssid[] = "m";  // your network SSID (name)
char pass[] = "mm......"; // your network password

//Set the pin numbers.
const byte potentiometerPin = A0;

int sensor1;
int sensor2;
int sensor3;
int sensor4;
int  pot1value; 
int pot2value;
int  pot3value; 
int  pot4value; 

// ThingSpeak Settings.
char thingSpeakAddress[] = "api.thingspeak.com";//The URL for the ThingSpeak API
String APIKey = "DUMKL7AOUZVP6TNW";             // enter your channel's Write API Key



// Initialize Wifi Client.
WiFiClient client;

void setup() {
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(A0,INPUT);
  //Start Serial for debugging on the Serial Monitor
  Serial.begin(115200);
  delay(100);

  //Display what SSID you are connecting to.
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  
  //Connect to an Access Point.
  WiFi.begin(ssid, pass);
  
  //Now we wait for the connetion to be established.
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // Print the SSID that you are connected with.
  Serial.println();
  Serial.print("You are now connected to SSID: ");
  Serial.println(WiFi.SSID());

}//close setup

void loop() {
   digitalWrite(D1,HIGH);
   delay(100);
   pot1value =analogRead(potentiometerPin);
    digitalWrite(D1,LOW);
    
  digitalWrite(D2,HIGH);
  delay(100);
   pot2value =analogRead(potentiometerPin);
  digitalWrite(D2,LOW);

  digitalWrite(D5,HIGH);
  delay(100);
   pot3value =analogRead(potentiometerPin);
  digitalWrite(D5,LOW);
  
  digitalWrite(D6,HIGH);
  delay(100);
   pot4value =analogRead(potentiometerPin);
  digitalWrite(D6,LOW);
  
if (pot1value>100)
{  sensor1= 0; }
else { sensor1 =1; }


if (pot2value>100)
{  sensor2= 0;}
else  {sensor2 =1;} 


if (pot3value>100)
{  sensor3= 0;}
else { sensor3 =1; } 


if (pot4value>100)
{  sensor4= 0; }
else  {sensor4 =1;} 


  //Convert the sensor data into String Obects.
  String Sensor1 = String(sensor1);
  String Sensor2 = String(sensor2);
  String Sensor3 = String(sensor3);
  String Sensor4 = String(sensor4);

  /*Concatenate the fields into a String Object
     which we can send as the message body.
  */
  String thingSpeakData = "field1=" +Sensor1 +"&field2=" + Sensor2 +"&field3=" + Sensor3+"&field4=" + Sensor1;


  /*** Update ThingSpeak ***/

  //Establish A connection with ThingSpeak.
  if (client.connect(thingSpeakAddress, 80)) {

    //The Message Start-Line (Method URI protocolVersion).
    client.println("POST /update HTTP/1.1");

    //Send the HTTP Header Fields.
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + APIKey);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(thingSpeakData.length());
    client.println(); //This empty line says "Header Fields are complete!"

    //Send the Message Body.
    client.print(thingSpeakData);

    //Let us know if the connection to ThingSpeak was established.
    if (client.connected()) {
      Serial.println("Connecting to ThingSpeak...");
      Serial.println();
    }
  }

  //Display info to the Serial Monitor for troubleshooting.
  Serial.print("Pot1value ");
  Serial.println(pot1value);
   Serial.print("Pot2value ");
  Serial.println(pot2value);
   Serial.print("Pot3value ");
  Serial.println(pot3value);
   Serial.print("Pot4value ");
  Serial.println(pot4value);
  Serial.print("sensor1= ");
  Serial.println(sensor1);
   Serial.print("sensor2= ");
  Serial.println(sensor2);
   Serial.print("sensor3= ");
  Serial.println(sensor3);
   Serial.print("sensor4= ");
  Serial.println(sensor4);
   Serial.println();
    Serial.println();
  
  //Wait between readings.
  delay(5000);

}//Close Loop
