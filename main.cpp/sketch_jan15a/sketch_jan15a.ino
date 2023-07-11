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

int deviceCount = 0;                                       // переменная датчиков
int tempC, tempC1, tempC2, tempC3, tempC4;                 // переменная температуры
unsigned long currentTime, currentTime1;                   // Переменная текущего времени
 

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
  lcd.init();                             //  Инициируем работу с LCD дисплеем
  lcd.backlight();                        //  Включаем подсветку LCD дисплея
  currentTime = millis();                 // запускаем отчет времени
  sensors.begin();                        // запустить библиотеку
  Serial.begin(9600);                     // запускаем монитор порта
  deviceCount = sensors.getDeviceCount();
//  Serial.print("Locating devices...");  // найти устройства на шине
//  Serial.print("Found ");
//  Serial.print(deviceCount, DEC);
//  Serial.println(" devices.");
//  Serial.println("");
  lcd.setCursor(4, 1);
  lcd.print("418137.010");
  lcd.setCursor(4, 2);
  lcd.print("ver.1.5.0");
  delay(2000);
  lcd.clear();
  lcd.setCursor(3, 1);              
  lcd.print("INITIALIZATION");
  lcd.setCursor(7, 2);              
  lcd.print("SENSORS");
  delay(2000);
  lcd.clear();
  
}

void loop (void)
{ 
       
  sensors.requestTemperatures();       // послать команду всем датчикам для преобразования температуры
  tempC = sensors.getTempCByIndex(0);  // присваиваем переменной значение с датчика
  tempC1 = sensors.getTempCByIndex(1);  
  tempC2 = sensors.getTempCByIndex(2);  
  tempC3 = sensors.getTempCByIndex(3);  
  tempC4 = sensors.getTempCByIndex(4);  
  lcd.createChar(1, simvol);           //  создаем символ градусов
  

/**    
         for (int i = 0;  i < deviceCount;  i++) // отобразить температуру с каждого датчика
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
    Serial.println(""); 
    }
 **/ 
   if (millis() - currentTime > 1000){   //проверяем сколько прошло миллисекунд
         currentTime = millis();
 
  
  lcd.setCursor(1, 0);               //  Устанавливаем курсор в позицию (2 столбец, 1 строка)
  lcd.print("1:");                   //  печатаем порядковый номер датчика
  lcd.print(tempC);                  //  печатаем температуру
  if (tempC == -127){                //  условие для проверки наличия датчика
    lcd.setCursor(1, 0);
    lcd.print("1:---");
  }
  lcd.print(char(1));                //  печатаем знак градуса
  lcd.print("C  ");                  //  печатаем знак цельсия
  
  lcd.setCursor(1, 1);               //  Устанавливаем курсор в позицию (2 столбец, 2 строка)
  lcd.print("2:");                 
  lcd.print(tempC1);
  if (tempC1 == -127){               //  условие для проверки наличия датчика
    lcd.setCursor(1, 1);
    lcd.print("2:---");
  }
  lcd.print(char(1));
  lcd.print("C  ");
  
  lcd.setCursor(1, 2);               //  Устанавливаем курсор в позицию (2 столбец,  3строка)
  lcd.print("3:");                 
  lcd.print(tempC2);
  if (tempC2 == -127){               //  условие для проверки наличия датчика
    lcd.setCursor(1, 2);
    lcd.print("3:---");
  }
  lcd.print(char(1));
  lcd.print("C  ");
  
  lcd.setCursor(11, 0);               //  Устанавливаем курсор в позицию (13 столбец, 1 строка)
  lcd.print("4:");                 
  lcd.print(tempC3);
  if (tempC3 == -127){                //  условие для проверки наличия датчика
    lcd.setCursor(11, 0);
    lcd.print("4:---");
  }
  lcd.print(char(1));
  lcd.print("C  ");

  lcd.setCursor(11, 1);               //  Устанавливаем курсор в позицию (13 столбец, 2 строка)
  lcd.print("5:");                 
  lcd.print(tempC4);
  if (tempC1 == -127){                //  условие для проверки наличия датчика
    lcd.setCursor(11, 1);
    lcd.print("5:---");
  }
  lcd.print(char(1));
  lcd.print("C  ");
  
  lcd.setCursor(7, 3);                //  Устанавливаем курсор в позицию (8 столбец, 4 строка)
  lcd.print("ELTOM");
 
   }
/**
   if (millis() - currentTime1 > 100000){   //проверяем сколько прошло миллисекунд
         currentTime1 = millis();
         lcd.setCursor(3, 3);
         lcd.print("I'm");
         lcd.setCursor(13, 3);
         lcd.print("JONE");
         delay(5000);
         lcd.setCursor(3, 3);
         lcd.print("   ");
         lcd.setCursor(13, 3);
         lcd.print("    ");
**/
}






    
