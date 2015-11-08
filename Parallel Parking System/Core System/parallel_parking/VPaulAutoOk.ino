
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
#define MINIMUM_LIMIT 20 //in cm

#define PARK_STATE_1 1 /*There is a car on the right*/ 
#define PARK_STATE_2 2 /*There is empty space on the right and PARK_STATE_1 was set*/ 
#define PARK_STATE_3 3 /*There is a car on the right and PARK_STATE_1 and PARK_STATE_2 where set*/ 

#define MIDDLESENZOR_OFFSET 2 //Distance in cm. Offset is needed because of the shape of the car 

#define NEW_LIMIT 3 //To be determined 
#define REAR_LIMIT 5

/*Globals*/ 
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 11; // PWM control (speed) for motor B
const byte DIRA = 12; // Direction control for motor A
const byte DIRB = 13; // Direction control for motor B


#define distance_FrontSensor sensorDistance(sensor_a_Trigger,sensor_a_Echo) 
#define distance_MiddleSensor sensorDistance(sensor_b_Trigger,sensor_b_Echo) - MIDDLESENZOR_OFFSET 
#define distance_BackSensor   sensorDistance(sensor_c_Trigger,sensor_c_Echo) 

/*Parking State*/ 
byte parkingState; 
int isParkingModePossible = 0;
int isFirstTimeOn = 0;
int parkingFinished = 0;
bool WheelsRight = false;
bool WheelsLeft = false;


/*Runs only once*/ 
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
 if (checkSpace() == PARK_STATE_3 && isParkingModePossible == 0)
 {
  //Run Parking Algo
  Serial.println("STOP");
  isParkingModePossible = 1;
  ParkingAlgo(); 
  
 }
 else 
 {
   if(isParkingModePossible == 1 && parkingFinished == 0)
     ParkingAlgo(); 
     {
       driveArdumoto(MOTOR_B, CCW, 255);
       delay(3000);
       stopArdumoto(MOTOR_B);
       delay(100);
       driveArdumoto(MOTOR_A, CW, 180);
       delay(800);
       stopArdumoto(MOTOR_A);
       delay(100);
       driveArdumoto(MOTOR_B, CW, 255);
       delay(2800);
       stopArdumoto(MOTOR_B);
       delay(100);
       driveArdumoto(MOTOR_A, CW, 130);
       delay(500);
       stopArdumoto(MOTOR_A);
       delay(100);
       driveArdumoto(MOTOR_B, CW, 255);
       delay(3000);
       stopArdumoto(MOTOR_B);
       delay(100);
       driveArdumoto(MOTOR_B, CCW, 200);
       delay(3000);
       stopArdumoto(MOTOR_B);
       delay(500);
       driveArdumoto(MOTOR_A, CCW, 150);
       delay(500);
       stopArdumoto(MOTOR_A);
       delay(100);
       parkingFinished=1;
     }
     
 }
}

/*Checks if there is space for parking*/ 
byte checkSpace()
{
   if(isFirstTimeOn == 0)
   {
     isFirstTimeOn = 1;
     driveArdumoto(MOTOR_A, CCW, 140);
     delay(500);
   }
   if(parkingState != 3)
     driveArdumoto(MOTOR_A, CCW, 90);  
  
    if((distance_FrontSensor <= MINIMUM_LIMIT)&& 
       (distance_MiddleSensor <= MINIMUM_LIMIT)&&
       (distance_BackSensor <= MINIMUM_LIMIT)&&
       (parkingState < 2))
       {
         parkingState = 1; 
       }

    if((distance_FrontSensor > MINIMUM_LIMIT)&& 
       (distance_MiddleSensor > MINIMUM_LIMIT)&&
       (distance_BackSensor > MINIMUM_LIMIT)&&
       (parkingState == 1))
       {
         parkingState = 2; 
       }

    if((distance_FrontSensor <= MINIMUM_LIMIT)&& 
       (distance_MiddleSensor <= MINIMUM_LIMIT)&&
       (distance_BackSensor <= MINIMUM_LIMIT)&&
       (parkingState == 2))
       {
         parkingState = 3; 
         driveArdumoto(MOTOR_A, CCW, 0); 
         delay(1000);
       } 
 Serial.println(distance_FrontSensor);
 Serial.println(distance_MiddleSensor);
 Serial.println(distance_BackSensor);
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


/**/ 
void ParkingAlgo()
{ 
  
 int distance_rearSensor_Simulation = 10, toRight = 0, toLeft = 0; 


/*1*/
  if(distance_MiddleSensor > NEW_LIMIT)
  {

   if(WheelsRight)
   {
   /* Turn to the right max */
   driveArdumoto(MOTOR_B, CCW, 255);
   delay(3000);
   toRight = 255;
   stopArdumoto(MOTOR_B);
   WheelsRight = true;

   driveArdumoto(MOTOR_A, CCW, 200);
   delay(3000); 
   driveArdumoto(MOTOR_A, CCW, 90);  
   }

   else if(WheelsLeft)
   {
   /* Straighten the Wheels, then turn to the right max */
   driveArdumoto(MOTOR_B, CCW, toLeft);
   delay(3000);
   driveArdumoto(MOTOR_B, CCW, 255);
   delay(3000);
   toRight = 255;
   stopArdumoto(MOTOR_B);
   WheelsRight = true;
   WheelsLeft = false;

   driveArdumoto(MOTOR_A, CCW, 140);
   delay(3000); 
   driveArdumoto(MOTOR_A, CCW, 90); 
   }
   
   else /* Wheels are straight */
   {
   /*1*/ //Wheels turn to the right max 
   driveArdumoto(MOTOR_B, CCW, 255);
   delay(3000);
   toRight = 255;
   stopArdumoto(MOTOR_B);
   WheelsRight = true;

   driveArdumoto(MOTOR_A, CW, 140);
   delay(3000); 
   driveArdumoto(MOTOR_A, CW, 90); 
   }  
  } 

/*2*/ 
  if((distance_MiddleSensor <= NEW_LIMIT) && (distance_FrontSensor >NEW_LIMIT))
  {
   stopArdumoto(MOTOR_A);

   if(WheelsRight)
   {
   /* Wheels are oriented to the Right, straighten them */
   driveArdumoto(MOTOR_B, CW, toRight);
   stopArdumoto(MOTOR_B);
   toRight = 0;
   WheelsRight = false;

   driveArdumoto(MOTOR_A, CW, 140);
   delay(500); 
   driveArdumoto(MOTOR_A, CW, 90); 
   }

   else if(WheelsLeft)
   {
   /* Wheels are oriented to the Left, straighten them */
   driveArdumoto(MOTOR_B, CCW, toLeft);
   stopArdumoto(MOTOR_B);
   toLeft = 0;
   WheelsLeft = false;

   driveArdumoto(MOTOR_A, CW, 140);
   delay(500); 
   driveArdumoto(MOTOR_A, CW, 90); 
   }

   else
  {
   /*2*/ //Forward wheels need to be straight
   driveArdumoto(MOTOR_A, CW, 140);
   delay(500); 
   driveArdumoto(MOTOR_A, CW, 90);  
  }

/*3*/
 if((distance_FrontSensor <= NEW_LIMIT) && (distance_rearSensor_Simulation > REAR_LIMIT))
  {
   stopArdumoto(MOTOR_A);

   if(WheelsRight)
   {
    /* Straighten the Wheels */
    driveArdumoto(MOTOR_B, CW, toRight);
    stopArdumoto(MOTOR_B);
    toRight = 0;
    WheelsRight = false;

    /* Turn Wheels to max left */
    driveArdumoto(MOTOR_B, CW, 255);
    stopArdumoto(MOTOR_B);
    toLeft = 255;
    WheelsLeft = true;
   }

   else
   {
   /* Turn Wheels to max left */
   driveArdumoto(MOTOR_B, CCW, 255);
   driveArdumoto(MOTOR_B, CCW, 255);
   toLeft = 255;
   WheelsLeft = true; 

   driveArdumoto(MOTOR_A, CW, 140);
   delay(500); 
   driveArdumoto(MOTOR_A, CW, 90); 
   }
  }

  /*4*/
  if (distance_rearSensor_Simulation <= REAR_LIMIT)
  {
   stopArdumoto(MOTOR_A);
   
   if(WheelsRight)
   {
   /* Wheels are oriented to the Right, straighten them */
   driveArdumoto(MOTOR_B, CW, toRight);
   stopArdumoto(MOTOR_B);
   toRight = 0;
   WheelsRight = false;

   driveArdumoto(MOTOR_A, CCW, 140);
   delay(500); 
   driveArdumoto(MOTOR_A, CCW, 90); 
   }

   else if(WheelsLeft)
   {
   /* Wheels are oriented to the Left, straighten them */
   driveArdumoto(MOTOR_B, CCW, toLeft);
   stopArdumoto(MOTOR_B);
   toLeft = 0;
   WheelsLeft = false;

   driveArdumoto(MOTOR_A, CCW, 140);
   delay(500); 
   driveArdumoto(MOTOR_A, CCW, 90); 
   }

   else
  {
   /*2*/ //Forward wheels need to be straight
   driveArdumoto(MOTOR_A, CCW, 140);
   delay(500); 
   driveArdumoto(MOTOR_A, CCW, 90);  
  } 
  }
  }
}
