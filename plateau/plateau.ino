const int NB_PLAYERS = 1;

int randNumber;

byte colors[4][3] = {   {HIGH, LOW, LOW}, //RGB
  {LOW, HIGH, LOW},
  {LOW, LOW, HIGH},
  {HIGH, HIGH, LOW}
};

byte pins[4][3] = {   {2, 4, 3}, //pin RGB /!\ emplacement : 0 haut gauche
  {5, 7, 6}, // /!\ emplacement : 1 haut doite
  {8, 10, 9}, // /!\ emplacement : 2 bas droite
  {11, 13, 12} // /!\ emplacement : 3 bas gauche
};

int score = 0;
int tmp[4];
int count = 0;
bool gameRunning = false;

bool controllerIds[4]; // couleurs associées aux emplacements physiques : 0 = en haut à gauche, 1 = haut droite, 2 = bas droite, 3 = bas gauche
bool controllerState[4];

// FEEDBACKS
int pinFbGoodPlace[4] = {14 , 15, 16, 17};
int pinFbControllerOK[4] = {18, 19, 20, 21}; // LED PILIER ?

int pinPiezo = 22;

void setup()
{
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  randomSeed(analogRead(0));
}

void loop()
{
  if (!gameRunning) // si game pas lancée : init partie
  {
    StartGameSong();
    delay(1000);
    gameRunning = true;
    InitGame();
  }
  else
  {
    // Sinon : test si réussite
    if (Serial.available()) {
      ManageController(0, Serial.read());
    }

    if (Serial1.available()) {
      ManageController(1, Serial1.read());
    }

    if (Serial2.available()) {
      ManageController(2, Serial2.read());
    }

    if (Serial3.available()) {
      ManageController(3, Serial3.read());
    }

    // Test final :
    // 1 - Couleur au bon endroit ?
    // 2 - Controller 'fini' ?
    int nbrWon = 0;
    
    for (int i = 0; i < 4; i++)
    {
      if (controllerIds[i] == tmp[i] // tmp contient la suite
          && controllerState[i])
      {
        // manette gagné !
        nbrWon++;
      }
    }

    if (nbrWon >= NB_PLAYERS)
    {
      // feedback tout ça
      VictorySong();
      delay(2000);
      gameRunning = false;
    }
  }
}

void InitGame()
{
  FillTab();
  Colorize();
}

// Fill our tmp tab with random number
void FillTab()
{
  count = 0;
  while (count < 4)
  {
    randNumber = random(0, 4);
    bool alreadyHere = false;
    for (int i = 0; i < count; i++)
    {
      if (tmp[i] == randNumber)
        alreadyHere = true;
    }

    if (!alreadyHere) // Si pas deja présent
    {
      // ajouter à tmp
      tmp[count] = randNumber;
      count++;
    }
  }
}

// Init the colors
void Colorize()
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(pins[i][0], colors[tmp[i]][0]);//RED
    digitalWrite(pins[i][1], colors[tmp[i]][1]);//GREEN
    digitalWrite(pins[i][2], colors[tmp[i]][2]);//BLUE
  }
}

void ManageController(int id, int val)
{
  // SET ID
  controllerIds[id] = val & 0b00000011;

  // SET STATE
  bool successCtrl = (val & 0b10000000) != 0;

  if(successCtrl && !controllerState)
    GoodPlaceSong();
  
  controllerState[id] = successCtrl;
  
  digitalWrite(pinFbControllerOK[id], successCtrl ? HIGH : LOW);
  digitalWrite(pinFbGoodPlace[id], controllerIds[id] == tmp[id] ? HIGH : LOW);
}

void GoodPlaceSong()
{
  tone(pinPiezo, 1046.5f, 250);
  delay(250);
  
  tone(pinPiezo, 1397, 250);
  delay(250);
}

void VictorySong()
{ 
  tone(pinPiezo, 587 , 250); // D4
  delay(250);
  
  tone(pinPiezo, 740 , 250); // F#4
  delay(250);
  
  tone(pinPiezo, 988 , 500); // B4
  delay(500);
  
  tone(pinPiezo, 1175, 125); // D5
  delay(125);
  
  tone(pinPiezo, 988 , 250); // B4
  delay(250);
  
  tone(pinPiezo, 1175, 125); // D5
  delay(125);
  
  tone(pinPiezo, 880 , 250); // A4
  delay(250);
  
  tone(pinPiezo, 1175, 125); // D5
  delay(125);
  
  tone(pinPiezo, 988 , 375); // B4
  delay(375);
  
}

void StartGameSong()
{
  tone(pinPiezo, 523); // C4
  delay(250);

  tone(pinPiezo, 440); // A3
  delay(250);
  
  tone(pinPiezo, 587); // D4
  delay(62);
  
  tone(pinPiezo, 698); // F4
  delay(62);

  tone(pinPiezo, 587, 250); // D4
  delay(250);
}
