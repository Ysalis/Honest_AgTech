// Hook up 11 HC-SR04
//Group A of 4 HC-SR04
//Hook up 11 HC-SR04 with Trig to Arduino Pin 22, Echo to Arduino pin 23
#define TRIGGER_PIN_A_1 22
#define ECHO_PIN_A_1 23

#define TRIGGER_PIN_A_2 24
#define ECHO_PIN_A_2 25

#define TRIGGER_PIN_A_3 26
#define ECHO_PIN_A_3 27

#define TRIGGER_PIN_A_4 28
#define ECHO_PIN_A_4 29

//Group B of 4 HC-SR04
#define TRIGGER_PIN_B_1 30
#define ECHO_PIN_B_1 31

#define TRIGGER_PIN_B_2 32
#define ECHO_PIN_B_2 33

#define TRIGGER_PIN_B_3 34
#define ECHO_PIN_B_3 35

#define TRIGGER_PIN_B_4 36
#define ECHO_PIN_B_4 37

// Group of 3 HC-SR04
#define TRIGGER_PIN_C_1 38
#define ECHO_PIN_C_1 39

#define TRIGGER_PIN_C_2 40
#define ECHO_PIN_C_2 41

#define TRIGGER_PIN_C_3 42
#define ECHO_PIN_C_3 43

//define 10 PIN for DAC
#define PIN_1 44
#define PIN_2 45
#define PIN_3 46
#define PIN_4 47
#define PIN_5 48
#define PIN_6 49
#define PIN_7 50
#define PIN_8 51
#define PIN_9 52
#define PIN_10 53

//variables for DAC
int DAC[] = {PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9, PIN_10};
int L[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int n, r;

//define the time and the distance
float tMin, t;
int distanceA, distanceB, distanceC, total;

void setup() 
{
  Serial.begin(9600);

  //define if the pin is an input (trigger) or an output (echo)
  pinMode(TRIGGER_PIN_A_1, OUTPUT);
  pinMode(ECHO_PIN_A_1, INPUT);
  
  pinMode(TRIGGER_PIN_A_2, OUTPUT);
  pinMode(ECHO_PIN_A_2, INPUT);

  pinMode(TRIGGER_PIN_A_3, OUTPUT);
  pinMode(ECHO_PIN_A_3, INPUT);
  
  pinMode(TRIGGER_PIN_A_4, OUTPUT);
  pinMode(ECHO_PIN_A_4, INPUT);
  
  pinMode(TRIGGER_PIN_B_1, OUTPUT);
  pinMode(ECHO_PIN_B_1, INPUT);
  
  pinMode(TRIGGER_PIN_B_2, OUTPUT);
  pinMode(ECHO_PIN_B_2, INPUT);

  pinMode(TRIGGER_PIN_B_3, OUTPUT);
  pinMode(ECHO_PIN_B_3, INPUT);
  
  pinMode(TRIGGER_PIN_B_4, OUTPUT);
  pinMode(ECHO_PIN_B_4, INPUT);

  pinMode(TRIGGER_PIN_C_1, OUTPUT);
  pinMode(ECHO_PIN_C_1, INPUT);
  
  pinMode(TRIGGER_PIN_C_2, OUTPUT);
  pinMode(ECHO_PIN_C_2, INPUT);

  pinMode(TRIGGER_PIN_C_3, OUTPUT);
  pinMode(ECHO_PIN_C_3, INPUT);

  //define the pins use for Digital Analog Converter as output 
  for (int k = 0; k < 10; k++){
    pinMode(DAC[k], OUTPUT);
  }
}

void loop() 
{
  //Group A of sensors
  digitalWrite(TRIGGER_PIN_A_1, LOW);
  tMin = pulseIn(ECHO_PIN_A_1, HIGH);

  digitalWrite(TRIGGER_PIN_A_2, LOW);
  t = pulseIn(ECHO_PIN_A_2, HIGH);
  //compare the two times, if tMin is higher than t, tMin take the value of t. This allow to have the lowest distance when it is calculated
  if (tMin>t){
    tMin = t;
  }

  digitalWrite(TRIGGER_PIN_A_3, LOW);
  t = pulseIn(ECHO_PIN_A_3, HIGH);
  if (tMin>t){
    tMin = t;
  }

  digitalWrite(TRIGGER_PIN_A_4, LOW);
  t = pulseIn(ECHO_PIN_A_4, HIGH);
  if (tMin>t){
    tMin = t;
  }

  //calcul of the minimum distance of the group A of sensors
  // distance = halfway * speed of the sound * t * conversion ??s to s * conversion from meter to V
  // 0V = 0m and 10V = 4m
  distanceA = 0.5*340*tMin*0.000001*(10/4);
  //integer part of the distance
  distanceA = (int) distanceA;

  //DAC converter
  //Convert distanceA to binary
  for (int k = 0; k < 10; k++){
    n = distanceA;
    while (n !=0){
      r = n%2;
      n = (n-r)/2;
      L[k] = r;
    }
    digitalWrite(DAC[k],L[k]);
  }

  //Group B of sensors
  digitalWrite(TRIGGER_PIN_B_1, LOW);
  tMin = pulseIn(ECHO_PIN_B_1, HIGH);

  digitalWrite(TRIGGER_PIN_B_2, LOW);
  t = pulseIn(ECHO_PIN_B_2, HIGH);
  if (tMin>t){
    tMin = t;
  }

  digitalWrite(TRIGGER_PIN_B_3, LOW);
  t = pulseIn(ECHO_PIN_B_3, HIGH);
  if (tMin>t){
    tMin = t;
  }

  digitalWrite(TRIGGER_PIN_B_4, LOW);
  t = pulseIn(ECHO_PIN_B_4, HIGH);
  if (tMin>t){
    tMin = t;
  }
  distanceB = 0.5*340*tMin*0.000001*(10/4);
  distanceB = (int) distanceB; 

  //DAC converter
  for (int k = 0; k < 10; k++){
    n = distanceB;
    while (n !=0){
      r = n%2;
      n = (n-r)/2;
      L[k] = r;
    }
    digitalWrite(DAC[k],L[k]);
  }

  //Group C of sensors
  digitalWrite(TRIGGER_PIN_C_1, LOW);
  tMin = pulseIn(ECHO_PIN_C_1, HIGH);

  digitalWrite(TRIGGER_PIN_C_2, LOW);
  t = pulseIn(ECHO_PIN_C_2, HIGH);
  if (tMin>t){
    tMin = t;
  }

  digitalWrite(TRIGGER_PIN_C_3, LOW);
  t = pulseIn(ECHO_PIN_C_3, HIGH);
  if (tMin>t){
    tMin = t;
  }
  distanceC = 0.5*340*tMin*0.000001*(10/4);
  distanceC = (int) distanceC;

  //DAC converter
  for (int k = 0; k < 10; k++){
    n = distanceC;
    while (n !=0){
      r = n%2;
      n = (n-r)/2;
      L[k] = r;
    }
    digitalWrite(DAC[k],L[k]);
  }
}  
