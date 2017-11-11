#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PW";
Servo lock;

void setup() {
  Serial.begin(115200);
  delay(10);
  
  lock.attach(0);
  lock.write(30);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");


  // Print the IP address
  Serial.print("WIFI IP : ");
  Serial.print(WiFi.localIP());
  Serial.println("");

}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient
    http.begin("http://nocky-183812.appspot.com/open");  //Specify request destination
    
    int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      if (payload == "true") {
        Serial.println("door open");
        lock.write(70);
        delay(1500);
        lock.write(30);} //Print the response payload
    }

    http.end();   //Close connection
  }

  delay(5000);    //Send a request every X seconds
}

