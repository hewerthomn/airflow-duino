

#define PIN_LED 13
#define PIN_PIR_SENSOR 2
#define PIN_RELAY_CH_2 A1

#define FAN_DELAY 60000 * 60

int pirState = LOW;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_RELAY_CH_2, OUTPUT);
  pinMode(PIN_PIR_SENSOR, INPUT);

  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_RELAY_CH_2, LOW);
    
  Serial.begin(9600);
}

void loop() {
  readPIR();

  handleLed();
  handleRelay();

  delay(1000);
}

void readPIR() {

  if (digitalRead(PIN_PIR_SENSOR) == HIGH) {
    Serial.println("Movimento Detectado");
    pirState = HIGH;
  } else {
    Serial.println("Movimento NAO Detectado");
    pirState = LOW;    
  }  
}

bool hasMove() {
  return pirState == HIGH;
}

void handleLed() {
  if (hasMove()) {
    digitalWrite(PIN_LED, HIGH);
  } else {
    digitalWrite(PIN_LED, LOW);
  }
}

void handleRelay() {
  if (hasMove()) {
    digitalWrite(PIN_RELAY_CH_2, HIGH);
    delay(FAN_DELAY);
  } else {
    digitalWrite(PIN_RELAY_CH_2, LOW);
  }
}
