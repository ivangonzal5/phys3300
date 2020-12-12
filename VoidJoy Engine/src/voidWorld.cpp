#include "voidWorld.h"


//La funcion setGravity nos permite modificar la variable gravity declarada en voidWorld.h
//Se le puede pasar por argumento una referencia a un vector2D como constante, de esta manera se trabaja con la variable original que se pasa y se evita que sea modificada.
//Gravity sera luego utilizado en la funcion Step para simular la gravedad (afectando velocidad y posicion de los cuerpos).
void voidWorld::setGravity(const vec2D& g)
{
	gravity = g;
}


// addBody es la funcion que permite agregar objetos(cuerpos) a un vector(lista)[std::vector<vBody*> bodies;] definido en voidWorld.h
//En su argumento se puede pasar un puntero(direccion de la memoria) de algun objeto de tipo vBody.
//De esta forma se podra iterar luego en la funcion Step(float dt) de manera mas sencilla con un 'for' y proceder a la simulacion.
void voidWorld::addBody(vBody* b)
{
	bodies.push_back(b);
}


//La funcion Step es la que se encarga de actualizar cada frame(update) la velocidad y la posicion de los cuerpos (Se encarga de la simulacion). 
//En su interior contiene 2 'for' que iteran sobre cada uno de los objetos añadidos en la lista usando la funcion addBody, y de esta manera accede a sus propiedades
//de los vectores2D de velocidad y posicion.
//Esta funcion en su argumento se le pasa el deltatime, o tiempo del frame. Para luego tomarlo en consideracion en los calculos y evitar que la simulacion sea dependiente del frame.
//Se recurre al metodo de Euler para realizar los calculos.
void voidWorld::Step(float dt)
{
	//El primer 'for' itera dentro del vector bodies, de 0 a su tamaño total, actualizando el vector2D velocity en 'x' y 'y' de cada elemento contenido.
	//La velocidad es igual a la velocidad anterior mas la aceleracion multiplicado por deltatime.
	//Para calcular la aceleracion se utiliza la formula F=m*a, de la cual al despejar la aceleracion queda a = F/m, lo cual se puede tambien expresar como a = F * 1/m (invMass)
	//Las fuerzas a calcular son las que esten registradas en el cuerpo mas la fuerza de gravedad.
	for (int counter = 0; counter < bodies.size(); counter++) {
		bodies[counter]->velocity.x += (gravity.x + bodies[counter]->force.x * bodies[counter]->invMass) * dt;
		bodies[counter]->velocity.y += (gravity.y + bodies[counter]->force.y * bodies[counter]->invMass) * dt;
	}

	//El segundo 'for' itera dentro del vector bodies, de 0 a su tamaño total, actualizando el vector2D position en 'x' y 'y' de cada elemento contenido.
	//La nueva posicion es igual a la posicion anterior mas la velocidad multiplicado por el deltatime.
	for (int counter = 0; counter < bodies.size(); counter++) {
		bodies[counter]->position.x += bodies[counter]->velocity.x * dt;
		bodies[counter]->position.y += bodies[counter]->velocity.y * dt;

		bodies[counter]->force.setZero();
	}
}
