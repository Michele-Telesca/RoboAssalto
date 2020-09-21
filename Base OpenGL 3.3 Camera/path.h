#pragma once
#include "point3D.h"
#include "weapon.h"
#include "model.h"
#include "globalData.h"
#include "globalPathData.h"
#include <vector>

//vector <glm::vec4> path1_list;
//vector <glm::vec4> path2_list;

class path
{

public:

	//costruttore
	path() {}

	int path_Matrix[DIM][DIM] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};
	vector <glm::vec4> path_list;
	int path_EndPath;

	//prototipi
	void inizializzaPath(int path_M[DIM][DIM]);

	//GET e SET
	vector <glm::vec4> getPath_list() {
		return path_list;
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
	}
	else if (path_M == path2_Matrix) {
		path_EndPath = PATH2_ENDPATH;
	}
	else if (path_M == path3_Matrix) {
		path_EndPath = PATH3_ENDPATH;
	}

	//inizializzo la MATRICE
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			path_Matrix[i][j] = path_M[i][j];
		}
	}

	//INIZIALIZZO LA LISTA CON LE COORDINATE
	int step = 0;
	for (int i = 0; i < DIM; i++) { //z
		for (int j = 0; j < DIM; j++) { //x
			if (path_Matrix[i][j] != 1 && path_Matrix[i][j] != 0 && path_Matrix[i][j] != -1) {
				int index = path_Matrix[i][j];

				//conversione coordinate matrice -> game
				int coord_x = j - 10;
				int coord_z = i - 9;

				glm::vec4 coord_bot_iesima(coord_x, 0.5f, coord_z, index);
				path_list.push_back(coord_bot_iesima);
			}
		}
	}

}