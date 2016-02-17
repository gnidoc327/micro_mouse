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
int Lpower ;
int Rpower ;
int tactInput = false;



int echoPin[3] = {2, 3, 4};

int duration[3], distance[3], distance_2[3]; // Duration used to calculate distance

void setup() {

  Serial.begin (9600);

  pinMode(trigPin, OUTPUT);

  pinMode(2, INPUT);  //sound 123
  pinMode(3, INPUT);
  pinMode(4, INPUT);

}



void loop() {

  int &L = distance[0];
  int &F = distance[1];
  int &R = distance[2];


  int a = 0;
  for (a = 0; a < 3; a++) { // 2,3,4 번 핀 읽기
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration[a] = pulseIn(echoPin[a], HIGH);
    delay(10);
    distance[a] = distance_2[a];
    distance_2[a] = duration[a] / 58.2;
    if (distance_2[a] == 0 ) {
      distance_2[a] = distance[a];
    }
  
    Serial.print(distance[a]);
    Serial.print("   ");
  }
  Serial.println();


  Lpower = 0; // 왼쪽 모터의 속도 0~255 까지 변화 가능
  Rpower = 0; // 오른쪽 모터 속도 0~255 까지 변화 가능
  LForward = true; // 왼쪽 모터 순방향 false 이면 역방향 납땜과 선 연결따라 다를 수 있음
  RForward = true; // 오른쪽 모터 순방향
  setMotor(Lpower, Rpower, LForward, RForward); // 모터 제어 함수


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
