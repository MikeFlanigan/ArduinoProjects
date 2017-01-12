

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
char *words[] = {"dash", "dot"};
Serial.println(words[0]);
if (words[0]=="dash"){
  Serial.println("OMG");
}
Serial.println(sizeof(words));
}
