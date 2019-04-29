//https://arduinocod.blogspot.com/
#pragma once
// проверка, что библиотека еще не подключена
#ifndef L6Dig3x3_h // если библиотека 6Dig3x3 не подключена
#define L6Dig3x3_h // тогда подключаем ее

#include "Arduino.h"

class L6Dig3x3{
public:
	byte digit[6];  // коды управления сегментами разрядов
	void regen(); // регенерация, метод должен вызываться регулярно
	void tetradToSegCod(byte dig, byte tetrad);  // преобразования тетрады в коды сегментов 
	boolean print(unsigned int value, byte digitNum, byte blank); // вывод целого числа 
	boolean print2(unsigned int value, byte digitNum, byte blank); // вывод целого числа
	// конструктор
	// typeLed - тип управления, определяет активные состояния сигналов управления
	// 0 - выбор разряда -_-, выбор сегмента -_-
	// 1 - выбор разряда _-_, выбор сегмента -_-
	// 2 - выбор разряда -_-, выбор сегмента _-_
	// 3 - выбор разряда _-_, выбор сегмента _-_
	// digitPin0 ... digitPin3 - выводы выбора разрядов, = 255 - разряд отключен
	// segPinA ... segPinH - выводы выбора сегментов          
	L6Dig3x3(byte typeLed, 
		byte digitPin0, byte digitPin1, byte digitPin2,// 1 дисплей
		byte digitPin3, byte digitPin4, byte digitPin5,// 2 дисплей
		byte segPinA, byte segPinB, byte segPinC, byte segPinD,
		byte segPinE, byte segPinF, byte segPinG, byte segPinH);// сегменты и точка
private:
	byte _digitNumber;  // номер активного разряда      
	byte _typeLed; // тип управления
	byte _digitPin[6];  // выводы выбора разрядов
	byte _segPin[8];  // выводы выбора сегментов  
	const byte _segCod[16] = { // коды символов
	  B00111111,  // 0
	  B00000110,  // 1
	  B01011011,  // 2
	  B01001111,  // 3
	  B01100110,  // 4
	  B01101101,  // 5
	  B01111101,  // 6
	  B00000111,  // 7
	  B01111111,  // 8
	  B01101111,  // 9
	  B01110111,  // A
	  B01111100,  // b
	  B00111001,  // C
	  B01011110,  // d
	  B01111001,  // E
	  B01110001,  // F 
	};
};

#endif