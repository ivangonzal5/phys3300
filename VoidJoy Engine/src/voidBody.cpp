#include "voidBody.h"


//Este constructor nos permite instanciar un cuerpo colocando todas sus propiedades en valor 0, y su masa en 1.
vBody::vBody()
{
	position.setZero();

	velocity.setZero();

	force.setZero();

	mass = 1.0f;
	invMass = 1.0f; /* 1/mass */
}

//La funcion addForce permite pasar un vector2D como referencia y de forma constante para evitar su modificacion y añadir este valor a la variable de force (vec2D).
//La fuerza se utilizara en conjunto a la gravedad del world para calcular la velocidad del cuerpo.
void vBody::addForce(const vec2D& f)
{
	force += f;
}

//Esta funcion nos permite pasar una variable de tipo float en referencia y constante para evitar ser modificada de la masa del objeto.
//La masa es importante dentro del calculo de la fuerza y de la aceleracion.
//Se calcula el inverso de la masa para simplificar el calculo futuro de la aceleracion del objeto.
void vBody::setMass(const float& m)
{
	mass = m;
	invMass = 1 / m;
}


//Esta funcion nos permite imprimir en pantalla la informacion de dicho cuerpo.
//Asi podremos conocer el valor de las propiedades de velocidad, posicion, masa y masa inversa.
void vBody::displayBodyInfo()
{
	std::cout << "m: " << mass << std::endl;
	std::cout << "Inv mass: " << invMass << std::endl;
	std::cout << "pos: ", position.displayVector();
	std::cout << "vel: ", velocity.displayVector();
	std::cout << "\n" << std::endl;
}