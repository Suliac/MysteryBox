void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  // MATRIX
  
  // GND COL
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  // 5V ROW
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  Serial.begin(9600);
}

bool matrix[][3] = {
  {true, true, true},
  {true, true, true},
  {true, true, true}
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
  
  for(int col = 8; col <= 10; col++) {
    digitalWrite(11, matrix[col-8][0] ? HIGH : LOW);
    digitalWrite(12, matrix[col-8][1] ? HIGH : LOW);
    digitalWrite(13, matrix[col-8][2] ? HIGH : LOW);
    digitalWrite(col, LOW);
    delayMicroseconds(1000);
    digitalWrite(col, HIGH);
  }
}
