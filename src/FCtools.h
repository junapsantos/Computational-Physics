#ifndef __FCtools__
#define __FCtools__

#include <string>
#include "Vec.h"

#include "TGraph.h"
#include "TH1D.h"
using namespace std;

class FCtools {
public:


	static double RoundOffError(int);
	// retorna o erro relativo de arredondamento

	static TGraph* RoundOffErrorG(int , int );
	//Um método que retorne um objecto TGraph cuja abcissa seja o valor de i e a ordenada o erro de arredondamento

	static TH1D* RoundOffErrorH(int imin, int imax);
	//Um método que retorne um histograma unidimensional TH1D com a distribuição dos erros de arredondamento


	//(...)
	//file name, returns lines
	static vector<string> ReadFile2String(string);

	//file name, returns vectors of Vec’s
	static vector<Vec> ReadFile2Vec(string); //nao feita

	//file name, returns pointer to array of Vec’s, int provides number of lines
	static Vec* ReadFile2Vecp(string, int&); 
};

#endif