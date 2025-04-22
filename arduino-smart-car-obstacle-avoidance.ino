#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200
#define MOTOR_SPEED 100 // sets speed of DC motors
#define OBSTACLE_THRESHOLD 20 // 15 cm threshold for stopping

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;

int command; // Variable to store the command from the Bluetooth module
int speedCar = 100; // Initial car speed set to maximum (0 to 255)
int turnSpeed = 255; // Speed for turning
boolean goesForward = false;
int distance = 100;

void setup() {
  Serial.begin(9600);
  myservo.attach(10);
  myservo.write(90);  // Center the servo
  delay(2000);
  distance = readPing();
  delay(100);
  Stop(); // Initialize with motors stopped
}

void loop() {
  // Check if serial data is available
  if (Serial.available() > 0) {
    command = Serial.read(); // Read the command from the Bluetooth module

    switch (command) {
      case 'A': // Command to stop all functions
        stopAll();
        break;
      case 'B': // Command to activate obstacle avoidance
        while (command == 'B') {
          activateObstacleAvoidance();
          delay(100); // Adjust delay as needed to control loop timing
          if (Serial.available() > 0) {
            command = Serial.read(); // Read next command
          }
        }
        break;
      case '1': // Command to move forward
        speedCar = 100;
        forward();
        break;
      case '2': // Command to move backward
        backward();
        break;
      case '4': // Command to turn left
        turnLeft();
        break;
      case '3': // Command to turn right
        turnRight();
        break;
      case 'S': // Command to stop
        Stop();
        break;
    }
  }

  // Regular obstacle avoidance check if not interrupted by other commands
  if (command != 'B') {
    distance = readPing();
    if (distance <= OBSTACLE_THRESHOLD) {
      moveStop();
      lookAround();
    } else {
      moveForward();
    }
  }

  delay(100); // Adjust delay as needed to control loop timing
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = MAX_DISTANCE;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  goesForward = false;
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    motor1.setSpeed(MOTOR_SPEED);
    motor2.setSpeed(MOTOR_SPEED);
    motor3.setSpeed(MOTOR_SPEED);
    motor4.setSpeed(MOTOR_SPEED);
  }
}

void lookAround() {
  int distanceR = 0;
  int distanceL = 0;

  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if (distanceR >= distanceL) {
    turnRight();
  } else {
    turnLeft();
  }
}

int lookRight() {
  myservo.write(0);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(90);
  return distance;
}

int lookLeft() {
  myservo.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(90);
  return distance;
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.setSpeed(MOTOR_SPEED);
  motor2.setSpeed(MOTOR_SPEED);
  motor3.setSpeed(MOTOR_SPEED);
  motor4.setSpeed(MOTOR_SPEED);
  delay(500);
  moveStop();
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor1.setSpeed(MOTOR_SPEED);
  motor2.setSpeed(MOTOR_SPEED);
  motor3.setSpeed(MOTOR_SPEED);
  motor4.setSpeed(MOTOR_SPEED);
  delay(500);
  moveStop();
}

void stopAll() {
  Stop(); // Stop motors
  // Additional functions or actions to stop other systems if needed
}

void activateObstacleAvoidance() {
  distance = readPing();
  if (distance <= OBSTACLE_THRESHOLD) {
    moveStop();
    lookAround();
  } else {
    moveForward();
  }
}

void forward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor1.setSpeed(speedCar);
  motor2.setSpeed(speedCar);
  motor3.setSpeed(speedCar);
  motor4.setSpeed(speedCar);
}

void backward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.setSpeed(speedCar);
  motor2.setSpeed(speedCar);
  motor3.setSpeed(speedCar);
  motor4.setSpeed(speedCar);
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
