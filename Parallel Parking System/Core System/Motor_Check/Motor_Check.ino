#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

#define CW  0
#define CCW 1
#define MOTOR_A 0

const byte PWMA = 3;  // PWM control (speed) for motor A
const byte DIRA = 12; // Direction control for motor A


void setup() 
{
 setupArdumoto();
}

void loop() 
{
 showPWM_and_IncreasePWM();
 }


void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  /*else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }*/
  else 
  {   
  }
}   


void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  
  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(DIRA, LOW);
}

void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}

/**/ 
void pwmJump()
{
 driveArdumoto(MOTOR_A, CCW, 140);
 delay(500); 
}

/**/
void showPWM_and_IncreasePWM()
{ 
  byte valuePWM;
  pwmJump();
  /*more calibration*/    
  //for (valuePWM = 100; valuePWM <= 255; valuePWM++)
  //{
  //	driveArdumoto(MOTOR_A, CCW, valuePWM);
  //  lcd.setCursor(0,0);
  //  lcd.print("PWM:"); 
  //  lcd.print(valuePWM);  
  //  delay(4000); 
  //  lcd.clear();
  driveArdumoto(MOTOR_A, CCW, 90);
  delay(10000);   
 }

