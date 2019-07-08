/*
    This sketch sends a string to a TCP server, and prints a one-line response.
    You must run a TCP server in your local network.
    For example, on Linux you can use this command: nc -v -l 3000
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>
#include "secrets.h"

const char* ssid     = STASSID;
const char* password = STAPSK;
static String timetoarrive;


//const char* host = "djxmmx.net";
//const uint16_t port = 17;

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  //Serial.println();
  //Serial.println();
  //Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    //Serial.print(".");
    delay(500);
  }

  //Serial.println("");
  //Serial.println("WiFi connected");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());

  delay(500);
}


void loop() {
  //Serial.print("connecting to ");
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  String server = "www.zaragoza.es";
  // This will send the request to the server
  if (client.connect(server,80)) {
    //Serial.println("Conectado");
    client.print("GET /api/recurso/urbanismo-infraestructuras/transporte-urbano/poste/tuzsa-508?");
    client.println(" HTTP/1.0");
    client.println("Host: www.zaragoza.es");
    client.println("Content-Type: application/json");
    client.println("Accept: application/json");
    client.println();
  } else {
    //Serial.println("Connection Failed!!!");
  }

  while (client.available() == 0) {
    //Espero respuesta del servidor
    delay(1000);
  }
  
  String payload ="";
  if (client.available() > 0) {
    //Serial.println("Respuesta del servidor");
      char c;
      while (client.available() > 0) {
        c = client.read();
        payload += c;
    } 
  }
  //Serial.print("He leido la cadena");
  //Serial.println(payload);
  //Serial.println("@marcos: el primer caracter que busco está en la posición");
  //Serial.println(payload.indexOf("{"));
  //Serial.println("@marcos2:payload real");
  //Serial.println(payload.substring(payload.indexOf("{")));

//  JSON PROCESS
  if (payload.substring(payload.indexOf("{")).indexOf("error") < 0) { 
    const size_t capacity = 2*JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(7) + 460;
    DynamicJsonDocument doc(capacity);
    String payloadreal = payload.substring(payload.indexOf("{"));
    char json[2000];
    payloadreal.toCharArray(json,2000);
    //Serial.println("@marcos3:Json Content");
    //Serial.println(json);  
    //Serial.println(json);
  
    deserializeJson(doc, json);
    
    const char* id = doc["id"]; // "tuzsa-508"
    const char* title = doc["title"]; // "(508) IGNACIO ZAPATA/RUSTE Líneas: 50, N1, 39"
    const char* lastUpdated = doc["lastUpdated"]; // "2019-07-06T12:11:41Z"
    
    const char* geometry_type = doc["geometry"]["type"]; // "Point"
    
    float geometry_coordinates_0 = doc["geometry"]["coordinates"][0]; // 678373.18
    float geometry_coordinates_1 = doc["geometry"]["coordinates"][1]; // 4614646.32
    
    const char* link = doc["link"]; // "http://www.urbanosdezaragoza.es/frm_esquemaparadatime.php?poste=508"
    const char* icon = doc["icon"]; // "http://www.zaragoza.es/contenidos/iconos/bus.png"
    
    JsonObject destinos_0 = doc["destinos"][0];
    String destinos_0_linea = destinos_0["linea"]; // "39"
    const char* destinos_0_destino = destinos_0["destino"]; // "PINARES DE VENECIA."
    String destinos_0_primero = destinos_0["primero"]; // "5 minutos."
    const char* destinos_0_segundo = destinos_0["segundo"]; // "19 minutos."
    
    JsonObject destinos_1 = doc["destinos"][1];
    String destinos_1_linea = destinos_1["linea"]; // "50"
    const char* destinos_1_destino = destinos_1["destino"]; // "SAN GREGORIO."
    String destinos_1_primero = destinos_1["primero"]; // "23 minutos."
    const char* destinos_1_segundo = destinos_1["segundo"]; // "53 minutos."
  
    if (destinos_0_linea.equals("39")) {
      if (destinos_0_primero.equals("\0") or destinos_0_primero.equals("null")) {
        //Serial.print("El próximo 39 llega en ");
        //Serial.println(timetoarrive);
      } else {
        //Serial.print("El próximo 39 llega en ");
        //Serial.println(destinos_0_primero);
        timetoarrive = destinos_0_primero;
      } 
    } else {
      if (destinos_1_primero.equals("\0") or destinos_1_primero.equals("null")) {
        //Serial.print("El próximo 39 llega en ");
        //Serial.println(timetoarrive);
      } else {
        //Serial.print("El próximo 39 llega en ");
        //Serial.println(destinos_1_primero);
        timetoarrive = destinos_1_primero;
      } 
    }
   } else {
      //Serial.println("Error API Request");
      //Serial.print("El próximo 39 llega en ");
      //Serial.println(timetoarrive);
    }
  //Serial.write("@MARCOS:PRUEBA");
  Serial.println(timetoarrive);
  client.stop();

  //Serial.println("wait 5 sec...");
  delay(5000);
}
