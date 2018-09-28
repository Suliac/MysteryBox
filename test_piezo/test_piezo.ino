void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  //StartGameSong();
  //GoodPlaceSong();
  VictorySong();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void GoodPlaceSong()
{
  tone(2, 1046.5f, 250);
  delay(250);
  tone(2, 1397, 250);
  delay(250);
}

void VictorySong()
{ 
  tone(2, 587); // D4
  delay(250);
  tone(2, 740 , 250); // F#4
  delay(250);
  tone(2, 988 , 500); // B4
  delay(500);
  tone(2, 1175, 125); // D5
  delay(125);
  tone(2, 988 , 250); // B4
  delay(250);
  tone(2, 1175, 125); // D5
  delay(125);
  tone(2, 880 , 250); // A4
  delay(250);
  tone(2, 1175, 125); // D5
  delay(125);
  tone(2, 988 , 375); // B4
  
}

void StartGameSong()
{
  tone(2, 523); // C4
  delay(250);

  tone(2, 440); // A3
  delay(250);
  
  tone(2, 587); // D4
  delay(62);
  
  tone(2, 698); // F4
  delay(62);

  tone(2, 587, 250); // D4
  delay(250);
}
