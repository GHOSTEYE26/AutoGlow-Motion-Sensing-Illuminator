// Pins
int pirPin = 2;
int irPin = 3;
int lightPin = 4;   // LED ya Relay

// Variables
int pirState = 0;
int irState = 0;

unsigned long lastMotionTime = 0;
unsigned long delayTime = 10000; // 10 seconds auto OFF

bool lightStatus = false;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(irPin, INPUT);
  pinMode(lightPin, OUTPUT);

  digitalWrite(lightPin, LOW);

  Serial.begin(9600);
  Serial.println("Smart Room System Started...");
}

void loop() {

  pirState = digitalRead(pirPin);
  irState = digitalRead(irPin);

  // 👉 ENTRY DETECT (IR)
  if (irState == LOW) {
    Serial.println("Entry Detected by IR");
  }

  // 👉 MOTION DETECT (PIR)
  if (pirState == HIGH) {
    Serial.println("Motion Detected!");

    digitalWrite(lightPin, HIGH); // Light ON
    lightStatus = true;

    lastMotionTime = millis(); // time save
  }

  // 👉 AUTO OFF SYSTEM
  if (lightStatus == true && (millis() - lastMotionTime > delayTime)) {
    digitalWrite(lightPin, LOW); // Light OFF
    lightStatus = false;

    Serial.println("No motion - Light OFF");
  }

  delay(200);
}