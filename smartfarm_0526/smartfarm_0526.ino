#include <NTPClient.h> //보드설정 esp32 develkit v1. 오후3시51분  11월2일
// change next line to use with another board/shield
//#include <ESP8266WiFi.h>
#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char* ssid = "G140_IoT_2.4G";
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

const int led=26;
const int pump=25;
const int fan=27;
int Min;
int Sec;
int Hour;

void WiFi_Setup(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
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
  pinMode(fan, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(115200);
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
   
 while(!timeClient.update()) {
    timeClient.forceUpdate();
    break;
  }
   Serial.println("void loop WiFi connected.");
 // formattedTime = timeClient.getFormattedTime();
  Hour = timeClient.getHours();
  Min = timeClient.getMinutes();
  Sec = timeClient.getSeconds();
  Serial.print("Hour = "); 
  Serial.print(Hour);  Serial.print("    Min = "); 
  Serial.print(Min); Serial.print("    Sec = "); 
  Serial.print(Sec); delay(1000);

if (Hour>=6 && Hour<=22) {
      digitalWrite(led, 0);
      if (Min%35==0) {
          if (Sec++<20) {
              digitalWrite(pump,0);
              digitalWrite(fan,0);
                        }
          }
  else {
      digitalWrite(pump,1);
      digitalWrite(led,1);
      digitalWrite(fan,1);
      }
  }
