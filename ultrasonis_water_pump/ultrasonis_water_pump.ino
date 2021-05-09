//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//    Advanced Water level Indicator                                        //
//    Made by IoTFever                                                      //
//    Contact iotfever1@gmail.com                                           //
//    All Project Website - IoTFever.tech                                   //
//    Contact IoTFever.blogspot.com                                         //
//    Project Website --- https://www.instructables.com/member/iotfever/    //
//    WiFi Scrolling Display --- https://youtu.be/bLIyVbeDaXk               //
//    Arduino LED Cube --- https://youtu.be/vYDEDb1dkn8                     //
//    Like, Share and Subscribe                                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "IoTFever";  //Change wifi ssid
const char* password = "7878787878";   // Change wifi password
const int trigPin = D0;   //Define pins
const int echoPin = D1;   //Define pins
// defines variables
long duration;
int distance;
 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 int LEDPin = D3;
String page = "";
double data; 
double temp;
void setup(void){
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
  delay(1000);
  
 pinMode(trigPin, OUTPUT);   // Sets the trigPin as an Output     
 pinMode(echoPin, INPUT);
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", [](){
    page = "<h3>Water Level Distance:</h3> <h1>"+String(data)+" Cm</14><head><META HTTP-EQUIV=\"refresh\" CONTENT=\"1\"></head>"; 
    server.send(200, "text/html", page);   
  });
  
    server.on("/TurnOnLED", [](){
    page = "<p><strong>Motor is ON</strong></p>";
  page +="<p><a href=\"TurnOnLED\"><button>Turn on Motor</button></a>&nbsp; <a href=\"TurnOffLED\"><button>Turn off motor</button></a></p>";
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, HIGH);
    delay(500);
  });
  server.on("/TurnOffLED", [](){
      page = "<p><strong>Motor is OFF</strong></p>";
  page +="<p><a href=\"TurnOnLED\"><button>Turn on Motor</button></a>&nbsp; <a href=\"TurnOffLED\"><button>Turn off Motor</button></a></p>";
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, LOW);
    delay(500); 
  });
  
  
  
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  data = distance;
  if(data <= 20){
    digitalWrite(LEDPin, LOW);
  }
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(100);
  server.handleClient();
}
