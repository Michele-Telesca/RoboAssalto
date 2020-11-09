#pragma once
#include "button.h"
#include "model.h"
#include "skinned_mesh.h"
#include "globalData.h"
#include <irrKlang/irrKlang.h>

class mainMenu
{
	public:

		mainMenu() {}

		cube* background;
		unsigned int texture_background;

		button* button_NewGame;
		button* button_Right;
		button* button_Left;

		SkinnedMesh player_bryce;
		float animationTime_brycePosing;
		bool animation_brycePosing;

		SkinnedMesh player_michelle;
		float animationTime_michellePosing;
		bool animation_michellePosing;

		Model* shotgun;
		Model* sniper;
		
		Model* boundary_shotgun_unselected;
		Model* boundary_sniper_unselected;
		Model* boundary_shotgun_selected;
		Model* boundary_sniper_selected;

		glm::vec3 mousePoint;

		bool startNewGame; //quando è true starta il game

		int selected_player; //PLAYER_MICHELLE = 1 //PLAYER_BRYCE = 2;
		int selected_weapon; //WEAPON_SHOTGUN = 1 //WEAPON_SNIPER = 2;

		bool buttonClicked; //true quando l'utente clicca su un bottone del meu

		bool startMenuSoundtrack;  //quando è true si attiva la soundtrack del menu

		void init();
		void setShadersProperties(Shader simpleShader, Shader lightShader, Shader animShader);
		void draw(Shader simpleShader, Shader lightShader, Shader animShader);

		void setMousePoint(glm::vec3 w) {
			mousePoint = w;
		}

		glm::vec3 getMousePoint() {
			return mousePoint;
		}
};

void mainMenu::setShadersProperties(Shader simpleShader, Shader lightShader, Shader animShader) {
	
	//camera pos
	glm::vec3 pos_camera(0.0f, 12.0f, 1.0f);
	glm::vec3 at_camera(0.0f, 0.0f, 0.0f);
	pos_camera_mobile_global = pos_camera;
	glm::vec3 up(0.0, 1.0, 0.0);

	// ---- ANIMATION Shader ---- //
	animShader.use();

	//projection
	glm::mat4 projection_animation = glm::mat4(1.0f);	//identity matrix
	projection_animation = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	animShader.setMat4("projection", projection_animation);

	//view
	glm::mat4 view_animation = glm::mat4(1.0f);
	view_animation = glm::lookAt(pos_camera, at_camera, up);
	view_global = view_animation;
	animShader.setMat4("view", view_animation);

	//light properties
	animShader.setVec3("light.position", lightPos);
	animShader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
	animShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
	animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	// ---- SIMPLE Shader ---- //
	simpleShader.use();

	//view
	glm::mat4 view2 = glm::mat4(1.0f);
	view2 = glm::lookAt(pos_camera, at_camera, up);
	view_global = view2;
	simpleShader.setMat4("view", view2);

	//projection
	glm::mat4 projection2 = glm::mat4(1.0f);	//identity matrix
	projection2 = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	simpleShader.setMat4("projection", projection2);

	// ---- LIGHT Shader ---- //
	lightShader.use();

	//projection
	glm::mat4 projection3 = glm::mat4(1.0f);	//identity matrix
	projection3 = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	lightShader.setMat4("projection", projection3);

	//view
	glm::mat4 view3 = glm::mat4(1.0f);
	view3 = glm::lookAt(pos_camera, at_camera, up);
	view_global = view3;
	lightShader.setMat4("view", view3);

	//light per la mappa
	lightShader.setVec3("light.position", lightPos);
	lightShader.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
	lightShader.setVec3("light.diffuse", 0.7f, 0.7f, 0.7f);
	lightShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
}

void mainMenu::init() {

	startMenuSoundtrack = false;
	startNewGame = false;
	buttonClicked = false;
	selected_player = PLAYER_BRYCE;
	selected_weapon = WEAPON_SHOTGUN;

	button_NewGame = new button(3.5f, 1.0f, 2.58f, 0.3f, glm::radians(-85.1f), 1.0f, 0.0f, 0.0f);
	button_NewGame->init("models/menu/button_play.dae");

	button_Left = new button(-2.5f, 1.0f, -1.2f, 0.3f, glm::radians(-85.1f), 1.0f, 0.0f, 0.0f);
	button_Left->init("models/menu/button_left.dae");

	button_Right = new button(2.5f, 1.0f, -1.2f, 0.3f, glm::radians(-85.1f), 1.0f, 0.0f, 0.0f);
	button_Right->init("models/menu/button_right.dae");

	background = new cube(18.0f, 0.0f, 18.0f, glm::radians(4.9f), 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	player_bryce.loadMesh("animation/player_bryce/menu_posing/Listening To Music.dae");
	animationTime_brycePosing = 1.0f;
	animation_brycePosing = true;

	player_michelle.loadMesh("animation/player_michelle/menu_posing/Dwarf Idle.dae");
	animationTime_michellePosing = 0.0f;
	animation_michellePosing = false;

	shotgun = new Model();
	shotgun->loadModel("models/menu/shotgun/shotgun.dae");

	sniper = new Model();
	sniper->loadModel("models/menu/sniper/l96.dae");

	boundary_sniper_unselected = new Model();
	boundary_sniper_unselected->loadModel("models/menu/boundary_weapon_unselected.dae");
	boundary_shotgun_unselected = boundary_sniper_unselected;

	boundary_sniper_selected = new Model();
	boundary_sniper_selected->loadModel("models/menu/boundary_weapon_selected.dae");
	boundary_shotgun_selected = boundary_sniper_selected;

}

void mainMenu::draw(Shader simpleShader, Shader lightShader, Shader animShader) {
	
	setShadersProperties(simpleShader, lightShader, animShader);

	button_NewGame->drawButton(lightShader);
	button_Left->drawButton(lightShader);
	button_Right->drawButton(lightShader);
	background->drawCube(simpleShader, texture_background);

	if (selected_weapon == WEAPON_SNIPER) {
		glm::mat4 model_boun_sniper = glm::mat4(1.0f);
		model_boun_sniper = glm::translate(model_boun_sniper, glm::vec3(0.0f, 1.0f, 3.0f));
		model_boun_sniper = glm::rotate(model_boun_sniper, glm::radians(-86.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model_boun_sniper = glm::scale(model_boun_sniper, glm::vec3(0.38f, 0.38f, 0.38f));
		simpleShader.setMat4("model", model_boun_sniper);
		boundary_sniper_selected->Draw(simpleShader);

		glm::mat4 model_boun_shotgun = glm::mat4(1.0f);
		model_boun_shotgun = glm::translate(model_boun_shotgun, glm::vec3(-4.0f, 1.0f, 3.0f));
		model_boun_shotgun = glm::rotate(model_boun_shotgun, glm::radians(-85.25f), glm::vec3(1.0f, 0.0f, 0.0f));
		model_boun_shotgun = glm::scale(model_boun_shotgun, glm::vec3(0.38f, 0.38f, 0.38f));
		simpleShader.setMat4("model", model_boun_shotgun);
		boundary_shotgun_unselected->Draw(simpleShader);
	}
	else if(selected_weapon == WEAPON_SHOTGUN){
		glm::mat4 model_boun_shotgun = glm::mat4(1.0f);
		model_boun_shotgun = glm::translate(model_boun_shotgun, glm::vec3(-4.0f, 1.0f, 3.0f));
		model_boun_shotgun = glm::rotate(model_boun_shotgun, glm::radians(-85.25f), glm::vec3(1.0f, 0.0f, 0.0f));
		model_boun_shotgun = glm::scale(model_boun_shotgun, glm::vec3(0.38f, 0.38f, 0.38f));
		simpleShader.setMat4("model", model_boun_shotgun);
		boundary_shotgun_selected->Draw(simpleShader);

		glm::mat4 model_boun_sniper = glm::mat4(1.0f);
		model_boun_sniper = glm::translate(model_boun_sniper, glm::vec3(0.0f, 1.0f, 3.0f));
		model_boun_sniper = glm::rotate(model_boun_sniper, glm::radians(-86.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model_boun_sniper = glm::scale(model_boun_sniper, glm::vec3(0.38f, 0.38f, 0.38f));
		simpleShader.setMat4("model", model_boun_sniper);
		boundary_sniper_unselected->Draw(simpleShader);
	}



	lightShader.use();

	glm::mat4 model_shotgun = glm::mat4(1.0f);
	model_shotgun = glm::translate(model_shotgun, glm::vec3(-4.0f, 1.0f, 3.0f));
	model_shotgun = glm::rotate(model_shotgun, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model_shotgun = glm::scale(model_shotgun, glm::vec3(0.04f, 0.04f, 0.04f)); //bullet scale
	lightShader.setMat4("model", model_shotgun);
	lightShader.setVec3("colormodel", 1.0f, 1.0f, 1.0f);
	shotgun->Draw(lightShader);

	glm::mat4 model_sniper = glm::mat4(1.0f);
	model_sniper = glm::translate(model_sniper, glm::vec3(0.0f, 1.0f, 3.0f));
	model_sniper = glm::rotate(model_sniper, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model_sniper = glm::scale(model_sniper, glm::vec3(0.125f, 0.125f, 0.125f)); //bullet scale
	lightShader.setMat4("model", model_sniper);
	lightShader.setVec3("colormodel", 1.0f, 1.0f, 1.0f);
	sniper->Draw(lightShader); 



	animShader.use();

	//model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //per metterlo in posizione verticale sul pavimento
	model = glm::scale(model, glm::vec3(0.015f, 0.015f, 0.015f));
	animShader.setMat4("model", model);

	//material properties
	animShader.setVec3("material.ambient", 0.9f, 0.9f, 0.9f);
	animShader.setVec3("material.diffuse", 0.8f, 0.8f, 0.8f);
	animShader.setVec3("material.specular", 0.1f, 0.1f, 0.1f);
	animShader.setFloat("material.shininess", 76.8f);

	if (selected_player == PLAYER_BRYCE) {
		vector <glm::mat4> transforms;

		player_bryce.boneTransform(animationTime_brycePosing, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		player_bryce.render();
	}
	else if (selected_player == PLAYER_MICHELLE) {
		vector <glm::mat4> transforms;

		player_michelle.boneTransform(animationTime_michellePosing, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		player_michelle.render();
	}




}

