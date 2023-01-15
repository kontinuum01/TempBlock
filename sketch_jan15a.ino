[code]
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>        //  Подключаем библиотеку для работы с LCD дисплеем по шине I2C
LiquidCrystal_I2C lcd(0x27,20,4);     //  Объявляем  объект библиотеки, указывая параметры дисплея (адрес I2C = 0x27, количество столбцов = 16, количество строк = 2)
                                      //  Если надпись не появилась, замените адрес 0x27 на 0x3F

// линия данных подключена к цифровому выводу 2 Arduino
#define ONE_WIRE_BUS 2

// настройка объекта oneWire для связи с любым устройством OneWire
OneWire oneWire(ONE_WIRE_BUS);

// передать ссылку на oneWire библиотеке DallasTemperature
DallasTemperature sensors(&oneWire);

int deviceCount = 0;
float tempC;



// создаем свой символ градуса и присваиваем ему имя "simvol"
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


void setup(void)
{
  sensors.begin();                    // запустить библиотеку
  Serial.begin(9600);
  
  // найти устройства на шине
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
  //tempor();
}

void loop (void)
{ 
  // послать команду всем датчикам для преобразования температуры
  sensors.requestTemperatures(); 

  // отобразить температуру с каждого датчика
  for (int i = 0;  i < deviceCount;  i++)
  {
    Serial.print("Sensor ");
    Serial.print(i+1);
    Serial.print(" : ");
    tempC = sensors.getTempCByIndex(i);
    Serial.print(tempC);
    Serial.print((char)223);        // напечатать символ градусов
    Serial.print("C  |  ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
    Serial.print((char)223);        // напечатать символ градусов
    Serial.println("F");
  lcd.init();                       //  Инициируем работу с LCD дисплеем
  lcd.backlight();                  //  Включаем подсветку LCD дисплея
  lcd.createChar(1, simvol);        //  создаем символ градусов
  lcd.setCursor(0, 0);              //  Устанавливаем курсор в позицию (0 столбец, 0 строка)
  lcd.print("1: ");
  lcd.setCursor(2, 0);
  tempC = sensors.getTempCByIndex(0);
  lcd.print(tempC - 5.0);
  lcd.setCursor(7, 0);
  lcd.print(char(1));
  lcd.setCursor(8, 0);
  lcd.print("C");                   //  Выводим текст "LCD", начиная с установленной позиции курсора
  lcd.setCursor(0, 1);              //  Устанавливаем курсор в позицию (0 столбец, 1 строка)
  lcd.print("2: ");                 // Выводим текст "www.iarduino.ru", начиная с установленной позиции курсора
  lcd.setCursor(2, 1);
  tempC = sensors.getTempCByIndex(1);//  Устанавливаем курсор в позицию (0 столбец, 0 строка)
  lcd.print(tempC - 5.0);
  lcd.createChar(1, simvol);
  lcd.setCursor(7, 1);
  lcd.print(char(1));
  lcd.setCursor(8, 1 );
  lcd.print("C");
  lcd.setCursor(0, 2);              //  Устанавливаем курсор в позицию (0 столбец, 0 строка)
  lcd.print("3: ");
  lcd.setCursor(2, 2);
  tempC = sensors.getTempCByIndex(2);
  lcd.print(tempC - 5.0);
  lcd.setCursor(8, 2);
  lcd.print("C");                  //  Выводим текст "LCD", начиная с установленной позиции курсора
  lcd.setCursor(7, 2);             //  Устанавливаем курсор в позицию (0 столбец, 1 строка)
  lcd.print(char(1));              //выводим текст "www.iarduino.ru", начиная с установленной позиции курсора
  lcd.setCursor(11, 0);              //  Устанавливаем курсор в позицию (0 столбец, 0 строка)
  lcd.print("4: ");
  lcd.setCursor(13, 0);
  tempC = sensors.getTempCByIndex(3);
  lcd.print(tempC - 5.0);
  lcd.setCursor(19, 0);
  lcd.print("C");                  //  Выводим текст "LCD", начиная с установленной позиции курсора
  lcd.setCursor(18, 0);             //  Устанавливаем курсор в позицию (0 столбец, 1 строка)
  lcd.print(char(1));  
  lcd.setCursor(11, 1);              //  Устанавливаем курсор в позицию (0 столбец, 0 строка)
  lcd.print("5: ");
  lcd.setCursor(13, 1);
  tempC = sensors.getTempCByIndex(4);
  lcd.print(tempC - 5.0);
  lcd.setCursor(19, 1);
  lcd.print("C");                  //  Выводим текст "LCD", начиная с установленной позиции курсора
  lcd.setCursor(18, 1);             //  Устанавливаем курсор в позицию (0 столбец, 1 строка)
  lcd.print(char(1)); 
  lcd.setCursor(4, 3);
  lcd.print("Temperature");
   
 }
  
  Serial.println("");
  delay(5000);
}