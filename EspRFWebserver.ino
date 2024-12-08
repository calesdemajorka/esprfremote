
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <RCSwitch.h>

const char* ssid = "Android";
const char* password = "78951230";

// Ethernet configuration
ESP8266WebServer server(80);                           // Server Port 80

// RCSwitch configuration
RCSwitch mySwitch = RCSwitch();
int RCTransmissionPin = 2;

// More to do...
// You should also modify the processCommand() and 
// httpResponseHome() functions to fit your needs.
typedef struct sSwitch
{
    char* first_set;
    char* second_set;
} tSwitch;
static const tSwitch switches[2] = { {"11111", "00110"}, {"11111", "00010"} };

/**
 * Setup
 */
void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    server.on("/", httpResponseHome);
    server.on("/rf", handleRf);
    server.onNotFound(handleNotFound);
    server.begin();
    mySwitch.enableTransmit( RCTransmissionPin );
}

/**
 * Loop
 */
void loop()
{
    server.handleClient();
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

String getArgValue(String name)
{
  for (uint8_t i = 0; i < server.args(); i++)
    if(server.argName(i) == name)
      return server.arg(i);
  return "";
}

/**
 * Command dispatcher
 */
void handleRf() {
    uint8_t sw = getArgValue("sw").compareTo("1") == 0 ? 1 : 2;
    bool act = getArgValue("act").compareTo("on") == 0 ? true : false;
    sw -= 1;
    if( act )
    {
        mySwitch.switchOn( switches[sw].first_set, switches[sw].second_set );
    }
    else
    {
        mySwitch.switchOff( switches[sw].first_set, switches[sw].second_set );
    }
    httpResponseHome();
}

/**
 * HTTP Response with homepage
 */
void httpResponseHome() {
  String message = "<html>";
  message += "<head>";
  message +=     "<title>RCSwitch Webserver Demo</title>";
  message +=     "<style>";
  message +=         "body { font-family: Arial, sans-serif; font-size:12px; }";
  message +=     "</style>";
  message +=     "<meta name="viewport" content="width=device-width, initial-scale=1" />";
  message += "</head>";
  message += "<body>";
  message +=     "<h1>RCSwitch Webserver Demo</h1>";
  message +=     "<ul>";
  message +=         "<li><a href=\"./rf?sw=1&act=on\">Renifer Switch on</a></li>";
  message +=         "<li><a href=\"./rf?sw=1&act=off\">Renifer Switch off</a></li>";
  message +=     "</ul>";
  message +=     "<ul>";
  message +=         "<li><a href=\"./rf?sw=2&act=on\">Girlanda Switch on</a></li>";
  message +=         "<li><a href=\"./rf?sw=2&act=off\">Girlanda Switch off</a></li>";
  message +=     "</ul>";
  message +=     "<hr>";
  message +=     "<a href=\"https://github.com/sui77/rc-switch/\">https://github.com/sui77/rc-switch/</a>";
  message += "</body>";
  message += "</html>";
  server.send(200, "text/html", message);
}

/**
 * HTTP Redirect to homepage
 */
void httpResponseRedirect() {
  String message = "HTTP/1.1 301 Found";
  message += "Location: /";
  server.send(301,"text/plain", message);
}

/**
 * HTTP Response 414 error
 * Command must not be longer than 30 characters
 **/
void httpResponse414() {
  String message = "HTTP/1.1 414 Request URI too long";
  message += "Content-Type: text/plain";
  message += "414 Request URI too long";
  server.send(414, "text/plain", message);
}
