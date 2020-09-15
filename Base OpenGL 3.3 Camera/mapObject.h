#pragma once
#include "weapon.h"
#include "model.h"

class mapObject { //potrebbe essere utilizzato anche per l'albero 

public:

	//coordinate
	float x;
	float y;
	float z;
	float scale;
	float angle;
	float rotate_x;
	float rotate_y;
	float rotate_z;

	Model* mapObject_i;

	bool destroyed; //true se la roccia è distrutta
	
	mapObject(float px, float py, float pz, float s, float a, float r_x, float r_y, float r_z) {
		x = px;
		y = py;
		z = pz;
		scale = s;
		angle = a;
		rotate_x = r_x;
		rotate_y = r_y;
		rotate_z = r_z;
	}

	void initMapObject(string path);
	void drawMapObject(Shader myShader);

	void setX(float new_x) {
		x = new_x;
	}

	void setZ(float new_z) {
		z = new_z;
	}

};

void mapObject::initMapObject(string path) {

	//caricamento modello
	mapObject_i = new Model();
	mapObject_i->loadModel(path);

}

void mapObject::drawMapObject(Shader lightShader) {

	// material properties
	lightShader.setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
	lightShader.setFloat("material.shininess", 76.8f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::rotate(model, angle, glm::vec3(rotate_x, rotate_y, rotate_z));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	lightShader.setMat4("model", model);

	mapObject_i->Draw(lightShader);
}

