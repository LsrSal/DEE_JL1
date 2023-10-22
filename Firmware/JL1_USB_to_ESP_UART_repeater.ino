//Transparent UART repeater for JL1 board to access ESP12F through USB port.


void setup() {

  pinMode(PA9, OUTPUT); //CH340 Serial to USB Interface
  pinMode(PA10, INPUT);

  pinMode(PA2, OUTPUT); // ESP12F Serial
  pinMode(PA3, INPUT);  

  pinMode(PA1, OUTPUT); //Set enable for ESP
  digitalWrite(PA1,1);

  digitalWrite(PA9,1); //init for bit repeater
  digitalWrite(PA2,1);


attachInterrupt(digitalPinToInterrupt(PA10), ONE, CHANGE ); //UART1
attachInterrupt(digitalPinToInterrupt(PA3), TWO, CHANGE ); //UART2


}

void loop() {;}

void ONE() {digitalWrite(PA2,!digitalRead (PA2));}
void TWO() {digitalWrite(PA9,!digitalRead (PA9));}
