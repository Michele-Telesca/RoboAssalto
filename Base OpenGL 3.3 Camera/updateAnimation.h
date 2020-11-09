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
#include "mainMenu.h"

#include <irrKlang/irrKlang.h>


/* Classe di update per le animazioni:
   vengono gestiti 
   a) i tempi per gli aggiornamenti 
      delle animazioni del player, dei bot,
      del powerUp e del main menu;
   b) le tracce audio che accompagnano 
      le animazioni in game (sound effect)
	  e le soundtrack di background
	  del menù e del game */

/* NOTE - (1): maggiore è il valore attribuito all'incremento del tempo -> maggiore sarà la velocità di animazione 
          (2): per le animazioni ricorsive (camminata, corsa, attacco), quando il tempo dell'animazione supera 
		       una certa soglia, ricomincia */ 

class updateAnimation
{
public:	
		
	irrklang::ISoundEngine* SoundEngine_effect; //proprietà che gestisce il sound
	irrklang::ISoundEngine* SoundEngine_soundtrack; //proprietà che gestisce il sound
	
	//costruttore no-arg
	updateAnimation(){
		SoundEngine_effect = irrklang::createIrrKlangDevice(); //inizializzo il soundEngine
		SoundEngine_effect->setSoundVolume(0);
		SoundEngine_effect->play2D("audio/footstep grass.wav", false); //sound step
		SoundEngine_soundtrack = irrklang::createIrrKlangDevice(); //inizializzo il soundEngine
		SoundEngine_soundtrack->setSoundVolume(0);
		SoundEngine_soundtrack->play2D("audio/footstep grass.wav", false); //sound step
	}

	// ---- prototipi ---- //

	//richiamta tutto l'update dei tempi
	void updateAllAnimations(player* player, vector<villain*> botList, powerUp* powerUp);

	void gameSound(game* game);

	//bot animation time
	void botAnimation(vector<villain*> botList);
	void increaseBot_Walk_Attack(vector<villain*> botList);
	void increaseBot_Hit(vector<villain*> botList);
	void increaseBot_Dead(vector<villain*> botList);
	void bot_soundAattack(villain* bot);

	//player animation time
	void playerAnimation(player* player);
	void increasePlayer_Run(player* player);
	void increasePlayer_Stand(player* player);
	void playerShot_sound(player* player);

	//power up animation time
	void powerUpAnimation(powerUp* powerUp);
	void powerUp_sound(powerUp* powerUp);

	//menu
	void increase_menuPlayer_posing(mainMenu* main_menu);
	void menuSound(mainMenu* main_menu);

};

void updateAnimation::updateAllAnimations(player* player, vector<villain*> botList, powerUp* powerUp) {
	
	playerAnimation(player);
	
	if (!botList.empty()) { 
		botAnimation(botList); //incrementa le animazioni dei bot solo se la lista dei bot NON è vuota
	}

	powerUpAnimation(powerUp);
	powerUp_sound(powerUp);

}

void updateAnimation::powerUpAnimation(powerUp* powerUp) {
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

void updateAnimation::botAnimation(vector<villain*> botList) {
	increaseBot_Walk_Attack(botList);
	increaseBot_Hit(botList);
	increaseBot_Dead(botList);
}

void updateAnimation::playerAnimation(player* player) {
	increasePlayer_Run(player);
	increasePlayer_Stand(player);
	playerShot_sound(player);
}

void updateAnimation::bot_soundAattack(villain* bot) {
	if (bot->animationTime_botAttacking >= 1.49f && bot->animationTime_botAttacking <= 1.51f) {
		int sound_attack_index = randMtoN(1, 5);
		SoundEngine_effect->setSoundVolume(0.5);
		if (sound_attack_index == 1) {
			SoundEngine_effect->play2D("audio/zombie_attack1.wav", false); //zombie attack sound
		}
		else if (sound_attack_index == 2) {
			SoundEngine_effect->play2D("audio/zombie_attack2.wav", false); //zombie attack sound
		}
		else if (sound_attack_index == 3) {
			SoundEngine_effect->play2D("audio/zombie_attack3.wav", false); //zombie attack sound
		}
		else if (sound_attack_index == 4) {
			SoundEngine_effect->play2D("audio/zombie_attack4.wav", false); //zombie attack sound
		}
		else if (sound_attack_index == 5) {
			SoundEngine_effect->play2D("audio/zombie_attack5.wav", false); //zombie attack sound
		}
	}
}

void updateAnimation::increaseBot_Walk_Attack(vector<villain*> botList) {
	for (int i = 0; i < botList.size(); i++) {
		if (botList[i]->animation_botWalking == true) {
			botList[i]->animationTime_botWalking = botList[i]->animationTime_botWalking + 0.05f;     //incremento l'animazione
		}
		if (botList[i]->animation_botAttacking == true) {
			botList[i]->animationTime_botAttacking = botList[i]->animationTime_botAttacking + 0.05f; //incremento l'animazione
			bot_soundAattack(botList[i]); 
		}
		if (botList[i]->animationTime_botWalking >= 10.0f) {    //quando l'animazione supera la soglia
			botList[i]->animationTime_botWalking = 0.0f;          //reimposto il tempo di animazione all'inizio -> ricomincia da capo (per evitare bug)
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
		if (botList[i]->animationTime_botHit == 0.12f ) {
			int sound_hit_index = randMtoN(1,2);
			SoundEngine_effect->setSoundVolume(0.5);
			if (sound_hit_index == 1) {
				SoundEngine_effect->play2D("audio/zombie_hit1.wav", false); //zombie hit sound
			}
			else if (sound_hit_index == 2) {
				SoundEngine_effect->play2D("audio/zombie_hit2.wav", false); //zombie hit sound
			}
		}
		if (botList[i]->animationTime_botHit >= 2.0f) {   //quando l'animazione è finita
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
		if (botList[i]->animationTime_botDead >= 3.3f) {  //quando l'animazione è finita
			botList[i]->animationTime_botDead = 0.04f;    //resetto il tempo di animazione all'inizio
			botList[i]->animation_botDead = false;        //setto l'animazione a false
			botList[i]->isDead = true;					  //setto il booleano del bot "isDead" a true
		}
	}
}


void updateAnimation::increasePlayer_Stand(player* player) {
	player->animationTime_playerStanding = player->animationTime_playerStanding + 0.06f;   //incremento l'animazione
	if (player->animationTime_playerStanding > 20.0f) {  //quando l'animazione supera la soglia
		player->animationTime_playerStanding = 0.0f;     //resetto il tempo di animazione all'inizio -> ricomincia da capo (per evitare bug)
	}
}

void updateAnimation::increasePlayer_Run(player* player) {

	if (muoviDx == true || muoviSx == true || muoviSu == true || muoviGiu == true) { //se il player cammina
		player->animationTime_playerRunning = player->animationTime_playerRunning + 0.05f;  //incremento l'animazione

		if (player->animationTime_playerRunning == 0.05f) { //quando il player fa primo passo
			SoundEngine_effect->setSoundVolume(0.8);
			SoundEngine_effect->play2D("audio/footstep grass.wav", false); //sound step
		}
		if (player->animationTime_playerRunning >= 0.49f && player->animationTime_playerRunning <= 0.51f && player->wea->weapon_type == WEAPON_SHOTGUN) { //quando il player fa primo passo
			SoundEngine_effect->setSoundVolume(0.8);
			SoundEngine_effect->play2D("audio/footstep grass.wav", false); //sound step
		}
		if (player->animationTime_playerRunning >= 0.69f && player->animationTime_playerRunning <= 0.71f && player->wea->weapon_type == WEAPON_SNIPER) {
			SoundEngine_effect->setSoundVolume(0.8);
			SoundEngine_effect->play2D("audio/footstep grass.wav", false); //sound step
		}

		if (player->animationTime_playerRunning > 1.0f && player->wea->weapon_type == WEAPON_SHOTGUN) {   //quando il player fa il secondo passo
			player->animationTime_playerRunning = 0.0f;     //resetto il tempo di animazione all'inizio -> ricomincia da 
		}

		if (player->animationTime_playerRunning > 1.4f && player->wea->weapon_type == WEAPON_SNIPER) {   //quando il player fa il secondo passo
			player->animationTime_playerRunning = 0.0f;     //resetto il tempo di animazione all'inizio -> ricomincia da 
		}
	}
}

void updateAnimation::playerShot_sound(player* player) {
	if (player->startPlayerShot == true && player->numShotsAvailable > 0 && player->delayShotIsFinished) {
		if (player->wea->weapon_type == WEAPON_SHOTGUN) {
			SoundEngine_effect->setSoundVolume(0.3);
			SoundEngine_effect->play2D("audio/shotgun_fire.wav", false); //sound shot SHOTGUN
		}
		else if(player->wea->weapon_type == WEAPON_SNIPER){
			SoundEngine_effect->setSoundVolume(0.3);
			SoundEngine_effect->play2D("audio/sniper_fire.wav", false); //sound shot SNIPER
		}
	}
	else if (player->startPlayerShot == true && player->numShotsAvailable <= 0) {
		SoundEngine_effect->setSoundVolume(0.5);
		SoundEngine_effect->play2D("audio/weapon_empty.flac", false); //sound no shot available
	}
}

void updateAnimation::powerUp_sound(powerUp* powerUp) {
	if (powerUp->hit == true) {
		if (powerUp->powerUp_type == WEAPON_SHOTGUN) {
			SoundEngine_effect->setSoundVolume(0.7);
			SoundEngine_effect->play2D("audio/bullet powerUp.wav", false); //sound no shot available
		}
		else if (powerUp->powerUp_type == WEAPON_SNIPER) {
			SoundEngine_effect->setSoundVolume(0.7);
			SoundEngine_effect->play2D("audio/sight powerUp.wav", false); //sound no shot available
		}
		else if (powerUp->powerUp_type == MEDIKIT) {
			SoundEngine_effect->setSoundVolume(0.7);
			SoundEngine_effect->play2D("audio/medikit.wav", false); //sound no shot available
		}
		powerUp->hit = false;
	}
}

void updateAnimation::increase_menuPlayer_posing(mainMenu* main_menu) {
	
	if (main_menu->animation_brycePosing == true) {
		main_menu->animationTime_brycePosing = main_menu->animationTime_brycePosing + 0.06f;
		if (main_menu->animationTime_brycePosing >= 9.2f) {
			main_menu->animationTime_brycePosing = 1.0f;
		}
	}

	if (main_menu->animation_michellePosing == true) {
		main_menu->animationTime_michellePosing = main_menu->animationTime_michellePosing + 0.035f;
	}

}

void updateAnimation::menuSound(mainMenu* main_menu) {
	if (main_menu->startMenuSoundtrack == false) {
		SoundEngine_soundtrack->setSoundVolume(0.7f);
		SoundEngine_soundtrack->play2D("audio/menu_soundtrack2.wav", true); //sound no shot available
		main_menu->startMenuSoundtrack = true;
	}
	
}

void updateAnimation::gameSound(game* game) {
	if (game->startGameSoundtrack == false) {
		SoundEngine_soundtrack->setSoundVolume(0.3f);
		SoundEngine_soundtrack->play2D("audio/game_soundtrack1.wav", true); //sound no shot available
		game->startGameSoundtrack = true;
	}
}


