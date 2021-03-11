#include <AWS_IOT.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <stdio.h>
#include <stdlib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
//this is for esp32

AWS_IOT hornbill;

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionaly you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 28800, 28800);


char WIFI_SSID[]="SINGTEL-0ADF";
char WIFI_PASSWORD[]="0013474379";
char HOST_ADDRESS[]="a32ka2r8796cks-ats.iot.us-west-2.amazonaws.com";
char CLIENT_ID[]= "esp32";
char TOPIC_NAME[]= "esp/action";
const int LED=16;

int status = WL_IDLE_STATUS;
int tick=0,msgCount=0,msgReceived = 0;
char payload[512];
char rcvdPayload[512];
String info;



void setup() {
    Serial.begin(115200);
    delay(2000);
    pinMode(LED, OUTPUT);

    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(WIFI_SSID);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        // wait 5 seconds for connection:
        delay(5000);
    }

    Serial.println("Connected to wifi");

    if(hornbill.connect(HOST_ADDRESS,CLIENT_ID)== 0)
    {
        Serial.println("Connected to AWS");
        delay(1000);

        
    }
    else
    {
        Serial.println("AWS connection failed, Check the HOST Address");
        while(1);
    }

    delay(2000);

}

void loop() {
  timeClient.update();
  info="";
  

      DynamicJsonDocument doc(2048);
      double temp=rand()%60+1;
      doc["temperature"] = temp;
      doc["timestamp"] = timeClient.getFormattedDate();
      
       
      serializeJson(doc, info);
       //Serial.print(info);
      //output will be something like { "temperature" : 53, "timestamp" : "2021-03-11T21:08:32Z"  }
        
       //info.c_str() is to convert String data type to const char
       sprintf(payload,info.c_str());
       
        if(hornbill.publish(TOPIC_NAME,payload) == 0)
        {        
            Serial.print("Publish Message:");
            Serial.println(payload);
            delay(10000);
        }
        else
        {
            Serial.println("Publish failed");
        }
    
}
