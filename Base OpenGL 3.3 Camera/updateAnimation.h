#pragma once
#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "game.h"
#include "gameMap.h"
#include "player.h"
#include "villain.h"
#include "powerUp.h"
#include "playerShot.h"
#include <vector>

/* classe di update per le animazioni:
   qui vengono gestiti tutti i tempi per
   gli aggiornamenti delle animazioni 
   del player e dei bot */

/* NOTE - (1): maggiore � il valore attribuito all'incremento del tempo -> maggiore sar� la velocit� di animazione 
          (2): per le animazioni ricorsive (camminata, corsa, attacco), quando il tempo dell'animazione supera 
		       una certa soglia (settata in questo caso arbitrariamente a 10.0f) si riparte da 0.0f */ 

class updateAnimation
{
	public:	

	updateAnimation(){}

	// ---- prototipi ---- //

	//richiamta tutto l'update dei tempi
	void updateAllAnimations(player* player, vector<villain*> botList, powerUp* powerUp);

	//bot animation time
	void increaseBotTime(vector<villain*> botList);
	void increaseBot_Walk_Attack(vector<villain*> botList);
	void increaseBot_Hit(vector<villain*> botList);
	void increaseBot_Dead(vector<villain*> botList);

	//player animation time
	void increasePlayerTime(player* player);
	void increasePlayerStand_Run(player* player);

	//power up animation time
	void increasePowerUpTime(powerUp* powerUp);

};

void updateAnimation::updateAllAnimations(player* player, vector<villain*> botList, powerUp* powerUp) {
	
	increasePlayerTime(player); 
	
	if (!botList.empty()) { 
		increaseBotTime(botList); //incrementa le animazioni dei bot solo se la lista dei bot NON � vuota
	}

	increasePowerUpTime(powerUp);

}

void updateAnimation::increasePowerUpTime(powerUp* powerUp) {
	float rotation_speed = 4.0f;
	float translate_speed = 0.015f;
	float z_upLimit = 0.6f;
	float z_downLimit = 0.1f;

	//incremento la variabile per la rotazione
	powerUp->animationTime_rotate_y = powerUp->animationTime_rotate_y + rotation_speed;

	//incremento e decremento la variabile per la traslazione z+ e z-
	if (powerUp->animationUp == true) {
		powerUp->animationTime_translate_y = powerUp->animationTime_translate_y + translate_speed;
		if (powerUp->animationTime_translate_y >= z_upLimit) {
			powerUp->animationUp = false;
		}
	}
	else {
		powerUp->animationTime_translate_y = powerUp->animationTime_translate_y - translate_speed;
		if (powerUp->animationTime_translate_y <= z_downLimit) {
			powerUp->animationUp = true;
		}
	}
}

void updateAnimation::increaseBotTime(vector<villain*> botList) {
	increaseBot_Walk_Attack(botList);
	increaseBot_Hit(botList);
	increaseBot_Dead(botList);
}

void updateAnimation::increasePlayerTime(player* player) {
	increasePlayerStand_Run(player);
}

void updateAnimation::increaseBot_Walk_Attack(vector<villain*> botList) {
	for (int i = 0; i < botList.size(); i++) {
		if (botList[i]->animation_botWalking == true) {
			botList[i]->animationTime_botWalking = botList[i]->animationTime_botWalking + 0.05f;     //incremento l'animazione
		}
		if (botList[i]->animation_botAttacking == true) {
			botList[i]->animationTime_botAttacking = botList[i]->animationTime_botAttacking + 0.05f; //incremento l'animazione
		}

		if (botList[i]->animationTime_botWalking >= 10.0f) {    //quando l'animazione supera la soglia
			botList[i]->animationTime_botWalking = 0.0f;       //reimposto il tempo di animazione all'inizio -> ricomincia da capo (per evitare bug)
		}

		if (botList[i]->animationTime_botAttacking >= 3.6f || botList[i]->animation_botAttacking == false) {   //quando l'animazione supera la soglia oppure torna ad essere false
			botList[i]->animationTime_botAttacking = 0.0f;      //resetto il tempo di animazione all'inizio -> ricomincia da capo (per evitare bug)
		}
	}
}

void updateAnimation::increaseBot_Hit(vector<villain*> botList) {
	for (int i = 0; i < botList.size(); i++) {
		if (botList[i]->animation_botHit == true) {
			botList[i]->animationTime_botHit = botList[i]->animationTime_botHit + 0.04f; //incremento l'animazione
		}
		if (botList[i]->animationTime_botHit >= 2.0f) {   //quando l'animazione � finita
			botList[i]->animationTime_botHit = 0.08f;     //resetto il tempo di animazione all'inizio
			botList[i]->animation_botHit = false;         //setto l'animazione a false
		}
	}
}

void updateAnimation::increaseBot_Dead(vector<villain*> botList) {
	for (int i = 0; i < botList.size(); i++) {
		if (botList[i]->animation_botDead == true) {
			botList[i]->animationTime_botDead = botList[i]->animationTime_botDead + 0.04f; //incremento l'animazione
		}
		if (botList[i]->animationTime_botDead >= 3.3f) {  //quando l'animazione � finita
			botList[i]->animationTime_botDead = 0.04f;    //resetto il tempo di animazione all'inizio
			botList[i]->animation_botDead = false;        //setto l'animazione a false
			botList[i]->isDead = true;					  //setto il booleano del bot "isDead" a true
		}
	}
}


void updateAnimation::increasePlayerStand_Run(player* player) {
	player->animationTime_playerStanding = player->animationTime_playerStanding + 0.06f;  //incremento l'animazione
	player->animationTime_playerRunning = player->animationTime_playerRunning + 0.06f;    //incremento l'animazione
	if (player->animationTime_playerStanding > 10.0f) {  //quando l'animazione supera la soglia
		player->animationTime_playerStanding = 0.0f;     //resetto il tempo di animazione all'inizio -> ricomincia da capo (per evitare bug)
	}
	if (player->animationTime_playerRunning > 10.0f) {   //quando l'animazione supera la soglia
		player->animationTime_playerRunning = 0.0f;      //resetto il tempo di animazione all'inizio -> ricomincia da capo (per evitare bug)
	}
}

