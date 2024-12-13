#include <WiFi.h>
#include <WebServer.h>
#include <WiFiUdp.h>

WebServer server(80);
WiFiUDP udp;

/* Put your SSID & Password */
const char* ssid = "Safty Ring";  // Enter SSID here
const char* password = "12345678";  // Enter Password here

/* Put IP Address details */
IPAddress local_ip(192, 168, 43, 2); // Different IP address for this ESP32
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);

String warningMessage = " ";
String websend, webdata, WebLoction;

int count = 0;
const int Sw = 14;

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet); // Set static IP configuration
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());
  
  server.on("/", HTTP_GET, handle_OnConnect);
  server.begin();

  pinMode(Sw, INPUT);
}

void loop() {
  server.handleClient();

  int read = digitalRead(Sw);
  if (read == LOW) {
    count++;
    delay(500);
  }
  if (count >= 3) {
    WebLoction = "xx-xx-xx-xx-xx..";
    webdata = "Asking for help";
    Serial.println("Asking for help");
    websend = webdata;
    sendUDP("Hello, Asking for Help!");
    count = 0; // Reset count after sending UDP packet
  }
}

void handle_OnConnect() {
  Serial.println("Engine Status OFF");
  server.send(200, "text/html", SendHTML(websend));
}

String SendHTML(String websend) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Temperatur Monitor </title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #1abc9c;}\n";
  ptr += ".button-on:active {background-color: #16a085;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "<script>function autoRefresh() {  window.location = window.location.href;} setInterval('autoRefresh()', 2000); </script>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1> Smart Ring </h1>\n";
  ptr += "<h1> Information: " + websend + "</h1>\n";
  ptr += "<h1> Location: " + WebLoction + "</h1>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

void sendUDP(const char* message) {
  const char *udpAddress = "192.168.43.3"; // IP address of the UDP receiver (Different from the sender)
  const int udpPort = 1234; // Different port from the receiver

  udp.beginPacket(udpAddress, udpPort);
  udp.print(message);
  udp.endPacket();
}
