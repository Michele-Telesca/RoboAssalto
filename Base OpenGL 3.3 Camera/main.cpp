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

#include "model.h"
#include "game.h"
#include "gameMap.h"
#include "cube.h"
#include "update.h"

// dichiarazione oggetti
game* gameuno = new game();

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

//time
float timebase = 0;

double currentTime = 0.0f;
double previousTime = glfwGetTime();

//movimenti
bool muoviDx = false;
bool muoviSx = false;
bool muoviSu = false;
bool muoviGiu = false;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// vettori per la direzione della camera
glm::vec3 pos(0.0, 10.0, 0.0);
//glm::vec3 pos(0.0, 10.0, 5.0);		// Posizione camera
glm::vec3 at(0.0, 0.0, -1.0);		
//glm::vec3 at(0.0, 0.0, -10.0);		// Punto in cui "guarda" la camera
glm::vec3 up(0.0, 1.0, 0.0);		// Vettore up...la camera � sempre parallela al piano

glm::vec3 dir(0.0, 0.0, -0.1);		// Direzione dello sguardo
glm::vec3 side(1.0, 0.0, 0.0);		// Direzione spostamento laterale
glm::vec3 lightPos(0.0f, 15.0f, 0.0f);

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		muoviDx = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
		muoviDx = false;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		muoviSx = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
		muoviSx = false;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		muoviSu = true;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
		muoviSu = false;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		muoviGiu = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
		muoviGiu = false;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

	float player_xpos = gameuno->getPlayer()->getX(); //coordinata x del player
	float player_zpos = gameuno->getPlayer()->getZ(); //coordinata z del player
	//cout << "*** PLAYER Position (X,Z): (" << player_xpos << ", " << player_zpos << ")" << endl;

	//cout << "*** MOUSE - SCREEN Position (X,Z): (" << xpos << ", " << ypos << ")" << endl;

	///// --- Metodo 1 ---///

	// NORMALISED DEVICE SPACE
	double xpos_norm = 2.0 * xpos / SCR_WIDTH - 1.0f;
	double ypos_norm = 2.0 * ypos / SCR_HEIGHT - 1.0f;

	//Inizializzazione di projection, view e model
	glm::mat4 projection = glm::mat4(1.0f);	//identity matrix
	glm::mat4 view = glm::mat4(1.0f); //identity matrix
	glm::mat4 model = glm::mat4(1.0f);	//identity matrix
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = glm::lookAt({ 0.0f, 10.f, 0.0f }, { 0.0f, 0.0f, -1.0f }, up);

	// HOMOGENEOUS SPACE
	glm::vec4 screenPos = glm::vec4(xpos_norm, -ypos_norm, -1.0f, 1.0f);

	// Projection/Eye Space
	glm::mat4 invVP = glm::inverse(projection * view);
	glm::vec4 worldPos = invVP * screenPos;

	//glm::vec3 dir = glm::normalize(glm::vec3(worldPos));

	//cout << "*** MOUSE - WORLD Position (X,Z): (" << worldPos.x * 10 << ", " << worldPos.z * 10 << ")" << endl;

	///// -------------- ///

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// viene richiamata nel while e serve per disegnare gli oggetti creati nell'init, controllare lo stato degli oggetti e chiamare le fun di update dello stato
void render(Shader lightShader)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	currentTime = glfwGetTime();
	double timeInterval = currentTime - previousTime;
	if (timeInterval >= RENDER_SPEED) {

		if (muoviDx) {
			gameuno->getPlayer()->moveDx();
		}

		if (muoviSx) {
			gameuno->getPlayer()->moveSx();
		}

		if (muoviSu) {
			gameuno->getPlayer()->moveUp();
		}

		if (muoviGiu) {
			gameuno->getPlayer()->moveDown();
		}

		previousTime = currentTime;

	}

	//camera
	float x = gameuno->getPlayer()->getX();
	float z = gameuno->getPlayer()->getZ();

	//dal basso
	glm::vec3 pos_player(x, 10.0f, z + 5.0);
	glm::vec3 at_player(x, 0.0f, z - 5.0f);

	////terza persona
	//glm::vec3 pos_player(x, 0.8f, z - 9.0f);
	//glm::vec3 at_player(x, 0.5f, z - 1.0f);
	
	////dall alto
	//glm::vec3 pos_player(x, 30.0f, z);
	//glm::vec3 at_player(x, 0.0f, z - 1.0f);

	////prima persona
	//glm::vec3 pos_player(x, 0.8f, z);
	//glm::vec3 at_player(x, 0.5f, z - 1.0f);

	glm::mat4 view = glm::mat4(1.0f); //identity matrix
	view = glm::lookAt(pos_player, at_player, up);
	lightShader.setMat4("view", view);

	gameuno->draw(lightShader);

}

// viene richiamata prima dell'inizio del while e server per inizializzare il game (vengono creati gli oggetti)
void init() {

	gameuno->inizializza();

}

// load and create a texture 
unsigned int loadtexture(std::string filename)
{
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
																					// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
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
	glfwSetCursorPosCallback(window, mouse_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_BLEND);

	// caricamento texture
	gameuno->getGameMap()->texturePrato = loadtexture("texture/prato1.png");
	
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

	glEnable(GL_DEPTH_TEST);

	//dichiarazione degli shader
	Shader myShader("vertex_shader.vs", "fragment_shader.fs");
	Shader lightShader("vertex_shader_lights.vs", "fragment_shader_lights.fs");
	lightShader.use();

	//projection
	glm::mat4 projection = glm::mat4(1.0f);	//identity matrix
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	lightShader.setMat4("projection", projection);

	// ??
	//lightShader.setVec3("viewPos", camera.Position);

	// light properties
	lightShader.setVec3("light.position", lightPos);
	lightShader.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
	lightShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	lightShader.setVec3("light.specular", 0.5f, 0.5f, 0.5f);

	init();

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		render(lightShader);

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


