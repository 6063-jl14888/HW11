int STATE_0 = 0;
int STATE_1 = 1;

int cState = STATE_0;
int cCount = 0;

void setup() {
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
  for (int i = 6; i < 10; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  int v2 = digitalRead(2);
  int a0 = analogRead(A0);

  for (int i = 6; i < 10; i++) {
    int threshold = map(i, 6, 9, 1000, 4000);
    int v = a0 > threshold;
    if (cState == STATE_1 && a0 > 4000) {
      digitalWrite(i, LOW);  
    } else {
      digitalWrite(i, v);
    }
  }

  if (cState == STATE_0 && v2 == 1){
    cCount += 1;
    cState = STATE_1;
  } else if(cState == STATE_1 && v2 == 0){
    cState = STATE_0;
  }

  if (cState == STATE_1 && a0 > 4000) { 
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }

  delay(20);
}
