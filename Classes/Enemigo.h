#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "cocos2d.h"


USING_NS_CC;

class Enemigo : public cocos2d::Layer
{
public:
	
	virtual bool init();
	CREATE_FUNC(Enemigo);

	void setTipo(char* tipo);
	void setImagen(Sprite *imagen);
	void setDerecha(bool derecha);
	Vec2 getPos();
	void mover();

	Sprite *imagen;
	char* tipo;
	bool derecha;
	Vec2 pos;
	int velocidad;
};

#endif