#define ir_send A0
#define ir_receive1 A1
#define ir_receive2 A2
#define ir_receive3 A3


void setup() {
  // put your setup code here, to run once:
  pinMode(ir_send, OUTPUT);
  pinMode(ir_receive1, INPUT);
  pinMode(ir_receive2, INPUT);
  pinMode(ir_receive3, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ir_send, HIGH);

  int direct1 = 0;
  int direct2 = 0;
  int direct3 = 0;
    int count = 0;
    while(count < 10){
      direct1 += analogRead(ir_receive1);
      direct2 += analogRead(ir_receive2);
      direct3 += analogRead(ir_receive3);
      count++;
    }
    Serial.print(direct1/10);
    Serial.print("  ||  ");
    Serial.print(direct2/10);
    Serial.print("  ||  ");
    Serial.println(direct3/10);
    delay(100);
}
