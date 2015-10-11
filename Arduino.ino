const int buttonPin = 12;     // the number of the pushbutton pin
const int buttonColorPin = 11;
const int buttonStatePin = 2;

const int keypad0 = 10;
const int keypad0Color = 9;
const int keypad1 = 8;
const int keypad1Color = 7;
const int keypad2 = 6;
const int keypad2Color = 5;
const int keypad3 = 4;
const int keypad3Color = 3;


/*const int mazeup = 2;
const int mazeleft = 2;
const int mazeright = 12;
const int mazedown = 11;
const int mazeHitWall = 13;*/

int lastSentType = 0;

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
    
  pinMode(buttonPin, INPUT);     
  pinMode(buttonColorPin, OUTPUT);   
  pinMode(buttonStatePin, OUTPUT);   

  pinMode(keypad0, INPUT);    
  pinMode(keypad0Color, OUTPUT);   
  pinMode(keypad1, INPUT);
  pinMode(keypad1Color, OUTPUT);  
  pinMode(keypad2, INPUT);
  pinMode(keypad2Color, OUTPUT);  
  pinMode(keypad3, INPUT);     
  pinMode(keypad3Color, OUTPUT);  
  
  /*pinMode(mazeup, INPUT);    
  pinMode(mazeleft, INPUT);    
  pinMode(mazeright, INPUT);    
  pinMode(mazedown, INPUT);   
  pinMode(mazeHitWall, OUTPUT);   */
}

void loop() // run over and over
{
  //SEND COMMAND
  
  //buttton module
  if (lastSentType!=1 && digitalRead(buttonPin) == HIGH){
    Serial.println("1button");
    lastSentType=1;
  }else if(lastSentType==1 && digitalRead(buttonPin) == LOW){
    Serial.println("0button");
    lastSentType=2;
  }
  
  //keypad module
  else if(digitalRead(keypad0)==HIGH && lastSentType!=3){
        Serial.println("0keypad");
        lastSentType=3;
  }else if(digitalRead(keypad1)==HIGH && lastSentType!=4){
        Serial.println("1keypad");
        lastSentType=4;
  }else if(digitalRead(keypad2)==HIGH && lastSentType!=5){
        Serial.println("2keypad");
        lastSentType=5;
  }else if(digitalRead(keypad3)==HIGH && lastSentType!=6){
        Serial.println("3keypad");
        lastSentType=6;
  }
  
  /*maze module
  if(digitalRead(mazeup)==HIGH){
        Serial.println("0maze");
        lastSentType=7;
  }else if(digitalRead(mazeleft)==HIGH){
        Serial.println("1maze");
        lastSentType=7;
  }else if(digitalRead(mazeright)==HIGH){
        Serial.println("2maze");
        lastSentType=7;
  }else if(digitalRead(mazedown)==HIGH){
        Serial.println("3maze");
        lastSentType=7;
  }*/
  
  delay(100);
  
  
  //HANDLE RESULT
  if(Serial.available()){
    String result = Serial.readString();
    //button held, set color
    if(lastSentType==1){
      //set color depending on result
      digitalWrite(buttonColorPin, HIGH);
    }
    //button released, set state
    else if(lastSentType==2){
      //button solves
      if(result.equals("True")){
        digitalWrite(buttonStatePin, LOW);
      }else{
        digitalWrite(buttonStatePin, HIGH);
      }
    }
    
    //keypad 0 state
    else if(lastSentType==3){
      if(result.equals("True")){
        digitalWrite(keypad0Color, LOW);
      }else{
        digitalWrite(keypad0Color, HIGH);
      }
    }
    //keypad 1 state
    else if(lastSentType==4){
      if(result.equals("True")){
        digitalWrite(keypad1Color, LOW);
      }else{
        digitalWrite(keypad1Color, HIGH);
      }
    }
    //keypad 2 state
    else if(lastSentType==5){
      if(result.equals("True")){
        digitalWrite(keypad2Color, LOW);
      }else{
        digitalWrite(keypad2Color, HIGH);
      }
    }
    //keypad 3 state
    else if(lastSentType==6){
      if(result.equals("True")){
        digitalWrite(keypad3Color, LOW);
      }else{
        digitalWrite(keypad3Color, HIGH);
      }
    }
    
    /*maze handling
    else if(lastSentType==7){
      if(result.equals("True")){
        digitalWrite(mazeHitWall, HIGH);
      }else{
        digitalWrite(mazeHitWall, LOW);
      }
    }*/
  }
}
