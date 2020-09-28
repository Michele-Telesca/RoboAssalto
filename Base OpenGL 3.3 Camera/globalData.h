#pragma once

//GAME SETTINGS

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

float RENDER_SPEED = 0.03f; //Pi� � alto e pi� rallenta; pi� � basso e pi� velocizza

const int DIM = 40; //Dimensione floor 20x20
float TILE_DIM = 1.0; //Dimensione singola mattonella

float MOVE_STEP = TILE_DIM / 10; // = 0.125f; //Incremento dello spostamento del player 
float BOT_MOVE_STEP = TILE_DIM / 30; // = 0.05; //Incremento dello spostamento del BOT 

float EPSILON_1 = TILE_DIM / 100; // epsilon di collisione tra player e gameObject
float EPSILON_2 = BOT_MOVE_STEP / 10;
float EPSILON_3 = 0.25f; // epsilon di collisione tra player e bot

glm::vec3 lightPos(0.0f, 80.0f, 0.0f); //posizione luce

// ---- //
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
const int TREE5 = 12;
const int BUSH1 = 13;
const int BUSH2 = 14;
const int CHEST = 15;

const int PLAYER_STANDING = 0;
const int PLAYER_RUNNING = 1;

const int DIRECTION_RIGHT = 0;
const int DIRECTION_LEFT = 1;
const int DIRECTION_DOWN = 2;
const int DIRECTION_UP = 3;


// ---- Variabili ---- //
float animationTime_player = 0.0f; //contatore per le animazioni -> serve per gestire la verlocit� delle animazioni che incrementano in base alla velocit� di incremento della variabile
float animationTime_villain = 0.0f;

bool villain_walking = true;

//movimenti
bool muoviDx = false;
bool muoviSx = false;
bool muoviSu = false;
bool muoviGiu = false;
bool mouseSx = false;