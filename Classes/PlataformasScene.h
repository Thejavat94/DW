#ifndef PLATAFORMAS_SCENE_H
#define PLATAFORMAS_SCENE_H

#include "cocos2d.h"
#include "Enemigo.h"

USING_NS_CC;

const int VELOCIDADPRIN = 3;
const int FSALTOPRINCESA = 30000;
const int FGRAVEDAD = -800;

class PlataformasScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	
	Sprite *princesa;
	Enemigo *enemigoBasico;

	EventKeyboard::KeyCode teclaPresioanda;
	bool prinMovL;
	bool prinMovR;
	bool prinSalto;
	Vec2 prinPos;

	PhysicsWorld *fMundo;

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	//teclas
	void teclaPresionada(EventKeyboard::KeyCode idTecla, Event *evento);
	void teclaLevantada(EventKeyboard::KeyCode idTecla, Event *evento);
	
	void update(float dt);

	//Fisicas

	void setPhysicsWorld(PhysicsWorld *mundo);
	bool onContactBegin(PhysicsContact &contacto);
    
    // implement the "static create()" method manually
	CREATE_FUNC(PlataformasScene);
};

#endif
