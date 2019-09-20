#include <Servo.h>

//IR SENSOR
int sensorPin = A0; //ir analog input pin
int sensorValue = 0; //Variable that represents the analog input

//SERVOS
Servo vert_sweep;
Servo horz_sweep;
int vert_pin = 9; //Pin vertical sweeping servo is plugged into
int horz_pin = 10; //Pin horizontal sweeping servo is plugged into
int vert_pos = 0; //Position of vertical sweeping servo
int horz_pos = 0; //Position of horizontal sweeping servo
int current_angle;

//SIGNAL LIGHTS
int vert_led = 2;
int horz_led = 3;

//BUTTON
int butt_in = 4;
boolean _buffer = true;
boolean _on = false;

//FUNCTIONS
void sweep(Servo servo, int ledpin, int angle = 180, int d = 1); //Controls the vertical sweep
boolean _switch(boolean _on, int button_input = 4);


void setup() { //------------------------------------------------------------------------------------------
  Serial.begin(9600);
  // SIGNAL LIGHTS
  pinMode(vert_led, OUTPUT); //LED
  pinMode(horz_led, OUTPUT); //LED
  //SERVOS
  vert_sweep.attach(vert_pin); //Pin Vertical Sweeping Servo is hooked up to
  horz_sweep.attach(horz_pin); //Pin Horizontal Sweeping Servo is hooked up to 
  //BUTTON
  pinMode(butt_in, INPUT);
}

void loop() { //----------------------------------------------------------------------------------------
  _on = _switch(_on, butt_in);

  //while(_on == true){
    sweep(vert_sweep,vert_led, 0, -10);
    sweep(horz_sweep,horz_led, 0, -10);
    delay(1000);
  //digitalWrite(horz_led, HIGH);
  //}

}
void sweep(Servo servo, int ledpin, int angle = 180, int d = 1){ // ----------------------------------
  current_angle = servo.read();
  if(current_angle != angle){
    servo.write(current_angle+d);
  } else{
        digitalWrite(ledpin, HIGH);   // turn the LED off by making the voltage _low
  }
}

boolean _switch(boolean _on, int button_input = 4){//------------------------------------------------------------------
  int button = digitalRead(button_input);
  if(button > 0 && _buffer ==  true){
    if(_on == true){
      _on = false;
    } else{
      _on = true;
      vert_sweep.write(0);
      horz_sweep.write(0);
    }
    _buffer = false;
  }
  if(button == 0){
    _buffer = true;
  }
  return _on;
}
