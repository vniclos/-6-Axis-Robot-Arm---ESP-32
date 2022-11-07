#ifndef WEB_NOTFOUND_H
#define WEB_NOTFOUND_H

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += g_WebServer.uri();
  message += "\nMethod: ";
  message += (g_WebServer.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += g_WebServer.args();
  message += "\n";

  for (uint8_t i = 0; i < g_WebServer.args(); i++) {
    message += " " + g_WebServer.argName(i) + ": " + g_WebServer.arg(i) + "\n";
  }

  g_WebServer.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
#endif