#include "PlataformasScene.h"
#include "Enemigo.h"

USING_NS_CC;

Scene* PlataformasScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = PlataformasScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

bool PlataformasScene::init()
{
	Size tamañoPantalla = Director::getInstance()->getVisibleSize();
	
	if ( !Layer::init() )
        return false;

	//Creamos la princesa

	princesa = Sprite::create("provisional/princesa.png");
	princesa->setScaleX(0.1f);
	princesa->setScaleY(0.1f);
	princesa->setPosition(Point(tamañoPantalla.width / 2, 55));
	addChild(princesa, 1);
	
	this->scheduleUpdate();

	//Asignamos fisicas a la princesa

	auto cuerpo = PhysicsBody::createCircle(princesa->getBoundingBox().size.width / 2);
	cuerpo->setContactTestBitmask(true);
	cuerpo->setDynamic(true);

	princesa->setPhysicsBody(cuerpo);

	//Creamos enemigo

	Enemigo *enemigoBasico = Enemigo::create();
	Sprite *imagenEn = Sprite::create("provisional/enemigo.png");
	imagenEn->setScaleX(0.15f);
	imagenEn->setScaleY(0.15f);
	imagenEn->setPosition(Point(imagenEn->getContentSize().width / 2 * imagenEn->getScaleX(), 40));
	enemigoBasico->setImagen(imagenEn);
	enemigoBasico->setTipo("basico");

	addChild(enemigoBasico, 1);

	//Teclas

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(PlataformasScene::teclaPresionada, this);
	listener->onKeyReleased = CC_CALLBACK_2(PlataformasScene::teclaLevantada, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);	teclaPresioanda = EventKeyboard::KeyCode::KEY_NONE;
	prinMovL = false;
	prinMovR = false;
	prinSalto = false;
	prinPos.x = princesa->getPositionX();
	prinPos.y = princesa->getPositionY();


    return true;
}

void PlataformasScene::teclaPresionada(EventKeyboard::KeyCode idTecla, Event *evento){
	teclaPresioanda = idTecla;

	switch (teclaPresioanda) {

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		prinPos.x -= VELOCIDADPRIN;
		prinMovL = true;
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		prinPos.x += VELOCIDADPRIN;
		prinMovR = true;
		break;
	
	case EventKeyboard::KeyCode::KEY_SPACE:
		if (prinSalto == false){
			auto cuerpo = PhysicsBody::createCircle(princesa->getBoundingBox().size.width / 2);
			cuerpo->applyImpulse(Vec2(0, FSALTOPRINCESA));
			princesa->setPhysicsBody(cuerpo);
			prinSalto = true;
		}
		break;
	}
}

void PlataformasScene::teclaLevantada(EventKeyboard::KeyCode idTecla, Event *evento){
	if (teclaPresioanda == idTecla) {
		teclaPresioanda = EventKeyboard::KeyCode::KEY_NONE;
		if (prinMovL)
			prinMovL = false;
		if (prinMovR)
			prinMovR = false;
	}
	/*if (idTecla == EventKeyboard::KeyCode::KEY_SPACE)
	{
		auto cuerpo = PhysicsBody::createCircle(princesa->getBoundingBox().size.width / 2);
		cuerpo->applyImpulse(Vec2(0, FSALTOPRINCESA));
		princesa->setPhysicsBody(cuerpo);
		prinSalto = true;
	}*/
}

void PlataformasScene::update(float dt){
	
	Size tamañoPantalla = Director::getInstance()->getVisibleSize();

	//Movimiento enemigo
	if (enemigoBasico != NULL)
		enemigoBasico->mover();

	//Movimiento en X
	if (prinMovL)
		prinPos.x -= VELOCIDADPRIN;
	if (prinMovR)
		prinPos.x += VELOCIDADPRIN;

	if (prinPos.x > princesa->getContentSize().width / 2 * princesa->getScaleX() 
		&& prinPos.x < tamañoPantalla.width - princesa->getContentSize().width / 2 * princesa->getScaleX())
		princesa->setPositionX(prinPos.x);
	else
		prinPos.x = princesa->getPositionX();
		
	//Plataforma princesa
	if (princesa->getPositionY() < 55){
		auto cuerpo = PhysicsBody::createCircle(princesa->getBoundingBox().size.width / 2);
		cuerpo->applyForce(Vec2(0, 0));
		princesa->setPhysicsBody(cuerpo);
		princesa->setPositionY(55);
		prinSalto = false;
	}
}

void PlataformasScene::setPhysicsWorld(PhysicsWorld *mundo) {
	fMundo = mundo;
	fMundo->setGravity(Vec2(0, FGRAVEDAD));
}

void PlataformasScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
