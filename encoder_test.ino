volatile long count=0;
double sensed_output_1, control_signal_1;
double setpoint_1;
double Kp_1=1; //proportional gain
double Ki_1=1; //integral gain
double Kd_1=1; //derivative gain

double sensed_output_2, control_signal_2;
double setpoint_2;
double Kp_2=1; //proportional gain
double Ki_2=1; //integral gain
double Kd_2=1; 

int T=1; //sample time in milliseconds (ms)
unsigned long last_time;
double total_error, last_error;
int max_control=255;
int min_control=0; 
int const RF =10;
int const RB =11;
int const RE = 6;
int interruptPin_1=3;

int const LF =8;
int const LB =9;
int const LE = 5;
int interruptPin_2=2;



unsigned long Tick_1=0, Tick_2=0;
void tick(){

 count+=1;
}

int speedofmotors(int k)
{
  int i,f=0;
  int ticks;
  i=micros();
  f=micros()-i;
  interrupts();
  attachInterrupt(digitalPinToInterrupt(k), tick, RISING);
  while(f<1000) 
  {
    
    f=micros()-i;  }

  detachInterrupt(digitalPinToInterrupt(k));
  noInterrupts();
  ticks = count;
  count=0;
  i=0;
  f=0;
  return(ticks);  
}

void setup() {
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(RF,OUTPUT);
  pinMode(RB,OUTPUT);
  digitalWrite(RF,1);
  digitalWrite(RB,0);

  pinMode(4,OUTPUT);
  pinMode(LF,OUTPUT);
  pinMode(LB,OUTPUT);
  digitalWrite(LF,1);
  digitalWrite(LB,0);
  setpoint_1=50;
  setpoint_2=50;

}

void loop()
{
 // while(Tick_1 <= 1000000 && Tick_2 <= 1000000)
/* while(1)
  {
    sensed_output_1=speedofmotors(interruptPin_1);
    Tick_1 += sensed_output_1;
    control_signal_1 = PID_Control(Kp_1,Ki_1,Kd_1,setpoint_1,sensed_output_1);
    analogWrite(RE,control_signal_1);

    sensed_output_2=speedofmotors(interruptPin_2);    
    Tick_2 += sensed_output_2;     
    control_signal_2 = PID_Control(Kp_2,Ki_2,Kd_2,setpoint_2,sensed_output_2); //calls the PID function every T interval and outputs a control signal     
    analogWrite(LE,control_signal_2);
    
    Serial.print(sensed_output_1);
    Serial.print("\t");
    Serial.println(sensed_output_2);
  }*/
 // analogWrite(RE,0);
 // analogWrite(LE,0);
 sensed_output_2=speedofmotors(interruptPin_2); 
 Serial.println(sensed_output_2);
 
 
}

double PID_Control(double Kp, double Ki, double Kd, double setpoint, double sensed_output){

  unsigned long current_time = micros();
  double control_signal; //returns the number of milliseconds passed since the Arduino started running the program
 
  int delta_time = current_time - last_time; //delta time interval 
  
  if (delta_time >= T){

    double error = setpoint - sensed_output;
    
    total_error += error; //accumalates the error - integral term
    if (total_error >= max_control) total_error = max_control;
    else if (total_error <= min_control) total_error = min_control;
    
    double delta_error = error - last_error; //difference of error for derivative term

    control_signal = Kp*error + (Ki*T)*total_error + (Kd/T)*delta_error; //PID control compute
    if (control_signal >= max_control) control_signal = max_control;
    else if (control_signal <= min_control) control_signal = min_control;
    
    last_error = error;
    last_time = current_time;
    return control_signal;
    }  
}
