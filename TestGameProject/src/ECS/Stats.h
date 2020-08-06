#pragma once

#include "ECS.h"
#include "../Game.h"

class Stats : public Component
{
public:
	static int health;
	static int ammo;
	static int score;
	Stats()
	{
		health = 0;
		ammo = 0;
		score = 0;
	}
	Stats(int H, int A) 
	{
		health = H;
		ammo = A;
		score = 0;

	}


	Stats(int S)
	{
		score = S;
		
	}

	/*void init() override
	{
		&entity->addComponent<Stats>();
	}
	void update() override
	{
		&entity->getComponent<Stats>().health;
		&entity->getComponent<Stats>().ammo;
		&entity->getComponent<Stats>().score;
	}*/
	/*
	static void Damage()
	{
		
		&entity->getComponent<Stats>().health -= 1;
		
	}
	static void Shoot()
	{
		&entity->getComponent<Stats>().ammo -= 1;
		&entity->getComponent<ProjectileComponent>();

	}
	static void Score()
	{
		&entity->getComponent<Stats>().score += 1;
		&entity->getComponent<Stats>().ammo += 1;
	}
	*/
};