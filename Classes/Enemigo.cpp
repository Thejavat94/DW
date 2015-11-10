#include "Enemigo.h"

USING_NS_CC;

bool Enemigo::init(){

	if (!Layer::init())
		return false;
	
	tipo = "ninguno";
	derecha = true;
	return true;
}

void Enemigo::setTipo(char* Tipo){
	tipo = Tipo;
	if (tipo == "basico") {
		velocidad = 5;
	}
}

void Enemigo::setImagen(Sprite *Imagen){
	imagen = Imagen;
	pos.x = imagen->getPositionX();
	pos.y = imagen->getPositionY();

}

void Enemigo::setDerecha(bool Derecha){
	derecha = Derecha;
}

Vec2 Enemigo::getPos(){
	return pos;
}

void Enemigo::mover(){

	if (tipo == "basico")
	{
		if (derecha)
			imagen->setPositionX(imagen->getPositionX() + velocidad);
		else
			imagen->setPositionX(imagen->getPositionX() - velocidad);
		pos.x = imagen->getPositionX();
	}
}

