#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#ifndef STASSID
#define STASSID "PAV"
#define STAPSK  "6SG9z#uk"
#endif
const char* ssid = STASSID;
const char* password = STAPSK;
// Configuration parameters for Access Point
char ssid_ap[32] = "Sol11";
char * password_ap = "123456789";
IPAddress ip(111, 111, 111, 111); // arbitrary IP address (doesn't conflict w/ local network)
IPAddress gateway(111, 111, 111, 1);
IPAddress subnet(255, 255, 255, 0);
// Set up the server object
ESP8266WebServer server(80);
const char documentation_page[] =  {"<!DOCTYPE html>\n"
                                    "\n"
                                    "<html>\n"
                                    "<head>\n"
                                    "<style>\n"
                                    ".button {\n"
                                    "  background-color: #555555; /* Green */\n"
                                    "\n"
                                    "  color: white;\n"
                                    "  text-align: center;\n"
                                    "\n"
                                    "\n"
                                    "  font-size: 16px;\n"
                                    "  margin: 5px 5px;\n"
                                    "  cursor: pointer;\n"
                                    "}\n"
                                    "\n"
                                    ".input {\n"
                                    "display: none; \n"
                                    "}\n"
                                    ".ninja {\n"
                                    "display: none;\n"
                                    "font-size: 0pt;\n"
                                    "}\n"
                                    ".h1 {text-align: center;}\n"
                                    ".label {font-size: 24px;text-align: center;}\n"
                                    ".button2 {background-color: #555555;} /* Blue */\n"
                                    ".button3 {background-color: #555555;} /* Red */ \n"
                                    ".button4 {background-color: #555555;} /* Gray */ \n"
                                    ".button5 {background-color: #555555;} /* Black */\n"
                                    "\n"
                                    "body {\n"
                                    "  margin: 40px;\n"
                                    "}\n"
                                    "button:focus{background-color:#3d3c3a;}\n"
                                    "\n"
                                    ".box {\n"
                                    "  background-color: #444;\n"
                                    "  color: #fff;\n"
                                    "  border-radius: 5px;\n"
                                    "  padding: 20px;\n"
                                    "  font-size: 150%;\n"
                                    "  width: 100%;\n"
                                    "}\n"
                                    "\n"
                                    ".boxHeader {\n"
                                    "  background-color: #000000;\n"
                                    "  color: #fff;\n"
                                    "  border-radius: 5px;\n"
                                    "  padding: 20px;\n"
                                    "  font-size: 150%;\n"
                                    "  width: 600px;\n"
                                    "}\n"
                                    "\n"
                                    "    .wrapper {\n"
                                    "    \n"
                                    "    color: white;\n"
                                    "        width: 600px;\n"
                                    "        display: grid;\n"
                                    "    grid-gap: 10px;\n"
                                    "        grid-template-columns: repeat(2, 200px);\n"
                                    "    }\n"
                                    "    \n"
                                    "    \n"
                                    "    .wrapper2 {\n"
                                    "        width: 600px;\n"
                                    "        display: grid;\n"
                                    "    grid-gap: 10px;\n"
                                    "        grid-template-columns: 100px 390px;\n"
                                    "    }\n"
                                    "        .wrapperLink {\n"
                                    "        width: 600px;\n"
                                    "        display: grid;\n"
                                    "    grid-gap: 10px;\n"
                                    "        grid-template-columns: repeat(2, 200px);\n"
                                    "    }\n"
                                    "    \n"
                                    "    input {\n"
                                    "  width: 100%;\n"
                                    "\n"
                                    "}\n"
                                    "</style>\n"
                                    "</head>\n"
                                    "<body>\n"
                                    "<div class=\"wrapperLink\">\n"
                                    "<form action=\"/\">\n"
                                    "    <input class=\"box\" type=\"submit\" value=\"home\" />\n"
                                    "</form>\n"
                                    "<form action=\"/control\">\n"
                                    "    <input class=\"box\" type=\"submit\" value=\"control\" />\n"
                                    "</form>\n"
                                    "</div>\n"
                                    "<br><br>\n"
                                    "<h1 class= \"boxHeader\">shortcuts to move axis in \"/control\"</h1>\n"
                                    "<div class=\"wrapper\">\n"
                                    "\n"
                                    "<h1 class= \"box\"> + </h1>\n"
                                    "<h1 class= \"box\"> - </h1>\n"
                                    "<h1 class= \"box\">Y U I O P</h1>\n"
                                    "<h1 class= \"box\">H J K L ;</h1>\n"
                                    "</div>\n"
                                    "\n"
                                    "<h1 class= \"boxHeader\">s 200 200 200 200 200 200 200 200 200 200 == s stepvariable axis_speed_variable stepvariable axis_speed_variable ... == first two numbers are represent 1 axis, second two represent second axis etc.</h1>\n"
                                    "<br>\n"
                                    "<br>\n"
                                    "\n"
                                    "</body>\n"
                                    "</html>\n"
                                    ""
                                   };
const char home_page[] =  {"<!DOCTYPE html>\n"
                           "\n"
                           "<html>\n"
                           "<head>\n"
                           "<style>\n"
                           ".button {\n"
                           "  background-color: #555555; /* Green */\n"
                           "\n"
                           "  color: white;\n"
                           "  text-align: center;\n"
                           "\n"
                           "\n"
                           "  font-size: 16px;\n"
                           "  margin: 5px 5px;\n"
                           "  cursor: pointer;\n"
                           "}\n"
                           "\n"
                           ".input {\n"
                           "display: none; \n"
                           "}\n"
                           ".ninja {\n"
                           "display: none;\n"
                           "font-size: 0pt;\n"
                           "}\n"
                           ".label {font-size: 24px;text-align: center;}\n"
                           ".button2 {background-color: #555555;} /* Blue */\n"
                           ".button3 {background-color: #555555;} /* Red */ \n"
                           ".button4 {background-color: #555555;} /* Gray */ \n"
                           ".button5 {background-color: #555555;} /* Black */\n"
                           "\n"
                           "body {\n"
                           "  margin: 40px;\n"
                           "}\n"
                           "button:focus{background-color:#3d3c3a;}\n"
                           "\n"
                           ".box {\n"
                           "  background-color: #444;\n"
                           "  color: #fff;\n"
                           "  border-radius: 5px;\n"
                           "  padding: 20px;\n"
                           "  font-size: 150%;\n"
                           "  width: 100%;\n"
                           "}\n"
                           "\n"
                           "\n"
                           "\n"
                           "    .wrapper {\n"
                           "        width: 600px;\n"
                           "        display: grid;\n"
                           "    grid-gap: 10px;\n"
                           "        grid-template-columns: repeat(2, 200px);\n"
                           "    }\n"
                           "    \n"
                           "    \n"
                           "    .wrapper2 {\n"
                           "        width: 600px;\n"
                           "        display: grid;\n"
                           "    grid-gap: 10px;\n"
                           "        grid-template-columns: 100px 390px;\n"
                           "    }\n"
                           "    \n"
                           "    input {\n"
                           "  width: 100%;\n"
                           "\n"
                           "}\n"
                           "</style>\n"
                           "</head>\n"
                           "<body>\n"
                           "\n"
                           "\n"
                           "\n"
                           "<div class=\"wrapper\">\n"
                           "\n"
                           "<form action=\"/control\">\n"
                           "    <input class=\"box\" type=\"submit\" value=\"control robot\" />\n"
                           "</form>\n"
                           "<form action=\"/documentation\">\n"
                           "    <input class=\"box\" type=\"submit\" value=\"documentation\" />\n"
                           "</form>\n"
                           "\n"
                           "\n"
                           "</div>\n"
                           "<br>\n"
                           "<br>\n"
                           "\n"
                           "</body>\n"
                           "</html>\n"
                           ""
                          };
const char control_page[] =  {"<!DOCTYPE html>\n"
                              "<html>\n"
                              "<head>\n"
                              "<style>\n"
                              ".button {\n"
                              "  background-color: #555555; /* Green */\n"
                              "\n"
                              "  color: white;\n"
                              "  text-align: center;\n"
                              "\n"
                              "\n"
                              "  font-size: 16px;\n"
                              "  margin: 5px 5px;\n"
                              "  cursor: pointer;\n"
                              "}\n"
                              "\n"
                              "\n"
                              "\n"
                              ".label {font-size: 24px;text-align: center;}\n"
                              ".button2 {background-color: #555555;} /* Blue */\n"
                              ".button3 {background-color: #555555;} /* Red */ \n"
                              ".button4 {background-color: #555555;} /* Gray */ \n"
                              ".button5 {background-color: #555555;} /* Black */\n"
                              "\n"
                              "body {\n"
                              "  margin: 40px;\n"
                              "}\n"
                              "button:focus{background-color:#3d3c3a;}\n"
                              "\n"
                              ".box {\n"
                              "  background-color: #444;\n"
                              "  color: #fff;\n"
                              "  border-radius: 5px;\n"
                              "  padding: 20px;\n"
                              "  font-size: 150%;\n"
                              "  width: 100%;\n"
                              "  height: 100px;\n"
                              "}\n"
                              "\n"
                              ".boxHeader {\n"
                              "  background-color: #444;\n"
                              "  color: #fff;\n"
                              "  border-radius: 5px;\n"
                              "  padding: 20px;\n"
                              "  font-size: 150%;\n"
                              "  width: 100%;\n"
                              "}\n"
                              "\n"
                              ".textinput{\n"
                              "  background-color: #444;\n"
                              "  color: #fff;\n"
                              "  border-radius: 5px;\n"
                              "  padding: 20px;\n"
                              "  font-size: 150%;\n"
                              "  width: 108px;\n"
                              "  height: 56px;\n"
                              "}\n"
                              ".ninja {\n"
                              "display: none;\n"
                              "font-size: 0pt;\n"
                              "}\n"
                              ".textinputSCommand{\n"
                              "  background-color: #444;\n"
                              "  color: #fff;\n"
                              "  border-radius: 5px;\n"
                              "  padding: 20px;\n"
                              "  font-size: 150%;\n"
                              "  width: 320px;\n"
                              "  height: 56px;\n"
                              "}\n"
                              "    .wrapperLink {\n"
                              "        width: 600px;\n"
                              "        display: grid;\n"
                              "    grid-gap: 10px;\n"
                              "        grid-template-columns: repeat(2, 200px);\n"
                              "    }\n"
                              "    \n"
                              "\n"
                              "    .wrapper {\n"
                              "        width: 600px;\n"
                              "        display: grid;\n"
                              "    grid-gap: 10px;\n"
                              "        grid-template-columns: repeat(5, 150px);\n"
                              "    }\n"
                              "    \n"
                              "    \n"
                              "    .wrapper2 {\n"
                              "        width: 600px;\n"
                              "        display: grid;\n"
                              "    grid-gap: 10px;\n"
                              "        grid-template-columns: 100px 390px;\n"
                              "    }\n"
                              "    \n"
                              "\n"
                              "}\n"
                              "</style>\n"
                              "\n"
                              "\n"
                              "<body>\n"
                              "\n"
                              "<div class=\"wrapperLink\">\n"
                              "\n"
                              "<form action=\"/\">\n"
                              "    <input class=\"boxHeader\" type=\"submit\" value=\"home\" />\n"
                              "</form>\n"
                              "<form action=\"/documentation\">\n"
                              "    <input class=\"boxHeader\" type=\"submit\" value=\"documentation\" />\n"
                              "</form>\n"
                              "\n"
                              "\n"
                              "</div>\n"
                              "\n"
                              "\n"
                              "<br>\n"
                              "<br>\n"
                              "<br>\n"
                              "\n"
                              "\n"
                              "<div class=\"wrapper\">\n"
                              "<span class=\"label other\">1 axis</span>\n"
                              "<span class=\"label other\">2 axis</span>\n"
                              "<span class=\"label other\">3 axis</span>\n"
                              "<span class=\"label other\">4 axis</span>\n"
                              "<span class=\"label other\">5 axis</span>\n"
                              "<form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"ap\" id=\"ap1\" value=\"1\">\n"
                              "  <button class=\"box\" accesskey=\"y\">+</button>\n"
                              "  </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"ap\" id=\"ap2\" value=\"2\">\n"
                              "  <button class=\"box\" accesskey=\"u\">+</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"ap\" id=\"ap3\" value=\"3\">\n"
                              "  <button class=\"box\" accesskey=\"i\">+</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"ap\" id=\"ap4\" value=\"4\">\n"
                              "  <button class=\"box\" accesskey=\"o\">+</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"ap\" id=\"ap5\" value=\"5\">\n"
                              "  <button class=\"box\" accesskey=\"p\">+</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"an\" id=\"an1\" value=\"1\">\n"
                              "  <button class=\"box\" accesskey=\"h\">-</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"an\" id=\"an2\" value=\"2\">\n"
                              "  <button class=\"box\" accesskey=\"j\">-</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"an\" id=\"an3\" value=\"3\">\n"
                              "  <button class=\"box\" accesskey=\"k\">-</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"an\" id=\"an4\" value=\"4\">\n"
                              "  <button class=\"box\" accesskey=\"l\">-</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"an\" id=\"an5\" value=\"5\">\n"
                              "  <button class=\"box\" accesskey=\";\" >-</button>\n"
                              "    </form>\n"
                              "    \n"
                              "    \n"
                              "    <!- >\n"
                              "      <form action=\"/control\" method=\"get\">\n"
                              "<input class=\"textinput\"  onchange='callFunctions(this);'  type=\"text\" id=\"1\" name=\"speed1\" value=\"50\">\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "<input class=\"textinput\"  onchange='callFunctions(this);'  type=\"text\" id=\"2\" name=\"speed2\" value=\"50\">\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "<input class=\"textinput\"  onchange='callFunctions(this);'  type=\"text\" id=\"3\" name=\"speed3\" value=\"50\">\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "<input class=\"textinput\"  onchange='callFunctions(this);'  type=\"text\" id=\"4\" name=\"speed4\" value=\"50\">\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "   <input class=\"textinput\" onchange='callFunctions(this);'  type=\"text\" id=\"5\" name=\"speed5\" value=\"50\">\n"
                              "    </form>\n"
                              "    \n"
                              "    \n"
                              "    \n"
                              " <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"mcp\" id=\"mcp1\" value=\"1\">\n"
                              "  <button class=\"box\" accesskey=\"1\" onclick=\"copyTextValue();\">+</button>\n"
                              "  </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"mcp\" id=\"mcp2\" value=\"2\">\n"
                              "  <button class=\"box\" accesskey=\"2\" onclick=\"copyTextValue();\">+</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"mcp\" id=\"mcp3\" value=\"3\">\n"
                              "  <button class=\"box\" accesskey=\"3\" onclick=\"copyTextValue();\">+</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"mcp\" id=\"mcp4\" value=\"4\">\n"
                              "  <button class=\"box\" accesskey=\"4\" onclick=\"copyTextValue();\">+</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"mcp\" id=\"mcp5\" value=\"5\">\n"
                              "  <button class=\"box\" accesskey=\"5\" onclick=\"copyTextValue();\">+</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"mcn\" id=\"mcn1\" value=\"1\">\n"
                              "  <button class=\"box\" accesskey=\"6\" onclick=\"copyTextValue();\">-</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"mcn\" id=\"mcn2\" value=\"2\">\n"
                              "  <button class=\"box\" accesskey=\"7\" onclick=\"copyTextValue();\">-</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"mcn\" id=\"mcn3\" value=\"3\">\n"
                              "  <button class=\"box\" accesskey=\"8\" onclick=\"copyTextValue();\">-</button>\n"
                              "    </form>\n"
                              "  <form action=\"/control\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"mcn\" id=\"mcn4\" value=\"4\">\n"
                              "  <button class=\"box\" accesskey=\"9\" onclick=\"copyTextValue();\">-</button>\n"
                              "    </form>\n"
                              "  <form action=\"\" method=\"get\">\n"
                              "    <input class=\"ninja\" name=\"mcn\" id=\"mcn5\" value=\"5\">\n"
                              "  <button class=\"box\" accesskey=\"0\" onclick=\"copyTextValue(mcn5);\">-</button>\n"
                              "    </form>\n"
                              "</div>\n"
                              "<br>\n"
                              "<br>\n"
                              "<div>\n"
                              "<form action=\"/control_command\" class=\"wrapper2\" method=\"get\">\n"
                              "  <button class=\"box\" accesskey=\"s\">s</button>\n"
                              "  <input class=\"textinputSCommand\" type=\"text\" id=\"text_command\" name=\"text_command\">\n"
                              "</form>\n"
                              "</div>\n"
                              "</body>\n"
                              "</html>\n"
                              "\n"
                              "\n"
                              "\n"
                              "<script>    \n"
                              "        if(getSavedValue(\"1\")==null){}else document.getElementById(\"1\").value = getSavedValue(\"1\");  \n"
                              "         if(getSavedValue(\"2\")==null){}else document.getElementById(\"2\").value = getSavedValue(\"2\");   \n"
                              "        if(getSavedValue(\"3\")==null){}else  document.getElementById(\"3\").value = getSavedValue(\"3\"); \n"
                              "         if(getSavedValue(\"4\")==null){}else document.getElementById(\"4\").value = getSavedValue(\"4\"); \n"
                              "         if(getSavedValue(\"5\")==null){}else document.getElementById(\"5\").value = getSavedValue(\"5\"); \n"
                              "        \n"
                              "        \n"
                              "        var step;\n"
                              "for (step = 1; step < 6; step++) {\n"
                              "  document.getElementById(\"mcp\" + step.toString()).value =  step.toString() + \" \" +  document.getElementById(step.toString()).value.toString();\n"
                              "            document.getElementById(\"mcn\" + step.toString()).value = step.toString() + \" \" + document.getElementById(step.toString()).value.toString();\n"
                              "            document.getElementById(\"ap\" + step.toString()).value = step.toString() + \" \" +  document.getElementById(step.toString()).value.toString();\n"
                              "            document.getElementById(\"an\" + step.toString()).value =  step.toString() + \" \" +  document.getElementById(step.toString()).value.toString();\n"
                              "}\n"
                              "        /* Here you can add more inputs to set value. if it's saved */\n"
                              "  function callFunctions(object)\n"
                              "    {\n"
                              "    saveValue(object);\n"
                              "    changeSpeed(object.value, object.id);\n"
                              "    }\n"
                              "        //Save the value function - save it to localStorage as (ID, VALUE)\n"
                              "        function saveValue(e){\n"
                              "            var id = e.id;  // get the sender's id to save it . \n"
                              "            var val = e.value; // get the value. \n"
                              "            localStorage.setItem(id, val);// Every time user writing something, the localStorage's value will override . \n"
                              "        }\n"
                              "\n"
                              "        //get the saved value function - return the value of \"v\" from localStorage. \n"
                              "        function getSavedValue  (v){\n"
                              "            if (!localStorage.getItem(v)) {\n"
                              "                return \"200\";// You can change this to your defualt value. \n"
                              "            }\n"
                              "            return localStorage.getItem(v);\n"
                              "        }\n"
                              "        \n"
                              "        \n"
                              "        \n"
                              "// value == speed, id == num of axis\n"
                              "function changeSpeed(value, id) {\n"
                              "// value of hidden input == num of axis + speed\n"
                              "    document.getElementById(\"mcp\" + id).value = id + \" \" + value;\n"
                              "    document.getElementById(\"mcn\" + id).value = id + \" \" + value;\n"
                              "    document.getElementById(\"an\" + id).value =  id + \" \" + value;\n"
                              "    document.getElementById(\"ap\" + id).value =  id + \" \" + value;\n"
                              "}\n"
                              "\n"
                              "\n"
                              "\n"
                              "</script>\n"
                              "\n"
                              "\n"
                              ""
                             };


const int led = 13;

void handleRoot() {
  server.send_P(200, "text/html", home_page);
}
void handleDocumentation() {
  server.send_P(200, "text/html", documentation_page);
}
void handleControl() {
  server.send_P(200, "text/html", control_page);
  String ap = "";
  String an = "";
  String mcp = "";
  String mcn = "";
  String text_command = "";
  an = server.arg("an");
  ap = server.arg("ap");
  mcp = server.arg("mcp");
  mcn = server.arg("mcn");
  text_command = server.arg("text_command");
  String commandToSend = "";
  if (text_command != "") commandToSend = text_command;
  if (an != "") commandToSend = String("an" + an);
  if (ap != "") commandToSend = String("ap" + ap);
  if (mcp != "") commandToSend = String("mcp" + mcp);
  if (mcn != "") commandToSend = String("mcn" + mcn);
  Serial.println(commandToSend);
}


void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);

}

void setup(void) {
  Serial.begin(115200);
  //  WiFi.mode(WIFI_AP);
  //  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

    // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
    
  }
  delay(15000);
    Serial.println("WIFIED");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

    if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }


  // When the password is too short (less than 8 characters)
  //the WiFi.softAP(ssid, password) function desn't work.
//  WiFi.softAP(ssid_ap, password_ap);
  // Print IP Address as a sanity check
//

  //  pinMode(led, OUTPUT);
  //  digitalWrite(led, 0);
  //Serial.begin(115200);
  //WiFi.mode(WIFI_STA);
  //WiFi.begin(ssid, password);
  //Serial.println("");

  // Wait for connection
  //  while (WiFi.status() != WL_CONNECTED) {
  //    delay(500);
  //    Serial.print(".");
  //  }
  //  Serial.println("");
  //  Serial.print("Connected to ");
  //  Serial.println(ssid);
  //  Serial.print("IP address: ");
  //  Serial.println(WiFi.localIP());
  //
  //  if (MDNS.begin("esp8266")) {
  //    Serial.println("MDNS responder started");
  //  }

  server.on("/", handleRoot);
  server.on("/control", handleControl);
  server.on("/documentation", handleDocumentation);;
  //  server.on("/inline", []() {
  //    server.send(200, "text/plain", "this works as well");
  //  });

  //  server.on("/gif", []() {
  //    static const uint8_t gif[] PROGMEM = {
  //      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
  //      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
  //      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
  //      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
  //      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
  //    };
  //    char gif_colored[sizeof(gif)];
  //    memcpy_P(gif_colored, gif, sizeof(gif));
  //    // Set the background to a random set of colors
  //    gif_colored[16] = millis() % 256;
  //    gif_colored[17] = millis() % 256;
  //    gif_colored[18] = millis() % 256;
  //    server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
  //  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
    MDNS.update();
}
