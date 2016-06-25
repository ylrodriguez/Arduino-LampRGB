//Definiciones de pines.  Deben ser pines PWM en el Arduino para el RGB Led!
const int bluePin = 9;
const int redPin = 10;
const int greenPin = 11;
const int pirPin = 2;

int u, d, c, p; //Recibe las unidades, decenas y centenas y el resultado p
int input; //Donde se cambiara el color
int lastColor[3] = {246, 112, 0}; //Amarillo por defecto

unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 60000;           // interval at which to blink (milliseconds)

void setup() {
  //Se asignan los pines a usar
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(pirPin, INPUT);

  //Se empieza la serializacion
  Serial.begin(9600);

  for (int i = 0; i < 4; i++) {
    inicio(); //Parpadeo de luces para indicar inicio
  }
}
/*--------------------------------------------*/
void loop() {

  /*Revisa si se estan enviando datos desde la App*/
  if (Serial.available()) {
    input = Serial.read() - 48;
    delay(10);
    c = Serial.read() - 48;
    delay(10);
    d = Serial.read() - 48;
    delay(10);
    u = Serial.read() - 48;
    delay(10);
    p = (100 * c) + (10 * d) + u;
    if (input == 1) {
      analogWrite(redPin, p);
      lastColor[0] = p;
    }
    if (input == 2) {
      analogWrite(greenPin, p);
      lastColor[1] = p;
    }
    if (input == 3) {
      analogWrite(bluePin, p);
      lastColor[2] = p;
    }
  }
  /*Revisa si hay moviminto en el PIR*/
  int value = digitalRead(pirPin);
  if (value == HIGH)
  {
    movimiento();
  }
  else {
    analogWrite(redPin, lastColor[0]);
    analogWrite(greenPin, lastColor[1]);
    analogWrite(bluePin, lastColor[2]);
  }

  /*Revisa si ya ha pasado el tiempo estimado*/
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    for (int i = 0; i < 3; i++) {
      cambioHora();
    }

    previousMillis =  millis();
    analogWrite(redPin, lastColor[0]);
    analogWrite(greenPin, lastColor[1]);
    analogWrite(bluePin, lastColor[2]);
  }

}

/*--------------------------------------------*/

void inicio() {
  amarillo();
  delay(300);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  delay(300);
  amarillo();
}

void movimiento() {
  rojo();
  delay(50);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  delay(50);
}

void cambioHora() {
  int FADESPEED = 5;

  // fade from blue to violet
  for (int red = 0; red < 256; red++) {
    analogWrite(redPin, red);
    delay(FADESPEED);
  }
  // fade from violet to red
  for (int blue = 255; blue > 0; blue--) {
    analogWrite(bluePin, blue);
    delay(FADESPEED);
  }
  // fade from red to yellow
  for (int green = 0; green < 256; green++) {
    analogWrite(greenPin, green);
    delay(FADESPEED);
  }
  // fade from yellow to green
  for (int red = 255; red > 0; red--) {
    analogWrite(redPin, red);
    delay(FADESPEED);
  }
  // fade from green to teal
  for (int blue = 0; blue < 256; blue++) {
    analogWrite(bluePin, blue);
    delay(FADESPEED);
  }
  // fade from teal to blue
  for (int green = 255; green > 0; green--) {
    analogWrite(greenPin, green);
    delay(FADESPEED);
  }

  for (int i = 0; i < 50; i++) {
    amarillo();
    delay(50);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    delay(50);
  }
  for (int i = 0; i < 50; i++) {
    azul();
    delay(50);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    delay(50);
  }
  for (int i = 0; i < 50; i++) {
    rojo();
    delay(50);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    delay(50);
  }

}


void amarillo() {
  analogWrite(redPin, 246);
  analogWrite(greenPin, 112);
  analogWrite(bluePin, 0);
}

void azul() {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
}


void rojo() {
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}
