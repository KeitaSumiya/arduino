const int pinI = 0; //input

void setup() {
  pinMode(pinI, INPUT);
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(pinI);
  Serial.println(val);
}
