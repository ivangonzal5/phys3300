//Librerias necesarias para que el programa funcione
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

int main()
{
	//Estas variables guardan la cantidad maxima por compartimiento del inventario. Son const porque no deseo que su valor cambie.
	const int i_HerbsMaxSpaces = 5;
	const int i_MetalsMaxSpaces = 3;

	//Estas variables contienen cuantos slots han sido usado de cada compartimiento.
	int i_HerbsUsedSpaces = 0;
	int i_MetalsUsedSpaces = 0;

	//Vectores que contienen las posibles hierbas y minerales.
	const vector<string> vec_Herbs{ "Verila Pluma (VP)", "Secta Doralis (SD)", "Crystalia Fulminis (CF)" };
	const vector<string> vec_Metals{ "Cristal Azul (A)", "Cristal Verde (V)" };

	//Vector que contiene el Inventario del Jugador y que es igual a la suma de los compartimientos de hierba y minerales.
	vector<string> vec_Inventory;

	//Entrada de datos del Usuario.
	string userInput = "NA";

	//Estas variables nos permitiran encontrar una posicion random dentro del rango de i_min y i_max.
	const int i_min = 0;
	int i_max;
	int i_randomObjectPos;


	while (userInput != "exit" && userInput != "0")
	{
		//Informacion del UI para entrada de datos.
		cout << "============================================================================" << endl;
		cout << "(M)etals - (H)erbs - (I)nventory - (exit) or (0) ---> Waiting for input: "; cin >> userInput; cout << "\n";

		//If que nos permite evaluar si el usuario desea minar un metal o recoger una hierba dependiendo del userInput.
		//Entrada m o M para minar metales.
		if (userInput == "m" || userInput == "M")
		{
			//Si la entrada del usuario es una 'M', el programa verifica si tenemos espacio suficiente en el compartimiento de metales.
			if (i_MetalsUsedSpaces < i_MetalsMaxSpaces)
			{
				//Mostrara el mensaje de 'Minando' por 1 segundo.
				cout << "Minando.";
				sleep_for(milliseconds(500));
				cout << ".";
				sleep_for(milliseconds(500));
				cout << ".\n\n";

				//La variable i_max cambiara al size del vector de los metales -1.
				i_max = vec_Metals.size() - 1;

				//Buscara una posicion random dentro del rango del vector de los metales.
				i_randomObjectPos = rand() % (i_max - i_min + 1) + i_min;

				//Aumentara en 1 los espacios utilizados del compartimiento de metales.
				i_MetalsUsedSpaces++;

				//Mostrara un mensaje del metal obtenido y la cantidad de espacios tomados de los compartimientos.
				cout << "Has obtenido: " << vec_Metals[i_randomObjectPos] << "\n";
				cout << "Espacios restantes: Hierbas: " << i_HerbsUsedSpaces << "/" << i_HerbsMaxSpaces << " || Metales: " << i_MetalsUsedSpaces << "/" << i_MetalsMaxSpaces << "\n\n";

				//Agregara el objeto obtenido en el inventario.
				vec_Inventory.push_back(vec_Metals[i_randomObjectPos]);

			}
			//Si los espacios utilizados exceden los espacios maximos notificamos al usuario que el compartimiento esta lleno.
			else
			{
				cout << "COMPARTIMIENTO DE METALES LLENO." << "\n\n";
			}
		}

		//Entrada h o H para recoger hierbas.
		else if (userInput == "h" || userInput == "H")
		{
			//Si la entrada del usuario es una 'H', el programa verifica si tenemos espacio suficiente en el compartimiento de hierbas.
			if (i_HerbsUsedSpaces < i_HerbsMaxSpaces)
			{
				//Mostrara el mensaje de 'Recogiendo' por 1 segundo.
				cout << "Recogiendo.";
				sleep_for(milliseconds(500));
				cout << ".";
				sleep_for(milliseconds(500));
				cout << ".\n\n";

				//La variable i_max cambiara al size del vector de las hierbas -1.
				i_max = vec_Herbs.size() - 1;

				//Buscara una posicion random dentro del rango del vector de las hierbas.
				i_randomObjectPos = rand() % (i_max - i_min + 1) + i_min;

				//Aumentara en 1 los espacios utilizados del compartimiento de hierbas.
				i_HerbsUsedSpaces++;

				//Mostrara un mensaje de la hierba obtenida.
				cout << "Has obtenido: " << vec_Herbs[i_randomObjectPos] << "\n";
				cout << "Espacios restantes: Hierbas: " << i_HerbsUsedSpaces << "/"<< i_HerbsMaxSpaces << " || Metales: " << i_MetalsUsedSpaces << "/" << i_MetalsMaxSpaces << "\n\n";

				//Agregara el objeto obtenido en el inventario.
				vec_Inventory.push_back(vec_Herbs[i_randomObjectPos]);

			}
			//Si los espacios utilizados exceden los espacios maximos notificamos al usuario que el compartimiento esta lleno.
			else
			{
				cout << "COMPARTIMIENTO DE HIERBAS LLENO." << "\n\n";
			}
		}


		//Entrada i o I para abrir el inventario.
		else if (userInput == "i" || userInput == "I")
		{
			//Mostrara 'Inventario' por 1 segundo.
			cout << "Inventario.";
			sleep_for(milliseconds(500));
			cout << ".";
			sleep_for(milliseconds(500));
			cout << ".\n\n";


			//Si la suma de los espacios usados de hierbas y metales es 0, el inventario se encuentra vacio.
			if (i_HerbsUsedSpaces + i_MetalsUsedSpaces == 0)
			{
				cout << "Inventario Vacio" << "\n\n";
			}

			//De lo contrario procedemos a imprimir el inventario.
			else
			{
				//Con el for itera a traves del vector y lo imprime.
				for (int i = 0; i < vec_Inventory.size(); i++)
				{
					cout << vec_Inventory[i] << " | ";
				}
				//Muestra los espacios en los compartimientos de hierbas y metales.
				cout << "\nEspacios restantes: Hierbas: " << i_HerbsUsedSpaces << "/" << i_HerbsMaxSpaces << " || Metales: " << i_MetalsUsedSpaces << "/" << i_MetalsMaxSpaces << "\n\n";
			}
		}
	}


	return 0;
}