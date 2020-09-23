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

#include "model.h"
#include "game.h"
#include "gameMap.h"
#include "cube.h"
#include "update.h"
#include "villain.h"
#include "globalPathData.h"

// dichiarazione oggetti
game* gameuno = new game();

glm::vec3 pos_camera_mobile_global(1.0f);
glm::mat4 view_global(1.0f);

//time
float timebase = 0;
double currentTime = 0.0f;
double previousTime = glfwGetTime();

bool spawnBot = true;

//movimenti
bool muoviDx = false;
bool muoviSx = false;
bool muoviSu = false;
bool muoviGiu = false;
bool mouseSx = false;


// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//vettore up della camera
glm::vec3 up(0.0, 1.0, 0.0);

//posizione luce
glm::vec3 lightPos(0.0f, 80.0f, 0.0f);

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		mouseSx = true;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		mouseSx = false;
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
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

void ray_plane(glm::vec3 plane_normal_word, glm::vec3 plane_pos_word, glm::vec3 ray_word, glm::vec3 origin, float dim_square) {

	float denom = dot(plane_normal_word, ray_word);
	if (abs(denom) > 0.0001f)
	{
		float t = dot((plane_pos_word - origin), plane_normal_word) / denom;
		glm::vec3 p = origin + t * ray_word; //calcolo del punto intersecato p

		if ((t >= 0.0f) && (p.z >= plane_pos_word.z - dim_square / 2 && p.z <= plane_pos_word.z + dim_square / 2) && (p.x >= plane_pos_word.x - dim_square / 2 && p.x <= plane_pos_word.x + dim_square / 2)) {

			//cout << "********************************* HITTATO: (" << p.x << ", " << p.y << ", " << p.z << ")" << endl;
			float player_xpos = gameuno->getPlayer()->getX(); //coordinata x del player
			float player_zpos = gameuno->getPlayer()->getZ(); //coordinata z del player
			//cout << "*** PLAYER Position (X,Z): (" << player_xpos << ", " << player_zpos << ")" << endl;
			//cout << "*** Mouse Position (X,Z): (" << p.x << ", " << p.z << ")" << endl;

			gameuno->setMousePoint(p);
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


// viene richiamata nel while e serve per disegnare gli oggetti creati nell'init, controllare lo stato degli oggetti e chiamare le fun di update dello stato
void render(Shader lightShader)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	currentTime = glfwGetTime();
	double timeInterval = currentTime - previousTime;
	if (timeInterval >= RENDER_SPEED) {

		// ------- PLAYER MOVES ------- //
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
		if (mouseSx) {
			gameuno->getPlayer()->mouseSxIsSelected = true;
		}
		else {
			gameuno->getPlayer()->mouseSxIsSelected = false;
		}

		// ------- MOUSE ------- //
		mouse_position();

		// ------- BOT ------- //
		if (spawnBot == true) {
			gameuno->spawn_BOT(path1_Matrix);
			gameuno->spawn_BOT(path2_Matrix);
			gameuno->spawn_BOT(path3_Matrix);
			gameuno->spawn_BOT(path4_Matrix);
			gameuno->spawn_BOT(path5_Matrix);
			gameuno->spawn_BOT(path6_Matrix);
			gameuno->spawn_BOT(path7_Matrix);
			gameuno->spawn_BOT(path8_Matrix);
			gameuno->spawn_BOT(path9_Matrix);
			gameuno->spawn_BOT(path10_Matrix);

			spawnBot = false;
		}
		gameuno->moveAllBots();

		
		previousTime = currentTime;
	}

	// ------- CAMERA ------- //
	float x = gameuno->getPlayer()->getX();
	float z = gameuno->getPlayer()->getZ();

	////dal basso
	//glm::vec3 pos_camera_mobile(x, 10.0f, z + 5.0);
	//glm::vec3 at_camera_mobile(x, 0.0f, z - 5.0f);

	////corretta
	//glm::vec3 pos_camera_mobile(x, 12.0f, z + 10.0);
	//glm::vec3 at_camera_mobile(x, 0.0f, z );

	////dal basso
	//glm::vec3 pos_camera_mobile(x, 12.0f, z + 3.0);
	//glm::vec3 at_camera_mobile(x, 0.0f, z - 3.0f);

	////terza persona
	//glm::vec3 pos_player(x, 0.8f, z - 9.0f);
	//glm::vec3 at_camera_mobile(x, 0.5f, z - 1.0f);

	//dall alto
	glm::vec3 pos_camera_mobile(x, 60.0f, z);
	glm::vec3 at_camera_mobile(x, 0.0f, z - 1.0f);

	////prima persona
	//glm::vec3 pos_camera_mobile(x, 0.8f, z);
	//glm::vec3 at_camera_mobile(x, 0.5f, z - 1.0f);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(pos_camera_mobile, at_camera_mobile, up);
	pos_camera_mobile_global = pos_camera_mobile;
	view_global = view;
	lightShader.setMat4("view", view);

	// ------- DRAW ------- //
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
	//glfwSetCursorPosCallback(window, mouse_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_BLEND);

	// caricamento texture
	gameuno->getGameMap()->texturePrato = loadtexture("texture/prato1.png");
	//gameuno->getGameMap()->texturePrato = loadtexture("texture/unibas.jpg");
	gameuno->getPlayer()->texturePlayer = loadtexture("texture/target.png");


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

	//glEnable(GL_DEPTH);

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
