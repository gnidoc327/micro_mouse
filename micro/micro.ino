#define motorEnable1 5
#define motorRight1 6
#define motorRight2 7
#define motorEnable2 10
#define motorLeft1 11
#define motorLeft2 12
#define ir_send A0
#define ir_receive1 A1
#define ir_receive2 A2
#define ir_receive3 A3

void setRightMotor() {
  digitalWrite(motorRight1, 0);
  digitalWrite(motorRight2, 1);
}

void setRightMotorReverse() {
  digitalWrite(motorRight1, 1);
  digitalWrite(motorRight2, 0);
}

void setLeftMotor() {
  digitalWrite(motorLeft1, 1);
  digitalWrite(motorLeft2, 0);
}

void setLeftMotorReverse() {
  digitalWrite(motorLeft1, 0);
  digitalWrite(motorLeft2, 1);
}

void setLeftMotorStop(){
  digitalWrite(motorLeft1, 0);
  digitalWrite(motorLeft2, 0);
}

void setRightMotorStop(){
  digitalWrite(motorRight1, 0);
  digitalWrite(motorRight2, 0);

}

void motorStop(){
  setRightMotorStop();  
  setLeftMotorStop();  
}

void go(){
  setLeftMotorReverse();
  setRightMotorReverse();
  delay(900);  
}

void back(){
  setLeftMotor();
  setRightMotor();    
  delay(900);  
}

void turnLeft(){
  setLeftMotor();
  setRightMotorReverse();
  delay(450);
}

void turnRight(){
  setLeftMotorReverse();
  setRightMotor();        
  delay(450);
}

void mouseRun(){
  //0 = left
  //1 = go
  //2 = right
  int way = ir_sencing();
  Serial.println(way);
  switch(way){
    case 0:
      turnLeft();
      go();
      break;
    case 1:
      go();
      break;
    case 2:
      turnRight();
      go();
      break;
    case 3:
      turnLeft();
      turnLeft();
      break;
  }
  motorStop();
  delay(1000);
}

int ir_sencing(){
  //return value
  //0 = left way
  //1 = go
  //2 = right way
  int ir1 = 0;
  int ir2 = 0;
  int ir3 = 0; 
  int count = 0;
  
  while(count++ < 10){
    ir1 += analogRead(ir_receive1);
    ir2 += analogRead(ir_receive2);
    ir3 += analogRead(ir_receive3);
  }
  ir1 = ir1/10;
  ir2 = ir2/10;
  ir3 = ir3/10;

  Serial.print(ir1);
  Serial.print(" || ");
  Serial.print(ir2);
  Serial.print(" || ");
  Serial.println(ir3);
  
  if(ir1<20){
    return 0;
  }
  if(ir2<30){
    return 1;  
  }
  if(ir3<30){
    return 2;  
  }
  return 3;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(motorEnable1, OUTPUT);
  pinMode(motorEnable2, OUTPUT);
  pinMode(motorLeft1, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight1, OUTPUT);
  pinMode(motorRight2, OUTPUT);
  pinMode(ir_send, OUTPUT);
  pinMode(ir_receive1, INPUT);
  pinMode(ir_receive2, INPUT);
  pinMode(ir_receive3, INPUT);
  Serial.begin(9600);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  analogWrite(motorEnable1, 254);
  analogWrite(motorEnable2, 254);
  digitalWrite(ir_send, HIGH);
  mouseRun();
}


