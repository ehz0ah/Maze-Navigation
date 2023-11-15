#include <MeMCore.h> //include Mbot library

#define TURNING_TIME_MS 410 // The time duration (ms) for turning
#define TIMEOUT 1400 // Max microseconds to wait before moving on
#define SPEED_OF_SOUND 340 // Speed of sound to be 340m/s
#define ULTRASONIC 12 //Pin 12 (Port 1) for the ultrasonic sensor
#define IR_SENSOR A2 //Pin S1 of Port 3 is used to read voltage readings from the IR sensor
#define LDR_SENSOR A3 //Pin S2 of Port 3 is used to read voltage readings from the LDR sensor
#define LED_INPUT_1 A0 //Pin S1 of Port 4 is used to control input 1A on LS139P chip
#define LED_INPUT_2 A1 //Pin S2 of Port 4 is used to control input 1B on LS139P chip
#define LDRWait 100 // Define time delay before taking another LDR reading (in ms)
#define RGBWait 400 // Define time delay (in ms) before changing to another LED colour

MeBuzzer buzzer;// create the buzzer object
MeDCMotor leftMotor(M1); // assigning leftMotor to port M1
MeDCMotor rightMotor(M2); // assigning RightMotor to port M2
MeLineFollower lineFinder(PORT_2); // assigning lineFinder to RJ25 port 2


// Setting up default motor speeds to 220/255
uint8_t motorSpeed_left = 220;
uint8_t motorSpeed_right = 220;

/*
* Values for colour sensor calibration and measurements are stored as ints
* whiteArray, blackArray, greyDiff are used to calibrate the LDR and all subsequent colour measurements will be based off the values stored in these arrays
* colourArray holds the final RGB values measured by the LDR to be used for colour identification
*/
int colourArray[] = {0,0,0};
int whiteArray[] = {870,957,955};
int blackArray[] = {320,720,769};
int greyDiff[] =  {550,237,186};

/*
* The numbers in the bracket specify the frequency (represented by note) and the duration (ms)
* This function calls the Mcore to play Star Wars Theme
*/
void play_tune(){
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

//Find the average reading for the requested number of times of scanning LDR
int getAvgReading(int times){
int reading;
int total = 0;
//Take the reading as many times as requested and add them up, delaying 10ms in between taking each reading
for(int i = 0; i < times ; i++){
reading = analogRead(LDR_SENSOR);
total = reading + total;
delay(LDRWait);
}
//Calculate the average and return it
return total/times;
}

// Function to move the robot forward/straight
void go_straight(){
leftMotor.run(-motorSpeed_left - 35); // Negative: wheel turns anti-clockwise -35
rightMotor.run(motorSpeed_right + 10); // Positive: wheel turns clockwise +35
}


// Function that tells robot to turn left
void turn_left(){
leftMotor.run(motorSpeed_left); // Positive: wheel turns clockwise
rightMotor.run(motorSpeed_right); // Positive: wheel turns clockwise
}


// Function that tells robot to turn right
void turn_right(){
leftMotor.run(-motorSpeed_left); // Negative: wheel turns anti-clockwise
rightMotor.run(-motorSpeed_right); // Negative: wheel turns anti-clockwise
}


// Function that tells robot to stop moving
void stop_motors(){
leftMotor.stop(); // Stop left motor
rightMotor.stop(); // Stop right motor
}

// Function that tells motor to go slightly right
void nudge_right(){
leftMotor.run(-(motorSpeed_left+35)); // Negative: wheel turns anti clockwise
rightMotor.run(motorSpeed_right-35); // Positive: wheel turns clockwise
//Serial.println(197420);
}


// Function that tells motor to go slightly left
void nudge_left(){
leftMotor.run(-(motorSpeed_left-35)); // Negative: wheel turns anti-clockwise
rightMotor.run(motorSpeed_right+35); // Positive: wheel turns clockwise
}


// Function to u-turn the robot on the spot (orange waypoint)
void u_turn() {
turn_right();
delay(2*TURNING_TIME_MS-230);
}


// Function to make 2 consecutive left turns (purple)
void two_left_turns(){
turn_left();
delay(TURNING_TIME_MS-70);  
go_straight();
delay(680);
turn_left();
delay(TURNING_TIME_MS-50);
}


// Function to make 2 consecutive right turns (blue)
void two_right_turns(){
turn_right();
delay(TURNING_TIME_MS-80);
go_straight();
delay(730);
turn_right();
delay(TURNING_TIME_MS-80);
}

/*
* Controlling the digital pins of red, blue, green LEDs and the IR emitter
* At any one time, only one of the LEDs or the IR emitter will be turned on with the others turned off
*/
void turn_on_red(){
digitalWrite(LED_INPUT_1, LOW);
digitalWrite(LED_INPUT_2, LOW);
}
void turn_on_blue(){
digitalWrite(LED_INPUT_1, LOW);
digitalWrite(LED_INPUT_2, HIGH);
}
void turn_on_green(){
digitalWrite(LED_INPUT_1, HIGH);
digitalWrite(LED_INPUT_2, LOW);
}
void turn_on_IR(){
digitalWrite(LED_INPUT_1, HIGH);
digitalWrite(LED_INPUT_2, HIGH);
}

/*
* This function is used to calibrate the LDR to adjust to ambient lighting, it is used to determine the values to be stored in the respective arrays to be used for colour measurements
*/
void setBalance(){
//Set white balance
Serial.println("Put White Sample For Calibration ...");
delay(5000);
//Delay for five seconds for getting white sample ready
//Scan the white sample
//Turn on each LED one at a time, wait for 400ms before scanning 5 times to take average, and set the reading for each colour - red, green and blue - to whiteArray, turn off all LEDs by turning on IR emitter at the end
turn_on_red();
delay(RGBWait);
whiteArray[0] = getAvgReading(5);
delay(RGBWait);
turn_on_green();
delay(RGBWait);
whiteArray[1] = getAvgReading(5);
delay(RGBWait);
turn_on_blue();
delay(RGBWait);
whiteArray[2] = getAvgReading(5);
delay(RGBWait);
turn_on_IR();
//Helps us to record the values stored to whiteArray
for(int i = 0; i < 3; i++){
Serial.println("White Indexes are:");
Serial.println(whiteArray[i]);
}
//Set black balance
Serial.println("Put Black Sample For Calibration ...");
delay(5000);
//Delay for five seconds for getting black sample ready
//Scan the black sample
//Turn on each LED one at a time, wait for 400ms before scanning 5 times to take average, and set the reading for each colour - red, green and blue - to blackArray, turn off all LEDs by turning on IR emitter at the end
turn_on_red();
delay(RGBWait);
blackArray[0] = getAvgReading(5);
delay(RGBWait);
turn_on_green();
delay(RGBWait);
blackArray[1] = getAvgReading(5);
delay(RGBWait);
turn_on_blue();
delay(RGBWait);
blackArray[2] = getAvgReading(5);
delay(RGBWait);
turn_on_IR();
//Helps us to record the values stored to blackArray and greyDiff
for(int i = 0; i < 3; i++){
Serial.println("Black Indexes are:");
Serial.println(blackArray[i]);
//The difference between the maximum and the minimum gives the range
greyDiff[i] = whiteArray[i] - blackArray[i];
Serial.println("Grey Ranges are:");
Serial.println(greyDiff[i]);
}
delay(7000);
//Delay 7 seconds for transferring of robot to maze for test run during our trials, this is not used for the actual run
}


void detect_colour(int colourArray[]){
int red_readings[10];
int green_readings[10];
int blue_readings[10];
int red_total = 0;
int green_total = 0;
int blue_total = 0;
int red_average;
int green_average;
int blue_average;
//Taking one sample at a time, total of 10 samples for R
turn_on_red();
for(int i = 0; i < 10; i++){
red_readings[i] = ((float)(analogRead(LDR_SENSOR) - blackArray[0]))/(greyDiff[0])*255;
Serial.println("Red readings are:");
Serial.println(red_readings[i]);
}
//Taking one sample at a time, total of 10 samples for G
turn_on_green();
for(int i = 0; i < 10; i++){
green_readings[i] = ((float)(analogRead(LDR_SENSOR) - blackArray[1]))/(greyDiff[1])*255;
Serial.println("Green readings are:");
Serial.println(green_readings[i]);
}
//Taking one sample at a time, total of 10 samples for B
turn_on_blue();
for(int i = 0; i < 10; i++){
blue_readings[i] = ((float)(analogRead(LDR_SENSOR) - blackArray[2]))/(greyDiff[2])*255;
Serial.println("Blue readings are:");
Serial.println(blue_readings[i]);
}
//Take average for the last 5 readings for R
for (int i = 5; i < 10; i++){
red_total += red_readings[i];
red_average = red_total/5;
}
//Take average for the last 5 readings for B
for (int i = 5; i < 10; i++){
blue_total += blue_readings[i];
blue_average = blue_total/5;
}
//Take average for the last 5 readings for G
for (int i = 5; i < 10; i++){
green_total += green_readings[i];
green_average = green_total/5;
}
//Store the 3 average values at their respective positions in colourArray
colourArray[0] = red_average;
colourArray[1] = green_average;
colourArray[2] = blue_average;
//To check the final RGB values recorded

Serial.println("Final Readings");
for(int i=0; i<3; i++){
Serial.println(colourArray[i]);
}

}

/*
* Setting up the digital pins and begin serial communication with computer
*/
void setup() {
Serial.begin(9600);
pinMode(LED_INPUT_1, OUTPUT);
pinMode(LED_INPUT_2, OUTPUT);
pinMode(ULTRASONIC, OUTPUT);
//setBalance();
//setBalance() is only run during trial period
}

void loop(){
//Declare sensor state of line sensor
int sensorState = lineFinder.readSensors();

/*
* If black line is detected, stop the robot and detect the colour below
* If not, keep the robot going and adjust whenever its too close to wall
*/
if (sensorState == S1_IN_S2_IN || sensorState == S1_IN_S2_OUT || sensorState == S1_OUT_S2_IN){
stop_motors();
//read the RGB values of the current colour into colourArray
detect_colour(colourArray);
//if white, play star wars theme
if (colourArray[0] > 140 && colourArray[1] > 210 && colourArray[2] > 210){  
play_tune();
stop_motors();
delay(100000);
}
//if purple, 2 left turns in 2 grids
else if((colourArray[1] <= 160) && (colourArray[2] > colourArray[1]) && (colourArray[2] > colourArray[0])){  
two_left_turns();
}
//if orange, turn 180 degrees in same grid
else if((colourArray[1] >= 130) && (colourArray[0] > colourArray[1]) && (colourArray[0] > colourArray[2])){ 
u_turn();
}
//if red, turn left
else if((colourArray[1] < 130) && (colourArray[0] > colourArray[1]) && (colourArray[0] > colourArray[2])){ 
turn_left();
delay(TURNING_TIME_MS-80);
}
//if green, turn right
else if((colourArray[1] > colourArray[0]) && (colourArray[1] > colourArray[2])){
turn_right();
delay(TURNING_TIME_MS-90);
}
//if light blue, 2 right turns in 2 grids
else if((colourArray[1] > colourArray[0]) && (colourArray[2] > colourArray[1]) && (colourArray[2] > colourArray[0])){
two_right_turns();
}
//if unable to recognise colour,delay 50ms and try again
else {
delay(50);
}
}else{
//The ultrasonic sensor sends out a pulse and returns the time taken to receive the reflected pulse
digitalWrite(ULTRASONIC, LOW);
delayMicroseconds(2);
digitalWrite(ULTRASONIC, HIGH);
delayMicroseconds(10);
digitalWrite(ULTRASONIC, LOW);
pinMode(ULTRASONIC, INPUT);
long duration = pulseIn(ULTRASONIC, HIGH, TIMEOUT);
//distance of wall in cm from ultrasonic sensor is calculated using the duration
double distance_cm = duration / 2.0 / 1000000 * SPEED_OF_SOUND * 100;

/*
* Take voltage reading of IR detector with IR emitter off (blue is lit by default)
* Turn on IR emitter, let it stabilise for 10ms, take new voltage reading of IR detector and find the difference between this value and the previous one
* Emitter is then turned off by turning blue LED back on
*/
int v1 = analogRead(IR_SENSOR);
turn_on_IR();
delay(10);
int v2 = analogRead(IR_SENSOR);     
turn_on_blue();

/*
* If the difference between the 2 IR detector readings is above 330, it suggests the mBot is dangerously close to the right wall and need to turn slightly left
* If not in danger of hitting right wall, check if the ultrasonic sensor is deducing the mBot is within 8cm of left wall
* If within 9cm of left wall, turn slightly right, if not, the mBot is safe on both sides and can proceed straight
*/
if ((v2 - v1) > 330){
nudge_left();
delay(20);
}else if (distance_cm > 0 && distance_cm < 8){
nudge_right();
delay(5);
}else{
go_straight();
}
}
}
