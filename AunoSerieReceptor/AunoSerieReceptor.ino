#include <SoftwareSerial.h>
#include  <LiquidCrystal.h>
SoftwareSerial ESPserial(2, 3); // RX | TX
LiquidCrystal lcd(7,6,5,4,3,8);
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
    // IMPRIMIR "Hola Mundo" EN LA PRIMERA LINEA
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
    lcd.print(payload);
    //delay(3000);
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {  ESPserial.write( Serial.read() );  }
    
}
