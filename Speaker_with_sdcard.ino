// #include "DFRobotDFPlayerMini.h"
// #include "HardwareSerial.h"

// HardwareSerial mp3Serial(2); // UART2
// DFRobotDFPlayerMini mp3;

// void setup() {
//   Serial.begin(115200);

//   // ESP32 UART2
//   mp3Serial.begin(9600, SERIAL_8N1, 16, 17); // RX, TX

//   if (!mp3.begin(mp3Serial)) {
//     Serial.println("MP3 Module not detected");
//     while (true);
//   }

//   Serial.println("MP3 Module Ready");

//   mp3.volume(25);    // Volume: 0–30
//   delay(1000);

//   mp3.play(1);       // Plays 0001.mp3
// }

// void loop() {
//   // nothing needed
// }









// #include "DFRobotDFPlayerMini.h"
// #include "HardwareSerial.h"

// HardwareSerial mp3Serial(2);
// DFRobotDFPlayerMini mp3;

// void setup() {
//   Serial.begin(115200);
//   delay(2000);

//   mp3Serial.begin(9600, SERIAL_8N1, 16, 17); // RX, TX

//   Serial.println("Checking MP3 module...");

//   if (!mp3.begin(mp3Serial)) {
//     Serial.println("❌ MP3 Module NOT detected");
//     while (true);
//   }

//   Serial.println("✅ MP3 Module detected");

//   mp3.volume(20);
//   delay(1000);
//   mp3.play(1);
// }

// void loop() {
// }



// #include "DFRobotDFPlayerMini.h"
// #include "HardwareSerial.h"

// HardwareSerial mp3Serial(2);   // Use UART2
// DFRobotDFPlayerMini mp3;

// void setup() {
//   Serial.begin(115200);
//   delay(2000);   // Allow ESP32 to stabilize

//   // UART2 -> RX2 = GPIO16, TX2 = GPIO17
//   mp3Serial.begin(9600, SERIAL_8N1, 16, 17);

//   Serial.println("Initializing MP3 module...");

//   if (!mp3.begin(mp3Serial)) {
//     Serial.println("❌ MP3 Module not detected");
//     while (true);   // Stop here if module not found
//   }

//   Serial.println("✅ MP3 Module detected");

//   mp3.volume(100);        // MAX volume (0–30)
//   mp3.EQ(DFPLAYER_EQ_NORMAL);
//   mp3.outputDevice(DFPLAYER_DEVICE_SD);

//   delay(1000);
//   mp3.play(1);           // Plays 0001.mp3
// }

// void loop() {
//   // Nothing needed
// }







#include "DFRobotDFPlayerMini.h"
#include "HardwareSerial.h"

HardwareSerial mp3Serial(2);
DFRobotDFPlayerMini mp3;

bool trackFinished = false;
int currentTrack = 1;
int totalTracks = 3;

void setup() {
  Serial.begin(115200);
  delay(2000);

  mp3Serial.begin(9600, SERIAL_8N1, 16, 17);

  if (!mp3.begin(mp3Serial)) {
    Serial.println("MP3 NOT detected");
    while (true);
  }

  Serial.println("MP3 Ready");

  mp3.volume(30);
  mp3.play(currentTrack);
}

void loop() {
  if (mp3.available()) {
    uint8_t type = mp3.readType();
    int value = mp3.read();

    // Track finished event
    if (type == DFPlayerPlayFinished) {
      Serial.print("Track finished: ");
      Serial.println(value);

      currentTrack++;

      if (currentTrack <= totalTracks) {
        mp3.play(currentTrack);
      }
    }
  }
}
