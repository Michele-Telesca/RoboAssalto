#pragma once
#include<stdio.h>
#include "game.h"
#include "cube.h"
#include "mapObject.h"
#include "utility.h"
#include "globalData.h"
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

							// x = colonna; z = riga; 
int mapMatrix[DIM][DIM] = { {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},
							{0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,9,6,4,0,0,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,4,3,3,5,0,0,3,5,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,3,6,0,0,0,0,0,0,5,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,3,6,3,6,5,0,0,0,0,9,0,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,5,3,0,0,0,0,0,0,4,5,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,4,6,0,0,0,0,0,0,3,6,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,3,5,0,9,0,0,0,0,4,3,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,5,6,0,0,0,0,0,0,6,5,0,0,5,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,3,4,3,6,0,0,5,4,3,4,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,2,3,5,0,0,3,6,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,9,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,9,6,4,0,0,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,4,3,3,5,0,0,3,5,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,3,6,0,0,0,0,0,0,5,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,3,6,3,6,5,0,0,0,0,9,0,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,5,3,0,0,0,0,0,0,4,5,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,4,6,0,0,0,0,0,0,3,6,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,3,5,0,9,0,0,0,0,4,3,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,5,6,0,0,0,0,0,0,6,5,0,0,5,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,3,4,3,6,0,0,5,4,3,4,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,2,3,5,0,0,3,6,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{9,0,0,0,0,9,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},
						  };

vector <glm::vec2> mapObjectsCoord;


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
	
	for (float i = -DIM/2; i < DIM/2; i = i + TILE_DIM) {
		for (float j = DIM/2; j > -DIM/2; j = j - TILE_DIM) {
			// creo la singola mattonella del floor e la inserisco nel vettore tiles
			cube* tile = new cube(TILE_DIM, 0.0f, 1.0f, 0.0f, 0.0f, i, 1.0f, j);
			tiles.push_back(tile);
		}
	}

	// ---- mapObject ---- //
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {

			//conversione coordinate matrice -> game
			int x = j - 20;
			int z = i - 19;

			if (mapMatrix[i][j] == BUSH1) {
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
			else if (mapMatrix[i][j] == STONE1) {
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
				mapObjectsCoord.push_back(glm::vec2(x,z));
			}
			else if (mapMatrix[i][j] == STONE4) {
				mapObject* stone4 = new mapObject(x, 0.7f, z, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f);
				stone4->initMapObject("models/stones/stone4/stone4.dae");
				mapObjects.push_back(stone4);
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
				mapObject* tree5 = new mapObject(x, 1.8f, z, 0.28f, 0.0f, 1.0f, 0.0f, 0.0f);
				tree5->initMapObject("models/trees/tree5/tree5.dae");
				mapObjects.push_back(tree5);
				mapObjectsCoord.push_back(glm::vec2(x, z));
			}
			//else if (map[i][j] == 12) {
			//	//seleziono un punto random all'interno del quadrato 1x1
			//	float x_rand = randMToN(x - 0.45, x + 0.45);
			//	float z_rand = randMToN(z - 0.45, z + 0.45);

			//	mapObject* grass1 = new mapObject(x_rand, 1.0f, z_rand, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f);
			//	grass1->initMapObject("models/grass/grass1/grass1.dae");
			//	mapObjects.push_back(grass1);
			//}

		}
	}
	
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

	// ---- Objects ---- //
	for (int i = 0; i < mapObjects.size(); i++) {
		mapObjects[i]->drawMapObject(lightShader);
		glBindTexture(GL_TEXTURE_2D, 0); //PROVVISORIO
	}

}
