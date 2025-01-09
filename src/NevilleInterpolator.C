#include "NevilleInterpolator.h"

NevilleInterpolator::NevilleInterpolator(unsigned int fN, const double* fx, const double* fy, const TF1* fF0) :
DataPoints(fN, fx, fy),
F0(nullptr),
cInterpolator(nullptr) {

  if (fF0) F0 = new TF1(*fF0);
  FInterpolator = new TF1("FInterpolator", this, &NevilleInterpolator::fInterpolator, xmin, xmax, 0);

  cout << __PRETTY_FUNCTION__ << endl;
}

NevilleInterpolator::~NevilleInterpolator() {

  if (FInterpolator) delete FInterpolator;
  if (F0) delete F0;
  if (cInterpolator) delete cInterpolator;

  cout << __PRETTY_FUNCTION__ << endl;
}

NevilleInterpolator::NevilleInterpolator(const NevilleInterpolator& NI) :
NevilleInterpolator(NI.N, NI.x, NI.y, NI.F0) {;}

////////////////////////////////////////// interpolator methods

double NevilleInterpolator::Interpolate(double xval) const {
  double *gaveta = new double[N]; // auxiliar vector

    for (int i = 0; i < N; i++) {
        gaveta[i] = y[i]; 
    }

    for (int k = 1; k < N; k++){
        for (int i = 0; i < N - k; i++){
            gaveta[i] = ((xval - x[i + k]) * gaveta[i] - (xval - x[i]) * gaveta[i + 1]) / (x[i] - x[i + k]);  //Calculating the interpolated values
        }
    }
    //Last value calculated is yp[0] when k=N-1 and i=0.....
  double result = gaveta[0];
  delete[] gaveta;

 /* double result = 0.;
  for (int i=0; i<N; ++i) {
    double lx = 1.;

    for (int k=0; k<N; ++k)
      if (i!=k) lx *= (xval - x[i])) / (x[i] - x[i+k]);
    result += y[i]*lx;
  }*/

  return result;
} 

void NevilleInterpolator::Draw() const {
  DataPoints::Draw();
  FInterpolator->SetLineColor(38);
  FInterpolator->SetLineWidth(4);
  FInterpolator->Draw("same");
}

const TCanvas& NevilleInterpolator::GetCanvas()  {
  cInterpolator = new TCanvas("cInterpolator","", 0,0,800,600);
  DataPoints::Draw();
  FInterpolator->SetLineColor(38);
  FInterpolator->SetLineWidth(4);
  FInterpolator->Draw("same");
  return *cInterpolator;
}
//////////////////////////////////////// underlying func

void NevilleInterpolator::SetFunction(const TF1* fF0) {
  if (fF0) F0 = new TF1(*fF0);
}

//////////////////////////////////////// output

std::ostream& operator<< (std::ostream& s, const NevilleInterpolator& NI) {
  s << "Neville Interpolator " << "x:[" << NI.xmin << "," << NI.xmax << "]\n" << endl;
  for (int i=0; i<NI.N; ++i) {
    s << fixed << setprecision(6)
      << "(" << NI.x[i] << "," << NI.y[i] << ") f(x)=" << NI.Interpolate(NI.x[i]) << " \n" ;
  }
  s << "\n";
  return s;
}