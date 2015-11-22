#define IR1 4
#define IR2 8 
#define WATER_SENSOR 6
#define RELAY 2

//initialize values 
String sensorValue = "";
float counter = 0;
int millis1 = 0;
int millis2 = 0;
int diff = 0;
String directions ="";
bool intime = false;
String command ="nothing";
void setup() {
  // initialize pins to the sensors
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(WATER_SENSOR, INPUT);
  pinMode(RELAY, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //checking for status of states
  if(state1()==true){
    millis1 = millis();
  }
  if(state2()==true){
    millis2 = millis();
  }
   diff = (millis1 - millis2);
  if (diff>0){
    directions="rtol";
  }
  else if(diff<0){
    directions="ltor";
  }
  if(diff = 0){
    directions="nomove";
  }
  if (abs(diff)<2000){
    intime=true;
  }
  else{
    intime=false;
  }
  if ((directions=="rtol")&&(intime)){
    command="moving left";
  }
  else if ((directions=="ltor")&&(intime)){
    command="moving right";
  }
  //debugging purposes
  //Serial.println(millis1);
  //Serial.println(millis2);
  //Serial.println(diff);
  Serial.println(command);
  
  
  sensorValue = isExposedToWater();
  
  if ((sensorValue == "nothing")&&(command=="moving right")) {
    digitalWrite(RELAY, HIGH);
  }
  else {
    digitalWrite(RELAY, LOW);
  }
  delay(50);
}

// return true or false for different modes of the sensors
bool state1(){
  if(digitalRead(IR1)==LOW){
    return true;
  }
  else{
    return false;
  }
}
bool state2(){
  if(digitalRead(IR2)==LOW){
    return true;
  }
  else{
    return false;
  }
}
String isExposedToWater()
{
  if (digitalRead(WATER_SENSOR) == LOW)
    return "Water";
  else return "nothing";
}


