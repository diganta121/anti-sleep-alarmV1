//method 1 

int blin=8; //sleep sensor pin
int buzz=12; //buzzer pin
int timeDelay=1000;

  void setup() {
  
  pinMode(blin,INPUT);
  pinMode(buzz,OUTPUT);
}

void loop() {
  if(digitalRead(blin)==HIGH)
  {
    delay(timeDelay);
    
    if(digitalRead(blin)==HIGH)
    {
      digitalWrite(buzz,HIGH);
      
      delay(timeDelay);
    }
  }
  else if(digitalRead(blin)==LOW)
  {
    digitalWrite(buzz,LOW);
  }
  
}
