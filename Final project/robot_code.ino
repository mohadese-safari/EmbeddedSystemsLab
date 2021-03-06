//Initializing LED Pin
int left_motor = 6;
int right_motor = 5;
int left_left_sensor = A1;
int left_sensor = A2;
int middle_sensor = A3;
int right_sensor = A4;
int right_right_sensor = A5;
int max_speed = 200;
int min_speed = 20;
int middle_speed = 110;
int standard_speed = 150;
int sensitivity = 200;
void setup() {
  Serial.begin(9600);
  pinMode(right_motor, OUTPUT);
  pinMode(left_motor, OUTPUT);
  pinMode(left_sensor, INPUT);
  pinMode(middle_sensor, INPUT);
  pinMode(right_sensor, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void fastRotateRight() {
  analogWrite(right_motor, min_speed);
  analogWrite(left_motor, standard_speed);
}

void fastRotateLeft() {
  analogWrite(left_motor, min_speed);
  analogWrite(right_motor, standard_speed);
}

void slowRotateRight() {
  analogWrite(right_motor, min_speed);
  analogWrite(left_motor, standard_speed);
}

void slowRotateLeft() {
  analogWrite(left_motor, min_speed);
  analogWrite(right_motor, standard_speed);
}

void forward() {
  analogWrite(left_motor, standard_speed);
  analogWrite(right_motor, standard_speed);
}

int see(int sensor) {
  int result = analogRead(sensor);
  if (result < sensitivity)
    return 1;
  return 0;
}

void loop() {
//      Serial.print(see(right_right_sensor));
//      Serial.print(" ");
//      Serial.print(see(right_sensor));
//      Serial.print(" ");
//      Serial.print(see(middle_sensor));
//      Serial.print(" ");
//      Serial.print(see(left_sensor));
//      Serial.print(" ");
//      Serial.print(see(left_left_sensor));
//      Serial.println(" ");

//  slowRotateRight();
    if (see(right_right_sensor)) {
      slowRotateRight();
    }
  
    else if (see(left_left_sensor)) {
      slowRotateLeft();
    }
  
    else if (see(right_sensor)) {
      slowRotateRight();
    }
    else if (see(left_sensor)) {
      slowRotateLeft();
    } else if (see(middle_sensor)) {
      forward();
    }
}