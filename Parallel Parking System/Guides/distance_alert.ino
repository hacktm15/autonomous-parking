#define Led_RED 8
#define Led_GREEN 10
#define Led_YELLOW 7 

#define sensor_Trigger  12
#define sensor_Echo 13 


/*Runs only once*/ 
void setup()
{
 Serial.begin(9600);
 Pin_SetUp(); 
}

/*Runs continously in a loop*/ 
void loop()
{
  digitalWrite(Led_RED, HIGH);
  delay(10000);
  Serial.println(sensorDistance()); 
  Execution(sensorDistance()); 
}


/*Function that sets up the PIN*/
void Pin_SetUp()
{
  pinMode(Led_RED, OUTPUT); 
  pinMode(Led_GREEN, OUTPUT);
  pinMode(Led_RED, OUTPUT);
  
  pinMode(sensor_Trigger, OUTPUT);
  pinMode(sensor_Echo, INPUT);  
}

/*Function that returns the sensor distance in centimeters*/ 
long sensorDistance()
{
  long duration, distance;
  digitalWrite(sensor_Trigger, LOW);  
  delayMicroseconds(2); 
  digitalWrite(sensor_Trigger, HIGH);

  delayMicroseconds(10); 
  digitalWrite(sensor_Trigger, LOW);
  duration = pulseIn(sensor_Echo, HIGH);
  distance = (duration/2) / 29.1;
  
  return distance;   
}


/**/ 
void Execution(long distance_Value)
{
  if (distance_Value > 100)
  {
    digitalWrite(Led_RED, LOW);
    digitalWrite(Led_YELLOW, LOW);
    digitalWrite(Led_GREEN, HIGH);   
  }
  else if ((distance_Value > 50) && (distance_Value < 100))
  {
    digitalWrite(Led_RED, LOW);
    digitalWrite(Led_YELLOW, HIGH);
    digitalWrite(Led_GREEN, LOW);
    /*bips at 1000ms interval*/  
  }
  else if (distance_Value < 50)
  {
    digitalWrite(Led_RED, HIGH);
    digitalWrite(Led_YELLOW, LOW);
    digitalWrite(Led_GREEN, LOW);
   /*bips at 500ms*/ 
  }
 else 
  {
    Serial.println("Error in distance"); 
  } 
}















