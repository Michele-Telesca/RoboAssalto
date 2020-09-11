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

	// -- Quadrato centrale -- //
	// lato sx
	mapObject* stone1 = new mapObject(-3.5f, 1.0f, 3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone1->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone1);

	mapObject* stone2 = new mapObject(-3.5f, 1.0f, 2.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone2->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone2);

	mapObject* stone3 = new mapObject(-3.5f, 1.0f, 1.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone3->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone3);

	mapObject* stone4 = new mapObject(-3.5f, 1.0f, 0.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone4->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone4);

	mapObject* stone5 = new mapObject(-3.5f, 1.0f, -0.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone5->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone5);

	mapObject* stone6 = new mapObject(-3.5f, 1.0f, -1.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone6->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone6);

	mapObject* stone7 = new mapObject(-3.5f, 1.0f, -2.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone7->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone7);

	mapObject* stone8 = new mapObject(-3.5f, 1.0f, -3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone8->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone8);

	// sopra
	mapObject* stone9 = new mapObject(-2.5f, 1.0f, -3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone9->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone9);

	mapObject* stone10 = new mapObject(-1.5f, 1.0f, -3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone10->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone10);

	mapObject* stone11 = new mapObject(1.5f, 1.0f, -3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone11->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone11);

	mapObject* stone12 = new mapObject(2.5f, 1.0f, -3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone12->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone12);

	mapObject* stone13 = new mapObject(3.5f, 1.0f, -3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone13->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone13);

	// lato dx
	mapObject* stone14 = new mapObject(3.5f, 1.0f, -2.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone14->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone14);

	mapObject* stone15 = new mapObject(3.5f, 1.0f, -1.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone15->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone15);

	mapObject* stone16 = new mapObject(3.5f, 1.0f, -0.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone16->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone16);

	mapObject* stone17 = new mapObject(3.5f, 1.0f, 0.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone17->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone17);

	mapObject* stone18 = new mapObject(3.5f, 1.0f, 1.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone18->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone18);

	mapObject* stone19 = new mapObject(3.5f, 1.0f, 2.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone19->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone19);

	mapObject* stone20 = new mapObject(3.5f, 1.0f, 3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone20->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone20);

	// sotto
	mapObject* stone21 = new mapObject(2.5f, 1.0f, 3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone21->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone21);

	mapObject* stone22 = new mapObject(1.5f, 1.0f, 3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone22->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone22);

	mapObject* stone23 = new mapObject(-1.5f, 1.0f, 3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone23->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone23);

	mapObject* stone24 = new mapObject(-2.5f, 1.0f, 3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone24->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone24);

	mapObject* stone25 = new mapObject(-3.5f, 1.0f, 3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone25->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone25);

	// 4 stone extra
	mapObject* stone26 = new mapObject(1.5f, 1.0f, 4.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone26->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone26);

	mapObject* stone27 = new mapObject(-1.5f, 1.0f, 4.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone27->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone27);

	mapObject* stone28 = new mapObject(1.5f, 1.0f, -4.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone28->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone28);

	mapObject* stone29 = new mapObject(-1.5f, 1.0f, -4.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone29->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone29);

	// ---- //

	// -- Stone laterali dx -- //

	mapObject* stone30 = new mapObject(6.5f, 1.0f, 0.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone30->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone30);

	mapObject* stone31 = new mapObject(6.5f, 1.0f, 1.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone31->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone31);

	mapObject* stone32 = new mapObject(6.5f, 1.0f, 2.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone32->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone32);

	mapObject* stone33 = new mapObject(6.5f, 1.0f, 3.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone33->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone33);

	mapObject* stone34 = new mapObject(6.5f, 1.0f, 4.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone34->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone34);

	// -- Stone laterali sx -- //

	mapObject* stone35 = new mapObject(-4.5f, 1.0f, -1.0f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone35->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone35);

	mapObject* stone36 = new mapObject(-5.5f, 1.0f, -1.0f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone36->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone36);

	mapObject* stone37 = new mapObject(-6.5f, 1.0f, -1.0f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone37->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone37);

	mapObject* stone38 = new mapObject(-7.5f, 1.0f, -1.0f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
	stone38->initMapObject("models/stones/stone1/stone1.dae");
	mapObjects.push_back(stone38);

	// ---- TREES ---- //
	mapObject* tree1 = new mapObject(1.5f, 2.0f, -1.0f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f);
	tree1->initMapObject("models/trees/tree3/tree3.dae");
	mapObjects.push_back(tree1);

	mapObject* tree2 = new mapObject(-1.0f, 2.0f, 1.5f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f);
	tree2->initMapObject("models/trees/tree4/tree4.dae");
	mapObjects.push_back(tree2);

	mapObject* tree3 = new mapObject(7.5f, 2.0f, 2.5f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f);
	tree3->initMapObject("models/trees/tree3/tree3.dae");
	mapObjects.push_back(tree3);

	mapObject* tree4 = new mapObject(9.0f, 2.0f, 2.5f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f);
	tree4->initMapObject("models/trees/tree4/tree4.dae");
	mapObjects.push_back(tree4);
	
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