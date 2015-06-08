import processing.serial.*;

Serial myPort;
int time,readA, readB, serialCount = 0, xtick = 0;
int[] data = new int[800];
boolean firstContact = false;
int[] serialInArray = new int[2];
float max = 2000;

void setup() {
  size(840, 640);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  noStroke();
  if(xtick >=800) xtick = 0;
  
  time = ((readB << 8)) | (readA);
  int time1 = time*2;
  println(time1);
  
  fill(0);
  rect(0,0,840,640);
  stroke(255);
  rect(20,20,800,600);

  fill(255);
  text(time1,30,35);
  
  data[xtick] = int(map(time1, 0,max,0,600));
  
  for(int i=0; i<xtick+1; i++) {
    int x = i +20;
    int y = 620- data[i];
    line(x,y,x,620);
  }
  stroke(0,0,255);
  line(xtick+20,20,xtick+20,620);
  xtick++;
  
  delay(100);

}

void serialEvent(Serial myPort) {
  int inByte = myPort.read();
  if (firstContact == false) {
    if (inByte == 'A') {
      myPort.clear();          // clear the serial port buffer
      firstContact = true;     // you've had first contact from the microcontroller
      myPort.write('A');
      print("Connection Established");
    }
  }  
  else {
   serialInArray[serialCount] = inByte;
    serialCount++;
    
    if(serialCount>1) {
      readA = serialInArray[0];
      readB=serialInArray[1];
      //myPort.clear();
      myPort.write('A');
      serialCount=0;
    }
  }
}

