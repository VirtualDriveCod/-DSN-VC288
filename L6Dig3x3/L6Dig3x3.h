//https://arduinocod.blogspot.com/
#pragma once
// ��������, ��� ���������� ��� �� ����������
#ifndef L6Dig3x3_h // ���� ���������� 6Dig3x3 �� ����������
#define L6Dig3x3_h // ����� ���������� ��

#include "Arduino.h"

class L6Dig3x3{
public:
	byte digit[6];  // ���� ���������� ���������� ��������
	void regen(); // �����������, ����� ������ ���������� ���������
	void tetradToSegCod(byte dig, byte tetrad);  // �������������� ������� � ���� ��������� 
	boolean print(unsigned int value, byte digitNum, byte blank); // ����� ������ ����� 
	boolean print2(unsigned int value, byte digitNum, byte blank); // ����� ������ �����
	// �����������
	// typeLed - ��� ����������, ���������� �������� ��������� �������� ����������
	// 0 - ����� ������� -_-, ����� �������� -_-
	// 1 - ����� ������� _-_, ����� �������� -_-
	// 2 - ����� ������� -_-, ����� �������� _-_
	// 3 - ����� ������� _-_, ����� �������� _-_
	// digitPin0 ... digitPin3 - ������ ������ ��������, = 255 - ������ ��������
	// segPinA ... segPinH - ������ ������ ���������          
	L6Dig3x3(byte typeLed, 
		byte digitPin0, byte digitPin1, byte digitPin2,// 1 �������
		byte digitPin3, byte digitPin4, byte digitPin5,// 2 �������
		byte segPinA, byte segPinB, byte segPinC, byte segPinD,
		byte segPinE, byte segPinF, byte segPinG, byte segPinH);// �������� � �����
private:
	byte _digitNumber;  // ����� ��������� �������      
	byte _typeLed; // ��� ����������
	byte _digitPin[6];  // ������ ������ ��������
	byte _segPin[8];  // ������ ������ ���������  
	const byte _segCod[16] = { // ���� ��������
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