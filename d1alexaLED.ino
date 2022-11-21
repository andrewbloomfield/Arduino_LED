#include <ESP8266WiFi.h>
#include <Espalexa.h>

boolean connectWifi();

void espled(uint8_t state);

const char* ssid = "ssid";          //change these 2 lines for your wifi
const char* password = "password";

boolean wifiConnected = false;

Espalexa espalexa;

EspalexaDevice* device1; 

void setup() {

  pinMode(5, OUTPUT);
  
  Serial.begin(115200);
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    
    // Define your devices here. 
    espalexa.addDevice("Arduino LED", espled);


    espalexa.begin();
    
  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }

}

void loop() {

   espalexa.loop();
   delay(1);

}


void espled(uint8_t state){
  Serial.print("some text");
  Serial.println(state);

  if (state > 0){
    analogWrite(5,state);   
  }
  else{
    digitalWrite(5,LOW);
  }
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
