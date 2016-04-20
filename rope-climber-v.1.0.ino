int motorDir1 = 9;
int motorDir2 = 11;
int pwmPin = 5;
bool dir1 = false;
bool dir2 = false;

int voltagePin = A0;

int proximity_sensor1 = 4;
int proximity_sensor2 = 7;

bool manualmode = false;
bool autonomousmode = false;

char received;
 
void serialData() {
     if( Serial.available()) {
       received = Serial.read();
      Serial.print(received);
     } else {
  if(received != 's' || received != 'a' || received != 'd') {
        received = '\0';
  }
     }
}

float calcVoltage() {
  float voltage = 0;
  voltage = analogRead(voltagePin);
  voltage = 3.5 *  voltage * 5.0 / 1024.0 ;
  return voltage;
}

void Dir1() {
    analogWrite(pwmPin, 100);
    digitalWrite(motorDir1, HIGH);
    digitalWrite(motorDir2, LOW);
    dir1 = true;
    dir2 = false;
}

void Dir2() {
    analogWrite(pwmPin, 100);
    digitalWrite(motorDir1, LOW);
    digitalWrite(motorDir2, HIGH);
    dir2 = true;
    dir1 = false;
}

void stop_() {
  digitalWrite(motorDir1,0);
  digitalWrite(motorDir2,0);
  analogWrite(pwmPin,100); 
}

void config_autonomous(){
  manualmode = false;
  autonomousmode = true;
  Dir1();
}

void config_manual(void) {
  manualmode = true;
  autonomousmode = false;
}

void checkEnd(void) {
  /*Check for low proximity sensor reading and change direction of robot*/
  if(!digitalRead(proximity_sensor1)) {
    Dir1();
    Serial.write("Changing direction\r");
  } else if(!digitalRead(proximity_sensor2)) {
    Dir2();
    Serial.write("Changing direction\r");
  }
}

void manualMode() {
    if(received =='a')        Dir1();
    else if(received =='d')   Dir2();
    else if(received =='s')   stop_();    
}

void checkBatteryLevel(void) {
    /*Calculate battery voltage level and transmit*/
    int a = calcVoltage();
    while(a>0) {
      Serial.write(a%10+48);
      a/=10;
    }
    Serial.write("\r");
}

void setup() {
  Serial.begin(38400);
  pinMode(pwmPin, OUTPUT);
  pinMode(motorDir1, OUTPUT);
  pinMode(motorDir2, OUTPUT);  
  pinMode(proximity_sensor1, INPUT);
  pinMode(proximity_sensor2, INPUT);
  
  TCCR1B |= 1 << CS12; /*256 Prescaler for 16MHz clock = 0.625Hz = 1.6 second TIMER_OVERFLOW*/
  TIMSK1 |= 1 << TOIE1; /*Timer overflow interrupt configuration*/
  
  Serial.write("Configuration complete.\r The robot is ready.\r Press m for manual mode or x for autonomous mode.\r Press a or d to move the robot in manual mode.\r Press s to stop.\r");
}

void loop() {   
     serialData();
     switch(received) {
      case 's':
        stop_();
        config_manual();
        Serial.write("STOP command issued.\r");
        break;
      case 'm':
        config_manual();
        Serial.write("Manual mode ON.\r");
        break;
      case 'x':
        Serial.write("Autonomous mode ON.\r");
        config_autonomous();
        break;
     }

     if(manualmode) {
        manualMode();
     }
     else if(autonomousmode) {
        checkEnd();
     }
     delay(1);
}

/*Timer interrupt routine at overflow, i.e. at every 1.6 second*/
ISR(TIMER1_OVF_vect) {
     checkBatteryLevel();
}
