#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <FS.h>                      //Содержится в пакете
#include <WebSocketsServer.h>    //https://github.com/Links2004/arduinoWebSockets
#include <ESP8266SSDP.h>        //Содержится в пакете. Видео с уроком http://esp8266-arduinoide.ru/step3-ssdp

WebSocketsServer webSocket = WebSocketsServer(82);

WiFiUDP Udp;
ESP8266WebServer HTTP(80);
File fsUploadFile;

int16_t stack[256] = {0}; // здесь стек
uint8_t stackTop = 128; // Адрес вершины
String Lang = "";                    // файлы языка web интерфейса
const String texthtmlS   = "text/html";
const String emptyS   = "";
const String jsonEmptyS   = "{}";
const String setIndexS   = "setIndex";
String configlive = jsonEmptyS;
int flag = 0;

String command;
String dic=": 1+ 1 + ;\r\n: 1- 1 - ;\r\n: 4+ 4 + ;\r\n";

//const static char webphort[] PROGMEM =
const String webForth =
  "<!DOCTYPE html>\n\r"
  "<html>\n\r"
  " <head>\n\r"
  "  <meta charset=\"UTF-8\">\n\r"
  "  <title>Forth console</title>\n\r"
  " </head>\n\r"
  " <body>\n\r"
  "  <script>\n\r"
  "   var connection = new WebSocket(\"ws://\"+window.location.host+\":82\", ['arduino']);\n\r"
  "   connection.onmessage = function (e) {\n\r"
  "    console.log('Server: ', e.data);\n\r"
  "    document.getElementById('console').value += e.data;\n\r"
  "    document.getElementById(\"console\").scrollTop = document.getElementById(\"console\").scrollHeight;\n\r"
  "   }\n\r"
  "   function onChange() {\n\r"
  "    if (window.event.keyCode === 13) {\n\r"
  "     var console = document.getElementById(\"console\").value;\n\r"
  "     connection.send(console.split('ok>')[console.split('ok>').length-1]);\n\r"
  "     return true;\n\r"
  "    }\n\r"
  "   }\n\r"
  "  </script>\n\r"
  "  <textarea id=\"console\" style=\"width:100%;height:100%;\" onkeypress=\"onChange();\" cols=\"30\" rows=\"30\"></textarea>\n\r"
  " </body>\n\r"
  "</html>\n\r";


void setup()
{
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Serial.begin(115200);
  delay(100);
  SPIFFS.begin();
  delay(100);
  initFS();
  dic = readFile("vocabulary.txt", 4096 );
  SSDP_init();
  initWebSocket();
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println("Starting connection to server...");
  // if you get a connection, report back via serial:
  Serial.println("Booting espForth_44 ...");
  initHTTP();
}

void loop() {
  HTTP.handleClient();
  webSocket.loop();
  //getCom();
  handleForth();
}
