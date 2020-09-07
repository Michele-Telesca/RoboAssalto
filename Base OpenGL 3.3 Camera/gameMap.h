#pragma once
#include<stdio.h>
#include "game.h"
#include "cube.h"
#include <vector>

class gameMap {

public:

	gameMap() {}

	unsigned int texturePrato;

	vector <cube*> tiles; //vettore contenente le mattonelle del pavimento

	void initMap(); //crea gli oggetti della mappa
	void drawMap(Shader myShader); //disegna gli oggetti della mappa

};

void gameMap::initMap() {

	// ---- FLOOR ---- //
	float dim = 5;
	for (float i = -dim; i <= dim; i = i + 0.5) {
		for (float j = dim; j >= -dim; j = j - 0.5) {
			// creo la singola mattonella del floor e la inserisco nel vettore tiles
			cube* tile = new cube(0.5, 0.0f, 1.0f, 0.0f, 0.0f, i, 0.0f, j);
			tiles.push_back(tile);
		}
	}

}

void gameMap::drawMap(Shader myShader) {

	myShader.setInt("myTexture1", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturePrato);
	glBindVertexArray(cubeVAO);

	myShader.setVec3("colorcube", 1.0f, 1.0f, 1.0f); //bianco (colore neutro)

	for (int i = 1; i < tiles.size(); i++) {
		tiles[i]->drawCube(myShader);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

}