/*
Напишите программу которая будет мигать светодиодом сначала медленно, потом быстрее, быстрее, 
быстро и потом светодиод будет постоянно гореть 10 секунд непрерывно.
*/

int ledPin=13;

void setup(){
    pinMode(ledPin,OUTPUT);
}

void loop(){

    for(int i=40;i>10;i--){
        digitalWrite(ledPin,HIGH);
        delay(i*10);
        digitalWrite(ledPin,LOW);
        delay(i*10);
    }
    digitalWrite(ledPin,HIGH);
    delay(10000);

}