//https://arduinocod.blogspot.com/
#include "Arduino.h"
#include "L6Dig3x3.h"
//---------------------------- Функция 1 -------------------------------------
//---------------------------- конструктор -----------------------------------
L6Dig3x3::L6Dig3x3(
	byte typeLed, // тип дисплея
	byte digitPin0, byte digitPin1, byte digitPin2, //1 дисплей
	byte digitPin3, byte digitPin4, byte digitPin5, //2 дисплей
	byte segPinA, byte segPinB, byte segPinC, byte segPinD,//сегменты и точка
	byte segPinE, byte segPinF, byte segPinG, byte segPinH)
{

	// загрузка массивов выводов
	_digitPin[0] = digitPin0; _digitPin[1] = digitPin1; _digitPin[2] = digitPin2;//1 дисплей
	_digitPin[3] = digitPin3; _digitPin[4] = digitPin4; _digitPin[5] = digitPin5;//2 дисплей
	_segPin[0] = segPinA; _segPin[1] = segPinB; _segPin[2] = segPinC; _segPin[3] = segPinD;
	_segPin[4] = segPinE; _segPin[5] = segPinF; _segPin[6] = segPinG; _segPin[7] = segPinH;//сегменты и точка

	_typeLed = typeLed; // тип управления

	// инициализация выводов выбора разрядов
	for (int i = 0; i < 6; i++) {
		if (_digitPin[i] != 255) {    // если вывод не отключен
			pinMode(_digitPin[i], OUTPUT);
			// устанавливаем вывод в неактивное состояние
			if ((_typeLed & 1) == 0) digitalWrite(_digitPin[i], HIGH);
			else digitalWrite(_digitPin[i], LOW);
		}
	}

	// инициализация выводов выбора сегментов
	for (int i = 0; i < 8; i++) {
		pinMode(_segPin[i], OUTPUT);
		// устанавливаем вывод в неактивное состояние
		if ((_typeLed & 2) == 0) digitalWrite(_segPin[i], HIGH);
		else digitalWrite(_segPin[i], LOW);
	}
}

//---------------------------- Функция 2 ------------------------------------------
//---------------------------- регенерация индикаторов ----------------------------
// метод должен вызываться регулярно
void L6Dig3x3::regen()
{

	// выключение активного разряда
	if ((_typeLed & 1) == 0) digitalWrite(_digitPin[_digitNumber], HIGH);
	else digitalWrite(_digitPin[_digitNumber], LOW);

	// новый разряд
	while (true) {
		_digitNumber++;   if (_digitNumber > 5)  _digitNumber = 0;
		if (_digitPin[_digitNumber] != 255) break;
		_digitNumber++;   if (_digitNumber > 5)  _digitNumber = 0;
		if (_digitPin[_digitNumber] != 255) break;
		_digitNumber++;   if (_digitNumber > 5)  _digitNumber = 0;
		if (_digitPin[_digitNumber] != 255) break;
		_digitNumber++;   if (_digitNumber > 5)  _digitNumber = 0;
		if (_digitPin[_digitNumber] != 255) break;
	}

	// состояние сегментов для нового разряда
	byte  d;
	// учет активного состояния сегментов
	if ((_typeLed & 2) == 0) d = (digit[_digitNumber]) ^ 0xff;
	else d = digit[_digitNumber];

	// перегрузка состояния сегментов
	for (byte i = 0; i < 8; i++) {
		if ((d & 1) == 0) digitalWrite(_segPin[i], LOW);
		else digitalWrite(_segPin[i], HIGH);
		d = d >> 1;
	}

	// включение нового разряда
	if ((_typeLed & 1) == 0) digitalWrite(_digitPin[_digitNumber], LOW);
	else digitalWrite(_digitPin[_digitNumber], HIGH);
}

//-------------------------- Функция 3 -------------------------------------------------------
//-------------------------- преобразование тетрады в коды сегментов -------------------------
// аргументы: dig - номер разряда (0 ... 3)
//            tetrad - число для отображения
// в результате коды сегментов оказываются в элементе массива digit[]
void L6Dig3x3::tetradToSegCod(byte dig, byte tetrad) {
	digit[dig] = (digit[dig] | _segCod[tetrad & 0x0f]) & ((_segCod[tetrad & 0x0f]) | 0x80);
}

//--------------------------- Функция 4 ------------------------------------------------
//--------------------------- Печать в 1 дисплей ---------------------------------------
//--------------------------- вывод целого числа ---------------------------------------
// value - число
// digitNum - число разрядов
// blank != 0 - гашение незначащих разрядов 
// возвращает false - ошибка переполнения
boolean L6Dig3x3::print(unsigned int value, byte digitNum, byte blank) {

	// проверка ошибки переполнения
	
	
	if ((value > 999) && (digitNum == 3)) {
		digit[2] = (digit[2] & 0x80) | 0x40;
		digit[1] = (digit[1] & 0x80) | 0x40;
		digit[0] = (digit[0] & 0x80) | 0x40;
		return(false);
	}
	if ((value > 99) && (digitNum == 2)) {
		digit[1] = (digit[1] & 0x80) | 0x40;
		digit[0] = (digit[0] & 0x80) | 0x40;
		return(false);
	}

	// перевод числа в двоично-десятичный код
	byte d1 = 0;
	byte d2 = 0;




	// сотни
	while (true) {
		if (value < 100) break;
		value -= 100;
		d2++;
	}

	// десятки
	while (true) {
		if (value < 10) break;
		value -= 10;
		d1++;
	}

	// перегрузка и гашение незначащих разрядов
	
	if (digitNum > 2) {
		if ( (d2 == 0) && (blank != 0)) digit[2] &= 0x80; // гашение
		else tetradToSegCod(2, d2);
	}
	if (digitNum > 1) {
		if ( (d2 == 0) && (d1 == 0) && (blank != 0)) digit[1] &= 0x80; // гашение
		else tetradToSegCod(1, d1);
	}
	tetradToSegCod(0, value);

	return(true);
}

//--------------------------- Функция 5 ------------------------------------------------
//--------------------------- Печать в 2 дисплей ---------------------------------------
//--------------------------- вывод целого числа ---------------------------------------
// value - число
// digitNum - число разрядов
// blank != 0 - гашение незначащих разрядов 
// возвращает false - ошибка переполнения
boolean L6Dig3x3::print2(unsigned int value, byte digitNum, byte blank) {

	// проверка ошибки переполнения

	if ((value > 999) && (digitNum == 3)) {
		digit[5] = (digit[5] & 0x80) | 0x40;
		digit[4] = (digit[4] & 0x80) | 0x40;
		digit[3] = (digit[3] & 0x80) | 0x40;
		return(false);
	}
	if ((value > 99) && (digitNum == 2)) {
		digit[4] = (digit[4] & 0x80) | 0x40;
		digit[3] = (digit[3] & 0x80) | 0x40;
		return(false);
	}

	// перевод числа в двоично-десятичный код
	byte d1 = 0;
	byte d2 = 0;
	

	

	// сотни
	while (true) {
		if (value < 100) break;
		value -= 100;
		d2++;
	}

	// десятки
	while (true) {
		if (value < 10) break;
		value -= 10;
		d1++;
	}

	// перегрузка и гашение незначащих разрядов
	
	if (digitNum > 2) {
		if ((d2 == 0) && (blank != 0)) digit[5] &= 0x80; // гашение
		else tetradToSegCod(5, d2);
	}
	if (digitNum > 1) {
		if ((d2 == 0) && (d1 == 0) && (blank != 0)) digit[4] &= 0x80; // гашение
		else tetradToSegCod(4, d1);
	}
	tetradToSegCod(3, value);

	return(true);
}