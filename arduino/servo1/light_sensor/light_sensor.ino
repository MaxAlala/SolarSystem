const int lightSensor = 9;
const int LED_pin = 6;
int istherelight = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(lightSensor, INPUT); // Sets the echoPin as an Input
pinMode(LED_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
istherelight = digitalRead(lightSensor);
if(istherelight==1){
  digitalWrite(LED_pin, HIGH);
}else{
  digitalWrite(LED_pin, LOW);
}
}
