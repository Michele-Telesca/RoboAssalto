#pragma once
#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "game.h"
#include "gameMap.h"
#include "player.h"
#include "villain.h"
#include "playerShot.h"
#include <vector>

/* classe di update per le animazioni:
   qui vengono gestiti tutti i tempi per
   gli aggiornamenti delle animazioni 
   del player e dei bot */

/* NOTE - (1): maggiore è il valore attribuito all'incremento del tempo -> maggiore sarà la velocità di animazione 
          (2): per le animazioni ricorsive (camminata, corsa, attacco), quando il tempo dell'animazione supera 
		       una certa soglia (settata in questo caso arbitrariamente a 10.0f) si riparte da 0.0f */ 

class updateAnimation
{
	public:	

	updateAnimation(){}

	// ---- prototipi ---- //

	//richiamta tutto l'update dei tempi
	void updateAllAnimations(player* player, vector<villain*> botList);

	//bot animation time
	void increaseBotTime(vector<villain*> botList);
	void increaseBot_Walk_Attack(vector<villain*> botList);

	//player animation time
	void increasePlayerTime(player* player);
	void increasePlayerStand_Run(player* player);

};

void updateAnimation::updateAllAnimations(player* player, vector<villain*> botList) {
	increasePlayerTime(player);
	increaseBotTime(botList);
}

void updateAnimation::increaseBotTime(vector<villain*> botList) {
	increaseBot_Walk_Attack(botList);
}

void updateAnimation::increasePlayerTime(player* player) {
	increasePlayerStand_Run(player);
}

void updateAnimation::increaseBot_Walk_Attack(vector<villain*> botList) {
	for (int i = 0; i < botList.size(); i++) {
		if (botList[i]->animation_botWalking == true) {
			botList[i]->animationTime_botWalking = botList[i]->animationTime_botWalking + 0.05f;
		}
		if (botList[i]->animation_botAttacking == true) {
			botList[i]->animationTime_botAttacking = botList[i]->animationTime_botAttacking + 0.05f;
		}

		if (botList[i]->animationTime_botWalking > 10.0f) {
			botList[i]->animationTime_botWalking = 0.0f;
		}

		if (botList[i]->animationTime_botAttacking > 10.0f) {
			botList[i]->animationTime_botAttacking = 0.0f;
		}
	}
}

void updateAnimation::increasePlayerStand_Run(player* player) {
	player->animationTime_playerStanding = player->animationTime_playerStanding + 0.06f;
	player->animationTime_playerRunning = player->animationTime_playerRunning + 0.06f;
	if (player->animationTime_playerStanding > 10.0f) {
		player->animationTime_playerStanding = 0.0f;
	}
	if (player->animationTime_playerRunning > 10.0f) {
		player->animationTime_playerRunning = 0.0f;
	}
}

