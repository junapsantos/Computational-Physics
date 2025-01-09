#include "FCmatrixT.h"
#include <stdexcept>
using namespace std;

#include <cstdio>

#include "TROOT.h"

FCmatrixT::FCmatrixT() {
  printf("[%s] \n", __PRETTY_FUNCTION__);
}

FCmatrixT::FCmatrixT(double** a , int m, int n) {
  mrows=m;
  ncols=n;
  for (int i=0; i<m; ++i) {
    M.emplace_back(n, a[i]);   
  }
}

FCmatrixT::FCmatrixT(double* a , int m, int n) {
  if (!a)
     throw invalid_argument(Form("[%s] null pointer...!\n", __PRETTY_FUNCTION__));
   
  mrows=m;
  ncols=n;
  for (int i=0; i<m; ++i) {
    M.emplace_back(n, &a[i*n]);   
  }
}

FCmatrixT::FCmatrixT(const vector<Vec>& v) {
  mrows=v.size();
  for (int i=0; i<mrows; ++i) {
    M.emplace_back(v[i]);   
  }
  ncols=M[0].size();
}

FCmatrixT::FCmatrixT(const FCmatrixT& matrix) {
  mrows=matrix.GetRowN();
  for (int i=0; i<mrows; ++i) {
    M.emplace_back(matrix.M[i]);   
  }
  ncols=M[0].size();
}

FCmatrixT::~FCmatrixT() //Destructor
{
    printf("__PRETTY_FUNCTION__ = %s\n", __PRETTY_FUNCTION__);
}

///////////////// methods

int FCmatrixT::GetRowN() const {
  return mrows;  
}

int FCmatrixT::GetColN() const {
  return ncols;  
}

Vec &FCmatrixT::operator[](int i) //get a row by giving index inside []
{
    return M[i];
}

Vec FCmatrixT::operator[](int i) const
{
    return M[i];
}


Vec FCmatrixT::GetRow(int i) const //retrieve row i
{
    Vec v;
    v = M[i];
    return v;
}

Vec FCmatrixT::GetCol(int i) const //retrieve column i
{
    Vec v;
    double a[GetRowN()];

    for (int j = 0; j < GetRowN(); j++)
    {
        a[j] = M[j][i];
    }
    v.SetEntries(GetRowN(), a);
    return v;
}

void FCmatrixT::operator= (const FCmatrixT& matrix) {
  if (this != &matrix) {
    M.clear();
    for (int i=0; i< matrix.M.size(); ++i) {
      M.push_back(matrix.M[i]);
    }
  }
}

void FCmatrixT::Print() const  //prints the matrix
{
    Vec v1;
    for (int i = 0; i < GetRowN(); i++)
    {
        cout << setw(5) << "||";
        v1 = GetRow(i);

        for (int j = 0; j < GetColN(); j++)
        {
            cout << setw(4) << v1[j] << setw(4);
        }
        cout <<"||"<< endl;
    }
}

/*ostream& operator << (ostream& s, const FCmatrixT& matrix) { //MAIS UMA VEZ, NÃO SEI COMO POR ISTO A DAR
 s << "matrix: [\n";
 int a =matrix.GetRowN();
 printf("amendoins\n");
  for (int i=0; i<a; ++i) {
    s << "           " << matrix.M[i] << "\n";
    printf("cebolas\n");
  }
 s << "        ]";
 return s;
}*/