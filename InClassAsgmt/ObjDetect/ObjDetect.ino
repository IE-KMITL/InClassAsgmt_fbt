int led1 = LED_BUILTIN;
int buttonPin = D2;
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
  digitalWrite(led1,LOW);
}
  else 
{
  digitalWrite(led1,HIGH);
}
}
