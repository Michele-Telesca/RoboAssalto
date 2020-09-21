#pragma once

//GAME SETTINGS
<<<<<<< HEAD
float RENDER_SPEED = 0.03f; //Più è alto e più rallenta; più è basso e più velocizza
const int DIM = 40; //Dimensione floor 20x20
float TILE_DIM = 1.0; //Dimensione singola mattonella
float MOVE_STEP = TILE_DIM / 8; // = 0.125f; //Incremento dello spostamento del player
=======
float RENDER_SPEED = 0.04f; //Più è alto e più rallenta; più è basso e più velocizza

const int DIM = 20; //Dimensione floor 20x20
float TILE_DIM = 1.0f; //Dimensione singola mattonella

float MOVE_STEP = TILE_DIM / 8; // = 0.125f -> Incremento dello spostamento del player 
float EPSILON_1 = TILE_DIM / 100;

float BOT_MOVE_STEP = TILE_DIM / 10; // = 0.1 -> Incremento dello spostamento del BOT 
float EPSILON_2 = TILE_DIM / 100;
>>>>>>> origin/Giuseppe

// ---- //
const int BUSH1 = 1;
const int BUSH2 = 2;
const int STONE1 = 3;
const int STONE2 = 4;
const int STONE3 = 5;
const int STONE4 = 6;
const int TREE1 = 7;
const int TREE2 = 8;
const int TREE3 = 9;
const int TREE4 = 10;
const int TREE5 = 11;

