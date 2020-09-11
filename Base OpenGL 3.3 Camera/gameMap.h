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
	void drawMap(Shader lightShader); //disegna gli oggetti della mappa

};

void gameMap::initMap() {

	// ---- FLOOR ---- //
	float dim = 10;
	for (float i = -dim; i < dim; i = i + 1.0) {
		for (float j = dim; j > -dim; j = j - 1.0) {
			// creo la singola mattonella del floor e la inserisco nel vettore tiles
			cube* tile = new cube(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, i, 0.0f, j);
			tiles.push_back(tile);
		}
	}

	// ---- STONES ---- //
	/*mapObject* stone1 = new mapObject(1.0f, 2.0f, 1.0f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone1->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone1);

	mapObject* stone2 = new mapObject(-1.0f, 2.0f, -1.0f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone2->initMapObject("models/stones/stone2/stone2.dae");
	mapObjects.push_back(stone2);

	mapObject* stone3 = new mapObject(-2.0f, 2.0, -2.0f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone3->initMapObject("models/stones/stone3/stone3.dae");
	mapObjects.push_back(stone3);*/

	// ---- TREES ---- //
	mapObject* tree1 = new mapObject(-1.0f, 2.0f, 0.0f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f);
	tree1->initMapObject("models/trees/tree1/tree1.dae");
	mapObjects.push_back(tree1);

	mapObject* tree2 = new mapObject(1.0f, 2.0f, 0.0f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f);
	tree2->initMapObject("models/trees/tree2/tree2.dae");
	mapObjects.push_back(tree2);

	mapObject* tree3 = new mapObject(0.0f, 2.0f, -1.0f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f);
	tree3->initMapObject("models/trees/tree3/tree3.dae");
	mapObjects.push_back(tree3);

	mapObject* tree4 = new mapObject(0.0f, 2.0f, -2.0f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f);
	tree4->initMapObject("models/trees/tree4/tree4.dae");
	mapObjects.push_back(tree4);

	mapObject* tree5 = new mapObject(0.0f, 2.0f, -3.0f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f);
	tree5->initMapObject("models/trees/tree5/tree5.dae");
	mapObjects.push_back(tree5);

	// ---- BUSHES ---- //
	/*mapObject* bush1 = new mapObject(-1.0f, 2.0f, 1.0f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	bush1->initMapObject("models/bushes/bush1/bush1.dae");
	mapObjects.push_back(bush1);

	mapObject* bush2 = new mapObject(-2.0f, 2.0f, -1.0f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	bush2->initMapObject("models/bushes/bush2/bush2.dae");
	mapObjects.push_back(bush2);*/

}

void gameMap::drawMap(Shader lightShader) {

	// ---- FLOOR ---- //
	lightShader.setInt("myTexture1", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturePrato);
	glBindVertexArray(cubeVAO);
	lightShader.setVec3("colorcube", 1.0f, 1.0f, 1.0f); //bianco (colore neutro)
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i]->drawCube(lightShader);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	// ---- STONES ---- //
	for (int i = 0; i < mapObjects.size(); i++) {
		mapObjects[i]->drawMapObject(lightShader);
	}

}