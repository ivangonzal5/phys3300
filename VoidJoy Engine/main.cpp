#include "voidMath.h"
#include "voidWorld.h"

int main()
{
	//Se instancia un objeto de la clase voidWorld con el nombre de firstSimulation. 
	//voidWorld tiene un constructor que permite pasarle por argumento un vector2D la cual especifica la gravedad a usar en el mundo creado.
	voidWorld firstSimulation(vec2D(0.0f, 9.81f)); 


	//Se instancian 2 objetos de la clase vBody a las cuales se les llama firstBody y secondBody.
	vBody firstBody;
	vBody secondBody;


	//Se llama dos veces una funcion del objeto firstSimulation(De la clase voidWorld), en la cual se le pasa por argumento una referencia usando '&' de los
	//objetos antes creados de la clase vBody llamados firstBody y secondBody.
	firstSimulation.addBody(&firstBody);
	firstSimulation.addBody(&secondBody);


	//Se declara una variable de tipo float llamada frameTime con el valor 0.5f, frameTime es el tiempo en el que se renderiza o se procesa un frame o cuadro.
	//Por lo que el valor 0.5f representa la mitad de un segundo.
	float frameTime = 0.5f;


	//Se declara una variable contador la cual nos permitira hacer 10 iteraciones con la estructura de control 'While'.
	//Se hace de esta forma para generar 10 cuadros de la simulacion.
	int counter = 0;
	while (counter < 10)
	{
		//La clase vBody contiene una funcion la cual permite imprimir en la consola la informacion del cuerpo como la masa, velocidad, posicion.
		firstBody.displayBodyInfo();
		secondBody.displayBodyInfo();


		//Se llama a la funcion Step pasandole el frameTime que hemos especificado para calcular la simulacion de los cuerpos contenidos en el voidWorld.
		//Esta funcion actualizara su velocidad y su posicion en cada iteracion.
		firstSimulation.Step(frameTime);

		//Se aumenta el contador para uso del while.
		counter++;
	}

	return 0;
}