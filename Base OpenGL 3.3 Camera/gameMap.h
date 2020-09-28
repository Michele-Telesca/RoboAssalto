#pragma once
#include<stdio.h>
#include "game.h"
#include "cube.h"
#include "mapObject.h"
#include "utility.h"
#include "globalData.h"
#include <vector>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

						  // x = colonna; z = riga;
						  // 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
int mapMatrix[DIM][DIM] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 1
							{0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 2
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 3
							{0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0}, // 4
							{0,0,0,10,4,1,2,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,4,3,2,0,0,0,0}, // 5
							{0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0}, // 6
							{0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,1,0,0,0,0}, // 7
							{0,0,0,0,2,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,4,0,0,0,0}, // 8
							{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0}, // 9 
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 10
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0}, // 11
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,5,7,0,0,0,0,0,0,0,0}, // 12
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,5,0,0,0,0,0,10,0,0}, // 13
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,7,10,0,0,0,0,0,0,0,0}, // 14
							{0,0,10,0,0,0,0,0,0,0,0,0,0,0,10,3,2,0,0,0,0,0,3,1,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 15
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 16
							{0,0,0,0,0,0,0,0,0,11,0,0,0,0,4,1,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 17
							{0,0,0,0,0,0,0,0,0,1,2,1,4,1,2,2,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 18
							{0,10,0,0,0,0,0,0,0,0,0,0,0,10,4,3,0,0,0,0,0,0,0,1,3,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0}, // 19
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,15,0,0,0,2,4,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0}, // 20
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1,0,0,0,0,0,0,0,4,2,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0}, // 21
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0}, // 22
							{0,0,0,9,7,0,0,0,0,0,0,0,0,0,4,1,0,0,0,0,0,0,0,1,4,0,0,0,0,0,0,0,0,0,0,0,6,11,10,11}, // 23
							{0,0,5,7,6,3,0,0,0,0,0,0,0,0,1,2,14,0,0,0,0,0,11,4,2,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0}, // 24
							{0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,0,1,3,13,0,0,0,0,0,0,0,0,0,0,11,6,0,0,0}, // 25
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0}, // 26
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 27
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 28
							{0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 29
							{0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 30
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,7,6,0,0,0,0,0,0,0,0,0,0}, // 31
							{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,6,11,0,0,0,0,0,1,0,0,0,0}, // 32
							{0,0,0,0,2,0,0,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0}, // 33
							{0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0}, // 34
							{0,0,0,0,4,10,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,2,0,0,0,0}, // 35
							{0,0,0,11,1,2,4,3,1,0,0,0,0,0,0,0,0,7,11,3,0,0,0,0,0,0,0,0,0,0,0,1,4,2,4,1,0,0,0,0}, // 36
							{0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 37
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 38
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 39
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 40
};


vector <glm::vec2> mapObjectsCoord;


class gameMap {

public:

	gameMap() {}

	unsigned int texturePrato;
	cube* floor;
	vector <cube*> tiles; //vettore contenente le mattonelle del pavimento
	vector <mapObject*> mapObjects;

	void initMap(); //crea gli oggetti della mappa
	void drawMap(Shader lightShader); //disegna gli oggetti della mappa

};

void gameMap::initMap() {

	// ---- FLOOR ---- //
	
	for (float i = -DIM/2; i < DIM/2; i = i + TILE_DIM) {
		for (float j = DIM/2; j > -DIM/2; j = j - TILE_DIM) {
			// creo la singola mattonella del floor e la inserisco nel vettore tiles
			cube* tile = new cube(TILE_DIM, 0.0f, 1.0f, 0.0f, 0.0f, i, 1.0f, j);
			tiles.push_back(tile);
		}
	}

	//floor = new cube(DIM, 0.0f, 1.0f, 0.0f, 0.0f, -0.5f, (DIM/2) + 0.5f, 0.5f);

	// ---- mapObject ---- //
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {

			if (mapMatrix[i][j] != 0) {

				//conversione coordinate matrice -> game
				int x = j - 20;
				int z = i - 19;

				if (mapMatrix[i][j] == STONE1) {
					mapObject* stone1 = new mapObject(x, 0.7f, z, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
					stone1->initMapObject("models/stones/stone1/stone1.dae");
					mapObjects.push_back(stone1);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == STONE2) {
					mapObject* stone2 = new mapObject(x, 0.7f, z, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f);
					stone2->initMapObject("models/stones/stone2/stone2.dae");
					mapObjects.push_back(stone2);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == STONE3) {
					mapObject* stone3 = new mapObject(x, 0.7f, z, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f);
					stone3->initMapObject("models/stones/stone3/stone3.dae");
					mapObjects.push_back(stone3);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == STONE4) {
					mapObject* stone4 = new mapObject(x, 0.7f, z, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f);
					stone4->initMapObject("models/stones/stone4/stone4.dae");
					mapObjects.push_back(stone4);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == STONE5) {
					mapObject* stone5 = new mapObject(x, 1.8f, z, 0.28f, 0.0f, 1.0f, 0.0f, 0.0f);
					stone5->initMapObject("models/Stones/stone5/stone5.dae");
					mapObjects.push_back(stone5);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == STONE6) {
					mapObject* stone6 = new mapObject(x, 1.8f, z, 0.28f, 0.0f, 1.0f, 0.0f, 0.0f);
					stone6->initMapObject("models/Stones/stone6/stone6.dae");
					mapObjects.push_back(stone6);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == STONE7) {
					mapObject* stone7 = new mapObject(x, 1.8f, z, 0.28f, 0.0f, 1.0f, 0.0f, 0.0f);
					stone7->initMapObject("models/Stones/stone7/stone7.dae");
					mapObjects.push_back(stone7);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == TREE1) {
					mapObject* tree1 = new mapObject(x, 1.8f, z, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f);
					tree1->initMapObject("models/trees/tree1/tree1.dae");
					mapObjects.push_back(tree1);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == TREE2) {
					mapObject* tree2 = new mapObject(x, 1.8f, z, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f);
					tree2->initMapObject("models/trees/tree2/tree2.dae");
					mapObjects.push_back(tree2);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == TREE3) {
					mapObject* tree3 = new mapObject(x, 1.8f, z, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f);
					tree3->initMapObject("models/trees/tree3/tree3.dae");
					mapObjects.push_back(tree3);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == TREE4) {
					mapObject* tree4 = new mapObject(x, 1.8f, z, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f);
					tree4->initMapObject("models/trees/tree4/tree4.dae");
					mapObjects.push_back(tree4);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == TREE5) {
					mapObject* tree5 = new mapObject(x, 2.0f, z, 0.28f, 0.0f, 1.0f, 0.0f, 0.0f);
					tree5->initMapObject("models/trees/tree5/tree5.dae");
					mapObjects.push_back(tree5);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == BUSH1) {
					mapObject* bush1 = new mapObject(x, 0.6f, z, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f);
					bush1->initMapObject("models/bushes/bush1/bush1.dae");
					mapObjects.push_back(bush1);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == BUSH2) {
					mapObject* bush2 = new mapObject(x, 0.6f, z, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f);
					bush2->initMapObject("models/bushes/bush2/bush2.dae");
					mapObjects.push_back(bush2);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
				else if (mapMatrix[i][j] == CHEST) {
					mapObject* chest1 = new mapObject(x, 0.6f, z, 0.035f, 0.0f, 1.0f, 0.5f, 0.0f);
					chest1->initMapObject("models/chest/chest1.dae");
					mapObjects.push_back(chest1);
					mapObjectsCoord.push_back(glm::vec2(x, z));
				}
			}
			

		}
	}
	
}

void gameMap::drawMap(Shader lightShader) {

	// ---- FLOOR ---- //
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i]->drawCube(lightShader, texturePrato);
	}

	// ---- Objects ---- //
	for (int i = 0; i < mapObjects.size(); i++) {
		mapObjects[i]->drawMapObject(lightShader);
	}

}
