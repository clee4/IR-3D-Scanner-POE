#include <Servo.h>
int sensorValue;
//SERVOS
Servo vert_sweep; //Vertical Servo
Servo horz_sweep; //Horizontal Servo
int vert_pin = 11; //Pin vertical sweeping servo is plugged into
int horz_pin = 9; //Pin horizontal sweeping servo is plugged into
int vert_pos = 0; //Position of vertical sweeping servo
int horz_pos = 0; //Position of horizontal sweeping servo
int current_angle; //Represents current servo angle
int state = 1;

//SIGNAL LIGHTS
int vert_led = 12; //LED Pin that corresponds to when the Vertical Servo hits goal 
int horz_led = 13; //LED Pin that corresponds to when the Horizontal Servo hits goal

//FUNCTIONS
void sweep(Servo servo, int ledpin, int angle = 0, int d = -180); //Controls the vertical sweep
void sensor(int input); //Reads Sensor and prints input

void setup() { //------------------------------------------------------------------------------------------
  Serial.begin(9600);
  
  // SIGNAL LIGHTS
  pinMode(vert_led, OUTPUT); //LED
  pinMode(horz_led, OUTPUT); //LED
  
  //SERVOS
  vert_sweep.attach(vert_pin); //Pin Vertical Sweeping Servo is hooked up to
  vert_sweep.write(0);
  horz_sweep.attach(horz_pin); //Pin Horizontal Sweeping Servo is hooked up to 
  horz_sweep.write(0); 

  delay(1000);
}
void loop() { //----------------------------------------------------------------------------------------
    for (int x; x<180; x++){ //180 becuase it rotates horizontally 180 times
      if(state == 1 ){ //step one
        //Serial.println("move 1 degree");
        sweep(vert_sweep,vert_led, 180, 1); //go down to 180 at a 1 degree per second rate
      }
      if(state > 1){ //step 2
        sweep(horz_sweep,horz_led, 180, 10); //move one degree 
        sweep(vert_sweep, vert_led); //resets vertical servo back to 0
        state = 1; //Back to step 1
      }
      delay(100); //wait .01 sec
      sensorValue = analogRead(A0); //Reads analog input
      Serial.println(sensorValue); //Sends input to computer
    }
    Serial.println("works");
}

void sweep(Servo servo, int ledpin, int angle = 0, int d = -180){ // ----------------------------------
  current_angle = servo.read(); //gets current servo position
//  Serial.println(current_angle);
  if(current_angle != angle){ //makes sure we arent at goal angle
    servo.write(current_angle+d); //increase angle by set rate
  } else{
        digitalWrite(ledpin, HIGH);   // turn the LED on by making the voltage high
        state = 2;
  }
}
