
const int LED = 9;
const int button = 2;
void setup() {
Serial.begin(9600);
  // put your setup code here, to run once:
pinMode(LED, OUTPUT);
pinMode(LED, INPUT);
digitalWrite(LED, HIGH);
    
}
bool state = false;
bool remember = false;
void loop() {
  // put your main code here, to run repeatedly:

//  delay(100);

 if(digitalRead(button) == HIGH){
    delay(10);
    if(digitalRead(button) == HIGH){
      if(state == false){
        state = true;
      }else{
        state = false;
      }
      while(digitalRead(button) == HIGH){
  
      }
    }

  }
    if(state == true)
  digitalWrite(LED, HIGH);else
  digitalWrite(LED, LOW);

//  
//digitalWrite(LED, LOW);
//for(int i = 0; i < 255; i++ ){
//delay(10);
//analogWrite(LED, i);  
//}
//
//
//for(int i = 255; i > 0 ; i-- ){
//delay(10);
//a nalogWrite(LED, i);
//}
}
