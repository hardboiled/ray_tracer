#include "dataStructures.h"
#include "HW6_2_Utilities.h"
#include <fstream>
#include <iostream>
using namespace std;

void readInGlobals(char *acSrcFile)
{
    sphere s;
    plane p;

    ifstream infile(acSrcFile);
	if (!infile) {
		cout << "Error! Input file " << acSrcFile << " does not exist!" << endl;
		return;
	}
    
	infile  >> g_iNumPlanes >> g_iNumSpheres >> g_iNumLights;
    g_papoObjects = new object *[g_iNumSpheres + g_iNumPlanes];

    


    for(int i=0;i< g_iNumPlanes;++i) {
        g_papoObjects[i] = new plane();
        infile >> p.a0 >> p.b0 >> p.c0 >> p.d0;
        infile >> p.c.r >> p.c.g >> p.c.b;
        infile >> p.kamb >> p.kdiff >> p.kspec >> p.shininess >> p.reflPerc;
        *g_papoObjects[i] = p;
        ((plane *)g_papoObjects[i])->a0 = p.a0;
        ((plane *)g_papoObjects[i])->b0 = p.b0;
        ((plane *)g_papoObjects[i])->c0 = p.c0;
        ((plane *)g_papoObjects[i])->d0 = p.d0;
	}
    
    for(int i=g_iNumPlanes;i<g_iNumSpheres + g_iNumPlanes;++i) {
        g_papoObjects[i] = new sphere();
        infile >> s.pc.x >> s.pc.y >> s.pc.z >> s.r;
        infile >> s.c.r >> s.c.g >> s.c.b;
        infile >> s.kamb >> s.kdiff >> s.kspec >> s.shininess >> s.reflPerc;
        *g_papoObjects[i] = s;
        ((sphere *)g_papoObjects[i])->pc = s.pc;
        ((sphere *)g_papoObjects[i])->r = s.r;
	}

    // Now read lights
	g_patLightList = new light[g_iNumLights];
	infile >> g_tAmbientLight.r >> g_tAmbientLight.g >> g_tAmbientLight.b;
	for(int i=0;i<g_iNumLights;i++) {
		infile >> g_patLightList[i].p.x >> g_patLightList[i].p.y >> g_patLightList[i].p.z;
		infile >> g_patLightList[i].brightness.r >> g_patLightList[i].brightness.g >> g_patLightList[i].brightness.b;
	}
}
