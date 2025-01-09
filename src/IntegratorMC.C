#include "IntegratorMC.h"


IntegratorMC::IntegratorMC(double inicio, double final, TF1 *f){
  F = new TF1();
  F = f;
  x = inicio;
  y = final;
  dim = 1;

  //Integrator(x, y, F);
}

IntegratorMC::IntegratorMC(IntegratorMC& MC){
  NSamp = MC.NSamp;
  x = MC.x;
  y = MC.y;
  F = MC.F;
  dim = 1;
}

IntegratorMC::IntegratorMC(TF1& f){
  x = f.GetXmin();
  y = f.GetXmax();

  F = new TF1();
  F = &f;
  dim = 1;
}

IntegratorMC::IntegratorMC(TF1* f){
  x = f -> GetXmin();
  y = f -> GetXmax();

  F = new TF1();
  F = f;
  dim = 1;

}

IntegratorMC::IntegratorMC(double* xbeg, double* xend, TFormula* tf, int M){
    TForm = new TFormula();
    TForm = tf;
    dim = M;
    cout << "dim: " << dim << endl;
    x0 = new double[dim];
    x1 = new double[dim];

    for(int i = 0; i < dim; i++){
      x0[i] = xbeg[i];
      x1[i] = xend[i];
    }
}


void IntegratorMC::SetBoundaries(double inicio, double final){
    x = inicio;
    y = final;
}

void IntegratorMC::SetIntegrandFunction(TF1* f){
  F = f;
}
void IntegratorMC::IntegralMC(double inicio, double final, int NSamples, double& res, double& err){
}

void IntegratorMC::UniformRandom(double &res, double &err, int NSamples){
  NSamp = NSamples;
  TRandom3 rgen(0);
  double a;
  double res_quadrado = 0;
  double func = 0.;
  for(int i = 0; i < NSamp; i++){
    a = x + rgen.Uniform() * (y - x); 
    func = F -> Eval(a);
    res += func;
    res_quadrado += func * func;
  }
  cout << endl;
  err = sqrt(-((res/NSamp)*(res/NSamp) - (res_quadrado/NSamp))/NSamp);

  err = err * (y - x);
  res = res * (y - x);
  res = res/(NSamp); 
}

/*void IntegratorMC::UniformRandom_Multiplo(double &res, double &err, int NSamples){
  NSamp = NSamples;
  TRandom3 rgen(0);
  double xi = x0[0];
  double xf = x1[0];
  double *a = new double[dim];
  double h_part = 1;
  double res_quadrado = 0, res_aux = 0;
  double func = 0.;

  for(int k = 0; k < dim; k++)
    h_part =  h_part * (x1[k] - x0[k]);

  double h = h_part/NSamp;

  for(int i = 0; i < NSamp; i++){
    for(int j = 0; j < dim; j++)
      a[j] = x0[j] + rgen.Uniform() * (x1[j] - x0[j]);
       
    res_aux = res_aux + TForm -> EvalPar(a);
    res_quadrado = res_quadrado + TForm -> EvalPar(a) * TForm -> EvalPar(a);
  }

  res = res_aux * h;

  err = sqrt(res_quadrado / NSamp - pow(res_aux / NSamp, 2));
  for(int l = 0; l < dim; l++){
    err = err * (x1[l] - x0[l]) / sqrt(NSamp);
  } 

  delete[] a;
}*/

void IntegratorMC::UniformRandom_Multiplo(double &res, double &err, int nsamples) //Método Uniform Random
{
    TRandom3 rgen;
    double xi = x0[0];
    double xf = x1[0];
    double *a = new double[dim];
    double h_part = 1;
    double F2 = 0;
    double part_res = 0, part_err = 1;

    for (int i = 0; i < dim; i++)
    {
      h_part = h_part * (x1[i] - x0[i]);
    }

    double h = h_part / nsamples;

    for (int i = 0; i < nsamples; i++){
      for (int j = 0; j < dim; j++)
          a[j] = x0[j] + (x1[j] - x0[j]) * rgen.Uniform(0, 1);

      part_res = part_res + TForm->EvalPar(a);
      F2 = F2 + TForm->EvalPar(a) * TForm->EvalPar(a);
    }

    res = part_res * h;
    part_err = sqrt(F2 / nsamples - pow(part_res / (nsamples), 2));

    for (int i = 0; i < dim; i++)
    {
      part_err = part_err * (x1[i] - x0[i]) / (sqrt(nsamples));
    }

    err = part_err;
}

void IntegratorMC::ImportanceSampling(int& N, double& value, double& error, const TF1& px, const TF1& xy){
  double Fsum = 0.;
  double Fsum2 = 0.;
  error = 0;
  int count = 0;
  double error_t = 1.;
  gRandom->SetSeed(0);
  
  while ( count < N || error_t < error) {

  // check pdf normalization
  if (count == 0) {
    TF1 ftmp(px);
    printf("integral pdf [%f, %f]= %f \n", x, y, ftmp.Integral(x, y));
  }
  
  // generate uniform random y
  double x0 = gRandom->Uniform(); // [0,1]
  double x1 = xy.Eval(x0);

  // compute function ratio
  double ratiof;
  if(dim == 1){
    ratiof = F ->Eval(x1)/px.Eval(x1);
  }else{
    ratiof = TForm->Eval(x1)/px.Eval(x1);
  }
  

  // integral
  Fsum += ratiof;
  Fsum2 += ratiof*ratiof;

  // count
  count++;
  
  // error variance: variance = <f^2> - <f>^2
  double Fmean = Fsum/count;
  double Fmean2 = Fsum2/count;
  double variance = Fmean2 - Fmean*Fmean;
  error_t = sqrt(variance/count);
  }

  N = count;
  error = error_t;
  value = Fsum/N;
  
  printf("N=%d value=%f error=%f \n", N, value, error);
}

void IntegratorMC::RandomGen(TF1& px, TF1& xy) {
  // draw x random
  TH1F H("H", "random generated from xy", 120, -60, 60);
  TApplication A("A",0,0);
  gRandom->SetSeed(0);
  for (int i=0; i<1000; ++i) {
    double r = gRandom->Uniform(); // [0,1]
    H.Fill( xy.Eval(r) );
  }
  
  // scale histogram to integral=1
  H.Scale(1./H.Integral("width"));

  // display histogram and pdf
  TCanvas c("c","", 0, 0, 600,600);
  H.SetLineColor(38);
  H.SetLineWidth(4);  
  H.Draw("HISTO");
  px.SetLineColor(20);
  px.SetLineWidth(4);
  px.Draw("same");
  c.Update();
  A.Run();
}

void IntegratorMC::AcceptanceRejection(int NSamples, double& result, double& error){
  NSamp = NSamples;

  TF1 *f1 = new TF1("f1", F -> GetExpFormula() , x, y);
  double f_Max = f1 -> GetMaximum();

  TH1D *DN = new TH1D("h1", "Distribuicao Normalizada", 200, x, y);
  for(int i = 0; i < NSamples; i++)
    DN -> Fill(f1 -> GetRandom());

  double Normalizada = DN -> GetEntries();
  DN -> Scale(1/Normalizada);

  TRandom3 rgen(0);
  TH1D *h2 = new TH1D("h2", "AcceptanceRejection w/ f_Max", 200, x, y);
  for(int i = 0; i < NSamp; i++){
    double x1 = rgen.Uniform(x, y);
    double y1 = rgen.Uniform(0., 1.);
    if(y1 < (f1 -> Eval(x1) / f_Max))
      h2 -> Fill(x1);
  }

  Normalizada = h2 -> GetEntries();
  h2 -> Scale(1/ Normalizada);
  result = Normalizada / NSamp * f_Max * (y - x);
  error = (0.3 * M_PI) * f_Max / NSamp * sqrt(Normalizada * (1 - Normalizada / NSamp));

  TCanvas *C = new TCanvas("C", "C", 500, 500);

  DN -> SetLineColor(kGreen);
  DN -> SetLineWidth(1.0);

  DN -> SetLineColor(kRed);
  DN -> SetLineWidth(1.0);

  THStack *s = new THStack("histstack", "ROOT f1->GetRandom() vs User Accept-Reject");
  s->Add(DN);
  s->Add(h2);

  s->Draw("HIST nostack");

  C->BuildLegend();
  C->Modified();
  C->SaveAs("Accept-Reject.eps", "AP");

  delete C;
  delete s;
  delete f1;
  delete DN;
  delete h2;
}








