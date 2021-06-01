
boolean startCounting = LOW;

void setup()
{
  pinMode(13, OUTPUT); //led working indicator
  pinMode(12, INPUT);  //button
  pinMode(A3,INPUT);  //hall effect analog sensor
  pinMode(2, INPUT);

  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);

}

void loop()
{
  if (digitalRead(12) == HIGH){
    if(startCounting == LOW){
      startCounting = HIGH;
      digitalWrite(13, HIGH);
      int temp = calcRPM();
      Serial.print("RPM: ");
      Serial.println(temp);
      setCustomLeds(temp);
    }
  }
}

int calcRPM(){
  int rotations = 0;
  boolean countFlag = LOW;
  unsigned long startTime = millis();
  unsigned long currentTime = millis();
  unsigned long lastRotation = millis();

  while(currentTime - lastRotation < 5000){ //if more than 5 seconds have passed without a rotation stop the program
      currentTime = millis();
      int sensorRead = analogRead(A3);
      if (digitalRead(2) == HIGH)
      {
        countFlag = HIGH;
      }
      if (digitalRead(2) == LOW && countFlag == HIGH)
      {
        rotations++;
        countFlag=LOW;
        currentTime = millis();
        lastRotation = millis();
      }
      Serial.print("current time: ");
      Serial.print(currentTime);
      Serial.print(", last rotation:");
      Serial.println(lastRotation);
      delay(10);
  }

  int countRpm = int(60000/float(currentTime - startTime))*rotations;
  startCounting = LOW;
  digitalWrite(13, LOW);
  return countRpm;
}


void setCustomLeds(int a){ //set leeds based on RPM
  if(a < 20){
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, HIGH); 
  }
  else if (a >= 20 && a < 60){
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH); 
  }
  else if (a >= 60){
    digitalWrite(6, LOW);
    digitalWrite(4, LOW);
    digitalWrite(7, HIGH); 
  }
}
