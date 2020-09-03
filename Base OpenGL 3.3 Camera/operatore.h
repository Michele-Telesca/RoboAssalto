#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cstring>
#include <string>
#include <stack>
#include "shader_s.h"
#include "camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include <vector> 

unsigned int cubeVBO, cubeVAO;

Shader* myShader;

float verticesCube[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

class operatore {

private:

	float dimensione;

	float angle;
	float rotation_x;
	float rotation_y;
	float rotation_z;

	float posizione_x;
	float posizione_y;
	float posizione_z;

	Shader* myShader;

public:

	//Costruttore no arg

	operatore() { }

	//Costruttore con argomenti
	operatore(float d,
		float a, float r_x, float r_y, float r_z,
		float p_x, float p_y, float p_z,
		Shader* shader)
	{

		dimensione = d;

		angle = a;
		rotation_x = r_x;
		rotation_y = r_x;
		rotation_z = r_x;

		posizione_x = p_x;
		posizione_y = p_y;
		posizione_z = p_z;

		myShader = shader;

	}


	void drawCube() {

		//// light properties
		//myShader->setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
		//myShader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		//myShader->setVec3("light.specular", 0.5f, 0.5f, 0.5f);

		glm::mat4 model = glm::mat4(1.0f);	//identity matrix
		model = glm::translate(model, glm::vec3(posizione_x, posizione_y, posizione_z));
		model = glm::rotate(model, angle, glm::vec3(rotation_x, rotation_y, rotation_z));
		model = glm::scale(model, glm::vec3(dimensione, dimensione, dimensione));
		myShader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

	}

	void setShader(Shader* s) {
		myShader = s;
	}

	void setDimensione(float d) {
		dimensione = d;
	}

	void setRotation_x(float x) {
		rotation_x = x;
	}

	void setRotation_y(float y) {
		rotation_y = y;
	}

	void setRotation_z(float z) {
		rotation_z = z;
	}

	void setX(float x) {
		posizione_x = x;
	}

	void setY(float y) {
		posizione_y = y;
	}

	void setZ(float z) {
		posizione_z = z;
	}

	float getX() {
		return posizione_x;
	}

	float getY() {
		return posizione_y;
	}

	float getZ() {
		return posizione_z;
	}

	float getAngle() {
		return angle;
	}

	void setAngle(float a) {
		angle = a;
	}


};

