#include <SoftwareSerial.h>
#include  <LiquidCrystal.h>

#define PIN_LED 13
#define PIN_PULSADOR 10
SoftwareSerial ESPserial(2, 11); // RX | TX
LiquidCrystal lcd(7,6,5,4,3,8);
int estado_anterior;
int selbus = 39;

void setup() 
{
    Serial.begin(115200);     // communication with the host computer
    //while (!Serial)   { ; }
 
    // Start the software serial for communication with the ESP8266
    ESPserial.begin(115200);  
    // INDICAMOS QUE TENEMOS CONECTADA UNA PANTALLA DE 16X2
    lcd.begin(16, 2);
    // MOVER EL CURSOR A LA PRIMERA POSICION DE LA PANTALLA (0, 0)
    lcd.home();
    lcd.print("BusArrivingProject");
    // MOVER EL CURSOR A LA SEGUNDA LINEA (1) PRIMERA COLUMNA (0)
    lcd.setCursor ( 0, 1 );
    // IMPRIMIR OTRA CADENA EN ESTA POSICION
    lcd.print("mcochi");
    // ESPERAR UN SEGUNDO
  delay(1000);
    Serial.println("");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("Ready");
    Serial.println("");   
    pinMode(PIN_PULSADOR, INPUT_PULLUP);
    pinMode(PIN_LED, OUTPUT); 
    estado_anterior = digitalRead(10);
}
 
void loop() 
{
    String payload;
    // listen for communication from the ESP8266 and then write it to the serial monitor
    while ( ESPserial.available() > 0 )   { 
      lcd.clear(); 
      //Serial.write( ESPserial.read() );
      char c = ESPserial.read();
      payload +=c;
    }
    
    //delay(3000);
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {  ESPserial.write( Serial.read() );  }

    int sensorVal = digitalRead(PIN_PULSADOR);
//    Serial.println(sensorVal);
    if (sensorVal != estado_anterior) {
      if (sensorVal == HIGH) {
        digitalWrite(PIN_LED, LOW);
      }
      else {
        digitalWrite(PIN_LED, HIGH);
        ESPserial.write("CI");
        if (selbus == 39) {
          selbus = 50;
      } else {
          selbus = 39;
    }
        
        //Serial.println("CI");
      }
    }
    if (selbus == 39) {
    lcd.home();
    lcd.print("El 39 llega en");
    } else {
        lcd.home();
        lcd.print("El CI2 llega en");
    }
    lcd.setCursor(0,1);
    lcd.print(payload);
    if (payload[0] == '5') {
     tone(12, 440,100);
    }
    estado_anterior = sensorVal;
    
}
