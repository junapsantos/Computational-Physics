#include "NewtonInterpolator.h"

NewtonInterpolator::NewtonInterpolator(unsigned int fN, const double* fx, const double* fy, const TF1* fF0) :
DataPoints(fN, fx, fy), F0(nullptr), cInterpolator(nullptr) {

  if (fF0) F0 = new TF1(*fF0);
  FInterpolator = new TF1("FInterpolator", this, &NewtonInterpolator::fInterpolator, xmin, xmax, 0);

}


NewtonInterpolator::~NewtonInterpolator(){
  if (FInterpolator) delete FInterpolator;
  if (F0) delete F0;
  if (cInterpolator) delete cInterpolator;
}

double NewtonInterpolator::DiffTable(int i, int j) const  //Method responsible for calculating the coeficients for each term of the interpolation
{
    if (i == j)
        return y[i];
    else
    {
        return ((DiffTable(i + 1, j) - DiffTable(i, j - 1)) / (x[j] - x[i]));
    }
}

double NewtonInterpolator::Interpolate(double xval) const {
  double result, aux;
    result = y[0];
    for (int k = 1; k < N; k++)
    {
        aux=1.0;
        for (int i = 0; i < k; i++)
        {
            aux = aux * (xval - x[i]);  //Calculating the intermidiate interpolated points
        }
        result = result + DiffTable(0, k) * aux;  //Calling the DiffTable method to calculate the interpolated points
    }

    return result;
}

void NewtonInterpolator::Draw() const {
  DataPoints::Draw();
  FInterpolator->SetLineColor(38);
  FInterpolator->SetLineWidth(4);
  FInterpolator->Draw("same");
}

const TCanvas& NewtonInterpolator::GetCanvas()  {
  cInterpolator = new TCanvas("cInterpolator","", 0,0,800,600);
  DataPoints::Draw();
  FInterpolator->SetLineColor(38);
  FInterpolator->SetLineWidth(4);
  FInterpolator->Draw("same");
  return *cInterpolator;
}
//////////////////////////////////////// underlying func

void NewtonInterpolator::SetFunction(const TF1* fF0) {
  if (fF0) F0 = new TF1(*fF0);
}

//////////////////////////////////////// output

std::ostream& operator<< (std::ostream& s, const NewtonInterpolator& LI) {
  s << "NewtonInterpolator " << "x:[" << LI.xmin << "," << LI.xmax << "]" << std::endl;
  for (int i=0; i<LI.N; ++i) {
    s << std::fixed << std::setprecision(3)
      << "(" << LI.x[i] << "," << LI.y[i] << ") f(x)=" << LI.Interpolate(LI.x[i]) << " " ;
  }
  s << "\n";
  return s;
}