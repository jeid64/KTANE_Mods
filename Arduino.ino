byte inputData = 0;

int lastEvent = 0;

const int ButtonSucessPin = 13;
const int ButtonColorPinR = 11;
const int ButtonColorPinG = 10;
const int ButtonColorPinB = 9;

unsigned int keypadsValid = 0;
const int KeypadDataPin = 12;
const int KeypadClockPin = 8;

const int MazeResultPin = 5;

unsigned int curFreq = 0;
const int FreqDataPin = 4;
const int FreqClockPin = 3;
const int MorseLedPin = 7;
const int MorseResultPin = 6;

void setup() {
  // initialize serial:
  Serial.begin(9600);

  //initalize pins
  pinMode(ButtonColorPinR, OUTPUT);     
  pinMode(ButtonColorPinG, OUTPUT);     
  pinMode(ButtonColorPinB, OUTPUT);     
  pinMode(ButtonSucessPin, OUTPUT);     

  pinMode(KeypadDataPin, OUTPUT);     
  pinMode(KeypadClockPin, OUTPUT);   

  pinMode(MazeResultPin, OUTPUT);     

  pinMode(FreqDataPin, OUTPUT);     
  pinMode(FreqClockPin, OUTPUT); 
  pinMode(MorseLedPin, OUTPUT); 
  pinMode(MorseResultPin, OUTPUT); 

  pinMode(A5, INPUT_PULLUP); // sets analog pin for input 
  
  //set to 0
  shiftOut(FreqDataPin, FreqClockPin, MSBFIRST, curFreq); 
  shiftOut(KeypadDataPin, KeypadClockPin, MSBFIRST, keypadsValid);   
}

void loop() {
  //big button pressed
  int buttonPressed = analogToButton();
  delay(50);
  int buttonPressedCheck = analogToButton();
  //check to prevent noise, because fuck setting up shift registers
  if(buttonPressed == buttonPressedCheck){
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
    }
    else if(lastEvent!=4 && buttonPressed==3){
      Serial.println("1keypad");
      lastEvent = 4;
    }
    else if(lastEvent!=5 && buttonPressed==4){
      Serial.println("2keypad");
      lastEvent = 5;
    }
    else if(lastEvent!=6 && buttonPressed==5){
      Serial.println("3keypad");
      lastEvent = 6;
    }

    if(lastEvent!=7 && buttonPressed==6){
      Serial.println("1maze");
      lastEvent = 7;
    }
    else if(lastEvent!=8 && buttonPressed==7){
      Serial.println("3maze");
      lastEvent = 8;
    }
    else if(lastEvent!=9 && buttonPressed==8){
      Serial.println("2maze");
      lastEvent = 9;
    }
    else if(lastEvent!=10 && buttonPressed==9){
      Serial.println("0maze");
      lastEvent = 10;
    }
    //allow buttons to be pressed in a row
    else if((lastEvent==7 || lastEvent==8 || lastEvent==9 || lastEvent==10 || lastEvent==11 || lastEvent==12) && buttonPressed==0){
      lastEvent=0;
    }

    else if(lastEvent!=11 && buttonPressed==10){
      Serial.print(curFreq);
      Serial.println("transmit");
      lastEvent = 11;
    }
    else if(lastEvent!=12 && buttonPressed==11){
      curFreq++;
      if(curFreq==16){
        curFreq = 0;
      }

      shiftOut(FreqDataPin, FreqClockPin, MSBFIRST, curFreq);  

      lastEvent = 12;
    }
  }
}

int analogToButton(){
  int analog = analogRead(5);
  for (int i=0; i < 4; i++)
  {
    analog += analogRead(5);
  }
  analog = analog / 5;

  if(analog>1000){
    return 0;
  }
  else if(analog<20 && analog>10){
    return 1;
  }
  else if(analog<170 && analog>130){
    return 2;
  }
  else if(analog<270 && analog>230){
    return 3;
  }
  else if(analog<350 && analog>310){
    return 4;
  }
  else if(analog<410 && analog>370){
    return 5;
  }
  else if(analog<450 && analog>410){
    return 6;
  }
  else if(analog<490 && analog>450){
    return 7;
  }
  else if(analog<530 && analog>490){
    return 8;
  }
  else if(analog<555 && analog>530){
    return 9;
  }
  else if(analog<570 && analog>555){
    return 10;
  }
  else if(analog<580 && analog>570){
    return 11;
  }
  else{
    return 0;
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
  
  if(inputData==255){
    digitalWrite(MorseLedPin, HIGH);
  }
  else if(inputData==254){
     digitalWrite(MorseLedPin, LOW);
  }
  else{
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
    case 3:
      if(inputData==1){
        keypadsValid += 8;
        shiftOut(KeypadDataPin, KeypadClockPin, MSBFIRST, keypadsValid);   
      }
      break;
    case 4:
      if(inputData==1){
        keypadsValid += 4;
        shiftOut(KeypadDataPin, KeypadClockPin, MSBFIRST, keypadsValid);   
      }
      break;
    case 5:
      if(inputData==1){
        keypadsValid += 2;
        shiftOut(KeypadDataPin, KeypadClockPin, MSBFIRST, keypadsValid);   
      }
      break;
    case 6:
      if(inputData==1){
        keypadsValid += 1;
        shiftOut(KeypadDataPin, KeypadClockPin, MSBFIRST, keypadsValid);   
      }
      break;
    case 7:
    case 8:
    case 9:
    case 10:
      if(inputData==1){
        digitalWrite(MazeResultPin, HIGH);
        delay(1000);
        digitalWrite(MazeResultPin, LOW);
      }
      break;
    case 11:
      if(inputData==0){
        digitalWrite(MorseResultPin, HIGH);
        delay(1000);
        digitalWrite(MorseResultPin, LOW);
      }
      break; 
    }
  }
}

void handleColor(byte inputData)
{
  //white
  if(inputData==3){
    analogWrite(ButtonColorPinR, 255);
    analogWrite(ButtonColorPinG, 255);
    analogWrite(ButtonColorPinB, 255);  
  }
  //red
  else if(inputData==0){
    analogWrite(ButtonColorPinR, 255);
    analogWrite(ButtonColorPinG, 0);
    analogWrite(ButtonColorPinB, 0);  
  }
  //yellow
  else if(inputData==2){
    analogWrite(ButtonColorPinR, 255);
    analogWrite(ButtonColorPinG, 120);
    analogWrite(ButtonColorPinB, 0);  
  }
  //blue
  else if(inputData==1){
    analogWrite(ButtonColorPinR, 0);
    analogWrite(ButtonColorPinG, 0);
    analogWrite(ButtonColorPinB, 255);  
  }
  //color(75,75,0); // turn the RGB LED green  
}
