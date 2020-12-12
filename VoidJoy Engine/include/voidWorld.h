#ifndef VOIDWORLD_H
#define VOIDWORLD_H

#include "voidBody.h"
#include <vector>

struct voidWorld
{
	//Se definen 2 constructores, uno sin argumentos y uno donde se puede definir la gravedad del mundo desde el momento en el que se instancia.
	voidWorld() {}
	voidWorld(vec2D gravity) : gravity(gravity) {}

	// Se declara una variable de gravedad la cual sera un vector2D y simula la fuerza de atraccion de un cuerpo, se tomara en consideracion para los calculos de velocidad.
	vec2D gravity;

	// Se declara un vector(lista) la cual contendra todo los cuerpos en las que la funcion Step actuara utilizando un iterador (For).
	std::vector<vBody*> bodies;

	// Prototipo de la funcion que nos permitira cambiar la gravedad del world.
	void setGravity(const vec2D &g);

	// Prototipo de la funcion que nos permitira añadir cuerpos(objetos) al vector(lista) bodies.
	void addBody(vBody* b);

	// Prototipo de la funcion que nos permite simular, utilizando el metodo de euler.
	void Step(float dt); //Es importante decir que la simulacion sera mas exacta mientras el frametime sea mucho mas bajo.
};

#endif /* VOIDWORLD_H */
