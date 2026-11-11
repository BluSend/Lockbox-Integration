const unsigned char sense = 4;
const unsigned char LED = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(sense, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int proxmity = digitalRead(sense); // read the state of the switch
  if(proxmity == LOW){ // signal goes low when switch is closed
    Serial.println("Switch closed");
    digitalWrite(LED, HIGH);
  }
  else{
    Serial.println("Switch open");
    digitalWrite(LED, LOW);
  }
}
