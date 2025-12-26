#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define FLAME_PIN 25   // D25
#define LED_PIN   26   // D26

HardwareSerial mp3Serial(2);
DFRobotDFPlayerMini mp3;

bool fireDetected = false;

void setup() {
  Serial.begin(115200);

  pinMode(FLAME_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  mp3Serial.begin(9600, SERIAL_8N1, 16, 17);

  if (!mp3.begin(mp3Serial)) {
    Serial.println("❌ MP3 not detected");
    while (true);
  }

  mp3.volume(25);
  Serial.println("🔥 Fire system ready");
}

void loop() {
  int flame = digitalRead(FLAME_PIN);

  if (flame == LOW && !fireDetected) {
    fireDetected = true;

    Serial.println("🔥 Fire detected!");
    digitalWrite(LED_PIN, HIGH);
    mp3.play(2);

    delay(5000); // allow audio to finish
  }

  if (flame == HIGH) {
    fireDetected = false;
    digitalWrite(LED_PIN, LOW);
  }
}
