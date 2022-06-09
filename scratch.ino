#include <Wire.h>
#include <LIDARLite.h>

LIDARLite lidarLite;

int count = 0;
int dist = 0;

int buzzPin = 8;

void setup() {
  Serial.begin(9600);

  lidarLite.begin(0, true);
  lidarLite.configure(0);
  pinMode(buzzPin, OUTPUT);
}

double speed = 500;
double hertz = 4000;

void loop() {
  LIDAR_range();
  while (dist <= 45) {
   hertz = (-50*dist) + 5000;
   speed = (8*dist)+160;
   tone(buzzPin, hertz);
   delay(speed);
   noTone(buzzPin);
   delay(speed);
   LIDAR_range();
  }
}

void LIDAR_range() {
  if(count == 0) {
    dist = lidarLite.distance();
  } else {
    dist = lidarLite.distance(false);
  }
  delay(10);

  count++;
  count %= 100;

  Serial.println(dist);
}
