import processing.serial.*; 
Serial port;                             // Create object from Serial class 
int val;                                 // Data received from the serial port 
PFont font;
PImage tulip;
PImage[] qns = new PImage[10];

 
void setup() { 
  
  size(750, 300); 
  frameRate(4); 
  //printArray(Serial.list());
  
  String portName = Serial.list()[3];     //change the [x] to match your port
  port = new Serial(this, portName, 9600);
  
  font = createFont("VT323-Regular.ttf", 45);
  textFont(font);
  text("How you ever visited Queens, NY?", 80, 100);
  
  tulip = loadImage("tulip-leaf.png");
  
  for (int i = 0; i < qns.length; i++) {
    qns[i] = loadImage("qns_00"+i+".jpg");
  }

} 

void draw() { 
  
  if (0 < port.available()) {             // If data is available,
    val = port.read();                   // read it and store it in val
  } 
  
  if (val == 1)  { 
    image(tulip, random(width), random(height), 52, 65.5); 
   } 
   
   else if (val == 4) { 
    int index = int(random(0, qns.length));
    image(qns[index], 500, 150, 125, 125);
   } 
  
  println(val);
}
  