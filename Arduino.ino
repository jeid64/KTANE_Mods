void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
}

void loop() // run over and over
{
  if (Serial.available()){
    Serial.write(Serial.read());
    digitalWrite(13, HIGH);
  }
  delay(100);
  digitalWrite(13, LOW);
}
