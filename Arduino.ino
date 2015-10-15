byte inputData = 0;

int lastEvent = 0;

const int ButtonPin = 12;
const int ButtonSucessPin = 13;
const int ButtonColorPinR = 11;
const int ButtonColorPinG = 10;
const int ButtonColorPinB = 9;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  
  //initalize pins
  pinMode(ButtonPin, INPUT);     
  pinMode(ButtonColorPinR, OUTPUT);     
  pinMode(ButtonColorPinG, OUTPUT);     
  pinMode(ButtonColorPinB, OUTPUT);     
  pinMode(ButtonSucessPin, OUTPUT);     

}

void loop() {
  //big button pressed
  if(lastEvent!=1 && digitalRead(ButtonPin)==HIGH){
    Serial.println("1button");
    lastEvent = 1;
  }
  //big button depressed
  else if(lastEvent==1 && digitalRead(ButtonPin)==LOW){
    Serial.println("0button");
    lastEvent = 2;
  }
}


/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    inputData = (byte)Serial.read(); 
  }
  
  switch(lastEvent) {
    case 1:
     //light up button's color
     handleColor(inputData);
     break;
    case 2:
     //turn off color led
     analogWrite(ButtonColorPinR, 0);
     analogWrite(ButtonColorPinG, 0);
     analogWrite(ButtonColorPinB, 0); 
     //light up button sucess state
     if(inputData==0){
       digitalWrite(ButtonSucessPin, HIGH);
       delay(1000);
       digitalWrite(ButtonSucessPin, LOW);
     }
     break;
  }
}

void handleColor(byte inputData)
{
  if(inputData==3){
    analogWrite(ButtonColorPinR, 255);
    analogWrite(ButtonColorPinG, 255);
    analogWrite(ButtonColorPinB, 255);  
  }
  else if(inputData==0){
    analogWrite(ButtonColorPinR, 255);
    analogWrite(ButtonColorPinG, 0);
    analogWrite(ButtonColorPinB, 0);  
  }
  else if(inputData==2){
    analogWrite(ButtonColorPinR, 255);
    analogWrite(ButtonColorPinG, 255);
    analogWrite(ButtonColorPinB, 0);  
  }
  else if(inputData==1){
    analogWrite(ButtonColorPinR, 0);
    analogWrite(ButtonColorPinG, 0);
    analogWrite(ButtonColorPinB, 255);  
  }
}
