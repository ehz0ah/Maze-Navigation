#include <MeMCore.h> // Include Mbot library.

#define TURNING_TIME_MS 410 // The time duration (ms) for turning.
#define TIMEOUT 1400 // Max microseconds to wait before moving on.
#define SPEED_OF_SOUND 340 // Speed of sound to be 340m/s.
#define ULTRASONIC 12 // Pin 12 (port 1) for the ultrasonic sensor.
#define IR_SENSOR A2 // Pin S1 of Port 3 is used to read voltage readings from the IR sensor.
#define LDR_SENSOR A3 // Pin S2 of Port 3 is used to read voltage readings from the LDR sensor.
#define LED_INPUT_1 A0 // Pin S1 of Port 4 is used to control input 1A on LS139P chip.
#define LED_INPUT_2 A1 // Pin S2 of Port 4 is used to control input 1B on LS139P chip.
#define LDRWait 100 // Define time delay before taking another LDR reading (in ms).
#define RGBWait 400 // Define time delay (in ms) before changing to another LED colour.

MeBuzzer buzzer; // Create the buzzer object.
MeDCMotor leftMotor(M1); // Assigning leftMotor to port M1.
MeDCMotor rightMotor(M2); // Assigning RightMotor to port M2.
MeLineFollower lineFinder(PORT_2); // Assigning lineFinder to RJ25 port 2.

// Declaring motor speeds to 220 out of 255.
int motorSpeed_left = 220;
int motorSpeed_right = 220;

/*
* Integer arrays for color sensor calibration and measurements.
* WhiteArray, blackArray, greyDiff are utilized for calibrating the LDR.
* Subsequent color measurements are based on the values stored in these arrays.
* colourArray stores the final RGB values measured by the LDR for color identification.
*/
int colourArray[] = {0,0,0};
int whiteArray[] = {870,957,955};
int blackArray[] = {320,720,769};
int greyDiff[] =  {550,237,186};

/*
* The numbers inside the brackets denote the frequency (represented by note) and duration (in milliseconds).
* This function invokes the Mcore to play the Star Wars Theme (Imperial March).
*/
void celebrate() {
  buzzer.tone(440, 500);
  buzzer.tone(440, 500);
  buzzer.tone(440, 500);
  buzzer.tone(349, 376);
  buzzer.tone(523, 126);
    
  buzzer.tone(440, 500);
  buzzer.tone(349, 376);
  buzzer.tone(523, 126);
  buzzer.tone(440, 1000);
    
  buzzer.tone(659, 500);
  buzzer.tone(659, 500);
  buzzer.tone(659, 500);
  buzzer.tone(698, 376);
  buzzer.tone(523, 126);
  
  buzzer.tone(415, 500);
  buzzer.tone(349, 376);
  buzzer.tone(523, 126);
  buzzer.tone(440, 1000);
  
  buzzer.tone(880, 500);
  buzzer.tone(440, 376);
  buzzer.tone(440, 126);
  buzzer.tone(880, 500);
  buzzer.tone(831, 376);
  buzzer.tone(784, 126);
  
  buzzer.tone(740, 166);
  buzzer.tone(698, 166);
  buzzer.tone(740, 166);
  delay(250);
  buzzer.tone(466, 250);
  buzzer.tone(622, 500);
  buzzer.tone(587, 376);
  buzzer.tone(554, 126);
  
  buzzer.tone(523, 166);
  buzzer.tone(494, 166);
  buzzer.tone(523, 166);
  delay(250);
  buzzer.tone(349, 250);
  buzzer.tone(415, 500);
  buzzer.tone(349, 376);
  buzzer.tone(415, 126);
  
  buzzer.tone(523, 500);
  buzzer.tone(440, 376);
  buzzer.tone(523, 126);
  buzzer.tone(659, 1000);
  
  buzzer.tone(880, 500);
  buzzer.tone(440, 376);
  buzzer.tone(440, 126);
  buzzer.tone(880, 500);
  buzzer.tone(831, 376);
  buzzer.tone(784, 126);
  
  buzzer.tone(740, 166);
  buzzer.tone(698, 166);
  buzzer.tone(740, 166);
  delay(250);
  buzzer.tone(466, 250);
  buzzer.tone(622, 500);
  buzzer.tone(587, 376);
  buzzer.tone(554, 126);

  buzzer.tone(523, 166);
  buzzer.tone(494, 166);
  buzzer.tone(523, 166);
  delay(250);
  buzzer.tone(349, 250);
  buzzer.tone(415, 500);
  buzzer.tone(349, 376);
  buzzer.tone(523, 126);
  
  buzzer.tone(440, 500);
  buzzer.tone(349, 376);
  buzzer.tone(523, 126);
  buzzer.tone(440, 1000);
}

// Takes in the number of times to scan the LDR as an input and calculates the average reading.
int getAvgReading(int times) {
  int reading;
  int total = 0;

  // Takes in LDR reading and add them up, with a delay of 100ms in between each reading.
  for(int i = 0; i < times ; i++) {
    reading = analogRead(LDR_SENSOR);
    total = reading + total;
    delay(LDRWait);
  }

  // Returns the calculated average.
  return total/times;
}

// Function for the robot to move foward.
void go_straight() {
  leftMotor.run(-motorSpeed_left - 35);
  rightMotor.run(motorSpeed_right + 10);
}

// Function to turn left.
void turn_left() {
  leftMotor.run(motorSpeed_left); 
  rightMotor.run(motorSpeed_right);
}

// Function to turn right.
void turn_right() {
  leftMotor.run(-motorSpeed_left);
  rightMotor.run(-motorSpeed_right);
}

// Function to stop moving.
void stop_motors() {
  leftMotor.stop(); 
  rightMotor.stop();
}

// Function to adjust to the right if too close to left wall.
void nudge_right() {
  leftMotor.run(-(motorSpeed_left+35));
  rightMotor.run(motorSpeed_right-35);
}

// Function to adjust to the left if too close to right wall.
void nudge_left() {
  leftMotor.run(-(motorSpeed_left-35)); 
  rightMotor.run(motorSpeed_right+35); 
}

// Function to u-turn on the spot.
void u_turn() {
  turn_right();
  delay(2*TURNING_TIME_MS-225);
}

// Function to turn left 2 consecutive times in 2 grids.
void double_left_turn() {
  turn_left();
  delay(TURNING_TIME_MS-70);  
  go_straight();
  delay(650);
  turn_left();
  delay(TURNING_TIME_MS-10);
}

// Function to turn right 2 consecutive times in 2 grids.
void double_right_turn() {
  turn_right();
  delay(TURNING_TIME_MS-80);
  go_straight();
  delay(750); 
  turn_right();
  delay(TURNING_TIME_MS-60);
}

/*
* Controls the digital pins for turning on red, blue, green LEDs and the IR emitter respectively.
* Only one of the LEDs or the IR emitter will be turned on at any given time.
*/
void shine_red() {
  digitalWrite(LED_INPUT_1, LOW);
  digitalWrite(LED_INPUT_2, LOW);
}
void shine_blue() {
  digitalWrite(LED_INPUT_1, LOW);
  digitalWrite(LED_INPUT_2, HIGH);
}
void shine_green() {
  digitalWrite(LED_INPUT_1, HIGH);
  digitalWrite(LED_INPUT_2, LOW);
}
void shine_IR(){
  digitalWrite(LED_INPUT_1, HIGH);
  digitalWrite(LED_INPUT_2, HIGH);
}

/*
* This function is employed to calibrate the LDR so that it is adapted to ambient lighting.
* It determines the values to be stored in respective arrays for subsequent color measurements.
*/
void setBalance() {
  // Calibrating white array
  Serial.println("Put White Sample For Calibration ...");

  // Delay 5s to get the white sample ready.
  delay(5000);

  /* Turn on each LED one at a time, wait for 400ms before scanning 5 times to take an average.
  * Set the readings for each color (red, green, and blue) to whiteArray.
  * Turn off all LEDs by activating the IR emitter at the end.
  */
  shine_red();
  delay(RGBWait);
  whiteArray[0] = getAvgReading(5);
  delay(RGBWait);
  shine_green();
  delay(RGBWait);
  whiteArray[1] = getAvgReading(5);
  delay(RGBWait);
  shine_blue();
  delay(RGBWait);
  whiteArray[2] = getAvgReading(5);
  delay(RGBWait);
  shine_IR();

  // Record white values down to store in white array.
  for(int i = 0; i < 3; i++) {
    Serial.println("White Indexes are:");
    Serial.println(whiteArray[i]);
  }

  // Calibrating black array
  Serial.println("Put Black Sample For Calibration ...");

  // Delay 5s to get black sample ready.
  delay(5000);

  /* Turn on each LED one at a time, wait for 400ms before scanning 5 times to take an average.
  * Set the readings for each color (red, green, and blue) to blackArray.
  * Turn off all LEDs by activating the IR emitter at the end.
  */
  shine_red();
  delay(RGBWait);
  blackArray[0] = getAvgReading(5);
  delay(RGBWait);
  shine_green();
  delay(RGBWait);
  blackArray[1] = getAvgReading(5);
  delay(RGBWait);
  shine_blue();
  delay(RGBWait);
  blackArray[2] = getAvgReading(5);
  delay(RGBWait);
  shine_IR();

  // Record black and grey values into black and grey array respectively.
  for(int i = 0; i < 3; i++) {
    Serial.println("Black Indexes are:");
    Serial.println(blackArray[i]);
    greyDiff[i] = whiteArray[i] - blackArray[i];
    Serial.println("Grey Ranges are:");
    Serial.println(greyDiff[i]);
  }

  // Delay 5s for us to transfer our robot to the maze to test.
  delay(5000);
}

/*
* Function is called whenever the robot detects a black line and stops. It then detects the color below.
* The function takes in the previously declared colourArray as it needs to store the final RGB readings in the array.
* The resulting colourArray allows us to determine what colour is below the robot.
*/
void detect_colour(int colourArray[]) {
  int red_readings[10];
  int green_readings[10];
  int blue_readings[10];
  int red_total = 0;
  int green_total = 0;
  int blue_total = 0;
  int red_average;
  int green_average;
  int blue_average;

  // Taking 10 samples for Red.
  shine_red();
  for(int i = 0; i < 10; i++) {
    red_readings[i] = ((float)(analogRead(LDR_SENSOR) - blackArray[0]))/(greyDiff[0])*255;
    Serial.println("Red readings are:");
    Serial.println(red_readings[i]);
  }

  // Taking 10 samples for Green.
  shine_green();
  for(int i = 0; i < 10; i++) {
    green_readings[i] = ((float)(analogRead(LDR_SENSOR) - blackArray[1]))/(greyDiff[1])*255;
    Serial.println("Green readings are:");
    Serial.println(green_readings[i]);
  }

  // Taking 10 samples for Blue.
  shine_blue();
  for(int i = 0; i < 10; i++){
    blue_readings[i] = ((float)(analogRead(LDR_SENSOR) - blackArray[2]))/(greyDiff[2])*255;
    Serial.println("Blue readings are:");
    Serial.println(blue_readings[i]);
  }

  // Take average for the last 5 readings for Red.
  for (int i = 5; i < 10; i++) {
    red_total += red_readings[i];
    red_average = red_total/5;
  }

  // Take average for the last 5 readings for Green.
  for (int i = 5; i < 10; i++) {
    green_total += green_readings[i];
    green_average = green_total/5;
  }

  // Take average for the last 5 readings for Blue.
  for (int i = 5; i < 10; i++) {
    blue_total += blue_readings[i];
    blue_average = blue_total/5;
  }

  // Storing the average values for each colour at respective index in colourArray, Red at index 0, Green at index 1, Blue at index 2.
  colourArray[0] = red_average;
  colourArray[1] = green_average;
  colourArray[2] = blue_average;

  // Tells us what is the final readings for the colour detected so that we can do the appropriate actions.
  Serial.println("Final Readings");
  for(int i=0; i<3; i++){
    Serial.println(colourArray[i]);
  }
}

/*
* Setting up the digital pins and begin serial communication with computer.
*/
void setup() {
  Serial.begin(9600);
  pinMode(LED_INPUT_1, OUTPUT);
  pinMode(LED_INPUT_2, OUTPUT);
  pinMode(ULTRASONIC, OUTPUT);
  // Calibrating the LDR. setBalance() is not called during the actual run as it is used during trial period only.
  setBalance();
}

void loop() {
  // Declare sensor state of line sensor.
  int sensorState = lineFinder.readSensors();

  /*
  * If black line is detected, stop the motors and begin detecting the colour beneath it.
  * Else, continue moving foward and nudges whenever it's too close to a wall.
  */
  if (sensorState == S1_IN_S2_IN || sensorState == S1_IN_S2_OUT || sensorState == S1_OUT_S2_IN) {

    // Black line detected thus stop motors and begin colour detecting.
    stop_motors();

    // Read the RGB values into colourArray.
    detect_colour(colourArray);

    // If white is detected, it signals the end of the maze hence it plays the celebratory tune.
    if (colourArray[0] > 140 && colourArray[1] > 210 && colourArray[2] > 210) { 
      celebrate();
      stop_motors();
      delay(100000);
    }

    // If purple is detected, do a double left turn in 2 grids.
    else if((colourArray[1] <= 180) && (colourArray[2] > colourArray[1]) && (colourArray[2] > colourArray[0])) {  
      double_left_turn();
    }

    // If orange is detected, do a u-turn on the spot.
    else if((colourArray[1] >= 130) && (colourArray[0] > colourArray[1]) && (colourArray[0] > colourArray[2])) {
      u_turn();
    }

    // If red is detected, turn left.
    else if((colourArray[1] < 130) && (colourArray[0] > colourArray[1]) && (colourArray[0] > colourArray[2])) { 
      turn_left();
      delay(TURNING_TIME_MS-80);
    }

    // If green is detected, turn right.
    else if((colourArray[1] > colourArray[0]) && (colourArray[1] > colourArray[2])) {
      turn_right();
      delay(TURNING_TIME_MS-100);  
    }

    // If blue is detected, do a double right turn in 2 grids
    else if((colourArray[1] > colourArray[0]) && (colourArray[2] > colourArray[1]) && (colourArray[2] > colourArray[0])) {
      double_right_turn();
    }

    // If colour detected is not recognise, retry after 50 milliseconds.
    else {
      delay(50);
    }
  }

  // No black line detected thus keep moving foward and nudge accordingly to distance to left and right wall.
  else {

    // The ultrasonic sensor sends out a pulse and returns the time taken to receive the reflected pulse.
    digitalWrite(ULTRASONIC, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC, LOW);
    pinMode(ULTRASONIC, INPUT);

    // Return 0 if the time taken to receive the reflected pulse exceed TIMEOUT.
    long duration = pulseIn(ULTRASONIC, HIGH, TIMEOUT);
    double distance_cm = duration / 2.0 / 1000000 * SPEED_OF_SOUND * 100;

    /*
    * Take the voltage reading of IR detector with IR emitter off.
    * Turn on the IR emitter and after letting it stabilise for 10ms, take the new voltage reading of IR detector and find the difference between this value and the previous one.
    * IR Emitter is then turned off by turning the blue LED back on.
    */
    int v1 = analogRead(IR_SENSOR);
    shine_IR();
    delay(10);
    int v2 = analogRead(IR_SENSOR);            
    shine_blue();

    // If the difference between the 2nd and 1st voltage reading exceeds 280, the robot is getting too close to the right wall and thus needs to nudge left.
    if ((v2 - v1) > 280) {    
      nudge_left();
      delay(5);
    }
    
    // If the robot is at a good distance away from the right wall, check the distance to the left wall using ultrasonic sensor.
    // If the distance is less than 8cm, the robot needs to nudge right as it is getting too close to the left wall.
    else if (distance_cm > 0 && distance_cm < 8) {
      nudge_right();
      delay(5);
    }

    // If both sides are at a good distance from the walls, continue moving straight.
    else{
      go_straight();
    }
  }
}
