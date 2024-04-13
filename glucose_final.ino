#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Define pins for the ultrasonic sensors
const int trigPin1 = D2; // GPIO pin for Trigger of sensor 1
const int echoPin1 = D4; // GPIO pin for Echo of sensor 1
const int trigPin2 = D3; // GPIO pin for Trigger of sensor 2
const int echoPin2 = D5; // GPIO pin for Echo of sensor 2

// WiFi credentials
const char* ssid = "Khushi wifi_4G";
const char* password = "0117678100674";

ESP8266WebServer server(80);

// Image URLs for bottles
const char* bottleImg1 = "https://www.pngkey.com/png/full/260-2608564_medicinal-clipart-medical-sign-medicine-clipart-hd.png";
const char* bottleImg2 = "https://www.pngkey.com/png/full/260-2608564_medicinal-clipart-medical-sign-medicine-clipart-hd.png";

// Background image URL
const char* backgroundImg = "https://img.onmanorama.com/content/dam/mm/en/lifestyle/health/images/2021/5/12/doctor-stethoscope-c.jpg";

void setup() {
  Serial.begin(115200);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print ESP8266 IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, handleRoot);
  // Start server
  server.begin();
}

void loop() {
  server.handleClient();

  // Measure distance from sensor 1
  long duration1, distance1;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  // Measure distance from sensor 2
  long duration2, distance2;
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  // Update web page
  delay(2000); // Wait for 2 seconds
}

void handleRoot() {
  // Measure distance from sensor 1
  long duration1, distance1;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;
  if (distance1>10){
    distance1=10;
  }

  // Measure distance from sensor 2
  long duration2, distance2;
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;
  if (distance2>10){
    distance2=10;
  }

  String content = "<html><head><meta http-equiv='refresh' content='2'><style>h1 { text-align: center; color: black; }</style></head><body style='background-image: url(";
  content += backgroundImg;
  content += "); background-size: cover;'>";
  content += "<h1>Room 23 Data</h1>";
  content += "<div style='display: flex; justify-content: space-around;'>";

  // Bottle 1
  content += "<div style='width: 200px; height: 400px; position: relative;'>";
  content += "<h3 style='text-align: center; color: black;'>Bottle 1</h3>";
  content += "<img src='";
  content += bottleImg1;
  content += "' style='max-width: 100%; max-height: 100%; position: absolute; bottom: 0;'>";
  content += "<div style='position: absolute; bottom: 0; width: 100%; height: " + String(map(distance1, 0, 10, 0, 50)) + "%; background-color: #007bff;'></div>";
  content += "</div>";

  // Bottle 2
  content += "<div style='width: 200px; height: 400px; position: relative;'>";
  content += "<h3 style='text-align: center; color: black;'>Bottle 2</h3>";
  content += "<img src='";
  content += bottleImg2;
  content += "' style='max-width: 100%; max-height: 100%; position: absolute; bottom: 0;'>";
  content += "<div style='position: absolute; bottom: 0; width: 100%; height: " + String(map(distance2, 0, 10, 0, 50)) + "%; background-color: #007bff;'></div>";
  content += "</div>";

  content += "</div>";
  content += "</body></html>";

  server.send(200, "text/html", content);
}
