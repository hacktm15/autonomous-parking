/*Sensor Check*/ 

/*Defines*/ 
#define sensor_a_Trigger 10
#define sensor_a_Echo 9
#define sensor_b_Trigger 8
#define sensor_b_Echo 7
#define sensor_c_Trigger 6
#define sensor_c_Echo 5

#define CW  0 /*Clockwise*/ 
#define CCW 1 /*Counter Clockwise*/ 
#define MOTOR_A 0 //Rear Wheels Motor 
#define MOTOR_B 1 //Front Direction Motor 

#define CAR_LENGTH 20 //int cm
#define MINIMUM_LIMIT 5 //in cm

#define PARK_STATE_1 1 /*There is a car on the right*/ 
#define PARK_STATE_2 2 /*There is empty space on the right and PARK_STATE_1 was set*/ 
#define PARK_STATE_3 3 /*There is a car on the right and PARK_STATE_1 and PARK_STATE_2 where set*/ 

/*Globals*/ 
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 11; // PWM control (speed) for motor B
const byte DIRA = 12; // Direction control for motor A
const byte DIRB = 13; // Direction control for motor B


long FrontSensor  = sensorDistance(sensor_a_Trigger,sensor_a_Echo); 
long MiddleSensor = sensorDistance(sensor_b_Trigger,sensor_b_Echo); 
long BackSensor   = sensorDistance(sensor_c_Trigger,sensor_c_Echo); 

/*parkingState*/ 
byte parkingState; 


/*Runs once*/ 
void setup() 
{
  Serial.begin(9600); 
  sensor_pinSetup();
  motor_pinSetup();  
}

/*Runs in a loop*/ 
void loop() 
{
 mainExecution(); 
}

/*Sensor PIN setup*/
void sensor_pinSetup()
{
  pinMode(sensor_a_Trigger, OUTPUT);
  pinMode(sensor_a_Echo, INPUT);  
  pinMode(sensor_b_Trigger, OUTPUT);
  pinMode(sensor_b_Echo, INPUT);  
  pinMode(sensor_c_Trigger, OUTPUT);
  pinMode(sensor_c_Echo, INPUT); 
}

/*Motor PIN setup*/ 
void motor_pinSetup()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}

/*Function that returns the sensor distance in centimeters*/ 
long sensorDistance(int sensor_x_Trigger, int sensor_x_Echo)
{
  long duration, distance;
  digitalWrite(sensor_x_Trigger, LOW);  
  delayMicroseconds(2); 
  digitalWrite(sensor_x_Trigger, HIGH);

  delayMicroseconds(10); 
  digitalWrite(sensor_x_Trigger, LOW);
  duration = pulseIn(sensor_x_Echo, HIGH);
  distance = (duration/2) / 29.1;
  
  return distance;   
}

/*Main Execution function*/ 
void mainExecution()
{
 if (checkSpace() == PARK_STATE_3)
 {
  //Run Parking Algo
 }
 else 
 {
  /*Conditions are not favourable for parallel parking*/
 }
}

/*Checks if there is space for parking*/ 
bool checkSpace()
{

  driveArdumoto(MOTOR_A, CW, 60); 
  
  if((FrontSensor <= MINIMUM_LIMIT)&& 
     (MiddleSensor <= MINIMUM_LIMIT)&&
     (BackSensor <= MINIMUM_LIMIT))
     {
       parkingState = 1; 
     }

  if((FrontSensor > MINIMUM_LIMIT)&& 
     (MiddleSensor > MINIMUM_LIMIT)&&
     (BackSensor > MINIMUM_LIMIT)&&
     (parkingState == 1))
     {
       parkingState = 2; 
     }

  if((FrontSensor <= MINIMUM_LIMIT)&& 
     (MiddleSensor <= MINIMUM_LIMIT)&&
     (BackSensor <= MINIMUM_LIMIT)&&
     (parkingState == 2))
     {
       parkingState = 3; 
       stopArdumoto(MOTOR_A); 
    } 

    return parkingState;  
}

/*driveArdumoto */ 
void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}   

/*stopArdumoto makes a motor stop*/
void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}

