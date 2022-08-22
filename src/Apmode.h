#include <Arduino.h>
#include <KDNSServer.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
const char getpassword_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>Config file wifi</h2>
  <form action="/setpassword" method="POST" enctype="application/x-www-form-urlencoded">
  SSID:<input type="text" name="ssid" >
PASSWORD:<input type="password" name="password">
 <hr>
   <input type="submit" value="Send">
</form>
</body>
</html>)rawliteral";
class ApMode
{

public:
    void run();
};

void ApMode::run()
{

    const byte DNS_PORT = 53;      // Capture DNS requests on port 53
    IPAddress apIP(10, 10, 10, 1); // Private network for server
    KDNSServer dnsServer;          // Create the DNS object

    // ESP8266WebServer webServer(80); // HTTP server
    AsyncWebServer webServer(80);
    Serial.begin(9600);
    pinMode(2, OUTPUT);
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("For test Apmode"); // WiFi name

    // if DNSServer is started with "*" for domain name, it will reply with
    // provided IP to all DNS request
    dnsServer.start(DNS_PORT, "*", apIP);

    // replay to all requests with same HTML
    // webServer.onNotFound([]()
    //                      { webServer.send(200, "text/html", responseHTML); });

    webServer.onNotFound([](AsyncWebServerRequest *request)
                         { request->send(200, "text/html", getpassword_html); });
    webServer.begin();
    while (true)
        dnsServer.processNextRequest();
}
