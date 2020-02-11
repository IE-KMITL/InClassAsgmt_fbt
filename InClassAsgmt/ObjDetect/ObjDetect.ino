const int Sensor=D2;
int inputVal = 0;
void setup() 
{                
  pinMode(Sensor,INPUT);    
  Serial.begin(9600);
}

void loop() 
{  
   if(digitalRead(Sensor)==HIGH)
{

Serial.println("sensor not detected object"" ");
delay(200);    // wait for a second
}
else 
{
Serial.println("sensor detected object");

}
}
//จากการทดลองวัตถุต่างๆ 5 ชนิดได้ผลการทดลองดังต่อไปนี้
// 1.สแตนดี้รูปน้องเตนล์ จับได้ในระยะ 13 ซม.
// 2.กระเป๋าดินสอสีดำ จับได้ในระยะ 5 ซม.
// 3.โพสอิทสีชมพู จับได้ในระยะ 15 ซม.
// 4.กระเป๋าตังสีเขียว จับได้ในระยะ 14 ซม.
// 5.กล่องสำลีสีเขียวอ่อน จับได้ในระยะ 13 ซม.
// สรุปได้ว่า จากการทดลองพบว่าวัตถุอื่นๆจะจับได้ในระยะใกล้กว่า 15 ซม.เพราะกระดาษสีขาวสะท้อนแสงได้ดีกว่า 
