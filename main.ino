
/*
   When Porsche pin A2 is HIGH (Home switch is on we will determine if it's day or night.
   If it's night, turn off the foglights and ON the headlights adn sidemarkers.
   If It's day for more than 30 seconds, turn ON the foglights and OFF the headlights and sidemarkers.

   Lights work normally in any other switch position and 'Home' feature still works as well.
*/


const int lightSensor = 0; // the cds cell is connected to analog pin 0
const int homePin = 1; // Wired to Porsche A2
const int dayPin = 2;  // HIGH when day
const int nightPin = 3; // HIGH when night
const int wiperSensor = 4; // Reading if the wipers are in Auto mode
const int wiperPin = 5; // HIGH when in Auto mode

// TODO figure out the right value for threshold to be day or night. This might be ass backwards.
const int lightSensorThreshold = 100;  // threshold value to decide when the detected light is day or night

const int lastStateCountThreshold = 30; // seconds to be day before changing state

int lastState = 0; // 0 = day, 1 = night;
int lastStateCount = 0; // seconds since last state change

void setup() {
  pinMode( lightSensor, INPUT);
  pinMode( wiperSensor, INPUT);
  pinMode( homePin, INPUT );
  pinMode( dayPin, OUTPUT);
  pinMode( nightPin, OUTPUT);
  pinMode( wiperPin, OUTPUT );
 
  digitalWrite(dayPin, LOW);
  digitalWrite(nightPin, LOW);
  digitalWrite(wiperPin, LOW);
}

void autoWipers() {
  delay ( 5000 );
    if ( digitalRead(wiperSensor ) == HIGH ) {
      digitalWrite( wiperPin, HIGH );
    }  
}

void loop() {
  if ( digitalRead(homePin) == HIGH ) { // Switch is turned to Home position
    if ( analogRead( lightSensor ) >= lightSensorThreshold ) { // It's daytime
      if ( lastState == 0 ) {  // Still daytime to increment the counter.
        lastStateCount++;
      }
      else { // First daytime state, reset counter
        lastStateCount = 0;
        lastState = 1;
      }
      if ( lastStateCount >= lastStateCountThreshold ) { // is has been daytime for 30 continuous seconds
        digitalWrite( dayPin, HIGH );
        digitalWrite( nightPin, LOW );
      }
    }

    else { // It's night time
      lastState = 1;
      digitalWrite( dayPin, LOW );
      digitalWrite( nightPin, HIGH );
    }
  }
  else {
    digitalWrite( dayPin, LOW );
    digitalWrite( nightPin, LOW );
    lastStateCount = 0;
  }
  delay(1000);
}   
