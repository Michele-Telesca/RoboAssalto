#pragma once
#include "point3D.h"
#include "weapon.h"
#include "model.h"
#include "globalData.h"
#include "path.h"
#include "globalPathData.h"
#include "utility.h"
#include <vector>

class villain {

public:

	villain() {}

	villain(float x, float y, float z) : x(x), y(y), z(z) {}

	//coordinate
	float x;
	float y;
	float z;
	
	float path_currentStep; //contatore dello step iesimo in cui si trova il bot 

	int life; //vita del player aggiornata 

	float chargingTime; //tempo di ricarica del colpo
	float timeLastShot; //tempo dell'ultimo colpo. serve per dare un tempo tra l'ultimo colpo e il prossimo

	Model* villain_model;

	weapon* weapon; //per avere la gittata del villain
	path* percorso;

	//Prototipi
	void drawVillain(Shader myShader);			 //disegna il player
	void animate();								 //animazione del player
	void initVillain(int path_Matrix[DIM][DIM]); //inializza il villain
	void move();		

	//GET e SET
	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	float getZ() {
		return z;
	}

	void setX(float posx) {
		x = posx;
	}

	void setY(float posy) {
		y = posy;
	}

	void setZ(float posz) {
		z = posz;
	}


};

void villain::initVillain(int path_Matrix[DIM][DIM]) {

	//inizializzo le coordinate di spawn
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			if (path_Matrix[i][j] == 1) {
				//conversione coordinate matrice -> game
				int coord_x = j - 10;
				int coord_z = i - 9;

				x = coord_x;
				z = coord_z;
			}
		}
	}

	//vita iniziale
	life = 100;

	path_currentStep = 1;

	//caricamento modello
	villain_model = new Model();
	villain_model->loadModel("models/bot/boty.DAE");
	
	//Creo ed inizializzo il path del villain
	percorso = new path(); 
	percorso->inizializzaPath(path_Matrix);

}


void villain::drawVillain(Shader myShader){

	// material properties
	myShader.setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
	myShader.setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
	myShader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
	myShader.setFloat("material.shininess", 76.8f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, 0.5f, z));
	model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	myShader.setMat4("model", model);

	villain_model->Draw(myShader);

}


void villain::move() {
	float epsilon = 0.1f;

	//ciclo la lista di coordinate del path 
	for (int i = 0; i < percorso->getPath_list().size(); i++) {

		//se il path_currentStep è compreso tra lo step precedente e quello successivo (nuove coordinate da raggiungere)
		//if (percorso->getPath_list()[i].w > path_currentStep && percorso->getPath_list()[i].w <= path_currentStep + 1.0f) {
		//if (floor(percorso->getPath_list()[i].w) == path_currentStep + 1.0f){
		if(isEqual(floor(percorso->getPath_list()[i].w), path_currentStep + 1.0f, epsilon)) {

			float newCoord_x = percorso->getPath_list()[i].x;
			float newCoord_z = percorso->getPath_list()[i].z;
			if (isEqual(z,newCoord_z, epsilon)) {
				if (newCoord_x > x) { //muovi a destra
					x = x + BOT_MOVE_STEP;
				}
				if (newCoord_x < x) { //muovi a sinistra
					x = x - BOT_MOVE_STEP;
				}
			}
			else if (isEqual(x, newCoord_x, epsilon)) {
				if (newCoord_z > z) { //muovi in basso
					z = z + BOT_MOVE_STEP;
				}
				if (newCoord_z < z) { //muovi in alto
					z = z - BOT_MOVE_STEP;
				}
			}

			//if (x == newCoord_x && z == newCoord_z) { //se il bot ha raggiungo la nuova coordinata
			//if ((x <= newCoord_x && x > newCoord_x - 0.1f) && (z <= newCoord_z && z > newCoord_z - 0.1f)) { //se il bot ha raggiungo la nuova coordinata
			if (isEqual(x, newCoord_x, epsilon) && isEqual(z, newCoord_z, epsilon)) {
				path_currentStep++; //incremento lo step a quello successivo
			}
			break;
		}
	}

	//se è arrivato a fine corsa -> RICOMINCIA
	if (path_currentStep == percorso->getPath_EndPath()) {
		path_currentStep = 1;
	}
}

void villain::animate() {

}

