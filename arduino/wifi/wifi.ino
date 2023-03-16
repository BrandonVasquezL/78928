#include <WiFi.h>
#include "ESPAsyncWebServer.h"

const char* ssid="Totalplay-DD9F";
const char*password="DD9FBFA2HZfk4G2k";

AsyncWebServer server(80);

void setup()
{
Serial.begin(115200);
conectarse();
server.on("/", HTTP_GET, [](AsyncWebServerRequest * request){
  int numParametros = request->params();
  Serial.print(numParametros);
  if(numParamentros == 0)
  request -> send(200, "text/html", "<h1>hola mundo</h1>");
  else{
    AsyncWebServer xp= request -> getParam(0);
    String html= "<h1>Hola "+ p->value()+"desde ESP32 </h1>";
    request-> send(200,"text/html",hmtl);
  }
});
server.on("/adios",HTTP.GET[](AsyncWebServerRequest * r){
  r->send(200,"text/html", "<h1>adios</h1>");
});

delay(10);

//se inicia la conexion
Serial.println();
Serial.println();
Serial.print("Connecting to");
Serial.println(ssid);

WiFi.begin(ssid,password);
//se verifica
while(WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
}
//lograda la conexion se muestra la informacion
Serial.print("");
Serial.print("WiFi connected");
Serial.print("IP address:");
Serial.print(WiFi.localIP());
}

void loop(){

}