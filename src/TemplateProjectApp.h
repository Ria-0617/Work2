#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder\Camera.h"
#include "cinder\gl\Light.h"
#include "cinder\gl\Material.h"
#include "cinder\ImageIo.h"
#include "cinder\gl\Texture.h"
#include "cinder\ObjLoader.h"

#include "JoyController.h"
#include "GameCamera.h"
#include "Player.h"
#include "Bullet.h"
#include "Boid.h"
#include "UI.h"

#include "Func.h"

#include <list>

class TemplateProjectApp : public ci::app::AppNative,JoyController {
	Player player;
	GameCamera camera1 = GameCamera(player.GetPos());
	UI uiCamera;
	std::list<Boid> boids;
	std::list<Bullet> bullets;

	// template
	ci::Color color = ci::Color(0.f, 0.f, 0.f);

	int enemyMaxNum = 100;
	int shotTime = 0;

public:
	void prepareSettings(Settings* settings);
	void setup();
	void shutdown();
	void update();
	void draw();
};
