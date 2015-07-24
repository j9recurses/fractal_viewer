/*
 * takes input from squeeze sensor and 2 pots to make fractal image grow and change
 */
int pot1Pin = 0;   // select the input pin for the potentiometer 1
int pot2Pin = 1;// select the input pin for the potentiometer 2
int pot3Pin = 2;
int potlightval = 500;
int lastpressureval = 300;
int growth_drop = 13;
int led1Pin = 3;   // select the pin for the LED 1
int led2Pin = 6;  // select the pin for the LED 2
int led3Pin = 9;
int inByte = 0; 


void setup() {
   Serial.begin(9600);   
   establishContact(); 
}

int detectchange_intensity(int potPin) {
  int potbefore = analogRead(potPin);
  //Serial.println("base val");
  //Serial.println(potbefore);
  delay(200);
  int potafter = analogRead(potPin);
  int potchange = (potafter - potbefore)/10;
  //Serial.println("change");
  //Serial.println(potchange);
  if(potchange > 0) {
   //Serial.println("***postive change*****");
    return potchange;
  }
 return 0;
}


int getwidth(int potPin) {
  //size of canvas = 1050w 750l
  potPin = analogRead(potPin);
  if(potPin > 1049){
    potPin = 1049;
  }
  return potPin;
}

int getheight(int potPin) {
  //size of canvas = 1050w 750l
  potPin = analogRead(potPin);
  if(potPin > 749){
    potPin = 749;
  }
  return potPin;
}
int getgrowth(int potPin,  int lastppval, int growth_drop ){
  //Serial.println("intial vals");
  //Serial.println("growth");
  //Serial.println(growth_drop);
  //Serial.println("last reading");
  //Serial.write(growth_drop);lastppval);
  int potpressure = analogRead(potPin);
  int newpot2val[] = {lastppval, growth_drop} ;
  //Serial.println("**new pressure*");
  //Serial.println(potpressure);
  int totalchange = potpressure - lastppval;
   //Serial.println("**total change*");
  if((totalchange > 150) || (totalchange <  -150)  ) {
    lastppval = potpressure;
    growth_drop = growth_drop-1;
    return growth_drop;
  //Serial.println("**inside***");
  //  Serial.println(growth_drop);
  }
  return growth_drop;
}



void loop() {
   //int potchange_squeeze = detectchange_intensity(pot2Pin);
   //if(potchange_squeeze > 0) {
     ///  potlightval = ( potlightval + potchange_squeeze);
       //Serial.println("final pot2 val");
       //Serial.write(pot2Val);
    //   analogWrite(led2Pin, potlightval); 
    //   analogWrite(led1Pin, potlightval);
     //  analogWrite(led3Pin, potlightval);
   ///}
    //Serial.println("growth 1");
    //Serial.println(growth_drop);
   //  Serial.println("last pressure");
    //Serial.println(lastpressureval);
    inByte = Serial.read();
    if(growth_drop == 0) {
      growth_drop = 17;
    }
    //int *newpot2Val = getgrowth(pot2Pin,lastpressureval, growth_drop );
    //lastpressureval = newpot2Val[0];
    //growth_drop = newpot2Val[1];
    //Serial.println(growth_drop);
    //use the light first
    Serial.write(getheight(pot2Pin));
    Serial.write(analogRead(pot1Pin));
  
   delay(1500);
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}
