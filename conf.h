//L298N MOTOR
#define RIGHT_IN1 4
#define RIGHT_IN2 2
#define LEFT_IN3 7
#define LEFT_IN4 8
#define RIGHT_PWM_ENA 5 //Must be PWM
#define LEFT_PWM_ENB 6  //Must be PWM

#define COMP_SPEED_R 0
#define COMP_SPEED_L 10

#define V_NORMAL 90 //Was 80
#define V_TURN 150 

//HCSR04 RADAR
#define RADAR_ZERO_OFFSET -5 //Deg ° -- compensation of setup

#define MAX_DISTANCE_TIME 6000 //102 cm
#define RADAR_SERVO_PIN 3 //Must be PWM
#define SERVO_DELAY 250

#define HC_TRIGGER 9
#define HC_ECHO 10

//CONTROL ALG
#define MAX_DISTANCE_BEFORE_TURN 40 //Cm
#define SAFE_DISTANCE 5 //Cm
#define ROTATATION_TIME 160
#define ROTATATION_STOP_TIME 500

#define DELAY_SERVO_PARK 500

//IR 
#define IR_PIN 13
#define IR_PULLUP_PIN A0