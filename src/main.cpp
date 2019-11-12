#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define analogue inputs
int pot1_PIN = A0; // pot1
int pot2_PIN = A1; // pot 2
int j1x_PIN = A2; // j1
int j1y_PIN = A3;
int j2x_PIN = A4; // j2
int j2y_PIN = A5;

// Define digital inputs
#define j1b_PIN 6 // Joystick button 1
#define j2b_PIN 5 // Joystick button 2
#define t1_PIN 2 // Toggle switch 1
#define t2_PIN 3 // Toggle switch 1
#define pb1_PIN 1 // Push button 1
#define pb2_PIN 0 // Push button 2
#define pb3_PIN 4 // Push button 3
#define pb4_PIN 9 // Push button 4

// Define data struct for transmitting
// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package
{
  byte j1x_VAL;
  byte j1y_VAL;
  byte j1b_VAL;
  byte j2x_VAL;
  byte j2y_VAL;
  byte j2b_VAL;
  byte pot1_VAL;
  byte pot2_VAL;
  byte t1_VAL;
  byte t2_VAL;
  byte pb1_VAL;
  byte pb2_VAL;
  byte pb3_VAL;
  byte pb4_VAL;
};

Data_Package data; // Create a variable with the above structure

// Define RF
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup()
{
  //Serial.begin(9600);

  // Define radio communication
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);

  // Activate the Arduino internal pull-up resistors
  pinMode(t1_PIN, INPUT_PULLUP);
  pinMode(t2_PIN, INPUT_PULLUP);
  pinMode(j1b_PIN, INPUT_PULLUP);
  pinMode(j2b_PIN, INPUT_PULLUP);
  pinMode(pb1_PIN, INPUT_PULLUP);
  pinMode(pb2_PIN, INPUT_PULLUP);
  pinMode(pb3_PIN, INPUT_PULLUP);
  pinMode(pb4_PIN, INPUT_PULLUP);

  // Set initial default values
  data.j1x_VAL = 127;
  data.j1y_VAL = 127;
  data.j2x_VAL = 127;
  data.j2y_VAL = 127;
  data.j1b_VAL = 1;
  data.j2b_VAL = 1;
  data.pot1_VAL = 0;
  data.pot2_VAL = 0;
  data.t1_VAL = 0;
  data.t2_VAL = 0;
  data.pb1_VAL = 0;
  data.pb2_VAL = 0;
  data.pb3_VAL = 0;
  data.pb4_VAL = 0;
}

void loop()
{
  // Read all analog inputs from 0 to 1023 into a Byte value from 0 to 255
  data.j1x_VAL = map(analogRead(j1x_PIN), 0, 1023, 0, 255);
  data.j1y_VAL = map(analogRead(j1y_PIN), 0, 1023, 0, 255);
  data.j2x_VAL = map(analogRead(j2x_PIN), 0, 1023, 0, 255);
  data.j2y_VAL = map(analogRead(j2y_PIN), 0, 1023, 0, 255);
  data.pot1_VAL = map(analogRead(pot1_PIN), 0, 1023, 0, 255);
  data.pot2_VAL = map(analogRead(pot2_PIN), 0, 1023, 0, 255);

  // Read all digital inputs
  data.j1b_VAL = digitalRead(j1b_PIN);
  data.j2b_VAL = digitalRead(j2b_PIN);
  data.t1_VAL = digitalRead(t1_PIN);
  data.t2_VAL = digitalRead(t2_PIN);
  data.pb1_VAL = digitalRead(pb1_PIN);
  data.pb2_VAL = digitalRead(pb2_PIN);
  data.pb3_VAL = digitalRead(pb3_PIN);
  data.pb4_VAL = digitalRead(pb4_PIN);

  // Send data from the structure to the receiver
  radio.write(&data, sizeof(Data_Package));
  /*
  Serial.print(data.j1x_VAL);
  Serial.print("; ");
  Serial.print(data.j1y_VAL);
  Serial.print("; ");
  Serial.print(data.j1b_VAL);
  Serial.print("; ");
  Serial.print(data.j2x_VAL);
  Serial.print("; ");
  Serial.print(data.j2y_VAL);
  Serial.print("; ");
  Serial.print(data.j2b_VAL);
  Serial.print("; ");
  Serial.print(data.pot1_VAL);
  Serial.print("; ");
  Serial.print(data.pot2_VAL);
  Serial.print("; ");
  Serial.print(data.t1_VAL);
  Serial.print("; ");
  Serial.print(data.t2_VAL);
  Serial.print("; ");
  Serial.print(data.pb1_VAL);
  Serial.print("; ");
  Serial.print(data.pb2_VAL);
  Serial.print("; ");
  Serial.print(data.pb3_VAL);
  Serial.print("; ");
  Serial.println(data.pb4_VAL);
  */
}