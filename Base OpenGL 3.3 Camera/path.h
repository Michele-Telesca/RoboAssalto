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

	//proprietà
	map <int, glm::vec2> path_map; //mappa per gestire il path del bot -> Viene inizializzata scansionando la matrice
								   //la chiave è un intero che rappresenta lo step del path, a cui corrispondono le rispettive coordinate x,z (vec2) 
	int path_EndPath; //il valore dell'ultimo step del path

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
	}
	else if (path_M == path2_Matrix) {
		path_EndPath = PATH2_ENDPATH;
	}
	else if (path_M == path3_Matrix) {
		path_EndPath = PATH3_ENDPATH;
	}
	else if (path_M == path4_Matrix) {
		path_EndPath = PATH4_ENDPATH;
	}
	else if (path_M == path5_Matrix) {
		path_EndPath = PATH5_ENDPATH;
	}
	else if (path_M == path6_Matrix) {
		path_EndPath = PATH6_ENDPATH;
	}
	else if (path_M == path7_Matrix) {
		path_EndPath = PATH7_ENDPATH;
	}
	else if (path_M == path8_Matrix) {
		path_EndPath = PATH8_ENDPATH;
	}
	else if (path_M == path9_Matrix) {
		path_EndPath = PATH9_ENDPATH;
	}
	else if (path_M == path10_Matrix) {
		path_EndPath = PATH10_ENDPATH;
	}

	//INIZIALIZZO LA MAPPA CON LE COORDINATE
	for (int i = 0; i < DIM; i++) { //z
		for (int j = 0; j < DIM; j++) { //x
			if (path_M[i][j] != 1 && path_M[i][j] != 0 && path_M[i][j] != -1) {
				int step = path_M[i][j];
				//conversione coordinate matrice -> game
				int coord_x = j - 20;
				int coord_z = i - 19;
				glm::vec2 coord_bot_iesima(coord_x, coord_z);
				path_map[step] = coord_bot_iesima;

			}
		}
	}

}

