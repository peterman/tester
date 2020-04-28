/*
 Name:		tester.ino
 Created:	28.04.2020 12:35:14
 Author:	PfeifferP

 Command:    0 = leer
             1 = Start
             2 = Stop
             3 = Cal
             4 = Read Status
             5 = Read Para
*/

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;     // whether the string is complete
unsigned long resp_time;         // speicher für ablauf 
int last_cmd;                    // Befehl senden und warten auf Antwort
unsigned long timer1 = 0;        // Timer 1
int period = 2000;               // 2 sek Timer
int zyklus = 5;                  // Zyklus Ablauf
int i = 0;

// the setup function runs once when you press reset or power the board
void setup() {
    // initialize serial:
    Serial.begin(9600);
    // reserve 200 bytes for the inputString:
    inputString.reserve(200);
    resp_time = millis();
}

// the loop function runs over and over again until power down or reset
void loop() {
    if (Serial.isRxEnabled())
    {
        serialEvent();
    }// *** check RX is coming

    if (stringComplete) {
        Serial.println(inputString);
        // clear the string:
        last_cmd = 0;
        inputString = "";
        stringComplete = false;
    }
    if (millis() >= timer1 + period) {
        timer1 += period;
        if (i <= zyklus) {
            i += 1;
            sendStart();
        }
        else {
            i = 0;
            sendStop();
        }


    }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char)Serial.read();
        // add it to the inputString:
        inputString += inChar;
        // if the incoming character is a newline, set a flag so the main loop can
        // do something about it:
        if (inChar == 0x15) {
            inputString = "Error";
            stringComplete = true;
        }
        if (inChar == '\r') {
            stringComplete = true;
        }
    }
}


void sendStart() {
    Serial.print("=CYE\r");
    resp_time = millis();

}

void sendStop() {
    Serial.print("=CYD\r");
}

void sendCal() {

}

