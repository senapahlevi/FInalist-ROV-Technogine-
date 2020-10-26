#define modepki   A2
#define modepki2  A3
#define modepka   A1
#define modepka2  A0
#define mobelki   4
#define mobelki2  7
#define mobelka   8
#define mobelka2  9
#define pwm1  10
#define pwm2  6
#define pwm3  11
#define pwm4  5
#define relay 12
int ch1, ch2, ch3;
const int Mundurlow = -150;
const int Mundurhigh = 90;
const int Nmin = 100; //normalmin
const int Nmax = 130; //normalmax
const int Ms = 200; // majusmall
const int Ml = 270; //majularge
const int stirlow = 100;
const int stirhigh = 120;
const int kananlow = 0;
const int kananhigh = 15;
const int kirilow = 200;
const int kirihigh = 255;
int sum = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, INPUT);        pinMode(3, INPUT);
  pinMode(relay, OUTPUT);    pinMode(2, INPUT);
  pinMode(pwm1, OUTPUT);     pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);     pinMode(pwm4, OUTPUT);
  pinMode(modepki, OUTPUT);  pinMode(modepki2, OUTPUT);
  pinMode(modepka, OUTPUT);  pinMode(modepka2, OUTPUT);
  pinMode(mobelki, OUTPUT);  pinMode(mobelki2, OUTPUT);
  pinMode(mobelka, OUTPUT);  pinMode(mobelka2, OUTPUT);
}
void maju() {
  digitalWrite(mobelki, LOW);
  digitalWrite(mobelki2, HIGH);
  digitalWrite(mobelka, HIGH );
  digitalWrite(mobelka2, LOW);
  analogWrite(pwm4, 255);
  analogWrite(pwm3, 255);
  Serial.println("Maju");
}

void naik() {
  digitalWrite(modepki, HIGH);
  digitalWrite(modepki2, HIGH);
  digitalWrite(modepka, HIGH);
  digitalWrite(modepka2, HIGH);
  analogWrite(pwm1, 255);
  analogWrite(pwm2, 255);
}
void turun() {
  digitalWrite(modepki, LOW);
  digitalWrite(modepki2, HIGH);
  digitalWrite(modepka, LOW);
  digitalWrite(modepka2, HIGH );
  analogWrite(pwm1, 255);
  analogWrite(pwm2, 255);
  Serial.println("Turun");
}
void kiri() {
  digitalWrite(mobelki, HIGH);
  digitalWrite(mobelki2, LOW);
  digitalWrite(mobelka, HIGH);
  digitalWrite(mobelka2, LOW);
  analogWrite(pwm4, 255);
  analogWrite(pwm3, 255);
  Serial.println("Kiri");
}
void kanan() {
  digitalWrite(mobelki, LOW);
  digitalWrite(mobelki2, HIGH);
  digitalWrite(mobelka, LOW);
  digitalWrite(mobelka2, HIGH);
  analogWrite(pwm4, 255);
  analogWrite(pwm3, 255);
  Serial.println("Kanan");
}
void berhenti() {
  digitalWrite(modepki, HIGH);
  digitalWrite(modepki2, HIGH);
  digitalWrite(modepka, HIGH);
  digitalWrite(modepka2, HIGH);
  digitalWrite(mobelki, HIGH);
  digitalWrite(mobelki2, HIGH);
  digitalWrite(mobelka, HIGH);
  digitalWrite(mobelka2, HIGH);
  //digitalWrite(relay,LOW);
  analogWrite(pwm1, 255);
  analogWrite(pwm2, 255);
  analogWrite(pwm4, 255);
  analogWrite(pwm3, 255);
}
void loop() {
  // put your main code here, to run repeatedly:
  ch1 = pulseIn(13, HIGH, 25000);
  ch2 = pulseIn(3, HIGH, 25000);
  ch3 = pulseIn(2, HIGH, 25000);
  ch1 = map(ch1, 950, 2100, 0, 255);
  ch2 = map(ch2, 950, 2045, 0, 255);
  // ch3 = map(ch2, 900,1500,0,255);
  // Normal
  if ( ch2 >= Nmin && ch2 <= Nmax && ch1 >= 15 && ch1 <= 200 && ch3 >= 1480 && ch3 <= 1500) {
    berhenti();
    digitalWrite(relay, LOW);
    while (ch2 >= Nmin && ch2 <= Nmax && ch1 >= 15 && ch1 <= 200 && ch3 >= 1480 && ch3 <= 1500)
    {
      ch2 = pulseIn(3, HIGH, 25000);
      ch2 = map(ch2, 950, 2045, 0, 255);
      ch1 = pulseIn(13, HIGH, 25000);
      ch1 = map(ch1, 950, 2100, 0, 255);
      ch3 = pulseIn(2, HIGH, 25000);
      ch3 = map(ch3, 900, 1500, 0, 255);
    }
  }
  // Hisap
  if ( ch3 >= 900 && ch3 <= 1000) //150-200
  {
    digitalWrite(relay, HIGH);
    turun();
    delay(10);
    Serial.println("Hisap");
    while (ch3 >= 900 && ch3 <= 1000) {
      ch3 = pulseIn(2, LOW, 25000);
      //ch3 = map(ch2, 900,1500,0,255);
      digitalWrite(relay, HIGH);
    }
  }
  //Lepas
  if ( ch3 >= 1480 && ch3 <= 1500) //150-200
  {
    digitalWrite(relay, LOW);
    delay(5);
    Serial.println("lepas");
    while (ch3 >= 900 && ch3 <= 1000) {
      ch3 = pulseIn(2, LOW, 25000);
      //ch3 = map(ch2, 900,1500,0,255);
      digitalWrite(relay, LOW);
    }
  }
  //Maju
  if (ch2 >= Ms && ch2 <= Ml) //200-270
  {
    maju();
    delay(5);
    Serial.println("Maju");
    while (ch2 >= Ms && ch2 <= Ml) {
      ch2 = pulseIn(3, HIGH, 25000);
      ch2 = map(ch2, 950, 2045, 0, 255);
    }
  }
  //Naik
  if (ch2 >= 0 + 10 & ch2 <= 90) //-150-90
  {
    naik();
    delay(5);
    Serial.println("Naik");
    while (ch2 >= 0 & ch2 <= 90) {
      ch2 = pulseIn(3, HIGH, 25000);
      ch2 = map(ch2, 950, 2045, 0, 255);
    }
  }
  //kanan
  if (ch1 >= kananlow && ch1 <= kananhigh) //0-15
  {
    kanan();
    delay(5);
    Serial.println("kanan");
    while (ch1 >= kananlow && ch1 <= kananhigh) {
      ch1 = pulseIn(13, HIGH, 25000);
      ch1 = map(ch1, 950, 2100, 0, 255);
    }
  }
  //kiri
  if (ch1 >= kirilow && ch1 <= kirihigh) //200-255
  {
    kiri();
    delay(5);
    Serial.println("kiri");
    while (ch1 >= kirilow && ch1 <= kirihigh) {
      ch1 = pulseIn(13, HIGH, 25000);
      ch1 = map(ch1, 950, 2100, 0, 255);
    }
  }
}

