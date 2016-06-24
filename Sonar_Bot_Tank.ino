#define FULL_SPEED 255
#define LEFT_WHEELS 1
#define RIGHT_WHEELS 2

#define trigPin 7
#define echoPin 6
//motor A connected between A01 and A02
//motor B connected between B01 and B02

const int FORWARD = 1;
const int BACKWARD = 0;

int STBY = 10; //standby

//Motor A
int PWMA = 3; //Speed control
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

void setup() {
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int getDistance() {

  long duration, distance;

  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration / 2) / 29.1;

  Serial.println(distance); 

  return distance;

  

//  if (distance >= 200 || distance <= 0) {
//    Serial.println("Out of range");
//    Serial.println(distance);
//  }
//  else {
//    Serial.print(distance);
//    Serial.println(" cm");
//    return distance;
//  }

//  return -1;
}

//////////////////////////////////////////////////////

void loop() {

  check();

}

//////////////////////////////////////////////////////

void check() {

  objectCheck();

}

//////////////////////////////////////////////////////

void objectCheck() {

  int dist = getDistance();

  if (dist > 30) {

    drive();

  } else {

    stop();

    delay(500);

    int distLeft = checkLeft();

    delay(1000);

    origin('L');

    delay(1000);

    int distRight = checkRight();

    delay(1000);

    origin('R');

    delay(1000);

    char direction = distanceCalculation(distRight, distLeft);

    switch (direction) {

      case 'L':

        moveLeft();

        break;

      case 'R':

        moveRight();

        break;

      default:

        reverse();

        break;

    }
  }
}

//////////////////////////////////////////////////////

int checkLeft() {

  reverse();

  stop();

  move(LEFT_WHEELS, 200, BACKWARD);
  move(RIGHT_WHEELS, 200, FORWARD);

  delay(500);

  stop();

  int distLeft = getDistance();

  return distLeft;

}

//////////////////////////////////////////////////////

int checkRight() {

  move(LEFT_WHEELS, 200, FORWARD);
  move(RIGHT_WHEELS, 200, BACKWARD);

  delay(500);

  stop();

  int distRight = getDistance();

  return distRight;

}

//////////////////////////////////////////////////////

void origin(char direction) {

  stop();
  delay(1000);

  // check which way it turns first to determine which way to reverse.

  switch (direction) {

    case 'L':

      // if checkLeft() has been called

      move(LEFT_WHEELS, 200, FORWARD);
      move(RIGHT_WHEELS, 200, BACKWARD);

      delay(500);

      stop();

      break;

    case 'R':

      // if checkRight() has been called

      move(LEFT_WHEELS, 200, BACKWARD);
      move(RIGHT_WHEELS, 200, FORWARD);

      delay(500);

      stop();
      
      break;

  }

}

//////////////////////////////////////////////////////

char distanceCalculation(int distLeft, int distRight) {

  delay(1000);

  if (distLeft > distRight) {

    return 'L';

  } else if (distRight > distLeft) {

    return 'R';

  } else {

    return 'B';

  }

  //else if(distLeft == distRight){

  //return 'B';

  // }


}

//////////////////////////////////////////////////////

void moveLeft() {

  stop();

  delay(1000);

  move(LEFT_WHEELS, 200, BACKWARD);
  move(RIGHT_WHEELS, 200, FORWARD);

  delay(500);

  stop();

}

//////////////////////////////////////////////////////

void moveRight() {

  stop();

  delay(1000);

  move(LEFT_WHEELS, 200, FORWARD);
  move(RIGHT_WHEELS, 200, BACKWARD);

  delay(500);

  stop();

}

//////////////////////////////////////////////////////

void drive() { 

  move(LEFT_WHEELS, FULL_SPEED, FORWARD);
  move(RIGHT_WHEELS, FULL_SPEED, FORWARD);

}

/////////////////////////////////////////////////////

void reverse() {

    move(LEFT_WHEELS, 200, BACKWARD);
    move(RIGHT_WHEELS, 200, BACKWARD);

    delay(1000);

    stop();

}

//////////////////////////////////////////////////////

void move(int motor, int speed, int direction) {
  //Move specific motor at speed and direction
  //motor: 0 for B 1 for A
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if (motor == 1) {
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  } else {
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop() {
  //enable standby
  digitalWrite(STBY, LOW);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Test 1.0
