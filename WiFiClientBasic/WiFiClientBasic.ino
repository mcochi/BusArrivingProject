/*
    This sketch sends a string to a TCP server, and prints a one-line response.
    You must run a TCP server in your local network.
    For example, on Linux you can use this command: nc -v -l 3000
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "secrets.h"

const char* ssid     = STASSID;
const char* password = STAPSK;

//const char* host = "djxmmx.net";
//const uint16_t port = 17;

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
}


void loop() {
  Serial.print("connecting to ");
//  Serial.print(host);
//  Serial.print(':');
//  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

//  if (!client.connect()) {
//    Serial.println("connection failed");
//    Serial.println("wait 5 sec...");
//    delay(5000);
//    return;
//  }
  String server = "www.zaragoza.es";
  
  // This will send the request to the server
  //client.println("hello from ESP8266");
  if (client.connect(server,80)) {
    Serial.println("Conectado");
    client.print("GET /api/recurso/urbanismo-infraestructuras/transporte-urbano/poste/tuzsa-508?");
    client.println(" HTTP/1.0");
    client.println("Host: www.zaragoza.es");
      client.println("Content-Type: application/xml");
      client.println("Accept: application/json");
//    client.println("accept-encoding: gzip, deflate");
    client.println();
  } else {
    Serial.println("Connection Failed!!!");
  }

  while (client.available() == 0) {
    //Espero respuesta del servidor
  }
  
  String payload ="";
  if (client.available() > 0) {
    Serial.println("Respuesta del servidor");
      char c;
      while (client.available() > 0) {
        c = client.read();
        payload += c;
    } 
  }

  Serial.println("He leido la cadena" + payload);
  
//  //read back one line from server
//  Serial.println("receiving from remote server");
//  String line = client.readStringUntil('\r');
//  Serial.println(line);

  Serial.println("closing connection");
  client.stop();

  Serial.println("wait 5 sec...");
  delay(5000);
}
