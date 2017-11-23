/*
   NOTE :

    in order to upload codes properly,
    should decouple pin D2 with pin RESET

    in order that ESP.deepSleep() works properly,
    should connect pin D2 to pin RESET

    door open control : https://nocky-183812.appspot.com/set-open

    esp8266 sleep mode reference :
    1. ESP8266 Github : https://github.com/esp8266/Arduino
    2. https://m.blog.naver.com/PostView.nhn?blogId=twophase&logNo=221081584842&categoryNo=36&proxyReferer=&proxyReferer=https%3A%2F%2Fwww.google.co.kr%2F

    when entering into deep sleep mode, current measured to be 4 mA
    for official measurements and details, see : https://github.com/esp8266/Arduino/issues/460
*/

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

/* Communication */
#define BAUD 115200
const char* WiFi_ID = "wonkong";
const char* WiFi_PW = "23942102";
const char* IS_OPEN = "http://nocky-183812.appspot.com/open";
const char* GET_INTERVAL = "http://nocky-183812.appspot.com/interval";
uint32_t SLEEP_INTERVAL = 5;
uint32_t SECONDS = 1000000;

/* Servo */
Servo LOCK;
#define SERVO_PIN 0
#define PUSH 10
#define PULL 170

/* Visualization */
#define VISUALIZE true

/* Initialization */
void setup() {
  if (VISUALIZE) {
    Serial.begin(BAUD);
    delay(10);

    // Connect to WiFi network
    Serial.println(); Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WiFi_ID);

    WiFi.begin(WiFi_ID, WiFi_PW);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("WIFI IP : "); Serial.print(WiFi.localIP());
    Serial.println("");
  }
  else {
    WiFi.begin(WiFi_ID, WiFi_PW);
    while (WiFi.status() != WL_CONNECTED) delay(500);
  }
}

/* Main Loop */
void loop() {
  check("is_open");
  SLEEP_INTERVAL = check("interval");

  if (SLEEP_INTERVAL > 0) {
    if (VISUALIZE) {
      Serial.print("sleep mode for ");
      Serial.print(SLEEP_INTERVAL);
      Serial.println(" seconds");
    }
    ESP.deepSleep(SLEEP_INTERVAL * SECONDS);
  }
  else{
    if (VISUALIZE) Serial.println("no sleep");
  }
}

/* Door Open */
void doorOpen() {
  LOCK.attach(SERVO_PIN);
  delay(10);
  LOCK.write(PULL);
  delay(2000);
  LOCK.write(PUSH);
  delay(2000);
  LOCK.write(PULL);
  delay(2000);
  LOCK.detach();
  delay(10);
}

/* Check IS_OPEN If the door should be opened */
uint32_t check(const char* check_type) {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status


    if (check_type == "is_open") {
      HTTPClient http;  //Declare an object of class HTTPClient

      http.begin(IS_OPEN);  //Specify request destination
      int httpCode = http.GET(); //Send the request
      if (httpCode > 0) { //Check the returning code
        String payload = http.getString();   //Get the request response payload
        if (payload == "true") {
          if (VISUALIZE) Serial.println("door open");
          doorOpen();
        } //Print the response payload
        else {
          if (VISUALIZE) Serial.println("door close");
        }
        http.end();   //Close connection
        return (uint32_t) 0;
      }
      else {
        http.end();   //Close connection
        return (uint32_t) 0;
      }
    }

    else if (check_type == "interval") {
      HTTPClient http;  //Declare an object of class HTTPClient

      http.begin(GET_INTERVAL);  //Specify request destination
      int httpCode = http.GET(); //Send the request
      if (httpCode > 0) { //Check the returning code
        String payload = http.getString();   //Get the request response payload
        if (VISUALIZE) {
          Serial.print("interval :");
          Serial.println((uint32_t)payload.toInt());
        }
        http.end();   //Close connection
        return (uint32_t) payload.toInt();
      }
      else {
        http.end();   //Close connection
        return (uint32_t) 0;
      }
    }
    else {
      if (VISUALIZE) Serial.println("check type error");
      return (uint32_t) 0;
    }
  }
}
