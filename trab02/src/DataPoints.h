#ifndef __DataPoints__
#define __DataPoints__

#include <cstdio>
#include <algorithm>
#include <stdexcept>
#include <iomanip> // setprecision()
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>


#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h" 
#include "TPad.h"
#include "TROOT.h"
#include "TAxis.h"


class DataPoints {

public:
	DataPoints();
	DataPoints(unsigned int, const double*, const double*);
	
virtual ~DataPoints();

virtual double Interpolate(double x) const {return 0.;}

virtual void Draw() const;
virtual const TGraph& GetGraph() const;

//virtual void Print(string);

friend std::ostream& operator<< (std::ostream&, const DataPoints&);

protected:
	int N; // number of data points
	double *x, *y; // arrays
	TGraph *gPoints; // graph with data points

	double xmin, xmax;
	double ymin, ymax;

	void SetMinMaxX();
	void SetMinMaxY();
};

#endif

