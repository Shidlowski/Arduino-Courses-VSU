// Напишем функцию, которая будет отображать заданные числа
int anodPins[] = {A1, A2, A3, A4}; // Задаем пины для кажого разряда
int segmentsPins[] = {5, 6, 7, 8, 9, 10, 11, 12}; //Задаем пины для каждого сегмента (из 7 + 1(точка))

void setup() {
  for (int i = 0; i < 4; i++) pinMode(anodPins[i], OUTPUT);
  for (int i = 0; i < 8; i++) pinMode(segmentsPins[i], OUTPUT);
  Serial.begin(9600);
}

//{A, B, C, D, E, F, G,DP}
int seg[12][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0}, //Цифра 0
  {0, 1, 1, 0, 0, 0, 0, 0}, //Цифра 1
  {1, 1, 0, 1, 1, 0, 1, 0}, //Цифра 2
  {1, 1, 1, 1, 0, 0, 1, 0}, //Цифра 3
  {0, 1, 1, 0, 0, 1, 1, 0}, //Цифра 4
  {1, 0, 1, 1, 0, 1, 1, 0}, //Цифра 5
  {1, 0, 1, 1, 1, 1, 1, 0}, //Цифра 6
  {1, 1, 1, 0, 0, 0, 0, 0}, //Цифра 7
  {1, 1, 1, 1, 1, 1, 1, 0}, //Цифра 8
  {1, 1, 1, 1, 0, 1, 1, 0}, //Цифра 9
  {0, 0, 0, 0, 0, 0, 1, 0}, //Знак -
  {0, 0, 0, 0, 0, 0, 0, 0}  //Пустой разряд
};

int err[4][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0}, //Пусто
  {1, 0, 0, 1, 1, 1, 1, 0}, //E
  {0, 0, 0, 0, 1, 0, 1, 0}, //r
  {0, 0, 0, 0, 1, 0, 1, 0}  //r
};

float numbers[] = {520.45, 251, -12, 3.14159, 100000, -85.2563}; // По очереди будем показывать числа - на 100000 на дисплее будет отображена ошибка Err

static int arr[4][8]; // Переменная-массив для хранения данных, которые не нужно каждый раз пересчитывать

int numindex = 0;
float value = 0.0;

int counter = -1;
void loop() {
  counter += 1;
  if ((counter % 200) == 0) { // Пауза между сменами 200 мс
    counter = 0;
    getDigits(numbers[numindex]);
    numindex += 1;
    if (numindex >= sizeof(numbers)/sizeof(float)) numindex = 0;
  }
  displayMessage(arr);
}


void getDigits (float value) {
  Serial.println("");

  // Выдаем ошибку на те значения, которые не можем показать
  if ((value >= 10000) ||
      (value <= -1000)) {

    for (int i = 0; i < 4; i++) { // Каждый разряд по очереди
      for (int k = 0; k < 8; k++) {// Каждый сегмент по очереди - исходя из заданной карты
        arr[i][k] = err[i][k];
      }
    }
    return; // Выходим
  }

  int digits = 4; // У нас 4 разряда
  if (value < 0) digits = 3; // Из-за минуса один символ убирается*/

  // Делим число на 2 группы - отдельно целую часть и дробную.
  int intPart = (int)abs(value);
  int intLength = ((String)intPart).length(); // Смотрим, сколько разрядов занимает целая часть

  char valueChars[8]; // По нормальному float в String преобразовать нельзя, поэтому...
  dtostrf(value, 5, 4, valueChars); //... копируем данные float в массив chars[]

  // На дробную часть у нас остается разрядов: digits-intLength
  String valueStr = valueChars;                                                 // Теперь с текстовым форматом можно работать
  //  Serial.print("valueStr: "); Serial.println(valueStr);

  int fracIndex = valueStr.indexOf(".");                                        // Получаем индекс начала дробной части
  String fracPartStr = valueStr.substring(fracIndex + 1, valueStr.length());    // Выделяем цифры дробной части
  int fracDigits = digits - intLength;
  fracPartStr = fracPartStr.substring(0, fracDigits);                           // Вычленяем цифры, которые будут выводиться на дисплей
  //  Serial.print("fracDigits: "); Serial.println(fracDigits);
  //  Serial.print("fracPartStr: "); Serial.println(fracPartStr);

  int fracInt = fracPartStr.toInt();                                            // Переменная для проверки, нужно ли что-то выводить, если нули, то нет
  //  Serial.print("fracInt: "); Serial.println(fracInt);

  // Собираем строку для отображения
  String output = (value < 0) ? "-" : "";
  output += (String)intPart;

  String outputFrac = ((digits - intLength <= 0) || (fracInt == 0)) ? "" : ((String)"." + fracPartStr);

  output += (String)outputFrac;

  // Дополняем символы спереди, если цифр слишком мало, например для "-1" делаем "  -1"
  String spaces = "     ";
  digits = 4;
  if (~output.indexOf(".")) digits += 1;
  if (output.length() < digits) output = spaces.substring(0, digits - output.length()) + output;

  // Формирум данные для показа:
  int dig = -1;
  for (int i = 0; i < output.length(); i++) {
    String _char = output.substring(i, i + 1);

    if (_char != ".") dig += 1; // Точка не занимает сегмент - увеличиваем на 1

    int actualdigit = 11; // По умолчанию пустой символ
    if ((_char == "-")) {
      actualdigit = 10;
    }
    else if (_char == " " || _char == ".") {
    }
    else {
      actualdigit = _char.toInt();
    }

    if (_char == ".") {
      arr[dig][7] = 1; // Если нужно - ставим точку
    }
    else  {
      for (int n = 0; n <= 7; n++) {
        arr[dig][n] = seg[actualdigit][n];
      }
    }
  }
}

void displayMessage(int dig[4][8]) {
  for (int i = 0; i < 4; i++) { // Каждый разряд по очереди
    for (int k = 0; k < 8; k++) {// Каждый сегмент по очереди - исходя из заданной карты
      digitalWrite(segmentsPins[k], ((dig[i][k] == 1) ? LOW : HIGH));
    }
    digitalWrite(anodPins[i], HIGH);
    delay(1);
    digitalWrite(anodPins[i], LOW);
  }
}