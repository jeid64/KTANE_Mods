byte inputData = 0;

int lastEvent = 0;

const int ButtonSucessPin = 13;
const int ButtonColorPinR = 11;
const int ButtonColorPinG = 10;
const int ButtonColorPinB = 9;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  
  //initalize pins
  pinMode(ButtonColorPinR, OUTPUT);     
  pinMode(ButtonColorPinG, OUTPUT);     
  pinMode(ButtonColorPinB, OUTPUT);     
  pinMode(ButtonSucessPin, OUTPUT);     
  
  pinMode(A5, INPUT_PULLUP); // sets analog pin for input 
}

void loop() {
  //big button pressed
  int buttonPressed = analogToButton(analogRead(5));
  
  if(lastEvent!=1 && buttonPressed==1){
    Serial.println("1button");
    lastEvent = 1;
  }
  //big button depressed
  else if(lastEvent==1 && buttonPressed==0){
    Serial.println("0button");
    lastEvent = 2;
  }
  
  if(lastEvent!=3 && buttonPressed==2){
    Serial.println("0keypad");
    lastEvent = 3;
  }else if(lastEvent!=4 && buttonPressed==3){
    Serial.println("1keypad");
    lastEvent = 4;
  }else if(lastEvent!=5 && buttonPressed==4){
    Serial.println("2keypad");
    lastEvent = 5;
  }else if(lastEvent!=6 && buttonPressed==5){
    Serial.println("3keypad");
    lastEvent = 6;
  }
}

boolean analogToButton(int analog){
  if(analog>1000){
    return 0;
  }else if(analog<20 && analog>10){
    return 1;
  }else if(analog<170 && analog>130){
    return 2;
  }else if(analog<270 && analog>230){
    return 3;
  }else if(analog<350 && analog>310){
    return 4;
  }else if(analog<410 && analog>370){
    return 5;
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
