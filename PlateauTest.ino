int randNumber;
const byte red = 2;
const byte blue = 3;
const byte green = 4;

byte colors[4][3] = {   
            {255,50,0}, //RGB
            {255,50,0},
            {255,50,0},
            {255,50,0}};

byte pins[4][3] = {   {6,5,3}, //pin RGB
            {4,7,4},
            {8,10,9},
            {11,13,12}};

int tmp[4];
int count = 0;

void setup()
{
  Serial.begin(9600);

    pinMode(6, OUTPUT); //r
    pinMode(3, OUTPUT); //g
    pinMode(5, OUTPUT); //b
  
  randomSeed(analogRead(0));
  
  while(count < 4)
  {
      
    randNumber = random(0,4);
    bool alreadyHere = false;
    for(int i = 0; i<count; i++)
    {
      if(tmp[i] == randNumber)
        alreadyHere =true;
    }
    
    if(!alreadyHere) // Si pas deja présent
    {
      
     // ajouter à tmp
      tmp[count] = randNumber;
      count++;
    }
    
  }
  
  for(int i =0; i<4;i++)
  {
    analogWrite(pins[i][0], colors[tmp[i]][0]);//RED
    analogWrite(pins[i][1], colors[tmp[i]][1]);//GREEN
    analogWrite(pins[i][2], colors[tmp[i]][2]);//BLUE

    Serial.println(tmp[i]);
  }
  
  
  /*
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);*/
}

void loop()
{
  //randNumber = random(0,4);
  //digitalWrite(red, HIGH);
}
