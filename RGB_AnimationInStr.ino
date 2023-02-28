#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>

#include "animatiocnDecoder.hpp" // arquivo com a função setAnimation()
#include"./html.h"
//#include "./infrastructure.h"
#include"./js.h"
#include"./style.h"

ESP8266WebServer server(80); // cria uma instância do servidor web


#define PIN 48
#define LED_COUNT 1
Adafruit_NeoPixel strip =
    Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRBW + NEO_KHZ800);

#define PINLEDR 12
#define PINLEDG 13
#define PINLEDB 14

int pinR = 12;
int pinG = 13;
int pinB = 14;

int R[] = {255, 0, 0, 23, 56, 217}; // reD
int G[] = {255, 0, 255, 123, 156, 187}; // 
int B[] = {25, 158, 100, 0, 156, 87}; // 

#define PIN 4
#define NUMPIXELS 4
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//ESP8266WebServer server(80);
String corRGB ="";


const char* animation =
"R20B0G0F100,R0B0G20F100,R0B20G0F100";

const char* animationweb = "";


void handleAnimation() {
  animationweb = server.arg("animation").c_str();
  Serial.println("Animação recebida:");
  Serial.println(animationweb);
  setAnimation(animationweb, strlen(animationweb));
  server.send(200, "text/html", "");
}



void handleGerador() {
    const char* animationweb = server.arg("animation").c_str();
  Serial.println(animationweb);
  setAnimation(animationweb, strlen(animationweb));
  server.send(200, "text/html", gerador);
}

void handleIndex() {                           // send HTML to the page
    Serial.println("GET /");
    server.send(200, "text/html", postForms);  // check HTML.h file
}

void handleStop() {                           // send HTML to the page
    stopAnimation();
    Serial.println("GET /stop");
    server.send(200, "text/html", "");  // check HTML.h file
}

void handlePlay() {                           // send HTML to the page
    Serial.println("GET /play");
    if(strlen(animationweb) > 2){
    setAnimation(animationweb, strlen(animationweb));
    }else{
      setAnimation(animation, strlen(animation));
    }
    
    server.send(200, "text/html", "");  // check HTML.h file
}

void handleRestart() {                           // send HTML to the page
    ESP.restart();
    Serial.println("GET /restart");
    server.send(200, "text/html", "");  // check HTML.h file
}

void handleStyle() {                           // send HTML to the page
    Serial.println("GET /style.css");
    server.send(200, "text/css", style);  // check HTML.h file
}
void handlejs() {                           // send HTML to the page
    Serial.println("GET /js");
    server.send(200, "application/javascript", js);  // check HTML.h file
}

void handleGetParam() {
 if (server.hasArg("cor")) {
   stopAnimation();
    String corRGB = server.arg("cor");
    String r = corRGB.substring(4,corRGB.indexOf(','));
    corRGB = corRGB.substring(corRGB.indexOf(',')+1);
    String g = corRGB.substring(0,corRGB.indexOf(','));
    corRGB = corRGB.substring(corRGB.indexOf(',')+1);
    String b = corRGB.substring(0,corRGB.length()-1);
    pixels.setPixelColor(0,pixels.Color(r.toInt(),g.toInt(),b.toInt()));
    pixels.show();

    analogWrite(pinR, r.toInt());
    analogWrite(pinG, g.toInt());
    analogWrite(pinB, b.toInt());

    Serial.print("r: ");
    Serial.println(r.toInt());
    Serial.print("g: ");
    Serial.println(g.toInt());    
    Serial.print("b: ");
    Serial.println(b.toInt());
 }

}   

void handleconfig() { 
 if (server.hasArg("set")) {
   //Definir qual Gpio é cada cor
    pinR = server.arg("pinR").toInt();
    pinG = server.arg("pinG").toInt();
    pinB = server.arg("pinB").toInt();

    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);  
    
 }
    server.send(200, "text/html", configLumee);
    Serial.println("GET /config");
}   


void setup() {
  Serial.begin(115200);
    WiFiManager wifiManager;
  wifiManager.autoConnect("AP-NAME", "AP-PASSWORD"); // conecta ao WiFi

  server.on("/animation", handleAnimation); // cria um endpoint para receber animações
  server.on("/gerador", handleGerador); // cria um endpoint para receber animações
  server.on("/", handleIndex);
  server.on("/style.css", handleStyle);
  server.on("/js", handlejs);
  server.on("/config", handleconfig);
  server.on("/cor", handleGetParam);
  server.on("/stop", handleStop);
  server.on("/play", handlePlay);
  server.on("/restart", handleRestart);
  server.begin(); // inicia o servidor web

    #ifdef ESP8266
    analogWriteFreq(8000);
    #endif
    pinMode(PINLEDR, OUTPUT);
    pinMode(PINLEDG, OUTPUT);
    pinMode(PINLEDB, OUTPUT);
    

    // while (!Serial) {
    // }
    delay(1000);
    Serial.println("Start");
    strip.begin();
    delay(50);
   
    setHandleLed([](uint8_t R, uint8_t G, uint8_t B) {
        analogWrite(PINLEDR,R);
        analogWrite(PINLEDG,G);
        analogWrite(PINLEDB,B);
        strip.setPixelColor(0, strip.Color(R, G, B, 100));
        strip.show();
    });
    setAnimation(animation, strlen(animation));


}



uint32_t lastTime = millis();

void loop() { 
  loopAnimation();
   if (lastTime != 0 && (millis() - lastTime) > 10000) {
        lastTime = 0;
        setStaticColor(255, 0, 255);
    }
  server.handleClient(); // lida com solicitações de clientes
    }



