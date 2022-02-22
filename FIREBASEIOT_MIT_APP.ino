#include "FirebaseESP8266.h"  
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "fir-28416.firebaseio.com"
#define FIREBASE_AUTH "wKGp39kJkvG0CuGLuFvnEpD2wRMyFkVmge6TKpeh"
#define WIFI_SSID "LMT" 
#define WIFI_PASSWORD "456789123ttt" 

#define led  2       // d4
#define led1 5       // d1
#define led2 4       // d2
#define led3 0       // d3

#define inPin  14     //d5 
#define inPin1 12     //d6
#define inPin2 13     //d7
#define inPin3 15     //d8

FirebaseData ledData;
FirebaseData ledData1;
FirebaseData ledData2;
FirebaseData ledData3;
FirebaseData lm35Data;

unsigned long tg;
void setup()
{
  Serial.begin(9600);
  tg = millis();
  pinMode(inPin,INPUT);
  pinMode(inPin1,INPUT);
  pinMode(inPin2,INPUT);
  pinMode(inPin3,INPUT);
  
  pinMode(led,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);

  digitalWrite(led,LOW); 
  digitalWrite(led1,LOW); 
  digitalWrite(led2,LOW); 
  digitalWrite(led3,LOW); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}


void nut_nhan_mit()
{  
  if (Firebase.getString(ledData, "/FirebaseIOT/led"))
    {
      Serial.println(ledData.stringData());
      if (ledData.stringData() =="1")   {digitalWrite(led, HIGH);}
      else if (ledData.stringData() == "0")  {digitalWrite(led, LOW);}
    }
  
  if (Firebase.getString(ledData1, "/FirebaseIOT/led1"))
  {
    Serial.println(ledData1.stringData());
    if (ledData1.stringData() =="1")  {digitalWrite(led1, HIGH);}
    else if (ledData1.stringData() == "0") {digitalWrite(led1, LOW);}
  }

  if (Firebase.getString(ledData2, "/FirebaseIOT/led2"))
  {
    Serial.println(ledData2.stringData());
    if (ledData2.stringData() =="1") {digitalWrite(led2, HIGH);}
    else if (ledData2.stringData() == "0") {digitalWrite(led2, LOW);}
  }

  if (Firebase.getString(ledData3, "/FirebaseIOT/led3"))
  {
    Serial.println(ledData3.stringData());
    if (ledData3.stringData() =="1") {digitalWrite(led3, HIGH);}
    else if (ledData3.stringData() == "0") {digitalWrite(led3, LOW);}
  }
  delay(100);
}

boolean oldswitchstate = LOW;
boolean newswitchstate = LOW;
boolean ledstatus = LOW;

boolean oldswitchstate1 = LOW;
boolean newswitchstate1 = LOW;
boolean ledstatus1 = LOW;

boolean oldswitchstate2 = LOW;
boolean newswitchstate2 = LOW;
boolean ledstatus2 = LOW;

boolean oldswitchstate3 = LOW;
boolean newswitchstate3 = LOW;
boolean ledstatus3 = LOW;

void nut_nhan_vl()
{

    newswitchstate = digitalRead(inPin);

    if ( newswitchstate != oldswitchstate )
    {
   if ( (unsigned long) (millis() - tg) > 1000)
   {
       if ( newswitchstate == HIGH )
       {
           if ( ledstatus == LOW )
           { 
            digitalWrite(led, HIGH);
            ledstatus = HIGH;
            Firebase.setString(ledData, "/FirebaseIOT/led", String(1)) ;
           }
           else
           { 
            digitalWrite(led, LOW);
            ledstatus = LOW; 
            Firebase.setString(ledData, "/FirebaseIOT/led", String(0)) ; 
           }
       }
       oldswitchstate = newswitchstate;
    tg = millis();
    Serial.print("thoi gian tre:");
    Serial.println(tg/1000);  
    }
 
   }


    newswitchstate1 = digitalRead(inPin1);
    if ( newswitchstate1 != oldswitchstate1 )
    {
       if ( newswitchstate1 == HIGH )
       {
           if ( ledstatus1 == LOW )
           { 
            digitalWrite(led1, HIGH);
            ledstatus1 = HIGH;
            Firebase.setString(ledData1, "/FirebaseIOT/led1", String(1)) ;
           }
           else
           { 
            digitalWrite(led1, LOW);
            ledstatus1 = LOW; 
            Firebase.setString(ledData1, "/FirebaseIOT/led1", String(0)) ; 
           }
       }
       oldswitchstate1 = newswitchstate1;
    }   


    newswitchstate2 = digitalRead(inPin2);
    if ( newswitchstate2 != oldswitchstate2 )
    {
       if ( newswitchstate2 == HIGH )
       {
           if ( ledstatus2 == LOW )
           { 
            digitalWrite(led2, HIGH);
            ledstatus2 = HIGH;
            Firebase.setString(ledData2, "/FirebaseIOT/led2", String(1)) ;
           }
           else
           { 
            digitalWrite(led2, LOW);
            ledstatus2 = LOW; 
            Firebase.setString(ledData2, "/FirebaseIOT/led2", String(0)) ; 
           }
       }
       oldswitchstate2 = newswitchstate2;
    } 


    newswitchstate3 = digitalRead(inPin3);
    if ( newswitchstate3 != oldswitchstate3 )
    {
       if ( newswitchstate3 == HIGH )
       {
           if ( ledstatus3 == LOW )
           { 
            digitalWrite(led3, HIGH);
            ledstatus3 = HIGH;
            Firebase.setString(ledData3, "/FirebaseIOT/led3", String(1)) ;
           }
           else
           { 
            digitalWrite(led3, LOW);
            ledstatus3 = LOW; 
            Firebase.setString(ledData3, "/FirebaseIOT/led3", String(0)) ; 
           }
       }
       oldswitchstate3 = newswitchstate3;
    } 

} 

void lm35()
{
  float nhietdo = (analogRead(A0) * 3.3/1023)*100;
  Serial.println (nhietdo);
  Firebase.setFloat(lm35Data, "/FirebaseIOT/temperature", nhietdo) ; 
  delay(1000);
}


void loop() 
{
  nut_nhan_mit();
  nut_nhan_vl();
  lm35();
}
