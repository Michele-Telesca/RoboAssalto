#pragma once
#include<stdio.h>
#include "game.h"
#include "cube.h"
#include "mapObject.h"
#include "utility.h"
#include "globalData.h"
#include "model.h"
#include <vector>

class powerUp
{
	public:

		powerUp(){}

		float x;
		float y;
		float z;

		bool spawned; //true se il power up è spawnato
		bool hit; //true se è stato hittato dal player


		Model* shotgun;
		Model* sniper;
		Model* medikit;

		int powerUp_type;	//1: WEAPON_SHOTGUN //2: WEAPON_SNIPER

		vector<glm::vec3> spawnCoordsList; //lista di coordinate in cui può spawnare il powerUp

		bool animationUp = true; //gestisce l'animazione se trasla verso l'alto o il basso
		float animationTime_translate_y;
		float animationTime_rotate_y;

		void initPowerUp();
		void drawPowerUp(Shader lightShader);
};

void powerUp::initPowerUp() {

	spawned = false; //non ancora spawnato
	hit = false; //non ancora hittato dal player

	animationTime_translate_y = 0.0f;
	animationTime_rotate_y = 0.0f;

	//inizializzo i modelli dei powerUp
	shotgun = new Model();
	shotgun->loadModel("models/power_up/shotgun/shotgun.dae");
	sniper = new Model();
	sniper->loadModel("models/power_up/sniper/l96.dae");

	medikit = new Model();
	medikit->loadModel("models/power_up/medikit/medikit.dae");

	//inizilizzo la lista di coordinate di spawn dei powerUp
	spawnCoordsList.push_back(glm::vec3(0.0f, 1.0f, 15.0f));    // indice: 0
	spawnCoordsList.push_back(glm::vec3(-5.0f, 1.0f, 17.5f));   // indice: 1
	spawnCoordsList.push_back(glm::vec3(-7.5f, 1.0f, 6.0f));    // indice: 2
	spawnCoordsList.push_back(glm::vec3(-9.0f, 1.0f, -6.0f));   // indice: 3
	spawnCoordsList.push_back(glm::vec3(0.0f, 1.0f, -15.0f));   // indice: 4
	spawnCoordsList.push_back(glm::vec3(8.5f, 1.0f, -5.5f));    // indice: 5
	spawnCoordsList.push_back(glm::vec3(8.0f, 1.0f, 3.0f));		// indice: 6
	spawnCoordsList.push_back(glm::vec3(17.0f, 1.0f, -1.5f));   // indice: 7
	spawnCoordsList.push_back(glm::vec3(3.5f, 1.0f, 8.0f));     // indice: 8
	spawnCoordsList.push_back(glm::vec3(13.0f, 1.0f, 14.0f));   // indice: 9
}

void powerUp::drawPowerUp(Shader lightShader) {

	lightShader.use();

	// material properties
	lightShader.setVec3("material.ambient", 0.9f, 0.9f, 0.9f);
	lightShader.setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
	lightShader.setFloat("material.shininess", 76.8f);

	if (powerUp_type == WEAPON_SHOTGUN) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x, y + animationTime_translate_y, z));
		model = glm::rotate(model, glm::radians(animationTime_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f)); //bullet scale
		lightShader.setMat4("model", model);
		shotgun->Draw(lightShader); //bullet draw
	} 

	else if (powerUp_type == WEAPON_SNIPER) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x, y + animationTime_translate_y, z));
		model = glm::rotate(model, glm::radians(animationTime_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f)); //bullet scale
		lightShader.setMat4("model", model);
		sniper->Draw(lightShader); //bullet draw
	}

	else if (powerUp_type == MEDIKIT) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x, y + animationTime_translate_y, z));
		model = glm::rotate(model, glm::radians(animationTime_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f)); //bullet scale
		lightShader.setMat4("model", model);
		medikit->Draw(lightShader); //bullet draw
	}
	
}

