#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

// Объявляем объект дисплея (адрес I2C = 0x27, 20 столбцов, 4 строки)
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Линия данных подключена к цифровому выводу 2 Arduino
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int deviceCount = 0;        
unsigned long currentTime;  // Переменная таймера

// Массив для хранения температуры 5 датчиков (тип float для точности с запятой)
float temperatures[5]; 

// Создаем символ градуса
byte simvol[8] = {
  0b01100,
  0b10010,
  0b10010,
  0b01100,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup(void) {
  lcd.init();
  lcd.backlight();
  
  // Создаем кастомный символ градуса в памяти дисплея ОДИН РАЗ
  lcd.createChar(1, simvol); 
  
  sensors.begin();
  Serial.begin(115200); // Для Nano Every можно использовать высокую скорость 115200
  
  deviceCount = sensors.getDeviceCount();

  // Заставка: Прошивка/Артикул
  lcd.setCursor(4, 1);  lcd.print("418137.010");
  lcd.setCursor(4, 2);  lcd.print("ver.1.5.0");
  delay(2000);
  lcd.clear();
  
  // Заставка: Инициализация
  lcd.setCursor(3, 1);  lcd.print("INITIALIZATION");
  lcd.setCursor(7, 2);  lcd.print("SENSORS");
  delay(2000);
  lcd.clear();
  
  // Статичный текст выводим ОДИН РАЗ в setup, чтобы экран не мерцал в loop
  lcd.setCursor(7, 3);
  lcd.print("ELTOM");
  
  currentTime = millis(); // Запускаем отсчет времени прямо перед loop
}

void loop(void) { 
  // Таймер: опрос датчиков и обновление экрана строго раз в 1 секунду (1000 мс)
  if (millis() - currentTime >= 1000) {   
    currentTime = millis();

    // Запрашиваем температуру у всех датчиков одновременно
    sensors.requestTemperatures(); 

    // Массивы координат на экране для 5 датчиков: {столбец, строка}
    int columns[5] = {1, 1, 1, 11, 11};
    int rows[5]    = {0, 1, 2, 0,  1};

    // Опрашиваем каждый датчик в цикле и выводим на экран
    for (int i = 0; i < 5; i++) {
      temperatures[i] = sensors.getTempCByIndex(i);
      
      lcd.setCursor(columns[i], rows[i]);
      lcd.print(i + 1); // Выводим номер датчика (1, 2, 3, 4, 5)
      lcd.print(":");

      // Проверяем ошибки датчика (-127 или технические 85 градусов при старте)
      if (temperatures[i] == -127.00 || temperatures[i] == 85.00) {
        lcd.print("---   "); // Пишем прочерки и очищаем старые символы пробелами
      } else {
        lcd.print(temperatures[i], 1); // Выводим температуру с 1 знаком после запятой
        lcd.write(1);                  // Выводим созданный символ градуса
        lcd.print("C ");               // Буква C и пробел для очистки хвостов текста
      }
    }
  }
}
