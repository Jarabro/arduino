#include <DHT.h>
#include <Servo.h>
#define DHTTYPE DHT11
Servo myServer;

int gndPin = A0;
int vccPin = A1;
int xPin = A2;
int yPin = A3;
int swPin = A4;

int buzzerPin = 2;
int hzData[8] = {262, 294, 330, 349, 392, 440, 494, 523};

int gndPin2 = 6;
int vccPin2 = 3;
int triggerPin = 4;
int echoPin = 5;

int pinDht = 8;
DHT dht(pinDht, DHTTYPE);

int servo = 7.;


void setup() {
  Serial.begin(9600);
  pinMode(gndPin, OUTPUT);
  pinMode(vccPin, OUTPUT);
  pinMode(xPin, OUTPUT);
  pinMode(yPin, OUTPUT);
  pinMode(swPin, INPUT_PULLUP);
  digitalWrite(vccPin, HIGH);
  digitalWrite(gndPin, LOW);
  
  pinMode(buzzerPin, OUTPUT);

  pinMode(vccPin2, OUTPUT);
  pinMode(gndPin2, OUTPUT);  
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(vccPin2, HIGH);
  digitalWrite(gndPin2, LOW);

  dht.begin();

  myServer.attach(servo);
  }

void loop() {
  digitalWrite(S1, HIGH);
  Serial.print("x: ");
  Serial.print(analogRead(xPin));
  Serial.print("\ty: ");
  Serial.print(analogRead(yPin));
  if(!digitalRead(swPin)){
    Serial.println("\tON");
  }
  else{
    Serial.println("\tOFF");
  }
  if(analogRead(xPin) < 2 && analogRead(yPin) < 11){ //왼쪽
    for(int i = 0; i < 8; i++){
      tone(buzzerPin, hzData[i]);
      delay(200);
      noTone(buzzerPin);
      delay(200);
    }
  delay(100);
  }
  else if(analogRead(xPin) > 299 && analogRead(yPin) < 101){ //오른쪽
    float fDuration, fDistance;
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    fDuration = pulseIn(echoPin, HIGH); //반사되어 돌아온 시간 변수에 저장

    fDistance = ((float)(340 * fDuration)) / 10000 / 2;
    Serial.print(fDistance);
    Serial.println("cm");
    delay(300);
  }

  else if(analogRead(xPin) < 5 && analogRead(yPin) == 0 ){
    delay(2000);
    float fTemp = dht.readTemperature();
    float fHumi = dht.readHumidity();

    if(isnan(fTemp) || isnan(fHumi)){
      Serial.println("Failed to read from DHT");
      return;
    }

    Serial.print("Temperature: ");
    Serial.print(fTemp);
    Serial.print("[C]\t");
    Serial.print("Humidity: ");
    Serial.print(fHumi);
    Serial.println("[%]");
  }
  else if(analogRead(xPin) < 11 && analogRead(yPin) > 299){
    myServer.write(0);
    delay(1000);
    myServer.write(180);
    delay(1000);
  }
  delay(500);
}
  

