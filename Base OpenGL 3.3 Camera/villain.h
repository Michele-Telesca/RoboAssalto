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

	float rotationAngle; //angolo di rotazione corrente 

	// ---- variabili per gestire le rotazioni
	float angleToReach;  //angolo di rotazione che deve raggiungere quando effettua una rotazione
	bool sensoOrario;    //senso di rotazione 

	int old_direction; //Direzione da cui il bot arriva 
	float path_currentStep; //contatore dello step iesimo in cui si trova il bot 
	bool isOnPath; //true se è nella direzione (di rotazione) corretta del path -> viene setta a false quando il bot attacca, poichè cambia la rotazione verso il player

	int life; //vita del player aggiornata

	bool isDead;
	bool isAttacking;

	float chargingTime; //tempo di ricarica del colpo
	float timeLastShot; //tempo dell'ultimo colpo. serve per dare un tempo tra l'ultimo colpo e il prossimo

	// modelli 3D con scheletro e animazione
	SkinnedMesh meshWalking;
	SkinnedMesh meshAttacking;
	SkinnedMesh meshHit;
	SkinnedMesh meshDead;

	// booleani per le animazioni
	bool animation_botWalking;
	bool animation_botAttacking;
	bool animation_botHit;
	bool animation_botDead;

	// tempo per le animazioni
	float animationTime_botWalking;
	float animationTime_botAttacking;
	float animationTime_botHit;
	float animationTime_botDead;
	
	//weapon* weapon; //per avere la gittata del villain
	path* percorso;
	player* p;

	//Prototipi
	void drawVillain(Shader animShader, glm::mat4 view);			 //disegna il player
	void animate(Shader animShader);
	void initVillain(int path_Matrix[DIM][DIM]);					 //inializza il villain

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

	float getRotationAngle() {
		return rotationAngle;
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

	void setRotationAngle(float angle) {
		rotationAngle = angle;
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

	if (path_Matrix == path1_Matrix) {
		old_direction = START_DIRECTION_PATH1; //setto la direzione di movimento iniziale 
		rotationAngle = START_ROTATION_PATH1;  //setto la rotazione iniziale
	}
	else if (path_Matrix == path2_Matrix) {
		old_direction = START_DIRECTION_PATH2; //setto la direzione di movimento iniziale 
		rotationAngle = START_ROTATION_PATH2;  //setto la rotazione iniziale
	}
	else if (path_Matrix == path3_Matrix) {
		old_direction = START_DIRECTION_PATH3; //setto la direzione di movimento iniziale 
		rotationAngle = START_ROTATION_PATH3;  //setto la rotazione iniziale
	}
	else if (path_Matrix == path4_Matrix) {
		old_direction = START_DIRECTION_PATH4; //setto la direzione di movimento iniziale 
		rotationAngle = START_ROTATION_PATH4;  //setto la rotazione iniziale
	}
	else if (path_Matrix == path5_Matrix) {
		old_direction = START_DIRECTION_PATH5; //setto la direzione di movimento iniziale 
		rotationAngle = START_ROTATION_PATH5;  //setto la rotazione iniziale
	}
	else if (path_Matrix == path6_Matrix) {
		old_direction = START_DIRECTION_PATH6; //setto la direzione di movimento iniziale 
		rotationAngle = START_ROTATION_PATH6;  //setto la rotazione iniziale
	}
	else if (path_Matrix == path7_Matrix) {
		old_direction = START_DIRECTION_PATH7; //setto la direzione di movimento iniziale 
		rotationAngle = START_ROTATION_PATH7;  //setto la rotazione iniziale
	}
	else if (path_Matrix == path8_Matrix) {
		old_direction = START_DIRECTION_PATH8; //setto la direzione di movimento iniziale 
		rotationAngle = START_ROTATION_PATH8;  //setto la rotazione iniziale
	}
	else if (path_Matrix == path9_Matrix) {
		old_direction = START_DIRECTION_PATH9; //setto la direzione di movimento iniziale 
		rotationAngle = START_ROTATION_PATH9;  //setto la rotazione iniziale
	}
	else if (path_Matrix == path10_Matrix) {
		old_direction = START_DIRECTION_PATH10; //setto la direzione di movimento iniziale 
		rotationAngle = START_ROTATION_PATH10;  //setto la rotazione iniziale
	}

	angleToReach = rotationAngle;

	isOnPath = true;

	//vita iniziale
	life = 100;

	isDead = false;
	isAttacking = false;
	
	//creo ed inizializzo il path del villain
	percorso = new path(); 
	percorso->inizializzaPath(path_Matrix);

	//setto lo step corrente (relativo al path) del villain
	path_currentStep = 1;

	meshWalking.loadMesh("animation/villain/walking/Walking.dae");
	meshAttacking.loadMesh("animation/villain/attack/Zombie Punching.dae");
	meshHit.loadMesh("animation/villain/hit/Zombie Reaction Hit.dae");
	meshDead.loadMesh("animation/villain/dead/Zombie Death.dae");

	animation_botWalking = true;
	animation_botHit = false;
	animation_botDead = false;
	animation_botHit = false;

	animationTime_botWalking = 0.0f;
	animationTime_botAttacking = 0.0f;
	animationTime_botHit = 0.08f;
	animationTime_botDead = 0.0f;
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
	model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	animShader.setMat4("model", model);

	animate(animShader); //animazione
	
}

void villain::animate(Shader animShader) {

	vector <glm::mat4> transforms;

	if (animation_botWalking && !animation_botHit && !animation_botAttacking && !animationTime_botDead) {
		meshWalking.boneTransform(animationTime_botWalking, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshWalking.render();
	}
	else if (!animation_botWalking && animation_botAttacking && !animation_botHit && !animationTime_botDead) {
		meshAttacking.boneTransform(animationTime_botAttacking, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshAttacking.render();
	}
	else if (((animation_botHit && animation_botWalking) || (animation_botHit && animation_botAttacking)) && !animation_botDead ) {
		meshHit.boneTransform(animationTime_botHit, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshHit.render();
	}

	else if (animation_botDead) {
		meshDead.boneTransform(animationTime_botDead, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshDead.render();
	}

}

