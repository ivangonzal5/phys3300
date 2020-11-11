#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
class Password
{
public:
	//Variable que mantiene el programa corriendo en loop.
	bool RunProgram = true;

	//Miembros que definiran los requisitos de la contraseña.
	const int MinPassLenght = 8; //Tamaño minimo de la contraseña.
	const int RequiredNums = 1; //Cantidad de digitos del 0 al 9 requeridos en la contraseña.
	const int RequiredSpecialChar = 1; //Cantidad de caracteres especiales requeridos en la contraseña.
	const int RequiredCapitalChar = 1; //Cantidad de mayusculas requeridas en la contraseña.

	//Funciones prototipos publicas.
	Password(); //Constuctor
	void requestPass(); //Funcion que pide al usuario una contraseña.
	string generatePass(); //Funcion que genera una contraseña basada en los requisitos.

private:
	//Miembros privados que contienen todos los digitos posibles dentro de una contraseña.
	const string Chars = "abcdefghijklmnopqrstuvwxyz"; //Caracteres minusculas.
	const string CapitalChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //Caracteres mayusculas.
	const string Nums = "0123456789"; //Caracteres numericos.
	const string SpecialChar = "!$&?*/\\"; //Caracteres especiales.

	void addDigit(string& password, string availableDigits); //Funcion que permite añadir caracteres desde una cadena de string a la contraseña generada.

	bool verifyPass(const string& password); //Funcion que permite validar una contraseña con los requisitos propuestos.

	//Funciones privadas para criterios de contraseñas
	bool countCharacters(const string &password); //Cuenta los caracteres.
	bool checkForNums(const string& password); //Verifica que existan numeros en la contraseña.
	bool checkforSpecialChar(const string& password); //Verifica que existan caracteres especiales en la contraseña.
	bool checkCapital(const string& password); //Verifica que existan mayusculas en la contraseña.
	bool checkCharRepeat(const string& password); //Verifica si existen repeticiones seguidas de caracteres.
};

