//Автор VirtualDrive
//https://arduinocod.blogspot.com/

#include <L6Dig3x3.h>
#include <MsTimer2.h>
L6Dig3x3 disp(1, 16,15,14, 19,18,17,  2, 3, 4, 5, 6, 7, 8,9 );
void setup() {
 //Serial.begin(9600);
  // put your setup code here, to run once:
  MsTimer2::set(2, timerInterrupt); // прерывание по таймеру 2 мс 
  MsTimer2::start();
  //pinMode(21, INPUT_PULLUP);// притянуть А6 к земле
  //pinMode(20, INPUT_PULLUP);// притянуть А7 к земле
}

void loop() {
 
float sensorValue = analogRead(A6);// напряжение
   sensorValue= sensorValue/6,333333333333333;// полученное число разделить
   disp.print((int)(sensorValue * 10.), 3, 1); // напечатать результат на 1 дисплей 
    disp.digit[1] |= 0x80;// зажечь точку 2 разряда 1-го дисплея
   // Serial.println(sensorValue);
    

    float sensorValue2 = analogRead(A7);// ток
    sensorValue2=sensorValue2-14;// уберем погрешность
    float  T=sensorValue2*0.04;// полученный результат умножаем 
     disp.print2((int)(T * 100.), 3, 1);// напечатать результат на 2 дисплей  
    
disp.digit[5] |= 0x80;// зажечь точку 3 разряда 2-го дисплея или же по сути он же 5 разряд по счету

// Serial.println(sensorValue2);
 delay(500);
  }
void  timerInterrupt() {// обработчик прерывания 2 мс

  disp.regen(); // регенерация индикатора

}
