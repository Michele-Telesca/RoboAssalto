#pragma once
#include<stdio.h>
#include "game.h"
#include "operatore.h"

class gameMap {

public:

	gameMap() {};

	void inizializza(unsigned int texturePrato);

};

void gameMap::inizializza(unsigned int texturePrato) {

	// ---- FLOOR ---- //
	for (float i = -50; i <= 50; i = i + 0.5) {
		for (float j = 50; j >= -50; j = j - 0.5) {
			glBindTexture(GL_TEXTURE_2D, texturePrato);
			glBindVertexArray(cubeVAO);
			operatore* tile = new operatore(0.5, 0.0f, 1.0f, 0.0f, 0.0f, i, -2.0, j, myShader);
			tile->drawCube();
		}
	}

}