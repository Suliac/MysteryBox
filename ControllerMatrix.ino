unsigned int CONTROLLER_ID   = 0b00000011; // Change for each controller.

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  // MATRIX
  
  // GND COL
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  // 5V ROW
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  Serial.begin(9600);
}

bool matrix[][3] = {
  {true, false, true},
  {false, true, false},
  {true, false, true}
};

bool buttonMatrix[][3] = {
  {false, false, false},
  {false, false, false},
  {false, false, false}
};

void loop() {
  buttonMatrix[0][0] = digitalRead(5);
  buttonMatrix[0][1] = digitalRead(6);
  buttonMatrix[0][2] = digitalRead(7);
  
  buttonMatrix[1][0] = analogRead(A0)>500;
  buttonMatrix[1][1] = analogRead(A1)>500;
  buttonMatrix[1][2] = analogRead(A2)>500;

  buttonMatrix[2][0] = digitalRead(2);
  buttonMatrix[2][1] = digitalRead(3);
  buttonMatrix[2][2] = digitalRead(4);

  bool btnOk = true;

  for(int i=0; i<3; i++) {
    for(int j=0; j<3; j++) {
      if (btnOk && buttonMatrix[i][j] == matrix[i][j]){
        btnOk = true;
      }
      else {
        btnOk = false;
      }
    }
  }
  unsigned int vic  = btnOk ? 0b10000000 : 0b00000000;
  Serial.write((CONTROLLER_ID | vic));

  int cols[3] = {8, 12, 13};
  
  for(int col = 0; col <= 2; col++) {
    int val0 = buttonMatrix[col-8][0] ? 255 : (matrix[col][0] ? 50 : 0);
    int val1 = buttonMatrix[col-8][1] ? 255 : (matrix[col][1] ? 50 : 0);
    int val2 = buttonMatrix[col-8][2] ? 255 : (matrix[col][2] ? 50 : 0);
    
    analogWrite(9, val0);
    analogWrite(10, val1);
    analogWrite(11, val2);
    digitalWrite(cols[col], LOW);
    delayMicroseconds(1000);
    digitalWrite(cols[col], HIGH);
  }
}
