//Инфракрасный датчик расстояния
unsigned int infr;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  infr = 0;
  
}

void loop() { 
 infr = analogRead(A0);
 Serial.println("Расстояние в попугаях: ");
 Serial.println(infr);
 delay(1000);
}

// допишите программу так, что бы вместо попугаев получить в мм
