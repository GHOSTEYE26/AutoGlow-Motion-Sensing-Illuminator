# AutoGlow – Motion Sensing Illuminator

An automatic light control system that turns ON the light when **motion is detected** using a PIR sensor. It also detects entry/obstacles using an **IR Obstacle Avoidance Sensor**. The light turns OFF automatically after 10 seconds of no motion.

Built with **Arduino Nano** on a breadboard for a simple and effective smart lighting solution.

![Project Banner](https://github.com/GHOSTEYE26/AutoGlow-Motion-Sensing-Illuminator/blob/main/AutoGlow.jpeg?raw=true)

## ✨ Features

- Motion detection using HC-SR501 PIR Sensor
- Entry/Obstacle detection using IR Obstacle Avoidance Sensor
- Automatic light control (turns ON on motion)
- Auto turn OFF after 10 seconds of inactivity
- Real-time status on Serial Monitor
- Easy to build on breadboard

## 🛠️ Components Used

- Arduino Nano
- HC-SR501 PIR Motion Sensor
- IR Obstacle Avoidance Sensor
- LED (or Relay for actual bulb)
- Breadboard
- Jumper Wires
- 220Ω Resistor (for LED)

## 📌 Circuit Connections

| Component                  | Pin                  | Arduino Nano Pin |
|---------------------------|----------------------|------------------|
| PIR Sensor                | VCC                  | 5V               |
| PIR Sensor                | GND                  | GND              |
| PIR Sensor                | OUT                  | D2               |
| IR Obstacle Sensor        | VCC                  | 5V               |
| IR Obstacle Sensor        | GND                  | GND              |
| IR Obstacle Sensor        | OUT                  | D3               |
| LED (with 220Ω resistor)  | Positive (Anode)     | D4               |
| LED                       | Negative (Cathode)   | GND              |

**Note:** Adjust the potentiometers on the PIR sensor for sensitivity and time delay as needed.


## 📄 Code

```cpp
// Pins
int pirPin = 2;
int irPin = 3;
int lightPin = 4;   // LED or Relay

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
  Serial.println("AutoGlow - Smart Room System Started...");
}

void loop() {

  pirState = digitalRead(pirPin);
  irState = digitalRead(irPin);

  // Entry Detect (IR Sensor)
  if (irState == LOW) {
    Serial.println("Entry Detected by IR Sensor");
  }

  // Motion Detect (PIR Sensor)
  if (pirState == HIGH) {
    Serial.println("Motion Detected by PIR Sensor!");

    digitalWrite(lightPin, HIGH); // Light ON
    lightStatus = true;

    lastMotionTime = millis(); // Update time
  }

  // Auto OFF System
  if (lightStatus == true && (millis() - lastMotionTime > delayTime)) {
    digitalWrite(lightPin, LOW); // Light OFF
    lightStatus = false;

    Serial.println("No motion detected - Light turned OFF");
  }

  delay(200);
}
