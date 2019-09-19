
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


const char* ssid="MW40V_7BBD";
const char* password="70703124";


void setup() {
  
  // put your setup code here, to run once:
 Serial.begin(9600);
 WiFi.begin(ssid, password);

 while(WiFi.status() != WL_CONNECTED){
  delay(2000);
  Serial.print(".");
 }
 Serial.print("Connected");
   Serial.print("IP address: ");
  Serial.print(WiFi.localIP());

}

void loop() {

 

  if(WiFi.status() == WL_CONNECTED){ //Check Connectivity before Sending
    HTTPClient post;  
    HTTPClient stream;  
   int sensor=analogRead(A0); // Incoming analog signal read and appointed sensor

    Serial.println("Water Level Value: ");
    Serial.println(sensor);
    String value=String(sensor);
   
   if(sensor>50){
 
       String url="http://192.168.1.174:8080/alertsensor/post?id=1&reference=RT302&al=31.3451&log=-0.67548&state=active&type=wl&value="+value;
       post.begin(url);
       post.begin(url);
       post.addHeader("Content-Type","application/json");
      Serial.println(url);
      int httpCode= post.GET();
      
      if(httpCode>0){
          String payload= post.getString();
          Serial.println(payload);
                    }
      post.end(); //Close connection
              }
    String url2="http://192.168.1.174:8090/streamdata/post?id=1&value="+value;
    stream.begin(url2);
    stream.begin(url2);
    stream.addHeader("Content-Type","application/json");
    Serial.println(url2);
    int httpCode= stream.GET();
      
      if(httpCode>0){
          String payload= stream.getString();
          Serial.println(payload);
                    }
      stream.end(); 
    
    
  }
   

  
   
   delay(1000); //Send Request every 30 seconds;
   

}
