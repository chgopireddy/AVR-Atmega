int H1,H2,H3,Q1L,Q1H,Q2H,Q2L,Q3L,Q3H;

void setup() {
  pinMode(48,INPUT);
  pinMode(50,INPUT);
  pinMode(52,INPUT);


pinMode(41,OUTPUT);
pinMode(39,OUTPUT);
pinMode(37,OUTPUT);
pinMode(35,OUTPUT);
pinMode(33,OUTPUT);
pinMode(31,OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
   H1 = digitalRead(48);
   H2 = digitalRead(50);
   H3 = digitalRead(52);
   digitalWrite(41,H1 && !H2);      //Q1L
   digitalWrite(39,!(H2 && !H1));   //Q1H
   digitalWrite(37,H2 && !H3);      //Q2L
   digitalWrite(35,!(H3 && !H2));   //Q2H
   digitalWrite(33 , H3 && !H1);    //Q3L
   digitalWrite(31,!(H1 && !H3));   //Q3H
   
  
  // put your main code here, to run repeatedly:

}

