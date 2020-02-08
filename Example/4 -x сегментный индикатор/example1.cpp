/// Проверяем работоспособность
int anodPins[] = {A1, A2, A3, A4};
int segmentsPins[] = {5, 6, 7, 8, 9, 10, 11, 12};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(anodPins[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) {
    pinMode(segmentsPins[i], OUTPUT);
  }
}

int seg[] = {0, 1, 1, 0, 1, 1, 1, 0}; //Буква H

void loop() {
  // отображаем букву H на всех разрядах
  for (int i = 0; i < 4; i++) {
    for (int k = 0; k < 8; k++) {
      digitalWrite(segmentsPins[k], ((seg[k] == 1) ? LOW : HIGH));
    }
    digitalWrite(anodPins[i], HIGH); // Подали напряжение на анод - все индикаторы загорелись
    delay(1); // Дали паузу глазу воспринять 
    digitalWrite(anodPins[i], LOW); // Сняли напряжение с анода, чтобы переключение катодов не вызывали мерцание
  }
}