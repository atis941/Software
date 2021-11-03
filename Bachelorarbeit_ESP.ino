#include <Stepper.h> //for Stepper Motor setup
#include <WiFi.h> //for WiFi setup
#include <PubSubClient.h> //for MQTT setup

#define ssid "UPC0676608"
#define password "Pdrkhbwne4y6"
byte* new_payload = NULL; //the payload you get from the broker
char* new_topic = NULL; //the topic you get from the broker
#define mqttUser "atis941"
#define mqttPassword "kelkaposzta94"

//Set up MQTT
#define HiveMQ "broker.hivemq.com" // "IP" for HiveMQ
#define Chrome "192.168.0.1" //my IP adress for MQTT Lens
#define mqtt_broker "192.168.0.248" //IP adress of Raspberry PI
WiFiClient espClient; //create a WiFi client
PubSubClient mqttClient(espClient); //create an MQTT publish/subscribe client
//define Topics
#define mqttOpen "windowBlind/open" //Topic for Open
#define mqttClose "windowBlind/close" //Topic for Close
//End MQTT setup

//stepper Motor setup
int SPR = 2048; //steps per revolution
int motspeed = 20; //motor speed
int dt = 500; //delay time
const int PIN1 = 13;
const int PIN2 = 12;
const int PIN3 = 14;
const int PIN4 = 27;
Stepper myStepper(SPR,PIN1,PIN3,PIN2,PIN4);

void callback(char* topic, byte* payload,unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  memcpy(new_topic,topic,sizeof(topic)); // save the topic of the message you get
 
  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  memcpy(new_payload,payload,sizeof(payload)); // save the payload of the message you get
 
  Serial.println();
  Serial.println("-----------------------");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myStepper.setSpeed(motspeed);

  //Set up WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password); //create wifi connection with the Access Point
  while(WiFi.status() != WL_CONNECTED){ // Try connecting until it has succeeded
    delay(dt);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP Adress of ESP: ");
  Serial.println(WiFi.localIP());
  //End WiFi setup

  //mqttClient.setCallback(callback); //a message callback function, called when a message arrives for a subscription created by this client.

  //Connect to the MQTT server
  mqttClient.setServer(HiveMQ,1883);
  Serial.print("Connecting to MQTT Server");
  while(!mqttClient.connected()){
    Serial.print(".");
    delay(dt);
    if(mqttClient.connect("ESP32" ,mqttUser ,mqttPassword))//connect to the server (broker) as ESP32
      Serial.println("Connected - SUCCESS");
  }
  mqttClient.subscribe(mqttOpen); //Subscribe to the Topic of opening
  mqttClient.subscribe(mqttClose); //Subscribe to the Topic of closing
  mqttClient.setCallback(callback); //a message callback function, called when a message arrives for a subscription created by this client. 
}


void loop() {
  // put your main code here, to run repeatedly
  if(mqttClient.loop()){
    if(strcmp(new_topic,mqttOpen)){
       myStepper.step(SPR);
       delay(dt);
    }
    else if(strcmp(new_topic,mqttClose)){
      myStepper.step(-SPR);
      delay(dt);
    }
  }
  Serial.println(new_topic);
}
