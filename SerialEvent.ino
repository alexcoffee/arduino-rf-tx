#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
String inputString = "";
boolean stringComplete = false;

void setup() {
  inputString.reserve(200);
  Serial.begin(9600);
  mySwitch.enableTransmit(10);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (stringComplete) {
    Serial.println("ok");
    handleCommand(inputString);
    inputString = "";
    stringComplete = false;
  }
}

void handleCommand(String command)
{
  if (command.startsWith("send")) {
      mySwitch.send(command.substring(4).c_str());
      Serial.println(command.substring(4).c_str());
  }
  
  if (command == "1") {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if (command == "2") {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n' || inputString.length() >= 200) {
      stringComplete = true;
    } else {
      inputString += inChar;
    }
  }
}


