#include <Arduino.h>

#include <SoftwareSerial.h>

SoftwareSerial SerialEsp(2,3);

int delay_interval = 200;

int satisfied_button = 8;
int very_satisfied_button = 9;
int less_satisfied_button = 10;

int satisfied = 0;
int very_satisfied = 0;
int less_satisfied = 0;

int satisfied_status = 0;
int very_satisfied_status = 0;
int less_satisfied_status = 0;

void sf() {
  if(satisfied != satisfied_status && satisfied == 1) {
    SerialEsp.print("satisfied");
    Serial.print("satisfied");

    delay(delay_interval);
  }

  satisfied_status = satisfied;
}

void very_sf() {
  if(very_satisfied != very_satisfied_status && very_satisfied == 1) {
    SerialEsp.print("very_satisfied");
    Serial.print("very_satisfied");

    delay(delay_interval);
  }

  very_satisfied_status = very_satisfied;
}

void less_sf() {
  if(less_satisfied != less_satisfied_status && less_satisfied == 1) {
    SerialEsp.print("less_satisfied");
    Serial.print("less_satisfied");

    delay(delay_interval);
  }

  less_satisfied_status = less_satisfied;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialEsp.begin(9600);

  pinMode(satisfied_button, INPUT_PULLUP);
  pinMode(very_satisfied_button, INPUT_PULLUP);
  pinMode(less_satisfied_button, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  satisfied = digitalRead(satisfied_button);
  very_satisfied = digitalRead(very_satisfied_button);
  less_satisfied = digitalRead(less_satisfied_button);

  sf();
  very_sf();
  less_sf();

}

