#pragma once
#include "point3D.h"
#include "weapon.h"

class playerShot {

public:

	playerShot(point3D pcenter) : center(pcenter) {}

	point3D center; //punto in cui il colpo si trova

	point3D start; //punto da cui è partito
	point3D finish; //punto massimo in cui arriva il colpo
	
	bool destroyed;//true quando il colpo ha hittato un nemico o un oggetto... 


	void draw(); //disegna il colpo in base al weapon 

};

void playerShot::draw() {

}

