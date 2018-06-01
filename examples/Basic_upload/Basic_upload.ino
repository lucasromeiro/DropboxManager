/*
DropboxManager ESP8266

Copyright (c) 2018 Lucas Romeiro

Author: Lucas Romeiro
Contact: lucas_romeiro@hotmail.com

Example created to understand how file upload works.

To see the license, terms and explanations, open the library!

*/

#include <ESP8266WiFi.h>
#include <DropboxManager.h>



const char* ssid = "...........";
const char* password = "...........";


DropboxMan myDrop;


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  SPIFFS.begin();
  File file = SPIFFS.open("/test.txt","a");
  if(!file){ 
    Serial.println("Erro on create file.");
  } else {
    file.println("Test... From ESP8266!");
  }
  file.close();
  SPIFFS.end();

}

void loop() {
  myDrop.begin("<your token here>");
  if(myDrop.fileUpload("/test.txt","/math/test.txt",1)){//Sending a test.txt file to /math/test.txt
    Serial.println("File Sent!");
  }else{
    Serial.println("ERRO!");
  }
    
  while(true){
    yield();
    ESP.wdtFeed();
  }
}
