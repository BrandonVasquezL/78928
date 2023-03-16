#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebSrv.h>

const char* ssid="paila";
const char* password="278brando";

AsyncWebServer server(80);


void setup(){
Serial.begin(115200);
pinMode(2, OUTPUT);
conectarse();
server.on("/", HTTP_GET, [](AsyncWebServerRequest * request){
  digitalWrite(2, HIGH);
  int numParametros = request->params();
  Serial.print(numParametros);
  if(numParametros == 0)
  request -> send(200, "text/html", "<h1>hola mundo</h1>");
  else{
    AsyncWebParameter *p= request -> getParam(0);
    String html= "<h1>Hola "+ p->value()+"desde ESP32 </h1>";
    request-> send(200,"text/html",html);
  }
});
server.on("/adios",HTTP_GET,[](AsyncWebServerRequest *r){
  digitalWrite(2, LOW);
  r->send(200,"text/html", "<h1>adios</h1>");
});
}
void loop(){
}
  void conectarse(){
    Serial.print("conectado"); Serial.print(ssid);
    WiFi.begin(ssid,password);
    while(WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
 }
 Serial.print(WiFi.localIP());
}
