#include "Func1D.h"

/////////////////// constructors, destructor

Func1D::Func1D(const TF1* fp) : f(nullptr) {
  if (fp) {
    f = new TF1(*fp);
    Settings();
  }
}

Func1D::Func1D(const TF1& fp) : Func1D(&fp) {};

Func1D::~Func1D() {
  if (f) delete f;
  //cout << __PRETTY_FUNCTION__ << endl;
}
 

/////////////////// methods 
TF1* Func1D::GetFunc() const { //Retorna a função associada
    return f;
}

void Func1D::SetFunc(TF1* f2) { //Altera a função associada
    f=f2;
}


void Func1D::Settings() {
  f->SetNpx(1000);
  f->SetLineColor(kGreen);
  f->SetLineWidth(4);
}

double Func1D::Eval(double xval) const {
  return f->Eval(xval);
}

void Func1D::Draw() const {
  TApplication A("A",0,0);
  TCanvas* c= new TCanvas("c", "Func1D canvas", 0, 0, 1000, 800);
  TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();

  rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
  //TQObject::Connect("TCanvas", "Closed()", "TApplication", gApplication, "Terminate()");

  f->Draw();

  c->SetGrid();
  c->cd();     //ir para canvas 
  c->Update();
  c->SaveAs("Func1D.pdf");

  A.Run();

}