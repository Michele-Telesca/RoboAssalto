#pragma once
#include "point3D.h"
#include "weapon.h"
#include "model.h"
#include "globalData.h"
#include "globalPathData.h"
#include <vector>


class path
{

public:

	//costruttore
	path() {}

	//proprietà
	map <int, glm::vec2> path_map; //Mappa per gestire il path del bot -> Viene inizializzata scansionando la matrice
								   //la chiave è un intero che rappresenta lo step del path, a cui corrispondono le rispettive coordinate x,z (vec2) 
	
	int path_EndPath;			   //Valore di default dell'ultimo step del path
	int path_StartDirectionBot;    //Indica al bot la direzione iniziale del path
	float path_startRotationBot;   //Indica al bot la rotazione iniziale


	//prototipi
	void inizializzaPath(int path_M[DIM][DIM]);

	//GET e SET
	map <int, glm::vec2> getPath_map() {
		return path_map;
	} 

	int getPath_EndPath() {
		return path_EndPath;
	}

	void setPath_EndPath(int valore) {
		path_EndPath = valore;
	}

};

void path::inizializzaPath(int path_M[DIM][DIM]) {
	
	if (path_M == path1_Matrix) {
		path_EndPath = PATH1_ENDPATH;
		path_StartDirectionBot = START_DIRECTION_PATH1;
		path_startRotationBot = START_ROTATION_PATH1;
	}
	else if (path_M == path2_Matrix) {
		path_EndPath = PATH2_ENDPATH;
		path_StartDirectionBot = START_DIRECTION_PATH2;
		path_startRotationBot = START_ROTATION_PATH2;
	}
	else if (path_M == path3_Matrix) {
		path_EndPath = PATH3_ENDPATH;
		path_StartDirectionBot = START_DIRECTION_PATH3;
		path_startRotationBot = START_ROTATION_PATH3;
	}
	else if (path_M == path4_Matrix) {
		path_EndPath = PATH4_ENDPATH;
		path_StartDirectionBot = START_DIRECTION_PATH4;
		path_startRotationBot = START_ROTATION_PATH4;
	}
	else if (path_M == path5_Matrix) {
		path_EndPath = PATH5_ENDPATH;
		path_StartDirectionBot = START_DIRECTION_PATH5;
		path_startRotationBot = START_ROTATION_PATH5;
	}
	else if (path_M == path6_Matrix) {
		path_EndPath = PATH6_ENDPATH;
		path_StartDirectionBot = START_DIRECTION_PATH6;
		path_startRotationBot = START_ROTATION_PATH6;
	}
	else if (path_M == path7_Matrix) {
		path_EndPath = PATH7_ENDPATH;
		path_StartDirectionBot = START_DIRECTION_PATH7;
		path_startRotationBot = START_ROTATION_PATH7;
	}
	else if (path_M == path8_Matrix) {
		path_EndPath = PATH8_ENDPATH;
		path_StartDirectionBot = START_DIRECTION_PATH8;
		path_startRotationBot = START_ROTATION_PATH8;
	}
	else if (path_M == path9_Matrix) {
		path_EndPath = PATH9_ENDPATH;
		path_StartDirectionBot = START_DIRECTION_PATH9;
		path_startRotationBot = START_ROTATION_PATH9;
	}
	else if (path_M == path10_Matrix) {
		path_EndPath = PATH10_ENDPATH;
		path_StartDirectionBot = START_DIRECTION_PATH10;
		path_startRotationBot = START_ROTATION_PATH10;
	}

	//Inizializzo path_map: scansiono la matrice ed inserisco le coordinate del path con il relativo indice all'interno di una map
	for (int i = 0; i < DIM; i++) { //z
		for (int j = 0; j < DIM; j++) { //x
			if (path_M[i][j] != 0 && path_M[i][j] != -1) {
				int step = path_M[i][j];
				//conversione coordinate matrice -> game
				int coord_x = j - 20;
				int coord_z = i - 19;
				glm::vec2 coord_bot_iesima(coord_x, coord_z);
				path_map[step] = coord_bot_iesima;
				//cout << "index: " << step << " - " << "[x,z]: (" << path_map[step].x << ", " << path_map[step].y << ")" << endl;
			}
		}
	}

}

