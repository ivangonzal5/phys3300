// Importamos las librerías necesarias para el programa. 
#include<iostream>
#include<vector>
#include<string>
#include<ctime>

// Incluimos el namespace std. 
using namespace std;

//Declaramos las funciones que usaremos en este programa. 
void generateInventory(int maxGen, vector<string>& randomInventory);
bool uniqueCrystalVerification(vector<string> itemList);
void openInventory(vector<string> &inventory);
void opaqueCraftMenu(vector<string> &inventory);
bool createOpaque(string rawCrystal, vector<string> &inventory);
void replace(string rawCrystal, string opaqueCrystal, vector<string> &inventory);
void recoleccion(vector<string>& inventory);

//VARIABLE PARA SABER SI YA SE GENERO UN INVENTARIO DE RECOLECCION
bool RecoleccionGenerated = false;
//INVENTARIO DE RECOLECCION GLOBAL PARA QUE RECUERDE LOS ELEMENTOS AL SALIR DE LA FUNCION
vector<string> recInventory(5, "NA");

//LISTA DE ARTICULOS DESTRUIDOS PARA EVITAR QUE VUELVAN A APARECER
vector<string> destroyedCrystals;


//Escribimos el cuerpo de la función generateInventory().
//SE MODIFICO LA FUNCION PARA QUE ACEPTE POR ARGUMENTO EL NUMERO DE ELEMENTOS MAXIMOS Y EL NUMERO DE ELEMENTOS A GENERAR.
void generateInventory(int maxGen, vector<string> &randomInventory)
{

	//Declaramos un inventario (local).
	//vector<string> randomInventory(spaces, "NA");

	//Creamos un vector con todos los objetos posibles. 
	const vector<string> allItems = { "Crystallized Azure Dragon's Tears", "Crystallized Exiled Heretic's Bone", "Crystallized Great Feline's Ash", "Fishermen's Plate", "Iron Plate" };

	//Definimos las variables para el uso del rand().
	int randomItemPos;
	int min = 0;
	int max = allItems.size() - 1;

	//Definimos una variable que nos diga si hay un cristal presente en el inventario.
	bool containsCrystal = false;

	//Declaramos una variable booleana, "longBooleanExpression". Para el control de cristales únicos. 
	bool longBooleanExpression;

	//Declaramos una variable booleana para el control de Fishermen's Plates.
	bool shortBooleanExpression;

	//Declaramos una variable contador para el ciclo while. 
	int counter = 0;

	//EL MAXIMO NUMERO QUE GENERARA LA FUNCION
	int maxGenerate = maxGen;

	//Creamos el ciclo que llena el inventario "random". 
	while (counter < maxGenerate) {

		//Generamos la posición "random".
		randomItemPos = rand() % (max - min + 1) + min;

		//Usando la función uniqueCrystalVerification, verificamos si hay un cristal en el inventario.
		containsCrystal = uniqueCrystalVerification(randomInventory);

		//Si hay el item random escogido es un cristal y HAY un cristal presente en el inventario, entonces esta expresión tomará el valor de true. 
		longBooleanExpression = ((allItems[randomItemPos] == "Crystallized Azure Dragon's Tears") || (allItems[randomItemPos] == "Crystallized Exiled Heretic's Bone") || (allItems[randomItemPos] == "Crystallized Great Feline's Ash")) && containsCrystal;

		//Si hay tres o más Fisherme's Plate en el inventario Y el item random es un Fisherme's Plate, esta variable tomará el valor de true. 
		shortBooleanExpression = (count(randomInventory.begin(), randomInventory.end(), "Fishermen's Plate") >= 3) && (allItems[randomItemPos] == "Fishermen's Plate");

		//Si no hay cristal, entonces se puede agregar cualquier cosa al inventario.
		if (!longBooleanExpression && !shortBooleanExpression) {
			randomInventory[counter] = allItems[randomItemPos];
			counter++; //El counter solo se aumenta cuando se haya agregado algo al inventario. 
		}
	}

	//system("CLS");
	cout << "INVENTORY GENERATED! \n\n" << endl;
	system("pause"); //Para esperar que el usuario presione alguna tecla. 

	//return randomInventory;

}

//Creamos una función que verifique si ya existe un cristal en la lista pasada como argumento. 
bool uniqueCrystalVerification(vector<string> itemList)
{

	//Declaramos una variable counter por motivos prácticos. 
	int counter = 0;

	//Declaramos una variable que "diga" si hay un cristal en la lista pasada. 
	bool isCrystalPresent = false;

	//Declaramos el "longBooleanExpression". 
	bool longBooleanExpression;

	//Creamos el ciclo que verifica si hay un cristal en el vector (en la lista).
	while ((counter < itemList.size()) && (!isCrystalPresent)) {

		//Verificamos si hay alguno de los cristales en la lista de objetos. 
		longBooleanExpression = (itemList[counter] == "Crystallized Azure Dragon's Tears") || (itemList[counter] == "Crystallized Exiled Heretic's Bone") || (itemList[counter] == "Crystallized Great Feline's Ash");

		//Si hay un cristal, entonces cambiamos el valor de "isCrystalPresent" a "true".
		if (longBooleanExpression) {
			isCrystalPresent = true;
		}

		//Aumentamos el counter (ya que el while no lo hace solo).
		counter++;

	}

	return isCrystalPresent;

}

//Creamos una función para ver el inventario y tirar objetos del mismo. 
void openInventory(vector<string> &inventory)
{

	//Declaramos la variable que mantiene el inventario abierto. 
	bool inventoryOpened = true;

	//Declaramos la variable para la entrada del usuario. 
	int userInput;

	//Creamos el ciclo que nos mantiene el inventario abierto. 
	while (inventoryOpened) {

		//Encabezado. 
		system("CLS");
		cout << "===============================================================" << endl;
		cout << "= = INVENTORY = =" << "\n" << endl;

		//Creamos el ciclo que itera sobre el inventario para imprimirlo (mostrarlo en pantalla).
		for (int counter = 0; counter < inventory.size(); counter++) {

			cout << counter + 1 << ". " << inventory[counter] << endl;

		}

		//Creamos la opción EXIT.
		cout << inventory.size() + 1 << ". " << "EXIT" << endl;
		cout << "===============================================================" << endl;

		//Esperamos la entrada del usuario.
		cout << "AWAITING USER INPUT:  "; cin >> userInput;

		//Si el usuario introduce el número de algún item, entonces borra el item usando erase(). De otra forma, cierra el inventory. 
		if (userInput <= inventory.size()) {
			//SI ES UN CRISTAL PREGUNTARA SI DESEA BORRAR.
			if (inventory[userInput-1] == "Crystallized Azure Dragon's Tears" || inventory[userInput-1] == "Crystallized Exiled Heretic's Bone" || inventory[userInput-1] == "Crystallized Great Feline's Ash" || inventory[userInput-1] == "Opaque Azure Dragon's Sapphire" || inventory[userInput-1] == "Opaque Humanity's Emerald" || inventory[userInput] == "Opaque Feline's Ruby")
			{
				string userConfirmation;
				cout << "Are you sure you want to destroy this crystal? You wont be able to gather this unique crystal anymore. [YES/NO]"; 
				cin >> userConfirmation;
				if (userConfirmation == "YES")
				{
					//ALMACENA LOS CRISTALES DESTRUIDOS
					destroyedCrystals.push_back(inventory[userInput - 1]);
					inventory.erase(inventory.begin() + userInput - 1);

					//AL BORRAR UN ARTICULO, AGREGARA EL ESPACIO VACIO PARA MANTENER LA CANTIDAD DE 20 ESPACIOS DEL INVENTARIO
					inventory.push_back("NA");
				}
				else
				{
					cout << "Operacion Cancelada.\n";
					system("pause");
				}
			}
			else
			{
				inventory.erase(inventory.begin() + userInput - 1);

				//AL BORRAR UN ARTICULO, AGREGARA EL ESPACIO VACIO PARA MANTENER LA CANTIDAD DE 20 ESPACIOS DEL INVENTARIO
				inventory.push_back("NA");
			}


		}
		else if (userInput == inventory.size() + 1) {

			inventoryOpened = false;

		}

	}

}

void opaqueCraftMenu(vector<string> &inventory)
{

	//Declaro la variable que mantiene el inventario abierto.
	bool craftMenuOpen = true;

	//Declaro la variable para la entrada del usuario
	int craftMenuOption;

	while (craftMenuOpen) {

		//Declaro dos variables que serán útiles para "craftear" los items. 
		string rawCrystal = "NA";
		string opaqueCrystal = "NA";

		//Declaro la variable para saber si se puede crear el cristal deseado. 
		bool isCrafted = false;

		//Creamos el UI.
		system("CLS");
		cout << "===============================================================" << endl;
		cout << "= = OPAQUE CRYSTAL CRAFTING = =" << "\n" << endl;
		cout << "1. Opaque Azure Dragon's Sapphire" << endl;
		cout << "2. Opaque Humanity's Emerald" << endl;
		cout << "3. Opaque Feline's Ruby" << endl;
		cout << "4. Exit" << endl;
		cout << "===============================================================" << endl;

		//Esperamos la entrada del usuario.
		cout << "AWAITING USER INPUT:  "; cin >> craftMenuOption;

		//Controlamos el menú usando un switch. 
		switch (craftMenuOption) {

		case 1:
			rawCrystal = "Crystallized Azure Dragon's Tears";
			opaqueCrystal = "Opaque Azure Dragon's Sapphire";
			isCrafted = createOpaque(rawCrystal, inventory);
			break;

		case 2:
			rawCrystal = "Crystallized Exiled Heretic's Bone";
			opaqueCrystal = "Opaque Humanity's Emerald";
			isCrafted = createOpaque(rawCrystal, inventory);
			break;

		case 3:
			rawCrystal = "Crystallized Great Feline's Ash";
			opaqueCrystal = "Opaque Feline's Ruby";
			isCrafted = createOpaque(rawCrystal, inventory);
			break;

		case 4:
			craftMenuOpen = false;
			break;

		default:
			system("CLS");
			break;
		}

		//Solo hará el cambio al inventario si se ha creado algo.
		if (isCrafted) {

			replace(rawCrystal, opaqueCrystal, inventory);
			cout << "Opaque crystal crafted!" << endl;
			system("pause");

		}

	}

}


//Función que se encarga de verificar si existe el cristal adecuado en el inventario.
bool createOpaque(string rawCrystal, vector<string> &inventory)
{

	bool isCrafted = false;

	if (find(inventory.begin(), inventory.end(), rawCrystal) != inventory.end()) {

		isCrafted = true;

	}

	return isCrafted;

}

//Función que se encarga de reemplazar el rawCrystal por el opaqueCrystal. 
void replace(string rawCrystal, string opaqueCrystal, vector<string> &inventory) {

	int counter = 0;
	bool replaced = false;

	while (counter < inventory.size() && !replaced) {

		if (inventory[counter] == rawCrystal)
		{

			inventory[counter] = opaqueCrystal;
			replaced = true;

		}

		counter++;

	}

}


void recoleccion(vector<string> &inventory)
{
	//MANTIENE ABIERTO EL MENU
	bool recoleccionMenuOpen = true;

	//INPUT DEL USUARIO
	int recoleccionMenuOption;

	//CUENTA LA CANTIDAD DE ESPACIOS LIBRES DEL INVENTARIO
	int naSpaces = count(inventory.begin(), inventory.end(), "NA");



	//BUSCA SI EXISTEN CRISTALES EN EL INVENTARIO
	bool crystalPresent = false;
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] == "Crystallized Azure Dragon's Tears" || inventory[i] == "Crystallized Exiled Heretic's Bone" || inventory[i] == "Crystallized Great Feline's Ash" || inventory[i] == "Opaque Azure Dragon's Sapphire" || inventory[i] == "Opaque Humanity's Emerald" || inventory[i] == "Opaque Feline's Ruby")
		{
			crystalPresent = true;
		}
	}

	//GENERA UNA UNICA VEZ UN INVENTARIO DE RECOLECCION
	if (!RecoleccionGenerated)
	{
		generateInventory(5, recInventory);
		RecoleccionGenerated = true;
	}

	//DESTRUYE CRISTAL SEGUN LA LISTA DE ELEMENTOS DESTRUIDOS
	if (destroyedCrystals.size() != 0)
	{
		for (int i = 0; i < recInventory.size(); i++)
		{
			for (int j = 0; j < destroyedCrystals.size(); j++)
			{
				if (recInventory[i] == destroyedCrystals[j])
				{
					//DESTRUYE CRISTALES QUE HEMOS ELIMINADO DEL INVENTARIO.
					recInventory.erase(recInventory.begin() + i);

					//AL BORRAR UN ARTICULO, AGREGARA EL ESPACIO VACIO PARA MANTENER LA CANTIDAD DE 5 ESPACIOS DEL INVENTARIO DE RECOLECCION.
					recInventory.push_back("NA");
				}
			}
		}
	}


	while (recoleccionMenuOpen) {

		//Creamos el UI.
		system("CLS");

		//HEADER NOS DA INFORMACION DE NUESTRO INVENTARIO.
		cout << "===============================================================" << endl;
		cout << "TIENES " << naSpaces << " ESPACIOS DISPONIBLES EN TU INVENTARIO." << "\n" << endl;
		if (crystalPresent)
		{
			cout << "TIENES UN CRISTAL EN EL INVENTARIO." << endl;
		}
		else
		{
			cout << "NO TIENES CRISTALES EN EL INVENTARIO." << endl;
		}
		cout << "===============================================================" << endl;

		//LISTA DEL MENU DE RECOLECCION
		cout << "= = RECOLECCION = =" << "\n" << endl;
		//Creamos el ciclo que itera sobre el inventario para imprimirlo (mostrarlo en pantalla).
		for (int counter = 0; counter < recInventory.size(); counter++) {

			cout << counter + 1 << ". " << recInventory[counter] << endl;

		}

		//Creamos la opción EXIT.
		cout << recInventory.size() + 1 << ". " << "EXIT" << endl;
		cout << "===============================================================" << endl;

		//OPCION PARA HACER REFILL A LA LISTA DE RECOLECCION
		cout << recInventory.size() + 2 << ". " << "REFILL LIST (DEV ONLY)" << endl;
		cout << "===============================================================" << endl;

		//ENTRADA DEL USUARIO
		cout << "AWAITING USER INPUT:  "; cin >> recoleccionMenuOption;


		//Si el usuario introduce el número de algún item, entonces borra el item usando erase() y LO PASA AL INVENTARIO DEL USUARIO.
		if (recoleccionMenuOption <= recInventory.size()) {
			//SI EL INVENTARIO ESTA LLENO NO PERMITE AGREGARLO
			if (naSpaces == 0)
			{
				system("CLS");
				cout << "EL INVENTARIO ESTA LLENO. NO SE PUEDE AGREGAR MAS ARTICULOS.\n";
				system("pause"); //Para esperar que el usuario presione alguna tecla. 
			}
			else
			{
				//VERIFICA SI EL ITEM DEL MENU DE RECOLECCION ES UN CRISTAL
				bool crystalItem = false;
				if (recInventory[recoleccionMenuOption - 1] == "Crystallized Azure Dragon's Tears" || recInventory[recoleccionMenuOption - 1] == "Crystallized Great Feline's Ash" || recInventory[recoleccionMenuOption - 1] == "Crystallized Exiled Heretic's Bone")
				{
					crystalItem = true;
				}
				//SI EXISTE UN CRISTAL EN EL INVENTARIO NO LO AGREGA
				if (crystalItem && crystalPresent)
				{
					system("CLS");
					cout << "NO PUEDES AGREGAR UN CRISTAL YA QUE TIENES UNO EN EL INVENTARIO.\n";
					system("pause"); //Para esperar que el usuario presione alguna tecla. 
				}
				else
				{
					//AGREGA AL INVENTARIO EL ARTICULO Y LO ELIMINA DEL MENU DE RECOLECCION.
					inventory[inventory.size() - naSpaces] = recInventory[recoleccionMenuOption - 1];
					recInventory.erase(recInventory.begin() + recoleccionMenuOption - 1);

					//AL BORRAR UN ARTICULO, AGREGARA EL ESPACIO VACIO PARA MANTENER LA CANTIDAD DE 5 ESPACIOS DEL INVENTARIO DE RECOLECCION.
					recInventory.push_back("NA");
					system("CLS");
					cout << "NUEVO ARTICULO EN EL INVENTARIO! \n\n" << endl;
					recoleccionMenuOpen = false;
					system("pause"); //Para esperar que el usuario presione alguna tecla. 
				}
			}
		}
		//CIERRA EL MENU DE RECOLECCION
		else  if (recoleccionMenuOption == recInventory.size() + 1)
		{
			recoleccionMenuOpen = false;
		}
		//CIERRA EL MENU Y LA PROXIMA VEZ HARA REFILL DE ITEMS.
		else if (recoleccionMenuOption == recInventory.size() + 2)
		{
			RecoleccionGenerated = false;
			recoleccionMenuOpen = false;
		}
	}
}

int main()
{
	/*
	ASIGNACION 2:

	TODAS LAS FUNCIONES FUERON ACTUALIZADAS PARA UTILIZAR EL INVENTARIO QUE SE GENERA EN EL MAIN *vector<string> inventory(20, "NA")* COMO REFERENCIA.
		>LAS FUNCIONES SON AHORA VOID YA QUE NO REGRESAN NINGUN DATO, UTILIZAN LA REFERENCIA PARA TRABAJAR SOBRE EL INVENTARIO ORIGINAL.
		>SE ACTUALIZARON LAS FUNCIONES PROTOTIPOS.
		>SE AGREGO & EN EL ARGUMENTO DE LAS FUNCIONES PARA PASAR COMO REFERENCIA.
		>SE ELIMINO LA IGUALDAD EN EL SWITCH CASE DEL MAIN, ASI SOLO LLAMANDO LA FUNCION Y NO IGUALANDO EL INVENTARIO AL VALOR QUE RETORNA LA FUNCION.

		>LA FUNCION QUE MAS CAMBIO FUE >> void generateInventory(int maxGen, vector<string>& randomInventory) << YA QUE EN SU ARGUMENTO SE LE PASA UN VALOR DE CUANTOS SLOTS DEBE GENERAR.
		>TODAS LAS DEMAS FUNCIONES TRABAJAN IGUALES.
	*/

	//RANDOM SEED.
	srand(time(0));

	//Creamos un vector para el inventario. TIENE CAPACIDAD PARA 20 ESPACIOS
	vector<string> inventory(20, "NA");

	//Creamos una variable bool para mantener el menú funcionando. 
	bool menuOpen = true;

	//Creamos la variable para la entrada del usuario. 
	int mainMenuOption;

	//Usamos un ciclo while para mantener el menú funcionando. 
	while (menuOpen) {

		//Este comando limpia la ventana de comandos. 
		system("CLS");

		//Creamos el "UI" para el menú.
		cout << "===============================================================" << endl;
		cout << "= = MAIN MENU = =" << "\n" << endl;
		cout << "1. INVENTORY GENERATOR (FOR DEVELOPERS)" << endl;
		cout << "2. OPEN INVENTORY" << endl;
		cout << "3. CREATE OPAQUE CRYSTAL" << endl;
		cout << "4. MENU DE RECOLECCION" << endl;
		cout << "5. EXIT GAME" << endl;
		cout << "===============================================================" << endl;

		//Leemos la entrada del usuario. 
		cout << "AWAITING USER INPUT:  "; cin >> mainMenuOption;

		//Usamos un switch() para manejar el menú con la entrada del usuario.
		switch (mainMenuOption) {

		case 1:
			generateInventory(7, inventory);
			break;

		case 2:
			openInventory(inventory);
			break;

		case 3:
			opaqueCraftMenu(inventory);
			break;

		case 4:
			//NUEVO ENTRADA PARA EL MENU DE RECOLECCION
			recoleccion(inventory);
			break;

		case 5:
			menuOpen = false;
			break;

		default:
			system("CLS");
			break;

		}


	}

	return 0;

}