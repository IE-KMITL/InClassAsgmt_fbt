int led1 = D5;
int buttonPin = D8;
int buttonState = 0;

void setup() 
{
  pinMode(led1,OUTPUT);
  pinMode(buttonPin,INPUT);
}

void loop() 
{
  buttonState = digitalRead(buttonPin);
  if (buttonState==HIGH) 

{
  digitalWrite(led1,HIGH);
}
  else 
{
  digitalWrite(led1,LOW);
}
}
