#include <ESP8266WiFi.h> //Includes ESP8266 Wifi library
#include <ESP8266TimeAlarms.h>

//Defines representation of the pins used for each relay
#define Relay_01 16         //D0
#define AC 5                //D1
#define LightsandFans 4     //D2
#define UPS 0               //D3

//AlarmId id;

//Create a server on port 80
//(default port where browsers send http requests)
WiFiServer server(80);

void setup()
{
  //Initializes Serial for logging purposes only
  Serial.begin(115200);

  //Sets the mode of all pins
  pinMode(Relay_01, OUTPUT);
  pinMode(AC, OUTPUT);
  pinMode(LightsandFans, OUTPUT);
  pinMode(UPS, OUTPUT);

  //Adjust the state of all pins
  digitalWrite(Relay_01, HIGH);
  digitalWrite(AC, HIGH);
  digitalWrite(LightsandFans, HIGH);
  digitalWrite(UPS, HIGH);

  // create the alarms, to trigger at specific times
  //Alarm.alarmRepeat(16,50,0, MorningAlarm);  // 10:19 am every day
  //Alarm.alarmRepeat(18,20,0,EveningAlarm);  // 10:20 am every day

  Serial.print("Connected....!");//reporting current state (debug)
  //Makes the ESP connect to the WiFi network available at the place of use.
  //In our example the ssid of the network is networkWiFi and the password is passwordtest
  WiFi.begin("GANESH-PC", "12345678");

  // As long as the ESP does not connect to the network
  while (WiFi.status() != WL_CONNECTED)
  {
    //We wait 100 milliseconds
    delay(100);
    Serial.print(".");
  }

  //If you arrived here, it's because you connected to the network,
  //then we show it on the serial monitor to have a feedback
  Serial.println("");
  Serial.println("connected!!");

  //Fixed IP settings. You can change it according to your network
  Serial.println(WiFi.localIP());
  //send the configuration
  //iFi.config(ip, gateway, subnet);

  //Initialize the server we created on port 80
  server.begin();

  //We show on the serial monitor the IP that the ESP has
  //to check if it is the same as the one we configured
  Serial.print("server on: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  /*digitalClockDisplay();
  Alarm.delay(20000000); // wait one second between clock */
  //Checks if any clients are trying to connect
  WiFiClient client = server.available();
  if (!client)
  {
    //If there is no customer we can return it as there is nothing to do
    return;
  }
  //We read the request
  String req = client.readStringUntil('\r');
  req.replace("GET /", "");
  req.replace(" HTTP/1.1","");
  //Serial.print("Request: ");
  Serial.println(req);

  //This is the html we will return to the client
  //It basically consists of two buttons (ON and OFF) for each relay
  //The part that interests us is the <a href=' with the action linked to each button
  //When we click on one of these buttons this information will reach the ESP for
  //let it check which action it should perform
  //The part inside '<style>' is just for us to change the look of the page
  //which will be displayed, you can change it however you want
  String html =
    "<html>"
    "<head>"ś
    "<meta name='viewport' content='width=device-width, initial-scale=1, user-scalable=no'/>"
    "<title>Automation</title>"
    "<style>"
    "body{"
    "text-align: center;"
    "font-family: sans-serif;"
    "font-size:25px;"
    "padding: 25px;"
    "}"
    "p{"
    "color:#444;"
    "}"
    "button{"
    "outline: none;"
    "border: 2px solid #1fa3ec;"
    "border-radius:18px;"
    "background-color:#FFF;"
    "color: #1fa3ec;"
    "padding: 5px 25px;"
    "}"
    "button:active{"
    "color: #fff;"
    "background-color:#1fa3ec;"
    "}"
    "button:hover{"
    "border-color:#0000ff;"
    "}"
    "</style>"
    "</head>"
    "<body>"
    "<h3>Room 1</h3>"
    "<p> Relay_01 - "
    "<a href='Relay_01On'><button class='btn_1'>ON</button></a>"
    "<a href='Relay_01Off'><button>OFF</button></a>"
    "</p>"
    "<p>AC - "
    "<a href='ACOn'><button class='btn_2'>ON</button></a>"
    "<a href='ACOff'><button>OFF</button></a>"
    "</p>"
    "<p>LightsandFans - "
    "<a href='LightsandFansOn'><button>ON</button></a>"
    "<a href='LightsandFansOff'><button>OFF</button></a></p>"
    "<p>UPS - "
    "<a href='UPSOn'><button>ON</button></a>"
    "<a href='UPSOff'><button>OFF</button></a></p>"    
    "</body>"
    "</html>"; 
  //Write the html in the buffer that will be sent to the client
  client.print(html);
  // Send the buffer data to the client
  client.flush();

  //From here, we check if the request has any command
  //acting on the relays
  if (req.indexOf("Relay_01On") != -1)
  {
    digitalWrite(Relay_01, LOW);
  }
  else if (req.indexOf("Relay_01Off") != -1)
  {
    digitalWrite(Relay_01, HIGH);
  }

  if (req.indexOf("ACOn") != -1)
  {
    digitalWrite(AC, LOW);
  }
  else if (req.indexOf("ACOff") != -1)
  {
    digitalWrite(AC, HIGH);
  }

  if (req.indexOf("LightsandFansOn") != -1)
  {
    digitalWrite(LightsandFans, LOW);
  }
  else if (req.indexOf("LightsandFansOff") != -1)
  {
    digitalWrite(LightsandFans, HIGH);
  }

  if (req.indexOf("UPSOn") != -1)
  {
    digitalWrite(UPS, LOW);
  }
  else if (req.indexOf("UPSOff") != -1)
  {
    digitalWrite(UPS, HIGH);
  }
  delay(200);//waits for information traffic to complete
  //Close the connection with the client
  client.stop();
  //Serial.println("Client disconnected");
}
// functions to be called when an alarm triggers:
/*void MorningAlarm() {
  Serial.println("Alarm: - turn lights ON");
  digitalWrite(UPS, HIGH);
}

void EveningAlarm() {
  Serial.println("Alarm: - turn lights OFF");
  digitalWrite(UPS, LOW);
}
void digitalClockDisplay() {
  time_t tnow = time(nullptr);
  Serial.println(ctime(&tnow));
}*/
