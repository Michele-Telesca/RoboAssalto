#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "game.h"
#include "gameMap.h"
#include "player.h"
#include "villain.h"

/* classe Update qui vengono gestiti tutti
gli aggiornamenti relativi allo stato degli 
oggetti in game*/

class update {
public:

	update() {}

	bool collideFromRight = false;
	bool collideFromLeft = false;
	bool collideFromUp = false;
	bool collideFromDown = false;

	bool playerCollideFromRight(player* p, float obstacle_x, float obstacle_z, float offset, float epsilon);
	bool playerCollideFromLeft(player* p, float obstacle_x, float obstacle_z, float offset, float epsilon);
	bool playerCollideFromUp(player* p, float obstacle_x, float obstacle_z, float offset, float epsilon);
	bool playerCollideFromDown(player* p, float obstacle_x, float obstacle_z, float offset, float epsilon);

	void moveRight(player* p, vector <villain*> botList);
	void moveLeft(player* p, vector <villain*> botList);
	void moveUp(player* p, vector <villain*> botList);
	void moveDown(player* p, vector <villain*> botList);

	void moveSingleBot(villain* bot, player* p);
	void moveAllBots(vector <villain*> botList, player* p);
	bool botCollideVSPlayer(villain* bot, player* p);

};

											                                   	
bool update::playerCollideFromRight(player* p, float obstacle_x, float obstacle_z, float offset, float epsilon) { //offset: scostamento tra il centro della mattonella e il punto di collisione //epsilon: tolleranza di errore nel confronto tra coordinate
	if (isEqual(p->getX(), obstacle_x - (offset + MOVE_STEP), epsilon) && (p->getZ() >= (obstacle_z) -(TILE_DIM / 2) && p->getZ() <= (obstacle_z) +(TILE_DIM / 2)) ) {
		return true;
	}
	return false;
}

bool update::playerCollideFromLeft(player* p, float obstacle_x, float obstacle_z, float offset, float epsilon) {
	if (isEqual(p->getX(), obstacle_x + (offset + MOVE_STEP), epsilon) && (p->getZ() >= (obstacle_z)- (TILE_DIM / 2) && p->getZ() <= (obstacle_z) + (TILE_DIM / 2)) ) {
		return true;
	}
	return false;
}

bool update::playerCollideFromUp(player* p, float obstacle_x, float obstacle_z, float offset, float epsilon) {
	if ((p->getX() >= (obstacle_x) - (TILE_DIM / 2) && p->getX() <= (obstacle_x) + (TILE_DIM / 2)) && isEqual(p->getZ(), obstacle_z + (offset + MOVE_STEP), epsilon)) {
		return true;
	}
	return false;
}

bool update::playerCollideFromDown(player* p, float obstacle_x, float obstacle_z, float offset, float epsilon) {
	if ((p->getX() >= (obstacle_x) -(TILE_DIM / 2) && p->getX() <= (obstacle_x) + (TILE_DIM / 2)) && isEqual(p->getZ(), obstacle_z - (offset + MOVE_STEP), epsilon)) {
		return true;
	}
	return false;
}

void update::moveRight(player* p, vector <villain*> botList) {
	bool ostacolo = false;
	for (int i = 0; i < mapObjectsCoord.size(); i++) {
		float x_obj = (float)mapObjectsCoord[i].x;
		float z_obj = (float)mapObjectsCoord[i].y;
		if(playerCollideFromRight(p, x_obj, z_obj, (TILE_DIM / 2), EPSILON_1)){
			ostacolo = true;
			exit;
		}
	}
	for (int i = 0; i < botList.size(); i++) {
		if(playerCollideFromRight(p, botList[i]->getX(), botList[i]->getZ(), (TILE_DIM / 4), EPSILON_3)){
			ostacolo = true;
			exit;
		}
	}
	if (ostacolo == true) {
		p->setX(p->getX());
	}
	else {
		p->setX(p->getX() + MOVE_STEP);
	}
}

void update::moveLeft(player* p, vector <villain*> botList) {
	bool ostacolo = false;
	for (int i = 0; i < mapObjectsCoord.size(); i++) {
		float x_obj = (float)mapObjectsCoord[i].x;
		float z_obj = (float)mapObjectsCoord[i].y;
		if (playerCollideFromLeft(p, x_obj, z_obj, (TILE_DIM / 2), EPSILON_1)) {
			ostacolo = true;
			exit;
		}
	}
	for (int i = 0; i < botList.size(); i++) {
		if (playerCollideFromLeft(p, botList[i]->getX(), botList[i]->getZ(), (TILE_DIM / 4), EPSILON_3)) {
			ostacolo = true;
			exit;
		}
	}
	if (ostacolo == true) {
		p->setX(p->getX());
	}
	else {
		p->setX(p->getX() - MOVE_STEP);
	}
}

void update::moveUp(player* p, vector <villain*> botList) {
	bool ostacolo = false;
	for (int i = 0; i < mapObjectsCoord.size(); i++) {
		float x_obj = mapObjectsCoord[i].x;
		float z_obj = mapObjectsCoord[i].y;
		if (playerCollideFromUp(p, x_obj, z_obj, (TILE_DIM / 2), EPSILON_1)) {
			ostacolo = true;
			exit;
		}
	}
	for (int i = 0; i < botList.size(); i++) {
		if (playerCollideFromUp(p, botList[i]->getX(), botList[i]->getZ(), (TILE_DIM / 4), EPSILON_3)) {
			ostacolo = true;
			exit;
		}
	}
	if (ostacolo == true) {
		p->setZ(p->getZ());
	}
	else {
		p->setZ(p->getZ() - MOVE_STEP);
	}
}

void update::moveDown(player* p, vector <villain*> botList) {
	bool ostacolo = false;
	for (int i = 0; i < mapObjectsCoord.size(); i++) {
		float x_obj = mapObjectsCoord[i].x;
		float z_obj = mapObjectsCoord[i].y;
		if (playerCollideFromDown(p, x_obj, z_obj, (TILE_DIM / 2), EPSILON_1)) {
			ostacolo = true;
			exit;
		}
	}
	for (int i = 0; i < botList.size(); i++) {
		if (playerCollideFromDown(p, botList[i]->getX(), botList[i]->getZ(), (TILE_DIM / 4), EPSILON_3)) {
			ostacolo = true;
			exit;
		}
	}
	if (ostacolo == true) {
		p->setZ(p->getZ());
	}
	else {
		p->setZ(p->getZ() + MOVE_STEP);
	}
}



void update::moveAllBots(vector <villain*> botList, player* p) {
	if (botList.size() >= 1) {
		for (int i = 0; i < botList.size(); i++) {
			moveSingleBot(botList[i], p);
		}
	}
}

bool update::botCollideVSPlayer(villain* bot, player* p) {
	if ((bot->getX() >= p->getX() - TILE_DIM  && bot->getX() <= p->getX() + TILE_DIM) && (bot->getZ() >= p->getZ() - TILE_DIM && bot->getZ() <= p->getZ() + TILE_DIM)) {
		return true;
	}
	else {
		return false;
	}
}

void update::moveSingleBot(villain* bot, player* p) {

	int path_nextStep = bot->getPath_currentStep() + 1;

	//se il bot non è arrivato alla fine del suo path
	if (path_nextStep <= bot->getPath()->getPath_EndPath()) {

		//se il nextStep sia maggiore del currentStep
		if (path_nextStep > bot->getPath_currentStep()) {
			float newCoord_x = bot->getPath()->getPath_map()[path_nextStep].x;
			float newCoord_z = bot->getPath()->getPath_map()[path_nextStep].y; //coordinata z
			
			//Se il bot NON collide col player
			if (!botCollideVSPlayer(bot, p)) { 
				villain_walking = true;

				if (isEqual(bot->getZ(), newCoord_z, EPSILON_2)) {
					if (newCoord_x > bot->getX()) {
						bot->setX(bot->getX() + BOT_MOVE_STEP); //muovi a destra
					}
					else if (newCoord_x < bot->getX()) {
						bot->setX(bot->getX() - BOT_MOVE_STEP); //muovi a sinistra
					}
				}

				else if (isEqual(bot->getX(), newCoord_x, EPSILON_2)) {
					if (newCoord_z > bot->getZ()) {
						bot->setZ(bot->getZ() + BOT_MOVE_STEP); //muovi in basso
					}
					else if (newCoord_z < bot->getZ()) {
						bot->setZ(bot->getZ() - BOT_MOVE_STEP); //muovi in alto
					}
				}

				//Se le coordinate del bot (path_currentStep) hanno raggunto il nextStep
				if (isEqual(bot->getX(), newCoord_x, EPSILON_2) && isEqual(bot->getZ(), newCoord_z, EPSILON_2)) {
					bot->path_currentStep++;
				}
			}
			else {
				villain_walking = false;
				//SE IL BOT COLLIDE NON AVANZA
			}
		}
	}
	else {
		villain_walking = false;
		//SE IL BOT è ARRIVATO ALLA FINE DEL PATH NON VANZA
	}

}

