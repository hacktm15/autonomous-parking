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

// Motor definitions to make life easier:
#define MOTOR_A 0

/**/ 
void setup() 
{
	Serial.begin(9600); 
	sensor_pinSetup();
	motor_pinSetup();  
}

/**/ 
void loop() 
{
 Serial.println("Sensor A:");
 Serial.println(sensorDistance(sensor_a_Trigger, sensor_a_Echo));
 delay(50);
 Serial.println("Sensor B:");
 Serial.println(sensorDistance(sensor_b_Trigger,sensor_b_Echo));
 delay(50);
 Serial.println("Sensor C:");
 Serial.println(sensorDistance(sensor_c_Trigger,sensor_c_Echo)); 
 delay(50); 
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

