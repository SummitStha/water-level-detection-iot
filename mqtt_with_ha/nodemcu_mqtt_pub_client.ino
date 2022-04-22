#This program is for ESP8266 devices, particularly is made for NodeMCU. Its main function is to connect to a mqtt server, measure the water level in water tank with ultarsonic sensor, and publish the sensor data to mqtt subscribers.
#This Nodemcu setup used in collaboration with Home Assistant (HA), where mqtt server is running. The presentation, analysis, scheduling of the water tank motor is done on the HA side.

#include <ESP8266WiFi.h>
#include <PubSubClient.h>


// define Ultrasonic sensor pins numbers
const int tank_trigPin = 5;  //D1
const int tank_echoPin = 4;  //D2

// defines variables
int tank_distance,one_distance;
int fill = 50;
int time_to_fill = 1;


//
const int one_trgPin =
const int one_echoPin =

// Wifi configuration - Put your credentials here
const char* ssid = "******";
const char* password = "******";

// MQTT Configuration - fill with the credentials
// if you have a hostname set for the MQTT server, you can use it here
const char *serverHostname = "<HA IP here>";
const char* mqttUser = "****";
const char* mqttPassword = "****";
// otherwise you can use an IP address like this
//const IPAddress serverIPAddress(192, 168, 0, 11);
// the topic we want to use
const char *topic = "test/message";

WiFiClient espClient;
PubSubClient client(espClient);

// connect to wifi
void connectWifi() {
  delay(10);
  // Connecting to a WiFi network
  Serial.printf("\nConnecting to %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected on IP address ");
  Serial.println(WiFi.localIP());
}

// connect to MQTT server
void connectMQTT() {
  // Wait until we're connected
  while (!client.connected()) {
    // Create a random client ID
    String clientId = "ESP8266-";
    clientId += String(random(0xffff), HEX);
    Serial.printf("MQTT connecting as client %s...\n", clientId.c_str());
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqttUser, mqttPassword)) {
      Serial.println("MQTT connected");
      // Once connected, publish an announcement...
      //client.publish(topic, "hello from ESP8266");
    } else {
      Serial.printf("MQTT failed, state %s, retrying...\n", client.state());
      // Wait before retrying
      delay(2500);
    }
  }
}

float measure(int trigPin,int echopin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  int distance= duration*0.034/2;
  return distance;
}



void operation_tank()
{
//Custom calculation for fill, distance,time_to_fill is done on the basis of the size of the water tank, real time calculation to fill,etc.
  tank_distance= measure(tank_trigPin,tank_echoPin);

  if (distance<120 && distance>0)
  {
    fill= 116-distance;
    time_to_fill=(distance-20)*5/31;
  }

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.println("Fill: ");
  Serial.println(fill);
  Serial.println("%");
  Serial.println(time_to_fill);


  client.publish("toku/sensor",String(fill).c_str(),true);
  client.publish("toku/time_to_fill",String(time_to_fill).c_str(),true);

}


void operation_one()
{
  one_distance= measure(one_trgPin,one_echoPin);

}



void setup() {
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // Configure serial port for debugging
  Serial.begin(9600);
  // Initialise wifi connection - this will wait until connected
  connectWifi();
  // connect to MQTT server
  client.setServer(serverHostname, 1883);
}

void loop() {
    if (!client.connected()) {
      connectMQTT();
    }
    // this is ESSENTIAL!
    //client.loop();

    delay(5000);
}
