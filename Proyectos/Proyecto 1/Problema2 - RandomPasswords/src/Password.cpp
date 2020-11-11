#include "Password.h"

Password::Password()
{
	//La funcion srand nos permite darle un seed utilizando el tiempo para la generacion de digitos aleatorios para las contraseñas.
	srand((unsigned)time(0));

	//Variable que nos permite mantener el programa corriendo


	while (RunProgram)
	{
		//UI de Inicio para el programa.
		cout << "--Interface Password--" << endl << "[1]Introducir Password - [2]Generar Password  -> ";

		//Control de entrada del usuario
		int userInput;
		cin >> userInput;

		//Opciones del menu para elegir.
		switch (userInput)
		{
		case 1:
			requestPass(); //Llama la funcion que permite introducir un password creado por el usuario.
			break;
		case 2:
			generatePass(); //Llama la funcion que permite generar un password automaticamente.
			break;
		default:
			cout << "Porfavor utilizar 1 o 2 para elegir entrada." << endl << endl; //En caso de escribir una entrada no valida.
			break;
		}
	}
}

void Password::requestPass()
{
	//Opciones para las entradas del usuario.
	cout << "\nIngresar Password: ";
	string userInput;
	cin >> userInput;

	//Una vez el usuario introduzca la contraseña llamara la funcion que verifica si la contraseña es valida, en caso de ser valida se termina el programa.
	if (verifyPass(userInput))
	{
		RunProgram = false;
	}

}

string Password::generatePass()
{
	//rquiredLetters permite saber cuantos caracteres minusculas se deben utilizar despues de colocar los requerimientos (Mayusculas, Caracteres Especuales y numeros).
	int requiredLetters = MinPassLenght - RequiredCapitalChar - RequiredSpecialChar - RequiredNums;

	if (requiredLetters < 1)
	{
		requiredLetters = 1; //En caso de que la cantidad de numeros, mayusculas y caracteres especiales supere el requisito de digitos minimo de la contraseña se recurre a insertar al menos un caracter minuscula.
	}

	//Se crea un array con los requisitos antes propuestos para que la contraseña sea valida. De esta forma sera mas facil acceder a toda la informacion necesaria desde un "For".
	int passRequirements[4] = { RequiredCapitalChar, RequiredSpecialChar, RequiredNums, requiredLetters };

	//Variable donde se almacenara la contraseña generada.
	string newPassword;

	//Este for ira iterando en el array de requisitos. De esta forma se ira creando la contraseña con los caracteres necesarios.
	for (int i = 0; i < 4; i++)
	{
		while (passRequirements[i] > 0) //Mientras el valor dentro de la posicion del array no sea 0, se ira agregando los digitos requeridos.
		{
			switch (i) //Dependiendo del indice del array se llamara a la funcion que permite agregar digitos al nuevo password, pero pasandole en argumento el banco de caracteres a utilizar.
			{
			case 0:
				addDigit(newPassword, CapitalChars); //Llama la funcion de añadir digito, se le pasa newPassword como referencia, y el banco de digitos a utilizar, en este caso letras mayusculas.
				break;
			case 1:
				addDigit(newPassword, SpecialChar); //Llama la funcion de añadir digito, se le pasa newPassword como referencia, y el banco de digitos a utilizar, en este caso caracteres especiales.
				break;
				case 2:
				addDigit(newPassword, Nums); //Llama la funcion de añadir digito, se le pasa newPassword como referencia, y el banco de digitos a utilizar, en este caso numeros.
				break;
			case 3:
				addDigit(newPassword, Chars); //Llama la funcion de añadir digito, se le pasa newPassword como referencia, y el banco de digitos a utilizar, en este caso letras minusculas.
				break;
			}
			passRequirements[i] -= 1; //Al agregar el digito el requerimiento a cumplir debe disminuir en 1.
		}

	}
	random_shuffle(newPassword.begin(), newPassword.end()); //Funcion que se encuentra en la libreria de algorithm que permite mezclar de manera aleatoria los caracteres dentro del rango que se le pasa en el argumento.
	cout << "\nPassword Generado: " << newPassword << endl; //Imprime la contraseña generada.


	//Este fragmento validara que la contraseña generada no tenga caracteres reptidos.
	bool seekValidPass = true; //Mientras sea true, mantendra el while reorganizando la contraseña hasta generar una valida sin repeticones.
	while (seekValidPass)
	{
		//Se llama la funcion que verifica por repeticiones y se evalua su resultado.
		if (checkCharRepeat(newPassword))
		{
			seekValidPass = false; //En el caso no existan repeticiones se sale del while que busca las repeticiones.
		}
		else
		{
			random_shuffle(newPassword.begin(), newPassword.end()); //En el caso de que exista una repeticon, se reorganizara los caracteres aleatoriamente.
			cout << "Nuevo intento de Password: " << newPassword << endl; //Imprime la nueva contraseña generada.
		}
	}

	return newPassword;

	
}

bool Password::verifyPass(const string& password)
{
	//Se llamaran todas la funciones de verificaciones, en el caso de alguna ser invalida, validPassword cambiara a false.
	bool validPassword = true;
	if(!countCharacters(password))
	{
		validPassword = false;
	}
	if(!checkForNums(password))
	{
		validPassword = false;
	}
	if(!checkforSpecialChar(password))
	{
		validPassword = false;
	}
	if(!checkCapital(password))
	{
		validPassword = false;
	}
	if(!checkCharRepeat(password))
	{
		validPassword = false;
	}



	if (validPassword) //Se evalua el resultado de las funciones de verificacion.
	{
		//En caso de que aun sea true, la contraseña es valida.
		cout << "\nPassword Valido!" << endl;
		return true;
	}
	else
	{
		//En el caso de que una sea false, la contraseña no sera valida.
		cout << "\nPassword NO Valido!" << endl << endl;
		return false;
	}

}

void Password::addDigit(string& password, string availableDigits)
{
	int randomNumber = (rand() % availableDigits.size()); //Genera un numero aleatorio dentro del rango del string que se le pasa por argumento.
	password += availableDigits[randomNumber]; //Utiliza el numero generado aleatoriamente como indice para acceder a un caracter aleatorio dentro del string y añadirlo al password que pasa como referencia.
}

bool Password::countCharacters(const string& password)
{
	//Este if permite evaluar si la cantidad de caracteres de la contraseña es superior o inferior al minimo requerido.
	if (password.size() < MinPassLenght)
	{
		cout << "ERROR - El Password debe contener al menos " << MinPassLenght << " digitos." << endl; //En caso de que sea inferior, retorna false y la contraseña es invalida.
		return false;
	}
	else
	{
		cout << password.size() << " Digitos. -> OK!" << endl; //En caso de ser igual o superior, retorna true y la contraseña es valida con respecto a cantidad de caracteres.
		return true;
	}

}

bool Password::checkForNums(const string& password)
{
	bool containsNums = false; //Bool que guardara si la contraseña contiene digitos del 0 al 9.
	int countNums = 0; //Variable que guardara la cantidad de digitos del 0 al 9 encontrados dentro de la contraseña.

	//El primer "for" sera utilizado como indice para caminar dentro de los caracteres de la contraseña propuesta.
	for (int i = 0; i < password.size(); i++)
	{
		//El segundo "for" sera utilizado como indice para caminar dentro del banco de caracteres disponibles, en este caso los digitos del 0 al 9.
		for (int j = 0; j < Nums.size(); j++)
		{
			//El "if" evaluara si el caracter que se encuentra en el indice de la contraseña es igual al caracter que se encuentra en el indice del banco de caracteres.
			if (password[i] == Nums[j])
			{
				containsNums = true; //Si es cierto, cambia el bool que guarda si existe numeros dentro del password.
				countNums++; //Incrementa la cantidad de caracteres numericos encontrados en la contraseña.
			}
		}
	}

	//Dependiendo si existen o no caracteres numericos dentro de la contraseña se enviara el debido mensaje al usuario.
	if (containsNums == false)
	{
		cout << "ERROR - El Password debe contener al menos un digito del 0 al 9." << endl; //Si no contiene numeros la funcion retorna false.
		return false;
	}
	else
	{
		cout << countNums << " digitos del 0 al 9. -> OK!" << endl; //Si existe algun numero, la contraseña retorna true.
		return true;
	}
}

bool Password::checkforSpecialChar(const string& password)
{
	
	bool containsSpecialChar = false; //Bool que guardara si la contraseña contiene caracteres especiales.
	int countSpecialChar = 0; //Variable que guardara la cantidad de caracteres especiales encontrados dentro de la contraseña.

	//El primer "for" sera utilizado como indice para caminar dentro de los caracteres de la contraseña propuesta.
	for (int i = 0; i < password.size(); i++)
	{
		//El segundo "for" sera utilizado como indice para caminar dentro del banco de caracteres disponibles, en este caso los caracteres especiales.
		for (int j = 0; j < SpecialChar.size(); j++)
		{
			//El "if" evaluara si el caracter que se encuentra en el indice de la contraseña es igual al caracter que se encuentra en el indice del banco de caracteres.
			if (password[i] == SpecialChar[j])
			{
				containsSpecialChar = true; //Si es cierto, cambia el bool que guarda si existe caracteres especiales dentro del password.
				countSpecialChar++; //Incrementa la cantidad de caracteres especiales encontrados en la contraseña.
			}
		}
	}

	//Dependiendo si existen o no caracteres especiales dentro de la contraseña se enviara el debido mensaje al usuario.
	if (containsSpecialChar == false)
	{
		cout << "ERROR - El Password debe contener al menos un caracter especial " << SpecialChar << endl; //Si no contiene caracteres especiales la funcion retorna false.
		return false;
	}
	else
	{
		cout << countSpecialChar << " caracteres especiales. -> OK!" << endl; //Si existe algun caracter especial, la contraseña retorna true.
		return true;
	}
}

bool Password::checkCapital(const string& password)
{
	bool containsCapital = false; //Bool que guardara si la contraseña contiene caracteres en mayusculas.
	int countCapitalChar = 0; //Variable que guardara la cantidad de caracteres mayusculas encontrados dentro de la contraseña.

	//El primer "for" sera utilizado como indice para caminar dentro de los caracteres de la contraseña propuesta.
	for (int i = 0; i < password.size(); i++)
	{
		//El segundo "for" sera utilizado como indice para caminar dentro del banco de caracteres disponibles, en este caso los caracteres en mayusculas.
		for (int j = 0; j < CapitalChars.size(); j++)
		{
			//El "if" evaluara si el caracter que se encuentra en el indice de la contraseña es igual al caracter que se encuentra en el indice del banco de caracteres.
			if (password[i] == CapitalChars[j])
			{
				containsCapital = true; //Si es cierto, cambia el bool que guarda si existe caracteres mayusculas dentro del password.
				countCapitalChar++; //Incrementa la cantidad de caracteres mayusculas encontrados en la contraseña.
			}
		}
	}

	//Dependiendo si existen o no caracteres mayusculas dentro de la contraseña se enviara el debido mensaje al usuario.
	if (containsCapital == false)
	{
		cout << "ERROR - El Password debe contener al menos una mayuscula." << endl; //Si no contiene caracteres mayusculas la funcion retorna false.
		return false;
	}
	else
	{
		cout << countCapitalChar << " caracteres mayusculas. -> OK!" << endl; //Si existe algun caracter en mayuscula, la contraseña retorna true.
		return true;
	}

}

bool Password::checkCharRepeat(const string& password)
{
	int charIndex = 0; //Variable que sera el indice que caminara dentro de la contraseña propuesta.
	bool containsRepeatChar = false; //Bool que guardara si existe algun caracter repetido seguido.

	//Mientras no exista caracter repetido el while se encargara de seguir buscando si existe alguna repeticion.
	while (!containsRepeatChar)
	{
		if (password[charIndex] == password[charIndex + 1]) //El if preguntara si el caracter que se encuentra en el indice es igual al que se encuentra una posicion despues del indice.
		{
			//En caso de que sean caracteres iguales, el bool cambiara a true, se enviara un mensaje de error al usuario y la funcion retornara false.
			containsRepeatChar = true;
			cout << "ERROR - El Password no debe contener caracteres repetidos seguidos." << endl;
			return false;
		}
		else
		{
			//En caso de recorrer todo el string y llegar al final de la cadena del string sin ninguna repeticion la funcion retornara true y la contraseña es valida.
			if (charIndex + 1 == password.size()) 
			{
				cout << "No caracteres repetidos. -> OK!\n" << endl;
				return true;
			}
			charIndex++; //Si aun no esta al final de la cadena de string, aumentara el indice en 1 y volvera a evaluar si existen repeticiones.
		}
	}
}
