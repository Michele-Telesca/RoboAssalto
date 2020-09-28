#pragma once
#include "model.h"
#include "weapon.h"
#include "path.h"
#include "skinned_mesh.h"
#include "globalData.h"

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

	//Model* villain_model;
	SkinnedMesh meshWalking;
	SkinnedMesh meshAttacking;

	weapon* weapon; //per avere la gittata del villain
	path* percorso;
	player* p;

	//Prototipi
	void drawVillain(Shader animShader, glm::mat4 view);			 //disegna il player
	void animate();								 //animazione del player
	void initVillain(int path_Matrix[DIM][DIM]); //inializza il villain

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

	float getPath_currentStep() {
		return path_currentStep;
	}

	path* getPath() {
		return percorso;
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

	void setPath_currentStep(float valore) {
		path_currentStep = valore;
	}


};

void villain::initVillain(int path_Matrix[DIM][DIM]) {

	//inizializzo le coordinate di spawn
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			if (path_Matrix[i][j] == 1) {
				//conversione coordinate matrice -> game
				int coord_x = j - 20;
				int coord_z = i - 19;

				x = coord_x;
				z = coord_z;
			}
		}
	}

	//vita iniziale
	life = 100;

	//caricamento modello villain
	/*villain_model = new Model();
	villain_model->loadModel("models/bot/boty.DAE");*/
	
	//creo ed inizializzo il path del villain
	percorso = new path(); 
	percorso->inizializzaPath(path_Matrix);

	//setto lo step corrente (relativo al path) del villain
	path_currentStep = 1;

	meshWalking.loadMesh("animation/villain/walking/Walking.dae");
	meshAttacking.loadMesh("animation/villain/attack/Zombie Punching.dae");
}


void villain::drawVillain(Shader animShader, glm::mat4 view){

	animShader.use();

	//projection
	glm::mat4 projection = glm::mat4(1.0f);	//identity matrix
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	animShader.setMat4("projection", projection);

	//view
	animShader.setMat4("view", view);

	//model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, 0.5f, z));
	model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	animShader.setMat4("model", model);

	vector <glm::mat4> transforms;

	if (villain_walking == true) {
		meshWalking.boneTransform(animationTime_villain, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshWalking.render();
	}
	else if (villain_walking == false) {
		meshAttacking.boneTransform(animationTime_villain, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshAttacking.render();
	}

}

void villain::animate() {

}

