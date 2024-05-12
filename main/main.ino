#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <PZEM004Tv30.h>
#include "PzemModel.h"

// Replace these with your WiFi network settings
const char* ssid = "X 1phone"; //replace this with your WiFi network name
const char* password = "314159265359"; //replace this with your WiFi network password
const char* serverName = "http://172.20.10.11:5000/api/pzem";

// 速度
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

//設定TX,RX 接腳
PZEM004Tv30 pzem(13, 15);

void setup()
{
  delay(1000);
  Serial.begin(115200);
  Serial.print(".....");
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());  
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      PzemModel *model = GetPzemData();
      //model->Voltage = 111.2;
      PostData(model);
      delete model;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}


PzemModel * GetPzemData(){
  PzemModel* result = new  PzemModel();
    
    float voltage = pzem.voltage();
    if( !isnan(voltage) ){
      result->Voltage =voltage;        
    } else {
      Serial.println("Error reading voltage");
    }

    float current = pzem.current();
    if( !isnan(current) ){
      result->Current =current;        
    } else {
      Serial.println("Error reading current");
    }
    
    float power = pzem.power();
    if( !isnan(power) ){
      result->Power =power;
    } else {
      Serial.println("Error reading power");
    }

    float energy = pzem.energy();
    if( !isnan(energy) ){
      result->Energy =energy;
    } else {
      Serial.println("Error reading energy");
    }

    float frequency = pzem.frequency();
    if( !isnan(frequency) ){
      result->Frequency =frequency;
    } else {
      Serial.println("Error reading frequency");
    }

    float pf = pzem.pf();
    if( !isnan(pf) ){
      result->PF =pf;
    } else {
      Serial.println("Error reading power factor");
    }

  return result ;
}

void PostData(PzemModel * model){
  WiFiClient client;
  HTTPClient http;      
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);

  //Head
  http.addHeader("Content-Type", "application/json");
  //Body 
  int httpResponseCode = http.POST(model->ToJson());

  //Print Response 
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);

  // Free resources
  http.end();

}
