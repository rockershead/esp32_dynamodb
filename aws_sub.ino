#include <AWS_IOT.h>
#include <WiFi.h>
//this is for esp32

AWS_IOT hornbill;


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

void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
    strncpy(rcvdPayload,payLoad,payloadLen);
    rcvdPayload[payloadLen] = 0;
    msgReceived = 1;
}



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

        if(0==hornbill.subscribe(TOPIC_NAME,mySubCallBackHandler))
        {
            Serial.println("Subscribe Successfull");
        }
        else
        {
            Serial.println("Subscribe Failed, Check the Thing Name and Certificates");
            while(1);
        }
    }
    else
    {
        Serial.println("AWS connection failed, Check the HOST Address");
        while(1);
    }

    delay(2000);

}

void loop() {

    if(msgReceived == 1)
    {
        msgReceived = 0;
        Serial.print("Received Message:");
        Serial.println(rcvdPayload);

        if(String(rcvdPayload)=="ON")
        { Serial.println("ON");
          digitalWrite(LED,HIGH);}
        if(String(rcvdPayload)=="OFF")
        {digitalWrite(LED,LOW);}
        
    }
    
}
