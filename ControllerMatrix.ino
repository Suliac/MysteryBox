void setup() {
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(13, INPUT);

  // MATRIX
  
  // GND COL
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  // 5V ROW
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  
  Serial.begin(9600);
}

bool matrix[][3] = {
  {true, true, false},
  {false, false, true},
  {true, false, true}
};

bool buttonMatrix[][3] = {
  {false, false, false},
  {false, false, false},
  {false, false, false}
};

void loop() {
  buttonMatrix[0][0] = digitalRead(4);
  buttonMatrix[0][1] = digitalRead(5);
  buttonMatrix[0][2] = digitalRead(6);
  
  buttonMatrix[1][0] = analogRead(A0)>500;
  buttonMatrix[1][1] = analogRead(A1)>500;
  buttonMatrix[1][2] = analogRead(A2)>500;

  buttonMatrix[2][0] = digitalRead(2);
  buttonMatrix[2][1] = digitalRead(3);
  buttonMatrix[2][2] = digitalRead(13);

  unsigned int id   = 0b00000011;
  unsigned int vic  = 0b10000000;
  Serial.write((id | vic));
  
  for(int col = 7; col <= 9; col++) {
    digitalWrite(10, buttonMatrix[col-7][0] ? HIGH : LOW);
    digitalWrite(11, buttonMatrix[col-7][1] ? HIGH : LOW);
    digitalWrite(12, buttonMatrix[col-7][2] ? HIGH : LOW);
    digitalWrite(col, LOW);
    delayMicroseconds(1000);
    digitalWrite(col, HIGH);
  }
}
