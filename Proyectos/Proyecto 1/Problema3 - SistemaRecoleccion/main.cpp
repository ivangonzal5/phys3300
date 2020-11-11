// Importamos las librerías necesarias para el programa. 
#include<iostream>
#include<vector>
#include<string>
#include<ctime>

// Incluimos el namespace std. 
using namespace std;

//Declaramos las funciones que usaremos en este programa. 
void generateInventory(int maxGen, vector<string>& randomInventory, const vector<string>& allItems);
void openInventory(vector<string>& inventory);
void recoleccion(vector<string>& inventory);
bool probability(int chance);

//VARIABLE PARA SABER SI YA SE GENERO UN INVENTARIO DE RECOLECCION
bool RecoleccionGenerated = false;

//INVENTARIO DE RECOLECCION GLOBAL PARA QUE RECUERDE LOS ELEMENTOS AL SALIR DE LA FUNCION
vector<string> recInventory(5, "NA");


//La funcion generateInventory nos permite llenar un vector (randomInventory) con elementos aleatorios de otro vector(allItems), maxGen permite saber cuantos espacios generar.
void generateInventory(const int maxGen, vector<string>& randomInventory, const vector<string>& allItems)
{
	//Definimos las variables para el uso del rand().
	int randomItemPos;
	int min = 0;
	int max = allItems.size() - 1;

	//Declaramos una variable contador para el ciclo while. 
	int counter = 0;

	//Creamos el ciclo que llena el inventario "random". 
	while (counter < maxGen)
	{
		//Generamos la posición "random".
		randomItemPos = rand() % (max - min + 1) + min;

		randomInventory[counter] = allItems[randomItemPos];
		counter++; //El counter solo se aumenta cuando se haya agregado algo al inventario. 
	}

	//system("CLS");
	cout << "INVENTARIO GENERADO! \n\n" << endl;
	system("pause"); //Para esperar que el usuario presione alguna tecla. 

}



//Creamos una función para ver el inventario y tirar objetos del mismo. 
void openInventory(vector<string>& inventory)
{
	//Declaramos la variable que mantiene el inventario abierto. 
	bool inventoryOpened = true;

	//Declaramos la variable para la entrada del usuario. 
	int userInput;

	//Creamos el ciclo que nos mantiene el inventario abierto. 
	while (inventoryOpened) {

		//Encabezado del menu de inventario. 
		system("CLS");
		cout << "===============================================================" << endl;
		cout << "= = INVENTARIO = =" << "\n" << endl;

		//Creamos el ciclo que itera sobre el inventario para imprimirlo (mostrarlo en pantalla).
		for (int index = 0; index < inventory.size(); index++)
		{
			cout << index + 1 << ". " << inventory[index] << endl;
		}

		//Creamos la opción EXIT.
		cout << inventory.size() + 1 << ". " << "EXIT" << endl;
		cout << "===============================================================" << endl;

		//Esperamos la entrada del usuario.
		cout << "INTRODUZCA SELECCION: "; cin >> userInput;

		//Si el usuario introduce el número de algún item, entonces borra el item usando erase(). De otra forma, cierra el inventory. 
		if (userInput <= inventory.size()) 
		{
			inventory.erase(inventory.begin() + userInput - 1);

			//Al borrar un articulo se agrega un NA como espacio vacio para mantener la misma cantidad de slots originales.
			inventory.push_back("NA");
		}
		else if (userInput == inventory.size() + 1) 
		{
			inventoryOpened = false;
		}

	}

}


void recoleccion(vector<string>& inventory)
{
	const vector<string> allItems = { "Roca Blanda", "Roca Dura", "Roca Cristalina", "Roca Magica" };

	//Mantiene el menu de recoleccion abierto.
	bool recoleccionMenuOpen = true;

	//Variable que registra input del usuario.
	int recoleccionMenuOption;

	//Cuenta la cantidad de espacios disponibles del inventario.
	int naSpaces = count(inventory.begin(), inventory.end(), "NA");

	//Genera una unica vez los articulos disponibles en el menu de recoleccion.
	if (!RecoleccionGenerated)
	{
		generateInventory(5, recInventory, allItems);
		RecoleccionGenerated = true;
	}

	while (recoleccionMenuOpen) {

		//Creamos el UI.
		system("CLS");

		//El header nos da la cantidad de espacios disponibles en el inventario.
		cout << "===============================================================" << endl;
		cout << "TIENES " << naSpaces << " ESPACIOS DISPONIBLES EN TU INVENTARIO." << "\n" << endl;
		cout << "===============================================================" << endl;

		//Header de la lista de recoleccion
		cout << "= = RECOLECCION = =" << "\n" << endl;

		//Creamos el ciclo que itera sobre el inventario para imprimirlo (mostrarlo en pantalla).
		for (int counter = 0; counter < recInventory.size(); counter++) 
		{
			cout << counter + 1 << ". " << recInventory[counter] << endl;
		}

		//Creamos la opción EXIT para salir del menu de recoleccion.
		cout << recInventory.size() + 1 << ". " << "EXIT" << endl;
		cout << "===============================================================" << endl;

		//Opcion para salir del menu de recoleccion y permitir que la proxima vez que se abra genere nuevos items.
		cout << recInventory.size() + 2 << ". " << "REFILL LIST (DEV ONLY)" << endl;
		cout << "===============================================================" << endl;




		//Entrada del usario.
		cout << "INTRODUZCA SELECCION: "; cin >> recoleccionMenuOption;

		//Si el usuario introduce el número de algún item, lo pasa al Inventario del usuario y lo elimina de la lista de recoleccion.
		if (recoleccionMenuOption <= recInventory.size()) {
			//Si el inventario esta lleno no permite agregar items.
			if (naSpaces == 0)
			{
				system("CLS");
				cout << "EL INVENTARIO ESTA LLENO. NO SE PUEDE AGREGAR MAS ARTICULOS.\n";
				system("pause"); //Para esperar que el usuario presione alguna tecla. 
			}
			else 
			{
				//Bool que permite saber si se podra o no tomar el articulo sin que se destruya
				bool successLoot;

				//Si el item es una roca magica las probabilidades de exito son 50%, cualquier otro articulo tiene probabilidad de 75%.
				if (recInventory[recoleccionMenuOption - 1] == "Roca Magica")
				{
					//Llama la funcion probability con un chance de 50% de logro.
					successLoot = probability(50);
				}
				else
				{
					//Llama la funcion probability con un chance de 75% de logro.
					successLoot = probability(75);
				}

				if (successLoot)
				{
					//Agrega el item al inventario.
					inventory[inventory.size() - naSpaces] = recInventory[recoleccionMenuOption - 1];
					//Elimina el item del menu de recoleccion.
					recInventory.erase(recInventory.begin() + recoleccionMenuOption - 1);

					//Mensaje que permite saber al usuario que se agrego el item al inventario satisfactoriamente.
					cout << "SE HA TOMADO EL ARTICULO SATISFACTORIAMENTE! \n\n" << endl;
				}
				else
				{
					//Elimina el item del menu de recoleccion.
					recInventory.erase(recInventory.begin() + recoleccionMenuOption - 1);

					//Mensaje que permite saber al usuario que se destruyo el articulo.
					cout << "OH NO! EL ARTICULO SE HA QUEBRADO ANTES DE ENTRAR EN EL INVENTARIO. \n\n" << endl;
				}

				//Agrega un NA como espacio vacio en el menu de recoleccion.
				recInventory.push_back("NA");

				recoleccionMenuOpen = false; //Se cierra el menu de recoleccion.
				system("pause"); //Para esperar que el usuario presione alguna tecla. 
				system("CLS"); //Limpia la pantalla.
			}
		}
		//Cierra el menu de recoleccion.
		else  if (recoleccionMenuOption == recInventory.size() + 1)
		{
			recoleccionMenuOpen = false;
		}
		//Cierra el menu de recoleccion y la proxima vez que se abra generara nuevos articulos.
		else if (recoleccionMenuOption == recInventory.size() + 2)
		{
			RecoleccionGenerated = false;
			recoleccionMenuOpen = false;
		}
	}
}

bool probability(int chance)
{
	//Variable donde se guarda el numero aleatorio de 0 a 100.
	int randomNumber = (rand() % 100);
	//Mensaje al usuario del nivel de probabilidad.
	cout << "Probabilidad de loot: " << chance << endl;
	//Mensaje al usuario del valor de probabilidad alcanzado.
	cout << "Probabilidad alcanzada: " << randomNumber << endl;

	//Si el valor alcanzado esta dentro del nivel de logro se regresa true, de lo contrario si sobrepasa se retorna false.
	if (randomNumber <= chance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	//Creamos un vector con todos los objetos posibles. 
	const vector<string> allItems = { "Hierba mala", "Gusano Dorado" };

	//Comando que permite realizar busqueda de valores aleatorios en base al tiempo.
	srand(time(0));

	//Vector de Inventario con 20 espacios con NA
	vector<string> inventory(20, "NA");

	//Bool que permite el menu mantenerse abierto.
	bool menuOpen = true;

	//Creamos la variable para la entrada del usuario. 
	int userInput;

	//Usamos un ciclo while para mantener el menú funcionando. 
	while (menuOpen) {

		//Limpia la ventana de comandos.
		system("CLS");

		//UI del Menu.
		cout << "===============================================================" << endl;
		cout << "= = INVENTARIO Y RECOLECCION = =" << "\n" << endl;
		cout << "1. GENERADOR DE INVENTARIO" << endl;
		cout << "2. ABRIR INVENTARIO" << endl;
		cout << "3. MENU DE RECOLECCION" << endl;
		cout << "4. SALIR" << endl;
		cout << "===============================================================" << endl;

		//Leemos la entrada del usuario. 
		cout << "INTRODUZCA SELECCION:  "; cin >> userInput;

		//Usamos un switch() para manejar el menú con la entrada del usuario.
		switch (userInput) {

		case 1:

			//Genera objetos y los añade al inventario.
			generateInventory(7, inventory, allItems);
			break;

		case 2:
			//Abre el inventario.
			openInventory(inventory);
			break;

		case 3:
			//Abre el menu de recoleccion.
			recoleccion(inventory);
			break;

		case 4:
			//En caso de salir se cambia la variable menuOpen para terminar con el while que mantiene el menu funcionando.
			menuOpen = false;
			break;

		default:
			system("CLS");
			break;
		}
	}
	return 0;
}