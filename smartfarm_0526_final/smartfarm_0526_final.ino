#include <NTPClient.h> //보드설정 esp32 develkit v1. 오후3시51분  11월2일
// change next line to use with another board/shield
//#include <ESP8266WiFi.h>
#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char* ssid     = "G140_IoT_2.4G";
const char* password = "smart02_140@";
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
// Variables to save date and time
String formattedDate;
String formattedTime;
String formattedHour;
String dayStamp;
String timeStamp;
const int led = 26;
const int pump = 25;
const int fan = 27;
int pump_sw=0;
int Min;
int Sec;
int Hour;

void WiFi_Setup(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("."); 
   
    digitalWrite(pump,1); 
    digitalWrite(led,1);
    digitalWrite(fan,1);
   
   }
  
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 //digitalWrite(pump,0); 
  //  digitalWrite(led,0);
  // NTP
// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(32400);  
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
    pinMode(led, OUTPUT);
    pinMode(pump, OUTPUT);
    pinMode(fan, OUTPUT);
  WiFi_Setup();
  }

void timeControl(){
  while(!timeClient.update()) {
    timeClient.forceUpdate();
    break;
  }
  formattedTime = timeClient.getFormattedTime();
  Hour = timeClient.getHours();
  Min = timeClient.getMinutes();
  Sec = timeClient.getSeconds();

  }
void loop(){
  if (WiFi.status() != WL_CONNECTED){  
    Serial.println("wifi not connect");
    digitalWrite(pump,1); 
    digitalWrite(led,1);
    WiFi_Setup(); }
    
   Serial.println("wifi connect");
     timeClient.begin();
   timeClient.setTimeOffset(32400);  
    
 while(!timeClient.update()) {
    timeClient.forceUpdate();
    break;
  }
  formattedTime = timeClient.getFormattedTime();
  Hour = timeClient.getHours();
  Min = timeClient.getMinutes();
  Sec = timeClient.getSeconds();
    //digitalWrite(relay_uv,1);
    
  if (Hour>=6 && Hour<=18){
      digitalWrite(led,0);
      if (Min%35==0){
         if (Sec++<=20){
              digitalWrite(pump,0);
              digitalWrite(fan,0);
             }
              else {digitalWrite(pump,1); 
                    digitalWrite(fan,1); 
                   }
            }
    
          
    } 
    
   else {
         digitalWrite(pump,1); 
         digitalWrite(led,1);
         digitalWrite(fan,1);
        }
  }
