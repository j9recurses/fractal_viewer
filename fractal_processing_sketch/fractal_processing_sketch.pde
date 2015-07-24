import processing.serial.*;
float curlx = 0;
float curly = 0;
float f = sqrt(2)/2.;
Serial myPort; 
float deley = 6;
float growth = -2;
float growthTarget = 0;
int myX;
int myY;
int[] serialInArray = new int[3];    // Where we'll put what we receive
int serialCount = 0;                 // A count of how many bytes we receive
boolean firstContact = false; 
int currentValue =0;
int sensorgrowth;


void setup()
{
  size(550,550,P2D);
  //smooth();
  println(Serial.list()); 
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  println("listening on port: "+ myPort);
}

void draw()
{
  background(250);
  stroke(0);
  curlx += (radians(360./height*myX)-curlx)/deley;
  curly += (radians(360./height*myY)-curly)/deley;
  translate(width/2,height/3*2);
  line(0,0,0,height/2);
  branch(height/4.,17);
  branch(height/2.,17);
  //println(sensorgrowth);
  growthTarget = -1;
  growth += (growthTarget/10-growth+1.)/deley;
 // println(growth);
 delay(sensorgrowth);
}

void serialEvent(Serial myPort) {
  // read a byte from the serial port:
  int inByte = myPort.read();
  // if this is the first byte received, and it's an A,
  // clear the serial buffer and note that you've
  // had first contact from the microcontroller. 
  // Otherwise, add the incoming byte to the array:
  if (firstContact == false) {
    if (inByte == 'A') { 
      myPort.clear();          // clear the serial port buffer
      firstContact = true;     // you've had first contact from the microcontroller
      myPort.write('A');       // ask for more
    } 
  } 
  else {
    // Add the latest byte from the serial port to array:
    serialInArray[serialCount] = inByte;
    serialCount++;

    // If we have 3 bytes:
    if (serialCount > 1) {
      myX = serialInArray[0];
      myY = 0;
      myY = serialInArray[1];
      //sensorgrowth = serialInArray[0];
      // print the values (for debugging purposes only):
      println( "xaxis" + "\t" + "yaxis"+ "\t");
      println( myX + "\t" + myY+ "\t"  );
      serialInArray[1] = 0;
      // Send a capital A to request new sensor readings:
      myPort.write('A');
      // Reset serialCount:
      serialCount = 0;
    }
  }
}
  
void branch(float len,int num)
{
  len *= f;
  num -= 1;
  if((len > 1) && (num > 0))
  {
    pushMatrix();
    rotate(curlx);
    line(0,0,0,-len);
    translate(0,-len);
    branch(len,num);
    popMatrix();
      
//    pushMatrix();
//    line(0,0,0,-len);
//    translate(0,-len);
//    branch(len);
//    popMatrix();
    len *= growth;
    pushMatrix();
    rotate(curlx-curly);
    line(0,0,0,-len);
    translate(0,-len);
    branch(len,num);
    popMatrix();
    //len /= growth;
  }
}

