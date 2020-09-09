#pragma once
#include<stdio.h>
#include "game.h"
#include "cube.h"
#include "mapObject.h"
#include <vector>

class gameMap {

public:

	gameMap() {}

	unsigned int texturePrato;

	vector <cube*> tiles; //vettore contenente le mattonelle del pavimento
	vector <mapObject*> mapObjects;

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

	// ---- STONES ---- //
	mapObject* stone1 = new mapObject(1.0f, 2.0f, 1.0f);
	stone1->initMapObject("models/stones/stone11/stone111.dae");
	mapObjects.push_back(stone1);

	//mapObject* stone2 = new mapObject(-1.0f, 2.0f, -1.0f);
	//stone2->initMapObject("models/Stones/Ch16_nonPBR.DAE");
	//mapObjects.push_back(stone2);

	//mapObject* stone3 = new mapObject(-2.0f, 2.0, -2.0f);
	//stone3->initMapObject("models/Stones/Ch16_nonPBR.DAE");
	//mapObjects.push_back(stone3);

}

void gameMap::drawMap(Shader myShader) {

	// ---- FLOOR ---- //
	myShader.setInt("myTexture1", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturePrato);
	glBindVertexArray(cubeVAO);
	myShader.setVec3("colorcube", 1.0f, 1.0f, 1.0f); //bianco (colore neutro)
	for (int i = 1; i < tiles.size(); i++) {
		tiles[i]->drawCube(myShader);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	// ---- STONES ---- //
	for (int i = 0; i < mapObjects.size(); i++) {
		mapObjects[i]->drawMapObject(myShader, 1.0f);
	}


}