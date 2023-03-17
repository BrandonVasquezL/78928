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
#include "DHTesp.h"
#define DHTpin 15
DHTesp dht;

const char* ssid="paila";
const char* password="278brando";

AsyncWebServer server(80);


void setup(){
Serial.begin(115200);
pinMode(2, OUTPUT);
Serial.println();
conectarse();

dht.setup(DHTpin, DHTesp::DHT11);

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

server.on("/temp",HTTP_GET,[](AsyncWebServerRequest *t){

  t->send(200,"text/html", "<h1>Temperatura"+ temperatura()+"</h1>");
});

server.on("/hum",HTTP_GET,[](AsyncWebServerRequest *h){

  h->send(200,"text/html", "<h1>humedad"+ humedad()+"</h1>");
});
}
void loop(){
  delay(dht.getMinimumSamplingPeriod());


  float humedad =  dht.getHumidity();

  float temperatura = dht.getTemperature();                            


  if (isnan(humedad) || isnan(temperatura)) {

    Serial.println("No se pudo leer sensor DHT!");

    return;

  }
  Serial.print( dht.getStatusString() );

  Serial.print("\t");

  Serial.print(humedad, 1);

  Serial.print("\t\t");

  Serial.print(temperatura, 1);

  Serial.print("\t\t");

  Serial.print( dht.toFahrenheit(temperatura), 1);

  Serial.print("\t\t");

  Serial.print( dht.computeHeatIndex(temperatura, humedad, false), 1);

  Serial.print("\t\t");

  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperatura), humedad, true), 1);

  delay(2000);
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

String temperatura(){
  float temperaturas = dht.getTemperature();
  String valor = "";
   valor.concat(temperaturas);
   return valor;
}

String humedad(){
  float humedad =  dht.getHumidity();
  String valor2 = "";
   valor2.concat(humedad);
   return valor2;
}