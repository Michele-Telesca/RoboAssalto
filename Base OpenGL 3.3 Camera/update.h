#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "game.h"
#include "gameMap.h"
#include "player.h"
#include "villain.h"
#include "playerShot.h"

/* classe Update qui vengono gestiti tutti
gli aggiornamenti relativi allo stato degli 
oggetti in game*/

class update {
public:

	update() {}

	// ---- Movimento e collisioni del PLAYER ---- //
	void moveRight(player* p, vector <villain*> botList);
	void moveLeft(player* p, vector <villain*> botList);
	void moveUp(player* p, vector <villain*> botList);
	void moveDown(player* p, vector <villain*> botList);
	void calculateAnglePlayer(player* p); 

	bool playerCollideFromRight(player* p, float obstacle_x, float obstacle_z, float offset, float epsilon); 
	bool playerCollideFromLeft(player* p, float obstacle_x, float obstacle_z, float offset, float epsilon);
	bool playerCollideFromUp(player* p, float obstacle_x, float obstacle_z, float offset, float epsilon);
	bool playerCollideFromDown(player* p, float obstacle_x, float obstacle_z, float offset, float epsilon);

	// ---- BOT ---- //
	void updateBot(vector <villain*> botList, player* p, game* game);
	void moveBot(villain* bot, player* p);
	void rotateBot(villain* bot); //rotazione del bot
	void botCollideVSPlayer(villain* bot, player* p); //collisione del bot
	void killBOT(vector <villain*> botList, game* game);

	// ---- Movimento e collisioni degli SHOT ---- //
	void updateShot(vector <playerShot*> listShot, vector <villain*> botList);
	void shotHitBot(vector <playerShot*> listShot, villain* bot);

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

void update::updateBot(vector <villain*> botList, player* p, game* game) {
	if (botList.size() >= 1) { //se la lista di bot NON è VUOTA
		for (int i = 0; i < botList.size(); i++) {
			moveBot(botList[i], p);				  //movimento del singolo bot
			rotateBot(botList[i]);				  //effettua le rotazioni del singolo bot (in caso c'è un cambio di direzione)
			killBOT(botList, game);
		}
	}
}

void update::botCollideVSPlayer(villain* bot, player* p) {
	if ((bot->getX() >= p->getX() - TILE_DIM && bot->getX() <= p->getX() + TILE_DIM) && (bot->getZ() >= p->getZ() - TILE_DIM && bot->getZ() <= p->getZ() + TILE_DIM)) {
		//se il bot collide con il player NON AVANZA ma si gira verso il player e lo attacca
		bot->animation_botWalking = false; //setto il bool per l'animazione walk a false
		bot->animation_botAttacking = true; //setto il bool per l'animazione attack a true
		float new_rotationAngle = p->getAnglePlayer() - 180.0f;
		bot->setRotationAngle(new_rotationAngle);
		bot->isOnPath = false; //segnalo che il bot non è più ruotato correttamente secondo la sequenza del path
	}
	else {
		//se il bot NON collide con il player -> AVANZA 
		if (bot->animation_botWalking == false) {
			bot->animation_botWalking = true; //setto il bool per l'animazione walk a true
		}
		if (bot->animation_botAttacking == true) {
			bot->animation_botAttacking = false; //setto il bool per l'animazione attack a false
		}
	}
}


void update::rotateBot(villain* bot) {
	if (bot->rotationAngle != bot->angleToReach) { //se l'angolo di rotazione corrente è diverso dall'angolo di rotazione da raggiungere
		// IL BOT DEVE RUOTARE
		if (bot->sensoOrario == true) { 
			bot->rotationAngle = bot->rotationAngle - 15.0f;
		}
		else {
			bot->rotationAngle = bot->rotationAngle + 15.0f;
		}
	}
	else {
		//IL BOT NON DEVE RUOTARE
	}
}

void update::moveBot(villain* bot, player* p) {

	int path_nextStep = bot->getPath_currentStep() + 1;

	//se il bot non è arrivato alla fine del suo path
	if (path_nextStep <= bot->getPath()->getPath_EndPath()) {

		//se il nextStep sia maggiore del currentStep
		if (path_nextStep > bot->getPath_currentStep()) {
			float newCoord_x = bot->getPath()->getPath_map()[path_nextStep].x;
			float newCoord_z = bot->getPath()->getPath_map()[path_nextStep].y; //coordinata z

			botCollideVSPlayer(bot, p); //setta il booleano dell' animazione attacco se collide con il player
			shotHitBot(p->listShot, bot); //setta il booleano dell' animazione hit se viene colpito e se muore setta il booleano dell'animazione dead

			//Se il bot NON collide col player, NON è hittato dal proiettile, NON è morto-> AVANZA
			if (bot->animation_botWalking && !bot->animation_botAttacking && !bot->animation_botHit && !bot->animation_botDead) {

				//Se la rotazione del bot non è corretta secondo il del path
				if (bot->isOnPath == false) {
					//Allora risetto la rotazione secondo il path 
					if (bot->old_direction == DIRECTION_RIGHT) {
						bot->rotationAngle = 90.0f;
					}
					else if (bot->old_direction == DIRECTION_LEFT) {
						bot->rotationAngle = 270.0f;
					}
					else if (bot->old_direction == DIRECTION_UP) {
						bot->rotationAngle = 180.0f;
					}
					else if (bot->old_direction == DIRECTION_DOWN) {
						bot->rotationAngle = 0.0f;
					}
					bot->isOnPath = true; //Segnalo che ora la rotazione del bot è corretta secondo il path
				}

				if (isEqual(bot->getZ(), newCoord_z, EPSILON_2)) { //mi muovo lungo l'asse x

					if (newCoord_x > bot->getX()) {                         //dovrò muovere a destra
						if (bot->old_direction == 2) {                          //se la vecchia direzione era verso il basso     
							bot->angleToReach = bot->rotationAngle + 90.0f;        //setto l'angolo di rotazione da raggiungere a +90
							bot->sensoOrario = false;					           //setto il senso di rotazione ANTIORARIO
						}
						else if (bot->old_direction == 3) {                     //se la vecchia direzione era verso l'alto
							bot->rotationAngle = bot->rotationAngle - 90.0f;       //setto l'angolo di rotazione da raggiungere a -90
							bot->sensoOrario = true;						       //setto il senso di rotazione ORARIO
						}
						bot->setX(bot->getX() + BOT_MOVE_STEP);                 //muovi verso destra
						bot->old_direction = 0;
					}

					else if (newCoord_x < bot->getX()) {                    //dovrò muovere a sinistra
						if (bot->old_direction == 2) {                          //se la vecchia direzione era verso il basso
							bot->angleToReach = bot->rotationAngle - 90.0f;        //setto l'angolo di rotazioe da raggiungere a -90
							bot->sensoOrario = true;                               //setto il senso di rotazione ORARIO
						}
						else if (bot->old_direction == 3) {                     //se la vecchia direzione era verso l'alto
							bot->angleToReach = bot->rotationAngle + 90.0f;        //setto l'angolo di rotazione da raggiungere a +90
							bot->sensoOrario = false;							   //setto il senso di rotazione ANTIORARIO
						}
						bot->setX(bot->getX() - BOT_MOVE_STEP);                 //muovi verso sinistra
						bot->old_direction = 1;
					}
				}

				else if (isEqual(bot->getX(), newCoord_x, EPSILON_2)) { //mi muovo lungo l'asse z

					if (newCoord_z > bot->getZ()) {                         //dovrò muovere in basso
						if (bot->old_direction == 0) {                          //se la vecchia direzione era verso destra
							bot->angleToReach = bot->rotationAngle - 90.0f;        //setto l'angolo di rotazione da raggiungere a -90
							bot->sensoOrario = true;                               //setto il senso di rotazione ORARIO
						}
						else if (bot->old_direction == 1) {                     //se la vecchia direzione era verso sinistra
							bot->angleToReach = bot->rotationAngle + 90.0f;        //setto l'angolo di rotazione da raggiungere a +90
							bot->sensoOrario = false;                              //setto il senso di rotazione ANTIORARIO
						}
						bot->setZ(bot->getZ() + BOT_MOVE_STEP);                 //muovi verso il basso
						bot->old_direction = 2;
					}

					else if (newCoord_z < bot->getZ()) {                    //dovrò muovere in alto
						if (bot->old_direction == 0) {                          //se la vecchia direzione era verso destra
							bot->angleToReach = bot->rotationAngle + 90.0f;        //setto l'angolo di rotazione da raggiungere a +90
							bot->sensoOrario = false;							   //setto il senso di rotazione ANTIORARIO
						}
						else if (bot->old_direction == 0) {					    //se la vecchia direzione era verso sinistra
							bot->angleToReach = bot->rotationAngle - 90.0f;        //setto l'angolo di rotazione da raggiungere a -90
							bot->sensoOrario = true;							   //setto il senso di rotazione ORARIO
						}
						bot->setZ(bot->getZ() - BOT_MOVE_STEP);                 //muovo verso l'alto
						bot->old_direction = 3;
					}
				}
				//Se le coordinate del bot (path_currentStep) hanno raggunto il nextStep
				if (isEqual(bot->getX(), newCoord_x, EPSILON_2) && isEqual(bot->getZ(), newCoord_z, EPSILON_2)) {
					bot->path_currentStep++; //incremento lo step
				}
			}
			else {
				//In tutti gli altri casi: quando il bot NON cammina, ma è hittato, attacca o muore -> NON AVANZA
				
			}
		}
	}
	else {
		//se il bot è arrivato a fine path NON AVANZA ma attacca il tesoro
		bot->animation_botWalking = false;
		bot->animation_botAttacking = true;
		shotHitBot(p->listShot, bot);           //setta il booleano dell' animazione hit se viene colpito e se muore setta il booleano dell'animazione dead
		bot->angleToReach = bot->rotationAngle; //evita il bug della rotazione infinita XD (es bot path3)
	}

}


void update::calculateAnglePlayer(player* p) {

	float anglePlayerR = 0.0f;
	float anglePlayer = p->getAnglePlayer();

	if (muoviDx == true) {
		anglePlayerR = 90.0f;
		if (muoviSu == true) {
			anglePlayerR = 135.0f;
		}
		if (muoviGiu == true) {
			anglePlayerR = 45.0f;
		}
	}
	if (muoviSx == true) {
		anglePlayerR = 270.0f;
		if (muoviSu == true) {
			anglePlayerR = 225.0f;
		}
		if (muoviGiu == true) {
			anglePlayerR = 315.0f;
		}
	}

	if (muoviGiu == true) {
		if (muoviDx == false && muoviSx == false) {
			anglePlayerR = 0.0f;
		}
	}
	if (muoviSu == true) {
		if (muoviDx == false && muoviSx == false) {
			anglePlayerR = 180.0;
		}
	}
	if (muoviDx == false && muoviSx == false && muoviSu == false && muoviGiu == false) {
		anglePlayerR = anglePlayer;
	}

	if (anglePlayer - anglePlayerR > 0.0f ) {
		if (anglePlayer - anglePlayerR < 180.0f) {
			anglePlayer = anglePlayer - 15.0f;
		}
		else {
			anglePlayer = anglePlayer + 15.0f;

		}
	}
	if (anglePlayer - anglePlayerR < 0.0f) {
		if (anglePlayer - anglePlayerR > -180.0f) {
			anglePlayer = anglePlayer + 15.0f;
		}
		else {
			anglePlayer = anglePlayer - 15.0f;
		}
	}
	
	if(anglePlayerR == anglePlayer){
		anglePlayer = anglePlayerR;
	}
	if (anglePlayer == 360.0f) {
		anglePlayer = 0.0f;
	}
	if (anglePlayer < 0.0f) {
		anglePlayer = 345.0f;
	}


	p->setAnglePlayer(anglePlayer);

}

//update shot
void update::updateShot(vector <playerShot*> listShot, vector <villain*> botList) {
	for (int i = 0; i < numShot; i++) {
		if (listShot[i]->isShot) {
			listShot[i]->direction = listShot[i]->direction + 0.1f;
			float dx = (listShot[i]->direction)*sin(listShot[i]->angle); //direction * sin(angle)
			float dy = (listShot[i]->direction)*cos(listShot[i]->angle); 
			listShot[i]->x = listShot[i]->startX + dx * SHOT_SPEED; //startx + dx*speed
			listShot[i]->z = listShot[i]->startZ + dy * SHOT_SPEED;
			if ((listShot[i]->direction > 1.5f)) {
				listShot[i]->inizializza();
			}
		}	
	}

}

void update::shotHitBot(vector <playerShot*> listShot, villain* bot) {
	for (int s = 0; s < numShot; s++) { //ciclo la lista degli shot
		//se uno shot ha colpito il bot
		if ((listShot[s]->getX() >= bot->getX() - TILE_DIM / 2 && listShot[s]->getX() <= bot->getX() + TILE_DIM / 2) && (listShot[s]->getZ() >= bot->getZ() - TILE_DIM / 2 && listShot[s]->getZ() <= bot->getZ() + TILE_DIM / 2)) {
			listShot[s]->inizializza();

			bot->life = bot->life - 50; //diminuisce la vita del bot
			listShot[s]->startX = -1000.0f; //si ferma
			listShot[s]->startZ = -1000.0f; //si ferma
			bot->life = bot->life - 50;		//diminuisce la vita del bot
			cout << "HIT" << endl;
			cout << "bot life: " << bot->life << endl;

			if (bot->life <= 0) { //se la vita scende a 0 
				bot->animation_botDead = true; //setto a true l'animazione della morte
			}
			else {
				bot->animation_botHit = true; // setto a true l'animazione dell'hit
			}

		}
	}
}

void update::killBOT(vector <villain*> botList, game* game) {
	for (int i = 0; i < botList.size(); i++) {
		if (botList[i]->isDead == true) {
			botList[i]->isDead = false;
			game->kill_BOT();
		}
	}
}

