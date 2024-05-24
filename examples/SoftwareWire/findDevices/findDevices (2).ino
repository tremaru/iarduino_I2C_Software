// ДАННЫЙ ПРИМЕР ИЩЕТ ВСЕ МОДУЛИ НА ШИНЕ I2C:                       // * Строки со звёздочкой являются необязательными.
                                                                    //
#include <iarduino_I2C_Software.h>                                  //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_I2C_Address.
SoftTwoWire sWire(3,4);                                             //   Объявляем  объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                                    //
void setup(){                                                       //
     delay(500);                                                    // * Ждём завершение переходных процессов связанных с подачей питания.
     Serial.begin(9600);                                            //   Инициируем передачу данных в монитор последовательного порта на скорости 9600 бит/сек.
     while(!Serial){;}                                              // * Ждём завершения инициализации шины UART.
     sWire.begin();                                                 //   Инициируем работу с программной шиной I2C.
//   sWire.setClock(400000);                                        // * Изменить скорость передачи данных на указанную. По умолчанию скорость 100'000 бит/сек.
//   sWire.setPins(5,6);                                            // * Изменить назначенные ранее выводы шины I2C на указанные: SDA, SCL.
//   sWire.getPins(&sda,&scl);                                      // * Получить действующие выводы шины I2C в переменные: sda, scl.
//   sWire.setWireTimeout(25000);                                   // * Задать таймаут ожидания ведомого в мкс (0 = таймаут отключён). Если вторым параметром указать true, то по достижении таймаута шина будет отключена, как end().
//   sWire.end();                                                   // * Отключение шины. Для включения нужно вновь указать выводы setPins(), а потом begin().
}                                                                   //
                                                                    //
void loop(){                                                        //
     Serial.println("--------------");                              // *
     uint8_t sum=0;                                                 //   Количество найденных устройств.
//   Проходим по всем возможным адресам на шине I2C:                //
     for(uint8_t i=1; i<128; i++){                                  //   Для 7-и битной адресации диапазон адресов равен 1-127. Адрес 0 является адресом общего вызова.
     //  Передаём адрес очередного устройства и слушаем его ответ:  //
         sWire.beginTransmission(i);                                //   Инициируем передачу данных по шине I2C к устройству с адресом i. При этом сама передача не начнётся.
         if( sWire.endTransmission()==0 ){                          //   Выполняем инициированную ранее передачу (только адрес устройства). Функция возвращает: 0-успех / 1 - переполнен буфер / 2 - получен NACK при передаче адреса / 3 - получен NACK при передаче данных / 4 - другая ошибка / 5 - timeout.
         //  Информируем о наличии устройств:                       //
             if(!sum){ Serial.println(F("Найдены устройства:")); }  // *
         //  Выводим строку с адресом i:                            //
             Serial.print((String) (++sum)+") "+i+" = 0x");         //   Выводим строку с адресом на которое отреагировало устройство.
             Serial.println(i,HEX);                                 //   Завершаем строку тем же адресом, но в шестнадцатиричной системе счисления.
         }                                                          //
     }                                                              //
//   Информируем о завершении поиска устройств на шине I2C:         //
     if( sum ){ Serial.println((String) "Всего устройств: "+sum); } //   Выводим строку с количеством найденных устройств.
     else     { Serial.println( F("Устройства не найдены!") );    } //   Выводим строку об отсутствии найденных устройств.
//   Задержка перед новым поиском устройств:                        //
     delay(5000);                                                   // * 
}                                                                   //