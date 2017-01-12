void setup() {
  // put your setup code here, to run once:
pinMode(2, OUTPUT);
pinMode(13, OUTPUT);
pinMode(5, INPUT);
}

bool motion;

void loop() {
motion = digitalRead(5);
if (motion)
{
  digitalWrite(2,HIGH);
  delay(15000);
  digitalWrite(2,LOW);
}
else
{
  // do nothing!
}

}
