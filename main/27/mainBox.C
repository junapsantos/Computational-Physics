	#include <cstdio>    //printf
	#include <iostream> //cout
	#include <cstdlib>  //exit, rand, getchar
	#include <cmath>    //sin, cos
    #include <ctime>    //time()
	#include <map>
	#include <vector>
	#include <utility>
	#include <algorithm>
	#include <list> // list
	#include <string>
	#include "Box.h"
    using namespace std;

int main() {
	// criar dois cubos de lado 1
	Box B1;
	Box B2 = B1;
	// somar dois cubos
	Box B3 = B1 + B2;
	// criar dois paralelipipedos
	Box B5(1,1,2);
	Box B6(B5);
	// somar os dois paralelipipedos
	Box B7;
	B7 = B5 + B6;
	// calcular volumes
	float volume_3 = B3.GetVolume();
	float volume_7 = B7.GetVolume();
	cout << "volumes: " << volume_3 << " " << volume_7 << endl;

	/*B1.Dump();
	B3.Dump();
	B5.Dump();
	B6.Dump();
	B7.Dump();*/

	Box* pBoriginal=new Box(1,1,2);
	Box* pB2 = new Box();

	//com void
	pBoriginal->Addv(pB2);
	Box* pBresultado1 = pBoriginal;
	float volume_pb1=pBresultado1->GetVolume();
	cout << "volumes: " << volume_pb1 << " " << endl;

	//com return 
	Box* pBresultado2 = pBoriginal->Add(pB2);
	float volume_pb2=pBresultado2->GetVolume();
	cout << "volumes: " << volume_pb2 << " " << endl;

}