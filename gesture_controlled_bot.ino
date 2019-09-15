


//This program lets you to control your robot with gesture made by your hand

int GNDPin=A4; //Set Analog pin 4 as GND
int VccPin=A5; //Set Analog pin 5 as VCC          //these pins are connected to ADXL335 pins from arduino .here vcc of ADXL335 must be high 
int xPin=A3; //X axis input                    
int yPin=A2; //Y axis input
int zPin=A1; //Z axis input(not used)
int Q1=10,Q2=11,Q3=12,Q4=13; //Output pins to be connected to 10, 11, 12, 13 of Decoder IC(for motors input)
long x; //Variabe for storing X coordinates
long y; //Variabe for storing Y coordinates
long z; //Variabe for storing Z coordinates
void setup()
{
  Serial.begin(9600); //baud rate setting is done using serial.begin  and baud rate is no.of bytes transfered per sec communication channel
  pinMode(Q1,OUTPUT);
  pinMode(Q2,OUTPUT);
  pinMode(Q3,OUTPUT);
  pinMode(Q4,OUTPUT);
  pinMode(GNDPin, OUTPUT);
  pinMode(VccPin, OUTPUT);
  digitalWrite(GNDPin, LOW); //Set A4 pin LOW        //connected to ADXL335 pins
  digitalWrite(VccPin, HIGH); //Set A5 pin HIGH 
  }
void loop()
{
  x = analogRead(xPin); //Reads X coordinates
  y = analogRead(yPin); //Reads Y coordinates
  z = analogRead(zPin); //Reads Z coordinates (Not Used)
    if(x<330)      // Change the value for adjusting sensitivity  
      forward();
    else if(x>330) // Change the value for adjusting sensitivity
      backward();
    else if(y<330) // Change the value for adjusting sensitivity
      right();
    else if(y>330) // Change the value for adjusting sensitivity
      left();
    else
      stop_();
}
void stop_()
{
  Serial.println("");             //first map speed using z and then output is placed in low,high in every function 
  Serial.println("STOP");
  digitalWrite(Q1,LOW);
  digitalWrite(Q2,LOW);
  digitalWrite(Q3,LOW);
  digitalWrite(Q4,LOW);
}
void forward()
{
  Serial.println("");
  Serial.println("Forward");
  digitalWrite(Q1,HIGH);
  digitalWrite(Q2,LOW);
  digitalWrite(Q3,HIGH);
  digitalWrite(Q4,LOW);
}
void backward()
{
  Serial.println("");
  Serial.println("Backward");
  digitalWrite(Q1,LOW);
  digitalWrite(Q2,HIGH);
  digitalWrite(Q3,LOW);
  digitalWrite(Q4,HIGH);
}
void left()
{
  Serial.println("");
  Serial.println("Left");
  digitalWrite(Q1,LOW);
  digitalWrite(Q2,HIGH);
  digitalWrite(Q3,HIGH);
  digitalWrite(Q4,LOW);
}
void right()
{
  Serial.println("");
  Serial.println("Right");
  digitalWrite(Q1,HIGH);
  digitalWrite(Q2,LOW);
  digitalWrite(Q3,LOW);
  digitalWrite(Q4,HIGH);
}
