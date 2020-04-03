#define AIN1 D10 //motor A 
#define AIN2 D9 //motor A 
#define BIN3 D6 //motor B 
#define BIN4 D5 //motor B 

#define lefts D2 //sensorซ้าย
#define rights D11 //sensorขวา
#define backs D4 //sensorหลัง

#define RED 1
#define YELLOW 2
#define BLACK 3
#define NOCOLOR 0
#define maxSpd 255    // motor max speed

#include <HCSR04.h>
HCSR04 hc(D8,D7); //initialisation class HCSR04 (trig,echo);

int analogPin = A6; //ประกาศตัวแปร ให้ analogPin แทนขา analog ขาที่6

int led1 = D13;
int buttonPin = D12;
int val=0;
int old_val=0;
int state=0;

int color=0;
int getColor() {
  int NO_color = analogRead(analogPin);           //อ่านค่าสัญญาณ analog ขา6 ที่ต่อกับ TCRT5000 
  if ((NO_color>1900)&&(NO_color<2200))           //สีเหลือง
    return YELLOW;
  else if ((NO_color>2200)&&(NO_color<2500))      //สีแดง
    return RED;
  else if ((NO_color>3600)&&(NO_color<3900))      //สีดำ
    return BLACK;
  else                                            //ไม่พบสี
    return NOCOLOR;
}

void setup() {
  pinMode(lefts, INPUT);
  pinMode(rights, INPUT);
  pinMode(backs, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(led1, OUTPUT); 
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN3, OUTPUT);
  pinMode(BIN4, OUTPUT);
  Serial.begin(115200);
}

void loop() 
{ 
 color = getColor();
 val = digitalRead(buttonPin);
 if( (val==HIGH) && (old_val==LOW)) 
 {
  state=!state;
 }
 old_val=val;
 if (state==1) //เมื่อกดสวิทซ์ 1 ครั้ง ใช้กลยุทธ์รุก
 {
  digitalWrite(led1, HIGH);
  if((hc.dist()>10)&&((digitalRead(lefts)==HIGH)||(digitalRead(rights)==HIGH))&&(color == NOCOLOR))  // เดินหน้าเมื่อ sensor ด้านหน้า  ด้านข้าง และด้านล่างไม่ทำงาน 
  {
  AForward(maxSpd);
  BForward(maxSpd);
  }
  if((hc.dist()<10)&&(digitalRead(backs)==LOW)&&((digitalRead(lefts)==HIGH)||(digitalRead(rights)==HIGH))&&(color == NOCOLOR))  // break เมื่อ sensor ด้านหน้า ด้านหลังทำงาน แต่ด้านข้างและด้านล่างไม่ทำงาน
  {
  ABreakTime(1000);
  BBreakTime(1000); 
  }
  if((hc.dist()<10)&&(digitalRead(backs)==HIGH)&&((digitalRead(lefts)==LOW)||(digitalRead(rights)==LOW))&&(color == NOCOLOR))   // เดินถอยหลัง 3วิ เมื่อ sensor ด้านหน้าและข้างซ้ายหรือขวาทำงาน แต่ด้านหลังไม่ทำงาน
  {
  ARewardTime(3000);
  BRewardTime(3000);
  }

  if(color == RED)  // เดินกลับรถ เมื่อ sensor ด้านล่างตรวจจับเส้นสีแดงได้
  {
  AForwardTime(5000);
  BRewardTime(5000);
  }

  if(color == YELLOW)  // รถหยุด เมื่อ sensor ด้านล่างตรวจจับเส้นสีเหลืองได้
  {
  AStop();
  BStop();
  }
 }
 else
 {
  digitalWrite (led1,LOW);
  if((hc.dist()>5)&&((digitalRead(lefts)==HIGH)||(digitalRead(rights)==HIGH))&&(color == NOCOLOR))  // ถอยหลังเมื่อ sensor ด้านหน้า ด้านข้าง และด้านล่าง ไม่ทำงาน
  {
  AReward(maxSpd);
  BReward(maxSpd);
  }

  if((hc.dist()<5)&&((digitalRead(lefts)==HIGH)||(digitalRead(rights)==HIGH))&&(color == NOCOLOR)) // เดินหน้าเมื่อ sensor ด้านหน้าทำงาน แต่ด้านข้างและล่างไม่ทำงาน
  {
  AForwardTime(3000);
  BForwardTime(3000);
  }
  
  if((digitalRead(lefts)==LOW)||(digitalRead(rights)==LOW)&&(color == NOCOLOR))  // เบรค เมื่อ sensor ด้านข้างซ้ายหรือขวาทำงาน แต่ล่างไม่ทำงาน
  {
  ABreakTime(1000);
  BBreakTime(1000); 
  } 
    
  if(color == BLACK)  // กลับรถ เมื่อ sensor ด้านล่างตรวจจับเส้นสีดำได้
  {
  AForwardTime(5000);
  BRewardTime(5000);
  }
  
  }
  delay(20);
       
}

void AStop()
{
  digitalWrite(AIN1, LOW);   // motor stop
  digitalWrite(AIN2, LOW);    
}

void ABreak()
{
  digitalWrite(AIN1, HIGH);   // motor break
  digitalWrite(AIN2, HIGH);    
}

void BStop()
{
  digitalWrite(BIN3, LOW);   // motor stop
  digitalWrite(BIN4, LOW);    
}

void BBreak()
{
  digitalWrite(BIN3, HIGH);   // motor break
  digitalWrite(BIN4, HIGH);    
}

void AForward(int speed)
{
  digitalWrite(AIN2, LOW);   
  analogWrite(AIN1, speed);   
}

void BForward(int speed)
{
  digitalWrite(BIN4, LOW);   
  analogWrite(BIN3, speed);   
}

void AReward(int speed)
{
  digitalWrite(AIN1, LOW);   
  analogWrite(AIN2, speed);   
}

void BReward(int speed)
{
  digitalWrite(BIN3, LOW);   
  analogWrite(BIN4, speed);   
}

void ARewardTime(int time)
{
  digitalWrite(AIN1, LOW);   
  analogWrite(AIN2, maxSpd);
  delay (time);   
}

void BRewardTime(int time)
{
  digitalWrite(BIN3, LOW);   
  analogWrite(BIN4, maxSpd);
  delay (time);    
}

void AForwardTime(int time)
{
  digitalWrite(AIN2, LOW);   
  analogWrite(AIN1, maxSpd);
  delay (time);    
}

void BForwardTime(int time)
{
  digitalWrite(BIN4, LOW);   
  analogWrite(BIN3, maxSpd);
  delay (time);    
}

void ABreakTime(int time)
{
  digitalWrite(AIN1, HIGH);   
  digitalWrite(AIN2, HIGH);
  delay (time);    
}

void BBreakTime(int time)
{
  digitalWrite(BIN3, HIGH);   
  digitalWrite(BIN4, HIGH);
  delay (time);
      
}
