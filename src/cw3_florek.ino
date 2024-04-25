/* Szymon Florek WCY22IY2S1
* Winda pozusza sie miedzy kondygnacjami 0,1,2
* stan poczatkowy - winda ustawia sie na kondygnacji 1
*
* Opis stanów:
* 0000 0 – winda ustawia się na 1 piętrze – stan początkowy
* 0001 1 – winda znajduje się na 0 piętrze
* 0010 2 – winda znajduje się na 1 piętrze
* 0011 3 – winda znajduje się na 2 piętrze
* 0100 4 – winda porusza się z 0 na 1 piętro
* 0101 5 – winda porusza się z 0 na 2 piętro
* 0110 6 – winda porusza się z 1 na 2 piętro
* 0111 7 – winda porusza się z 1 na 0 piętro
* 1000 8 – winda porusza się z 2 na 1 piętro
* 1001 9 – winda porusza się z 2 na 0 piętro
*/

#define Button1Pin A0
#define Button2Pin A1
#define Button3Pin A2
#define Button4Pin A3
#define Sensor1Pin A4
#define Sensor2Pin A5
#define Sensor3Pin 12
#define Sensor4Pin 13
#define OutputQ1Pin 5
#define OutputQ2Pin 4

//variables to store button input
boolean button0 = 0;
boolean button1 = 0;
boolean button2 = 0;

//variables to store sensor input
boolean sensor0 = 0;
boolean sensor1 = 0;
boolean sensor2 = 0;
//variables to store state of state machine
boolean X1 = 0;
boolean X2 = 0;
boolean X3 = 0;
boolean X4 = 0;
//variables to store output for the motor
boolean Q1 = 0;
boolean Q2 = 0;

//function that reads input of sensors and buttons
void readInput(){
button0 = digitalRead(Button1Pin);
button1 = digitalRead(Button2Pin);
button2 = digitalRead(Button3Pin);

sensor0 = digitalRead(Sensor1Pin);
sensor1 = digitalRead(Sensor2Pin);
sensor2 = digitalRead(Sensor3Pin);
}

//setup function to set read/write modes for pins
void setup(){
pinMode(Button1Pin, INPUT);
pinMode(Button2Pin, INPUT);
pinMode(Button3Pin, INPUT);

pinMode(Sensor1Pin, INPUT);
pinMode(Sensor2Pin, INPUT);
pinMode(Sensor3Pin, INPUT);

pinMode(OutputQ1Pin, OUTPUT);
pinMode(OutputQ2Pin, OUTPUT);

Serial.begin(9600);
}

//function to calculate the next state;
void calculateState(){
boolean X1copy = 0;
boolean X2copy = 0;
boolean X3copy = 0;
boolean X4copy = 0;

//calculate next state based on previous state and input
X1copy = (!X1 && !X2 && X3 && X4 && button0)
|| (!X1 && !X2 && X3 && X4 && button1)
|| (X1 && !X2 && !X3 && !X4 && !sensor1)
|| (X1 && !X2 && !X3 && X4 && !sensor0);

X2copy = (!X1 && !X2 && !X3 && X4 && button1)
|| (!X1 && !X2 && !X3 && X4 && button2)
|| (!X1 && !X2 && X3 && !X4 && button0)
|| (!X1 && !X2 && X3 && !X4 && button2)
|| (!X1 && X2 && !X3 && !X4 && !sensor1)
|| (!X1 && X2 && !X3 && X4 && !sensor2)
|| (!X1 && X2 && X3 && !X4 && !sensor2)
|| (!X1 && X2 && X3 && X4 && !sensor0);

X3copy = (!X1 && !X2 && !X3 && !X4 && sensor1)
|| (!X1 && !X2 && X3 && !X4 && button0)
|| (!X1 && !X2 && X3 && !X4 && button2)
|| (!X1 && X2 && !X3 && !X4 && sensor1)
|| (!X1 && X2 && !X3 && X4 && sensor2)
|| (!X1 && X2 && X3 && !X4 && !sensor2)
|| (!X1 && X2 && X3 && !X4 && sensor2)
|| (!X1 && X2 && X3 && X4 && !sensor0)
|| (X1 && !X2 && !X3 && !X4 && sensor1)
|| (!X1 && !X2 && X3 && !X4 && !button0 && !button2)
|| (!X1 && !X2 && X3 && X4 && !button0 && !button1);

X4copy = (!X1 && !X2 && !X3 && X4 && sensor2)
|| (!X1 && !X2 && X3 && !X4 && button0)
|| (!X1 && !X2 && X3 && X4 && button0)
|| (!X1 && X2 && !X3 && X4 && !sensor2)
|| (!X1 && X2 && !X3 && X4 && sensor2)
|| (!X1 && X2 && X3 && !X4 && sensor2)
|| (!X1 && X2 && X3 && X4 && !sensor0)
|| (!X1 && X2 && X3 && X4 && sensor0)
|| (X1 && !X2 && !X3 && X4 && !sensor0)
|| (X1 && !X2 && !X3 && X4 && sensor0)
|| (!X1 && !X2 && !X3 && X4 && !button1 && !button2)
|| (!X1 && !X2 && X3 && X4 && !button0 && !button1);

//make next state current state
X1 = X1copy;
X2 = X2copy;
X3 = X3copy;
X4 = X4copy;
}

//function to calculate output for the elevator motor
void calculateOutput(){
Q1 = (!X1 && X2 && X3 && X4)
|| (X1 && !X2 && !X3 && !X4)
|| (X1 && !X2 && !X3 && X4)
|| (!X1 && !X2 && !X3 && !X4);

Q2 = (!X1 && !X2 && !X3 && X4)
|| (!X1 && !X2 && X3 && !X4)
|| (!X1 && !X2 && X3 && X4);
}

//function to set output onto the pins

void writeOutput(){
digitalWrite(OutputQ1Pin, Q1);
digitalWrite(OutputQ2Pin, Q2);
}

void report(){
Serial.println("Odczyt przyciskow: ");
Serial.print("przycisk 0:");
Serial.println(button0);
Serial.print("przycisk 1:");
Serial.println(button1);
Serial.print("przycisk 2:");
Serial.println(button2);

Serial.println("Odczyt sensorow: ");
Serial.print("sensor 0:");
Serial.println(sensor0);
Serial.print("sensor 1:");
Serial.println(sensor1);
Serial.print("sensor 2:");
Serial.println(sensor2);

Serial.println("Obliczony stan: ");
Serial.print(X1);
Serial.print(X2);
Serial.print(X3);
Serial.println(X4);

Serial.println("Wyjscia (Q1Q2): ");
Serial.print(Q1);
Serial.println(Q2);
}

void loop() {

readInput();
calculateState();
calculateOutput();
writeOutput();
report();
}
