#include <AccelStepper.h>
#include <Button.h>
#include <TimerEvent.h>
#include <RotaryEncoder.h>

#define dirPin 4
#define stepPin 7
#define motorInterfaceType 1

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

Button button1 = Button(5);
Button button2 = Button(6);
Button button3 = Button(9);


RotaryEncoder encoder(2, 3, RotaryEncoder::LatchMode::TWO03);


int position = 0;
int speed = 500;
int currentPosition = 0;

int aState;
int aLastState;

boolean updateDisplay = false;

void setup() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  button1.begin();
  button2.begin();
  button3.begin();

  Serial.begin(115200);
  Serial.println(" ------ START ----- ");
  stepper.setMaxSpeed(500);
  stepper.setCurrentPosition(position);
  display.display();
  delay(2000);
  displayText(speed, stepper.currentPosition(), position);
  stepper.setSpeed(500);
  stepper.setAcceleration(5000);


  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  attachInterrupt(digitalPinToInterrupt(2), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), checkPosition, CHANGE);
}

void checkPosition()
{
  encoder.tick(); // just call tick() to check the state.
  int newPos = encoder.getPosition();
  static int pos = 0;
  static int dir = 0;
  if (pos != newPos) {
    Serial.print("pos:");
    Serial.print(newPos);
    Serial.print(" dir:");
    dir = (int)(encoder.getDirection());
    Serial.println(dir);
    pos = newPos;
    switch (dir) {
      case 1: {
          position = position + 10;
          updateDisplay = true;
        }
      case -1: {
          position = position - 10;
          updateDisplay = true;
        }
    }
  } // if

}



void loop() {
  static int pos = 0;

  if (button1.pressed()) {
    position = position + 100;
    updateDisplay = true;
  }
  if (button2.pressed()) {
    position = position - 100;
    updateDisplay = true;
  }
  if (button3.pressed()) {
    digitalWrite(8, LOW);
    stepper.moveTo(position);
    updateDisplay = true;
  }


  if (stepper.distanceToGo() == 0)  {
    digitalWrite(8, HIGH);
    updateDisplay = true;
  }

  if (updateDisplay) {
    displayText(speed, stepper.currentPosition(), position);
    updateDisplay = false;
  }
  stepper.run();
}


void displayText(int speed, int position, int nextpos) {
  display.clearDisplay();
  display.cp437(true);
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.print(F("S: ")); display.print(speed * 0.01, 0); display.println(F("mm/s"));
  display.print(F("Z: ")); display.print(position * 0.01, 1); display.println(F("mm"));
  display.print(F("P: ")); display.print(nextpos * 0.01, 1); display.println(F("mm"));

  display.display();
}
