#define enablePin 9
#define in1Pin 11
#define in2Pin 8
#define enable2Pin 10
#define in2_1Pin 13
#define in2_2Pin 12

#define tactPin A0
#define trigPin 5 // Trigger Pin


boolean LForward = true; // 전진 후진 선택 변수
boolean RForward = true; // 전진 후진 선택 변수

int leftPower = 200;
int rightPower = 220;

int tactInput = false;

int echoPin[3] = {2, 3, 4};

int duration[3], distance[3], distance_2[3]; // Duration used to calculate distance

void setup() {

  Serial.begin (9600);

  pinMode(trigPin, OUTPUT);

  pinMode(echoPin[0], INPUT);  //sound 123
  pinMode(echoPin[1], INPUT);
  pinMode(echoPin[2], INPUT);

  pinMode(7, OUTPUT);
  pinMode(A1, INPUT);
}



void loop() {
  int light=0;
  
  microRun();

  digitalWrite(7, true);
  light = analogRead(A1);
  if(light < 200){
      microGo();
      delay(500);
      microStop();
      delay(5000);
  }
  Serial.println(light);
}

void calcDistance() {
  int a = 0;

  for (a = 0; a < 3; a++) { // 2,3,4 번 핀 읽기
    digitalWrite(trigPin, LOW);
    delayMicroseconds(100);
    digitalWrite(trigPin, HIGH);

    duration[a] = pulseIn(echoPin[a], HIGH);
    distance[a] = distance_2[a];
    distance_2[a] = duration[a] / 58.2;
    if (distance_2[a] == 0 ) {
      distance_2[a] = distance[a];
    }
  }
}

int checkWall() {
  if(distance[0] > 3){
    return 0;
  } else if(distance[1] > 3){
    return 1;
  } else if(distance[2] > 3){
    return 2;
  } else {
    return 3;  
  }
}

void microRun(){
  calcDistance(); 
  switch(checkWall()){
  case 0:
    microLeft();
  break;  
  case 1:
    microGo();
  break;  
  case 2:
    microRight();
//    delay(500);
  break;  
  case 3:
    microBack();
//    delay(200);
  break;  
  }  
/*    Serial.print(distance[0]);
  Serial.print("     ");
  Serial.print(distance[1]);
  Serial.print("     ");
  Serial.println(distance[2]);
*/  delay(50);
  microStop();
  delay(50);
}

void microLeft(){
  setMotor(100, rightPower, true, true); 
}

void microGo(){
  setMotor(leftPower, rightPower, true, true);   
}

void microRight(){
  setMotor(leftPower, 110, true, true); 
}

void microStop(){
  setMotor(0, 0, true, true);   
}

void microBack(){
  setMotor(leftPower, rightPower, false, false); 
}


void setMotor(int Lpower, int Rpower , boolean LForward, boolean RForward) { // 모터제어 함수
  analogWrite(enablePin, Lpower); // Lpower값으로 enable핀 PWM 제어
  digitalWrite(in1Pin,  LForward); // !는 inverter 역할으로, 0이면 1로 1은 0으로 변환
  digitalWrite(in2Pin,  ! LForward); // 한쪽이 1이면 다른쪽이 0이여야 하므로
  analogWrite(enable2Pin, Rpower);
  digitalWrite(in2_1Pin, RForward);
  digitalWrite(in2_2Pin, ! RForward); // 왼쪽 모터 제어와 오른쪽 모터에서 ! 위치가 다른
  //이유는 모터가 180도 대칭이여서 같은 방향으로 하면 반대방향으로 돌기 때문입니다.
}
