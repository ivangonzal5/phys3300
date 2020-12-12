#ifndef VOIDBODY_H
#define VOIDBODY_H

#include "voidMath.h"

struct vBody
{

	// Se declara el constructor del struct, esta constructor no acepta argumentos.
	vBody();

	// Se declaran variables de tipo float los cual contendran la informacion de la masa, y la masa inversa del body.
	float mass;
	float invMass;

	// Se declara un vector2D la cual nos permitira saber la posicion (x,y) del objeto. Importante para saber su ubicacion en un sistema de coordenadas.
	vec2D position;

	// Se declara un vector2D de velocidad la cual sera modificada dependiendo de la aceleraciones o fuerzas del mundo o contenidas en el objeto.
	vec2D velocity;

	// Se declara un vector2D la cual contiene la sumatoria de las fuerzas que actuan sobre el objeto o cuerpo.
	vec2D force;
	
	// Protipo de la funcion addForce, la cual nos permite modificar y aplicar fuerzas en el objeto.
	void addForce(const vec2D& f);

	// Prototipo de la funcion que nos permite especificar la masa del cuerpo.
	void setMass(const float &m);

	// Prototipo de la funcion la cual nos podra imprimir en la consola la informacion actual del cuerpo, posicion, velocidad, etc.
	void displayBodyInfo();
};

#endif /* VOIDBODY_H */