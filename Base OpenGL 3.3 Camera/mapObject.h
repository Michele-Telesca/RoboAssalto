#pragma once
#include "weapon.h"
#include "model.h"

class mapObject { //potrebbe essere utilizzato anche per l'albero 

public:

	//coordinate
	float x;
	float y;
	float z;

	Model* mapObject_i;

	bool destroyed; //true se la roccia è distrutta
	
	mapObject(float px, float py, float pz) {
		x = px;
		y = py;
		z = pz;
	}

	void initMapObject(string path);
	void drawMapObject(Shader myShader, float scale);

};

void mapObject::initMapObject(string path) {

	//caricamento modello
	mapObject_i = new Model();
	mapObject_i->loadModel(path);

}

void mapObject::drawMapObject(Shader myShader, float scale) {

	myShader.setVec3("colorcube", 1.0f, 1.0f, 1.0f); //bianco (colore neutro)

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	myShader.setMat4("model", model);

	mapObject_i->Draw(myShader);
}

