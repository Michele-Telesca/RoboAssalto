#include "skinned_mesh.h"

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
#include <map>
#include "shader_s.h"
#include "camera.h"
#include "stb_image.h"

#include <gl/glu.h>

#include "update.h"
#include "updateAnimation.h"
#include "model.h"
#include "game.h"
#include "gameMap.h"
#include "cube.h"
#include "villain.h"
#include "player.h"
#include "playerShot.h"
#include "globalData.h"
#include "globalPathData.h"
#include "mainMenu.h"
#include "pauseMenu.h"

#include <irrKlang/irrKlang.h>

// dichiarazione oggetti
game* gameuno = new game();
mainMenu* main_menu = new mainMenu();
pauseMenu* pause_menu = new pauseMenu();

update* update_game = new update();
updateAnimation* update_animation = new updateAnimation();


//time
float timebase = 0;
double currentTime = 0.0f;
double previousTime = glfwGetTime();

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//vettore up della camera
glm::vec3 up(0.0, 1.0, 0.0);


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{	
	if (quit == true) {
		glfwSetWindowShouldClose(window, true);
	}

	//CALLBACK MENU
	if (!gameuno->inGame || gameuno->gamePause) {
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			if (!mouseSx) {
				mouseSx = true;
			}
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			if (mouseSx) {
				main_menu->buttonClicked = true;
				pause_menu->buttonClicked = true;
			}
			mouseSx = false;
		}
	}

	//CALLBACK GAME
	if (gameuno->inGame) {
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			mouseSx = true;
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			if (mouseSx) {
				startPlayerShot = true;
			}
			mouseSx = false;
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			if (buttonEsc == false) {
				buttonEsc = true;
				if (gameuno->gamePause == false) {
					cout << "metto in pausa" << endl;
					gameuno->gamePause = true;
				}
				else {
					cout << "tolgo la pausa" << endl;
					gameuno->gamePause = false;
				}
			}	
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
			buttonEsc = false;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			if (muoviSx != true) {
				muoviDx = true;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
			muoviDx = false;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			if (muoviDx != true) {
				muoviSx = true;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
			muoviSx = false;
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			if (muoviGiu != true) {
				muoviSu = true;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
			muoviSu = false;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			if (muoviSu != true) {
				muoviGiu = true;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
			muoviGiu = false;
		}
	}
}

void ray_plane(glm::vec3 plane_normal_word, glm::vec3 plane_pos_word, glm::vec3 ray_word, glm::vec3 origin, float dim_square) {

	float denom = dot(plane_normal_word, ray_word);
	if (abs(denom) > 0.0001f)
	{
		float t = dot((plane_pos_word - origin), plane_normal_word) / denom;
		glm::vec3 p = origin + t * ray_word; //calcolo del punto intersecato p

		if ((t >= 0.0f) && (p.z >= plane_pos_word.z - dim_square && p.z <= plane_pos_word.z + dim_square) && (p.x >= plane_pos_word.x - dim_square && p.x <= plane_pos_word.x + dim_square)) {

			//cout << "********************************* HITTATO: (" << p.x << ", " << p.y << ", " << p.z << ")" << endl;
			float player_xpos = gameuno->getPlayer()->getX(); //coordinata x del player
			float player_zpos = gameuno->getPlayer()->getZ(); //coordinata z del player
			//cout << "*** PLAYER Position (X,Z): (" << player_xpos << ", " << player_zpos << ")" << endl;
			//cout << "*** Mouse Position (X,Z): (" << p.x << ", " << p.z << ")" << endl;

			gameuno->setMousePoint(p);
			main_menu->setMousePoint(p);
			pause_menu->setMousePoint(p);
		}

	}

}

void mouse_position() {

	POINT cp;
	GetCursorPos(&cp);	//Projection e View

	glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	//glm::mat4 view_matrix = glm::lookAt(pos_camera_fissa, at_camera_fissa, up);
	glm::mat4 view_matrix = view_global;

	//Step 1: 3d Normalised Device Coordinates
	float x = (2.0f * cp.x) / (float)SCR_WIDTH - 1.0f;
	float y = 1.0f - (2.0f * cp.y) / (float)SCR_HEIGHT;
	float z = 1.0f;
	glm::vec3 ray_nds(x, y, z);

	//Step 2: 4d Homogeneous Clip Coordinates
	glm::vec4 ray_clip(ray_nds.x, ray_nds.y, -1.0, 1.0);

	//Step 3: 4d Eye (Camera) Coordinates
	glm::vec4 ray_eye = inverse(projection_matrix) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

	//Step 4: 4d World Coordinates
	glm::vec3 ray_word((inverse(view_matrix) * ray_eye).x, (inverse(view_matrix) * ray_eye).y, (inverse(view_matrix) * ray_eye).z);
	ray_word = glm::normalize(ray_word);

	glm::vec3 plane_normal_word(0.0f, 1.0f, 0.0f);
	glm::vec3 plane_pos_word(-0.75f, 1.0f, 0.75f);
	ray_plane(plane_normal_word, plane_pos_word, ray_word, pos_camera_mobile_global, DIM);

}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void renderGame(Shader simpleShader, Shader lightShader, Shader animShader) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	currentTime = glfwGetTime();
	double timeInterval = currentTime - previousTime;
	if (timeInterval >= RENDER_SPEED) {
	

		player* player = gameuno->getPlayer();
		vector <villain*> botList = gameuno->getSpawnedBotList();

		// ------- PLAYER MOVES ------- //

		if (muoviDx) {
			update_game->moveRight(player, botList);
		}

		if (muoviSx) {
			update_game->moveLeft(player, botList);
		}

		if (muoviSu) {
			update_game->moveUp(player, botList);
		}

		if (muoviGiu) {
			update_game->moveDown(player, botList);
		}
		if (mouseSx) {
			gameuno->getPlayer()->mouseSxIsSelected = true;
		}
		else {
			gameuno->getPlayer()->mouseSxIsSelected = false;
		}
		if (startPlayerShot) {
			gameuno->getPlayer()->startPlayerShot = true;
			startPlayerShot = false;
		}
		else {
			gameuno->getPlayer()->startPlayerShot = false;
		}

		update_game->calculateAnglePlayer(player); //player rotation

		// ------- MOUSE ------- //
		mouse_position();

		// -------- BOT -------- //
		gameuno->BOT_spawner();
		gameuno->kill_BOT();
		update_game->updateBot(botList, player, gameuno);

		// ------ POWERUP ------ //
		gameuno->powerUp_spawner();
		update_game->hitPowerUp(player, gameuno->power_up);

		// -------- SHOT ------- //
		update_game->updateShot(player->listShot, botList, player->wea, player);


		// ----- ANIMATION ----- //
		update_animation->updateAllAnimations(player, botList, gameuno->power_up);
		update_animation->gameSound(gameuno);

		// ------- SOUND ------- //
		previousTime = currentTime;
	}

	// ------- CAMERA ------- //
	float x = gameuno->getPlayer()->getX();
	float z = gameuno->getPlayer()->getZ();

	////dal basso
	//glm::vec3 pos_camera_mobile(x, 5.0f, z + 5.0);
	//glm::vec3 at_camera_mobile(x, 0.0f, z - 5.0f);

	//corretta
	glm::vec3 pos_camera_mobile(x, 12.0f, z + 10.0f);
	glm::vec3 at_camera_mobile(x, 0.0f, z);

	////dall alto
	//glm::vec3 pos_camera_mobile(x, 20.0f, z);
	//glm::vec3 at_camera_mobile(x, 0.0f, z - 1.0f);

	//view
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(pos_camera_mobile, at_camera_mobile, up);
	pos_camera_mobile_global = pos_camera_mobile;
	view_global = view;
	lightShader.setMat4("view", view);

	simpleShader.setMat4("view", view);

	// ------- DRAW ------- //
	gameuno->draw(simpleShader, lightShader, animShader, view);
}

void renderMainMenu(Shader simpleShader, Shader lightShader, Shader animShader) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	currentTime = glfwGetTime();
	double timeInterval = currentTime - previousTime;
	if (timeInterval >= RENDER_SPEED) {

		//setto a false la soundtrack del game
		if (gameuno->startGameSoundtrack == true) {
			update_animation->SoundEngine_soundtrack->stopAllSounds();
			gameuno->startGameSoundtrack = false;
		}

		// ------- MOUSE ------- //
		mouse_position();
		update_game->cursorMainMenu(main_menu); //update del cursore
		update_animation->increase_menuPlayer_posing(main_menu); //update delle animazioni dei player da selezionare
		update_animation->menuSound(main_menu);

		if (main_menu->startNewGame) { //il flag startNewGame è true (l'utente ha cliccato su play)
			gameuno->loadingGame->init(); //inizializzo la barra di caricamento 
			gameuno->loadingGame->isLoading = true; //setto il caricamento a true
			main_menu->startNewGame = false; //resetto il flag startNewGame
			
		}
		previousTime = currentTime;
	}

	main_menu->draw(simpleShader, lightShader, animShader);

}

void renderLoading(Shader simpleShader) {

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//setto a false la soundtrack del menu
	if (main_menu->startMenuSoundtrack == true) {
		update_animation->SoundEngine_soundtrack->stopAllSounds();
		main_menu->startMenuSoundtrack = false;
	}

	cout << "gameuno->loadingGame->statusLoading" << gameuno->loadingGame->statusLoading << endl;
	gameuno->loadingGame->draw(simpleShader, gameuno->loadingGame->statusLoading/13.2f); //draw della barra di caricamento

	if (gameuno->loadingGame->statusLoading == 100.0f) { //quando statusLoading ha raggiunto il 100%
		gameuno->loadingGame->isLoading = false;  //setto il loading completato
		gameuno->gamePause = false;				  //setto il flag gamePause a false
		gameuno->inGame = true;                   //setto il flag inGame a true
	}

}

void renderPauseMenu(Shader simpleShader, Shader lightShader) {
	glClearColor(0.2f, 0.3f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	currentTime = glfwGetTime();
	double timeInterval = currentTime - previousTime;
	if (timeInterval >= RENDER_SPEED) {

		// ------- MOUSE ------- //
		mouse_position();
		update_game->cursorPauseMenu(pause_menu, gameuno);

		previousTime = currentTime;
	}

	pause_menu->draw(simpleShader, lightShader);
}

// viene richiamata nel while e serve per disegnare gli oggetti creati nell'init, controllare lo stato degli oggetti e chiamare le fun di update dello stato
void render(Shader simpleShader, Shader lightShader, Shader animShader)
{

	if (!gameuno->inGame && !gameuno->loadingGame->isLoading) {
		renderMainMenu(simpleShader, lightShader, animShader);
	}
	else if (!gameuno->inGame && gameuno->loadingGame->isLoading && !gameuno->loadingGame->drawLoadingBar) {
		renderLoading(simpleShader);
		gameuno->loadingGame->drawLoadingBar = true;
	}
	else if (!gameuno->inGame && gameuno->loadingGame->isLoading && gameuno->loadingGame->drawLoadingBar) {
		renderLoading(simpleShader);
		gameuno->init(main_menu->selected_player, main_menu->selected_weapon);
		gameuno->loadingGame->drawLoadingBar = false;
		gameuno->loadingGame->statusLoading++;
	}
	else if (gameuno->inGame && !gameuno->loadingGame->isLoading && !gameuno->gamePause) {
		renderGame(simpleShader, lightShader, animShader);
	}
	else if (gameuno->inGame && !gameuno->loadingGame->isLoading && gameuno->gamePause) {
		renderPauseMenu(simpleShader, lightShader);
	}

}

// viene richiamata prima dell'inizio del while e server per inizializzare il game (vengono creati gli oggetti)
void init() {

	main_menu->init();
	pause_menu->init();

}

// load and create a texture 
unsigned int loadtexture(std::string filename, bool png)
{
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
																					// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		{
			if (nrChannels == 4) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
		}
	}
	else
	{
		std::cout << "Failed to load texture " << filename.c_str() << std::endl;
		return -1;
	}
	stbi_image_free(data);

	return texture;
}

int main()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

																											 // glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3.3 - Roboassalto", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// caricamento texture
	gameuno->getGameMap()->texturePrato = loadtexture("texture/background_menu.jpg", false);
	gameuno->getPlayer()->texture1 = loadtexture("texture/target.png", true);
	gameuno->getPlayer()->textureLife = loadtexture("texture/lifeBar.png", true);
	gameuno->getPlayer()->textureShotBar = loadtexture("texture/shotBar.png", true);
	gameuno->textureLifeBar = loadtexture("texture/lifeBar.png", true);
	gameuno->getPlayer()->textureShadow = loadtexture("texture/ombra.png", true);

	gameuno->loadingGame->texture_statusbar = loadtexture("texture/loadingBar.png", true);
	gameuno->loadingGame->texture_boundary = loadtexture("texture/texture_boundary.png", true);
	gameuno->loadingGame->texture_background = loadtexture("texture/background_menu.jpg", false);

	main_menu->texture_background = loadtexture("texture/background_menu.jpg", false);
	pause_menu->texture_background = loadtexture("texture/background_menu.jpg",false);

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(false);

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_STATIC_DRAW);
	glBindVertexArray(cubeVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	//glEnable(GL_DEPTH);

	//dichiarazione degli shader
	Shader simpleShader("vertex_simple.vs", "fragment_simple.fs");
	Shader lightShader("vertex_lights.vs", "fragment_lights.fs");
	Shader animationShader("vertex_anim_lights.vs", "fragment_anim_lights.fs");

	init();

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		render(simpleShader, lightShader, animationShader);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &cubeVBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}
