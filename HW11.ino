int STATE_0 = 0;
int STATE_1 = 1;

int cState = STATE_0;
int cCount = 0;

int STATE_a = 0;
int STATE_b = 1;

int cState1 = STATE_a;
int cCount1 = 0;

void setup() {
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
  for (int i = 6; i < 10; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  int v2 = digitalRead(2);
  int v3 = digitalRead(3);
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

  if (cState == STATE_0 && v2 == 1) {
    cCount += 1;
    cState = STATE_1;
  } else if (cState == STATE_1 && v2 == 0) {
    cState = STATE_0;
  }

  if (cState1 == STATE_a && v3 == 1) {
    cCount1 += 1;
    cState1 = STATE_b;
  } else if (cState1 == STATE_b && v3 == 0) {
    cState1 = STATE_a;
  }

  if (cState == STATE_1 && a0 > 4000 && cState1 == STATE_b) {
    digitalWrite(5, LOW);
    digitalWrite(11, LOW);
    digitalWrite(4, HIGH);
  } else if (cState == STATE_0 && a0 < 1000 && cState1 == STATE_a) {
    digitalWrite(5, HIGH); 
    digitalWrite(11, LOW);
    digitalWrite(4, LOW);
  } else if (cState == STATE_0 && a0 >= 1000 && a0 <= 4000 && cState1 == STATE_a) {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(11, HIGH);
    delay(500);
    digitalWrite(11, LOW);
    delay(200);
  } else if (cState == STATE_1 || cState1 == STATE_b) { 
    digitalWrite(5, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(4, LOW);
    digitalWrite(11, HIGH);
    delay(500);
    digitalWrite(11, LOW);
    delay(200);
  }


  delay(20);
  }
