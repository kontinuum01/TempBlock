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

int deviceCount = 0;       // переменная датчиков
float tempC;               // переменная температуры
unsigned long currentTime; // Переменная текущего времени


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

void setup (void)
{
  lcd.init();                           //  Инициируем работу с LCD дисплеем
  lcd.backlight();                      //  Включаем подсветку LCD дисплея
  currentTime = millis();               // запускаем отчет времени
  sensors.begin();                      // запустить библиотеку
  Serial.begin(9600);                   // запускаем монитор порта
  deviceCount = sensors.getDeviceCount();
 /** Serial.print("Locating devices...");  // найти устройства на шине
  Serial.print("Found ");
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
 **/ 
  lcd.setCursor(3, 1);              //  Устанавливаем курсор в позицию (0 столбец, 0 строка)
  lcd.print("INITIALIZATION");
  lcd.setCursor(7, 2);              //  Устанавливаем курсор в позицию (0 столбец, 0 строка)
  lcd.print("SENSORS");
  delay(3000);
  lcd.clear();
  
}

void loop (void)
{ 
        
  sensors.requestTemperatures(); // послать команду всем датчикам для преобразования температуры
    
   for (int i = 0;  i < deviceCount;  i++) // отобразить температуру с каждого датчика
  {
     if (millis() - currentTime > 5000){   //проверяем сколько прошло миллисекунд
         currentTime = millis();
    
/**    Serial.print("Sensor ");
    Serial.print(i+1);
    Serial.print(" : ");
    tempC = sensors.getTempCByIndex(i);
    Serial.print(tempC);
    Serial.print((char)223);        // напечатать символ градусов
    Serial.print("C  |  ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
    Serial.print((char)223);        // напечатать символ градусов
    Serial.println("F");
    Serial.println(""); 
**/  
  lcd.createChar(1, simvol);        //  создаем символ градусов
  lcd.setCursor(0, 0);              //  Устанавливаем курсор в позицию (0 столбец, 0 строка)
  lcd.print("1: ");
  lcd.setCursor(2, 0);
  tempC = sensors.getTempCByIndex(0);
  lcd.print(tempC);
  lcd.setCursor(7, 0);
  lcd.print(char(1));
  lcd.setCursor(8, 0);
  lcd.print("C"); 
  lcd.setCursor(0, 1);               //  Устанавливаем курсор в позицию (0 столбец, 1 строка)
  lcd.print("2: ");                 
  lcd.setCursor(2, 1);
  tempC = sensors.getTempCByIndex(1);
  lcd.print(tempC);
  lcd.createChar(1, simvol);
  lcd.setCursor(7, 1);
  lcd.print(char(1));
  lcd.setCursor(8, 1 );
  lcd.print("C");
  lcd.setCursor(0, 2);              
  lcd.print("3: ");
  lcd.setCursor(2, 2);
  tempC = sensors.getTempCByIndex(2);
  lcd.print(tempC);
  lcd.setCursor(8, 2);
  lcd.print("C");                    //  Выводим текст "С", начиная с установленной позиции курсора
  lcd.setCursor(7, 2);               
  lcd.print(char(1));              
  lcd.setCursor(11, 0);              
  lcd.print("4: ");
  lcd.setCursor(13, 0);
  tempC = sensors.getTempCByIndex(3);
  lcd.print(tempC);
  lcd.setCursor(19, 0);
  lcd.print("C");                   //  Выводим текст "С", начиная с установленной позиции курсора
  lcd.setCursor(18, 0);             
  lcd.print(char(1));  
  lcd.setCursor(11, 1);              
  lcd.print("5: ");
  lcd.setCursor(13, 1);
  tempC = sensors.getTempCByIndex(4);
  lcd.print(tempC);
  lcd.setCursor(19, 1);
  lcd.print("C");                   //  Выводим текст "C", начиная с установленной позиции курсора
  lcd.setCursor(18, 1);             
  lcd.print(char(1)); 
  lcd.setCursor(7, 3);
  lcd.print("ELTOM");
  
  }
}

}

    
