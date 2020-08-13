// This code is made by Charles Projects

// First, you will need library of pitches
#include "pitches.h"

/* Second, you should create an array for melody notes and their durations,
but the array of the melody notes and durations HAVE TO have the same size.
*/


// The definition of the melody array 
int melody[] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4,
NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4,
NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4,
NOTE_D4, NOTE_D4, NOTE_C4,
NOTE_G4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4,
NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4,
NOTE_C4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_F4,
NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4,
NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4,
NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4,
NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4,
NOTE_D4, NOTE_D4, NOTE_C4};

// For note duration, I used 2, 4, 8. They mean half-note, quarter-note, and 8th note, respectively.
int durations[] = {4, 4, 4, 4, 8, 8, 8, 8, 2, 4, 4, 4, 4, 4, 4, 2, 4, 8, 8, 4, 4, 4, 8, 8, 2, 8, 4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 2, 4, 4, 4, 4, 8, 8, 8, 8, 2, 4, 4, 4, 4, 4, 4, 1};

// The loop iteration is used to obtain the arrays' length.
int songLength = sizeof(melody)/sizeof(melody[0]);

// The definitions of the echo and trig pins in Arduino Nano
int echoPin = 11;
int trigPin = 12;

long durationus; //durationus mean "Duration for Ultrasonic Sensor"
int distance;

void setup() {
  for (int i = 2; i <= 7; i++) {
    pinMode (i, OUTPUT);
  }
  
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT); 
  
}

void loop() {
  // Orders the Ultrasonic Sensor to measure distance and reads the measured data
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durationus = pulseIn(echoPin, HIGH);
  distance = (durationus * .0343) / 2;

  // This condition is to determine an object with a distance of 15 centimeters.
  if (distance > 0 && distance <= 15) {ledmelodytimer();}
    
}

void ledmelodytimer() {
  // This is for all LEDs except Red.
  for (int i = 7; i >= 3; i--) {
    digitalWrite (i, HIGH);
    Serial.print(i);
    
    for (int di = (7-i)*9; di <= (8-i)*9-1; di++) {
      int duration = 1000 / durations[di];
      tone(8, melody[di], duration);
      Serial.print(di);
      
      // This is for pausing between notes.
      int pause = duration * 30/18;
      delay(pause);
      
      // This is for stopping the notes.
      noTone(8);
    }
    
  }
  
  // Turns off all other LEDs except Red
  for (int i = 3; i <= 7; i++) {
      digitalWrite (i, LOW);
  }
  
  
  // This is for Red LED. All other LEDs are turned off.
  digitalWrite (2, HIGH);
  
  for (int di = 45; di <= 52; di++) {
    int duration = 1000 / durations[di];
    tone(8, melody[di], duration);
    Serial.print(di);
    
    // This is for pausing between notes.
    int pause = duration * 30/18;
    delay(pause);
    
    // This is for stopping the notes.
    noTone(8);
  }
  
  // Turns off the Red LED
  digitalWrite (2, LOW);
}
