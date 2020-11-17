#pragma once
//GAME SETTINGS

//global camera
glm::vec3 pos_camera_mobile_global(1.0f);
glm::mat4 view_global(1.0f);

bool quit = false;

// FOR FIRST
const int FIRST = 0;
// valore unitario
const float UNIT = 1.0f;
const float INIT_ZERO = 0.0f;
//PI
const float PI = 3.14f;
const float HALF_PI = 3.14f / 2.0F;
//camera parameters
const float UP_X = 0.0f;
const float UP_Y = 1.0f;
const float UP_Z = 0.0f;

const float PROJECTION_ANGLE_45 = 45.0f;

//time start 
const float TIMEBASE_START = 0.0f;
const double TIME_START = 0.0f;
const float DELTA_TIME_START = 0.0f;
const float LAST_FRAME_START = 0.0f;

//time utility
const int TIME_END_FIRST_INTRO = 15;
const int TIME_END_SECOND_INTRO = 20;
const int TIME_END_LAST_INTRO = 25;

//plane hit mouse
const float PLANE_NORMAL_X = 0.0f;
const float PLANE_NORMAL_Y = 1.0f;
const float PLANE_NORMAL_Z = 0.0f;

const float PLANE_POS_X = 0.75f;
const float PLANE_POS_Y = 1.0f;
const float PLANE_POS_Z = 0.75f;

//clear color parameters
const float COLOR_R = 0.2f;
const float COLOR_G = 0.3f;
const float COLOR_B = 0.3f;


//TEXTURE FONT
const int FIRST_NAMBER = 0;
const int LAST_NAMBER = 10;

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

//VERTEX ATTRIBUTES
const int STRIDE = 8;

float RENDER_SPEED = 0.03f; //Più è alto e più rallenta; più è basso e più velocizza

const int DIM = 40; //Dimensione floor 20x20
float TILE_DIM = 1.0; //Dimensione singola mattonella

float MOVE_STEP = TILE_DIM / 9; // = 0.1000f; //Incremento dello spostamento del player 
float BOT_MOVE_STEP = TILE_DIM / 30; // = 0.05; //Incremento dello spostamento del BOT 

float EPSILON_1 = MOVE_STEP/2; // epsilon di collisione tra player e gameObject
float EPSILON_2 = BOT_MOVE_STEP / 100;
float EPSILON_3 = 0.25f; // epsilon di collisione tra player e bot

// -- CAMERA -- //
glm::vec3 lightPos(0.0f, 25.0f, 0.0f); //posizione luce
//glm::vec3 lightPos(0.0f, -UNIT, 0.0f); //DIREZIONE luce
const float MOBILE_CAMERA_OFFSET_Y = 12.0f;
const float MOBILE_CAMERA_OFFSET_Z = 10.0f;
const float MOBILE_CAMERA_AT_Y = 0.0f;


// -- PLAYER -- //
const int PLAYER_MICHELLE = 1;
const int PLAYER_BRYCE = 2;

const float MIN_LIFE_PLAYER = 0.0f;
const float MIN_LIFE_CHEST = 0.0f;

const float PLAYER_SPOW_X = 0.0f;
const float PLAYER_SPOW_Y = 0.5f;
const float PLAYER_SPOW_Z = 0.0f;
const float CHARGING_TIME = 5.0f;


const int MAX_SHOT_AVAILABLE = 3;
const int MIN_SHOT_AVAILABLE = 0;

const float ANGLE_PLAYER_ROTATE = 90.0f;

const float ANGLE_0 = 0.0f;
const float ANGLE_180 = 180.0f;
const float ANGLE_360 = 360.0f;
const float ANGLE_270 = 270.0f;
const float ANGLE_45 = 45.0f;
const float ANGLE_135 = 135.0f;
const float ANGLE_225 = 225.0f;
const float ANGLE_315 = 315.0f;





const float ANGLE_90 = 90.0f;

const float ANGLE_OFFSET = 15.0f;

const float SHADOW_OFFSET_Y_PLAYER = 0.02f;
const float SHADOW_SCALE_PLAYER = 1.4f;

const float OFFSET_SHOT_BAR = 2.22f;
const float SCALE_OFFSET_SHOT_BAR = 0.03f;
const float SCALE_SHOT_BAR_Y = 0.01f;
const float SCALE_SHOT_BAR_Z = 0.10f;

const float OFFSET_POSITION_LIFEBAR = 2.4f;
const float SCALE_LIFEBARZ = 0.15f;

const float OFFSET_Y_CHESTlIFE_BAR = 1.5f;


// -- MAPOBJECT -- //
const int STONE1 = 1;
const int STONE2 = 2;
const int STONE3 = 3;
const int STONE4 = 4;
const int STONE5 = 5;
const int STONE6 = 6;
const int STONE7 = 7;
const int TREE1 = 8;
const int TREE2 = 9;
const int TREE3 = 10;
const int TREE4 = 11;
const int GRASS = 12;
const int BUSH1 = 13;
const int BUSH2 = 14;
const int FENCE = 15;
const int CHEST = 16;

// -- DIREZIONI bot (riferimenti per i path) -- //
const int DIRECTION_RIGHT = 0;
const int DIRECTION_LEFT = 1;
const int DIRECTION_DOWN = 2;
const int DIRECTION_UP = 3;

const int ZOMBIE_PRISONER = 1;
const int ZOMBIE_DERRICK = 2;
const int ZOMBIE_COP = 3;

// -- SPECULAR VALUE -- //
const int HIGH = 2;
const int MODERATE = 1;
const int NONE = 0;

// -- SHOT, WEAPON, POWERUP -- //
const int numShot = 3; //numero proiettili
const float SHOT_SPEED = 4.0f; //velocità proiettili
const float SHOT_DIM2 = 0.03; //dimensione x,z del proiettile
const float SHOT_DIM = 0.20; //dimensione x,z del proiettile

bool startPlayerShot = false;

float DELAY_SHOTGUN = 1.1f; //secondi per l'ejectingBullet SHOTGUN
float DELAY_SNIPER = 2.0f; //secondi per l'ejectingBullet SNIPER

const int WEAPON_SHOTGUN = 1;
const float LENGTH_RANGE_SHOTGUN = 3.0f; //lunghezza di mira
const float LENGTH_BASE_SHOTGUN = 2.0f;
const float ANGLE_RANGE_SHOTGUN = 90.0f;

const int WEAPON_SNIPER = 2;
const float LENGTH_RANGE_SNIPER = 9.0f; //lunghezza di mira
const float LENGTH_BASE_SNIPER = 1.0f;
const float ANGLE_RANGE_SNIPER = 90.0f;

const int MEDIKIT = 3;

// -- KEYBOARD/MOUSE BUTTON -- //
bool moveDx = false;
bool muoviSx = false;
bool muoviSu = false;
bool muoviGiu = false;

bool mouseSx = false;
bool buttonEsc = false;

// -- LIFE and DAMAGE -- //
const float PLAYER_LIFE = 100.0f;
const float CHEST_LIFE = 250.0f;
const float MEDIKIT_HEAL = 50.0f;

const float SNIPER_DAMAGE = 50.0f;
const float SHOTGUN_DAMAGE = 130.0f;

const float ZOMBIE_PRISONER_LIFE = 100.0f;
const float ZOMBIE_PRISONER_DAMAGE = 15.0f;

const float ZOMBIE_DERRICK_LIFE = 200.0f;
const float ZOMBIE_DERRICK_DAMAGE = 25.0f;

const float ZOMBIE_COP_LIFE = 300.0f;
const float ZOMBIE_COP_DAMAGE = 50.0f;


const int FIRST_INTRO = 1;
const int SECOND_INTRO = 2;
const int LAST_INTRO = 3;



//GAME PARAMETERS
const int INITIAL_SCORE = 0.0f;

const int STATUS_LOADING_0 = 0;
const int STATUS_LOADING_1 = 15;
const int STATUS_LOADING_2 = 50;
const int STATUS_LOADING_3 = 60;
const int STATUS_LOADING_4 = 80;
const int STATUS_LOADING_5 = 90;


const int FINAL_DIFFICULTY = 6;
const int START_DIFFICULTY = 0;

const float SCALE_SCORE_X = 2.5f;
const float SCALE_SCORE_Y = 0.1f;
const float SCALE_SCORE_Z = 2.5f;
const float OFFSET_Y_SCORE = 3.0f;
const float OFFSET_Z_SCORE = 5.0f;

const float OFFSET_TEN_X = 1.8f;
const float OFFSET_TEN_Y = 3.0f;
const float OFFSET_TEN_Z = 5.0f;
const float SCALE_TEN_X = 0.7f;
const float SCALE_TEN_Y = 0.1f;
const float SCALE_TEN_Z = 0.7F;
const float OFFSET_UNIT_X = 2.5f;

 