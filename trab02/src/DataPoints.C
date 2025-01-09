#include "DataPoints.h"
using namespace std;


// using initialization list of constructor
DataPoints::DataPoints() : 
N(0), 					// nb of elements = 0
x(nullptr), y(nullptr), // set null pointers
gPoints(nullptr) {};

DataPoints::DataPoints(unsigned int fN, const double* fx, const double* fy) : N(fN), x(new double[N]), y(new double[N]) {
	
	copy(fx, fx+N, x);
	copy(fy, fy+N, y);

	gPoints = new TGraph(N,x,y);
	gPoints->SetMarkerStyle(20);
	gPoints->SetMarkerColor(kGreen);
	gPoints->SetMarkerSize(1.5);

	SetMinMaxX();
  	SetMinMaxY();

	gPoints->GetXaxis()->SetRangeUser(0.9*xmin, 1.1*xmax);
    gPoints->GetYaxis()->SetRangeUser(0.9*ymin, 1.1*ymax);

	cout << __PRETTY_FUNCTION__ << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DataPoints::~DataPoints() {
	delete [] x;
	delete [] y;
	cout << __PRETTY_FUNCTION__ << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const TGraph& DataPoints::GetGraph() const {
	cout << __PRETTY_FUNCTION__ << endl;
	return *gPoints;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DataPoints::Draw() const {
	/*TPad *pad1 = gPoints.CreatePad("pad1");
	gPoints.AddObject(g,"pad1","AP");
	gPoints.AddObject(pad1);*/
	gPoints->Draw("AP");
	//pad1->SaveAs("GDataPoints.pdf");
	cout << __PRETTY_FUNCTION__ << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DataPoints::SetMinMaxX() {
	auto it = minmax_element(x, x+N);
	xmin = *it.first;
	xmax = *it.second;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DataPoints::SetMinMaxY() {
	auto it = minmax_element(y, y+N);
	ymin = *it.first;
	ymax = *it.second;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*void DataPoints::Print(string FILE)
{
	cout << __PRETTY_FUNCTION__ << endl;

    for (int i = 0; i < N; i++)
    {
        printf("[Datapoints] (x=%f, y=%f) ", x[i], y[i]);
    }
    printf("\n");

    printf("FILE: %s\n", FILE.c_str());

}*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<< (std::ostream& s, const DataPoints& datapoints) { //MAIS UMA VEZ, NÃO SEI COMO POR ISTO A DAR
	
	//ANDRÉ
	/* s << "DataPoints: [\n";
	for (int i=0; i<datapoints.N; i++) {
	  s << "           " << datapoints.x[i] << "\n";
	  s << "           " << datapoints.y[i] << "\n";
	}

	s << "        ]";*/

	//BAROON
	s << "Nb points stored: " << datapoints.N << std::endl;

	for (int i=0; i<datapoints.N; ++i) {
		s << std::fixed << std::setprecision(3)
		<< "(" << datapoints.x[i] << "," << datapoints.y[i] << ")" ;
	 }

	return s;
}