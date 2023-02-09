#define buzzer 7
static const int sensorPin = 10;                    // sensor input pin 
int SensorStatePrevious = LOW;                      // previousstate of the sensor

unsigned long minSensorDuration = 3000; // Time we wait before  the sensor active as long 
unsigned long minSensorDuration2 = 6000;
unsigned long SensorLongMillis;                // Time in ms when the sensor was active
bool SensorStateLongTime = false;                  // True if it is a long active

const int intervalSensor = 50;                      // Time between two readings sensor state
unsigned long previousSensorMillis;                 // Timestamp of the latest reading

unsigned long SensorOutDuration;                  // Time the sensor is active in ms

//// GENERAL ////

unsigned long currentMillis;          // Variabele to store the number of milleseconds since the Arduino has started

void setup() {
  Serial.begin(9600);                 // Initialise the serial monitor

  pinMode(sensorPin, INPUT);          // set sensorPin as input
  Serial.println("STARTED");
  pinMode(buzzer,OUTPUT);
}

void loop() {

  currentMillis = millis();    // store the current time
  // read the sensor state

  
  // If the difference in time between the previous reading is larger than intervalsensor
  if(currentMillis - previousSensorMillis > intervalSensor) {
    
    // Read the digital value of the sensor (LOW/HIGH)
    int SensorState = digitalRead(sensorPin);    

    // If the EYE has been active AND
    // If the sensor wasn't activated before AND
    // IF there was not already a measurement running to determine how long the sensor has been activated
      if (SensorState == HIGH && SensorStatePrevious == LOW && !SensorStateLongTime) {
     SensorLongMillis = currentMillis;
       SensorStatePrevious = HIGH;
      
      Serial.println("EYE CLOSED");
    }

    // Calculate how long the sensor has been activated
   SensorOutDuration = currentMillis - SensorLongMillis;

    // If the EYE is active AND
    // If there is no measurement running to determine how long the sensor is active AND
    // If the time the sensor has been activated is larger or equal to the time needed for a long active
    if (SensorState == HIGH && !SensorStateLongTime && SensorOutDuration >= minSensorDuration) {
      SensorStateLongTime = true;
      Serial.println(" LONG EYE CLOSE ");
      digitalWrite(LED_BUILTIN,HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN,LOW);
      delay(70);
      digitalWrite(LED_BUILTIN,HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN,LOW);      
    }
    if (SensorState == HIGH && SensorStateLongTime && SensorOutDuration >= minSensorDuration2) {
     SensorStateLongTime = false;
      digitalWrite(LED_BUILTIN,HIGH);
      digitalWrite(buzzer,HIGH);
      Serial.println("SLEEPING!!!!!!");
    }    
    // If the sensor is OPEN AND
    // If the sensor was activated before
    if (SensorState == LOW && SensorStatePrevious == HIGH) {
      SensorStatePrevious = LOW;
      SensorStateLongTime = false;
      digitalWrite(buzzer,LOW);
      digitalWrite(LED_BUILTIN,LOW);      
      Serial.println("EYE OPEN");

    }
    
    // store the current timestamp in previousSensorMillis
   previousSensorMillis = currentMillis;

  }
  
}
