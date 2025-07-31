#include "DFRobotDFPlayerMini.h"
//#include <SoftwareSerial.h> // You're no longer using it.

DFRobotDFPlayerMini myDFPlayer;
#define RXD2 16
#define TXD2 17
// void printDetail(uint8_t type, int value);
// I usually find that function and and its lengthy definition
// superfluous. Replace both later if you want.

void setup()
{
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.begin(115200);
  delay(200); // My preference for print stability
  

  // if (!myDFPlayer.begin(Serial1, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
  // What was your source of that? I've removed the test entirely for
  // now, assuming your priority is getting it working.

  if (!myDFPlayer.begin(Serial2)) {// Start communication with DFPlayer
  // myDFPlayer.begin(Serial1, true, false); // Start communication with DFPlayer
    Serial.println("ERROR");
  }

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  delay(1000); // Add this to allow player to fully initialise

  myDFPlayer.volume(15);  //Set volume value. From 0 to 30

  Serial.println("setup ended"); // I like this reassurance
}

void loop()
{
  //  myDFPlayer.play(001); // Ensure that your files have been renamed to 001, 002, etc.
  Serial.println(1);
  myDFPlayer.play(0001);
  // Note: the 'name' is irrelevant to the module (but not to you,
  // of course). That command plays the first file that was copied
  // or moved to the uSD;  chronologically. Could be called
  // anything.

  delay(5000); // If you actually want to hear anything each time
  // through the loop! To hear entire tracks...another discussion.
  Serial.println(2);
  myDFPlayer.play(0002);
  delay(5000);
}
