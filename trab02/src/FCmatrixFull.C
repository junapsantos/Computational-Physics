#include <stdexcept>
#include <cstdio>

using namespace std;
 
#include "TROOT.h"
#include "FCmatrixFull.h"
#include "FCmatrixAlgorithm.h"

//////////////////////////////////////// Constructors /////////////////////////////////////////////////////
FCmatrixFull::FCmatrixFull() {

	Vec v;
    M.push_back(v);
    classname = "DefaultMatrixFull";

	//printf("[%s] \n", __PRETTY_FUNCTION__);
}

/////////////////////////////////////////////

FCmatrixFull::~FCmatrixFull() //Destructor
{
    //printf("__PRETTY_FUNCTION__ = %s\n", __PRETTY_FUNCTION__);
}

/////////////////////////////////////////////

FCmatrixFull::FCmatrixFull(double** a , int m, int n) {
  for (int i=0; i<m; ++i) {
    M.emplace_back(n, a[i]);   
  }
  classname = "FCmatrixFull";
}

/////////////////////////////////////////////
 
FCmatrixFull::FCmatrixFull(double* a , int m, int n) {
  if (!a)
     throw invalid_argument(Form("[%s] null pointer...!\n", __PRETTY_FUNCTION__));
   
  for (int i=0; i<m; ++i) {
    M.emplace_back(n, &a[i*n]);   
  }
  classname = "FCmatrixFull";
}

/////////////////////////////////////////////

FCmatrixFull::FCmatrixFull(vector<Vec> v) {
  
  for (int i=0; i<v.size(); ++i) {
    M.emplace_back(v[i]);   
  }
  
  classname = "FCmatrixFull";
}

/////////////////////////////////////////////

FCmatrixFull::FCmatrixFull(const FCmatrixFull& matrix) {
  ;
  for (int i=0; i<matrix.GetRowN(); ++i) {
    M.emplace_back(matrix.M[i]);   
  }

  classname = "FCmatrixFull";
}

//////////////////////////////////////////operators///////////////////////////////////////////////////////

Vec& FCmatrixFull::operator[](int i) //get a row by giving index inside []
{
    return M[i];
}

/////////////////////////////////////////////

Vec FCmatrixFull::operator[](int i) const
{
    return M[i];
}

/////////////////////////////////////////////

/*FCmatrixFull& FCmatrixFull::operator=(const FCmatrix& M2)
{
	M.clear();
    Vec v;

    //igualar a um vec a respetiva linha e colocaçao da mesma na matriz final
    for(int i=0; i< M2.GetRowN(); i++)
    {
        v = M2.GetRow(i);
        M.push_back(v);
    }
    classname = M2.GetName();
    return *this;
}*/

/////////////////////////////////////////////

void FCmatrixFull::operator= (const FCmatrix& matrix) {
  if (this != &matrix) {
    M.clear();
    for (int i=0; i< matrix.GetRowN(); ++i) {
      M.push_back(matrix[i]);
    }
  }
}

/////////////////////////////////////////////

FCmatrixFull FCmatrixFull::operator+(const FCmatrix& M2) const
{
	Vec v;
    vector<Vec> Vv; 

    //soma das respetivas linhas e colocaçao do resultado na matriz final
    for(int i=0; i<M2.GetRowN(); i++)
    { 
        v=M2.GetRow(i);
        Vv.push_back(v + M[i]);
    }

    FCmatrixFull MResult(Vv);
    MResult.classname = "FCmatrixFull";
    return MResult;
}

/////////////////////////////////////////////

FCmatrixFull FCmatrixFull::operator-(const FCmatrix& M2) const
{
	Vec v;
    vector<Vec> Vv; 

    //soma das respetivas linhas e colocaçao do resultado na matriz final
    for(int i=0; i<M2.GetRowN(); i++)
    { 
        v=M2.GetRow(i);
        v=v*(-1);
        Vv.push_back(v + M[i]);
    }

    FCmatrixFull MResult(Vv);
    MResult.classname = "FCmatrixFull";
    return MResult;
}

/////////////////////////////////////////////

FCmatrixFull FCmatrixFull::operator*(const FCmatrix & M2) const
{
	if (M2.GetRowN() == GetColN()){
		vector<Vec> Vv;
    	double a[M2.GetColN()];
    	Vec v(M2.GetColN());

	    for(int i=0; i<M.size(); i++)
	    {
	        /*multiplicaçao das duas matrizes efetuando o produto interno entre a linha da primeira matriz e coluna da segunda*/
	        
	        for(int j=0; j<M2.GetColN(); j++)
	        {
	            Vec v2 = M2.GetCol(j);
	            //colocaçao dos resultados num array, fazendo o produto interno
	            a[j]= v2.dot(M[i]);
	        }
	        /*definir as entradas dos vec que guardam a linha i e colocaçao destas no vector of vec da matriz final*/
	     	v.SetEntries(M2.GetColN(), a);
	        Vv.push_back(v);
	    }

    	FCmatrixFull MResult(Vv);
    	MResult.classname = "FCmatrixFull";
    	return MResult;

    }else{
        
        cout << "Para multiplicar duas matrizes garanta que a segunda tem número de linhas igual ao número de colunas da primeira - retorno de uma matriz nula.." << endl;
        FCmatrixFull MResult;
        MResult.classname = "FCmatrixFull";
        return MResult;
    }
}    

/////////////////////////////////////////////

FCmatrixFull FCmatrixFull::operator*(double c) const
{
    vector<Vec> Vv;    

    //mulplicalao de cada linha pela constante double e colocaçao do resultados na matriz final
    for(int i=0; i<M.size(); i++)
    {
        Vec v = M[i];
        for (int j=0; j<v.size(); j++){
        	v[j]=c*v[j];
    	}
        Vv.push_back(v);
    }

    FCmatrixFull MResult(Vv);
    MResult.classname = "FCmatrixFull";
    return MResult;
}

/////////////////////////////////////////////

Vec FCmatrixFull::operator*(const Vec& v) const
{
    
     if (GetColN() != v.size())
    {
    	Vec nul;
        cout << "É impossível multiplicar esta matrix por este vetor.\nCertifique-se que a dimensão das colunas da matriz é igual à dimensão do vetor.\n";
        return nul;
    }
	double a[GetColN()];
    Vec v2(v);
    /*multiplicaçao da matriz pelo vec atraves do produto interno da linha da 
    matriz pelo vec e retorno do vec final*/
    for(int i=0; i<GetColN(); i++)
    {
        a[i]= v2.dot(M[i]);
    }

    Vec vresult(GetColN(), a);
    return vresult;

}

//////////////////////////////////////////////methods///////////////////////////////////////////////////
int FCmatrixFull::GetRowN() const {
	int mrows=M.size();
	return mrows;  
}

/////////////////////////////////////////////

int FCmatrixFull::GetColN() const {
	int ncols=M[0].size();
	return ncols;  
}

/////////////////////////////////////////////

string FCmatrixFull::GetName() const
{
    return classname;
}

/////////////////////////////////////////////

Vec FCmatrixFull::GetRow(int i) const //retrieve row i
{
    Vec v;
    v = M[i];
    return v;
}

/////////////////////////////////////////////

Vec FCmatrixFull::GetCol(int i) const//retrieve column i
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

/////////////////////////////////////////////

int FCmatrixFull::GetRowMax(int i)
{
    Vec v=GetRow(i);
    int Max;
    for (int j=0; j<GetColN()-1; j++)
    {
        if (v[j] > v[j+1])
        {
            Max = j;
        }else{
            Max = j+1;
        }
    }
    return Max;
}

/////////////////////////////////////////////

int FCmatrixFull::GetColMax(int i)  //in column-i, return row-index of max element (in absolute value)
{
    Vec v = GetCol(i);
    double a;
    double b= 0;
    int max = 0;
    
    for (int j = 0; j < v.size(); j++){
        a = 0;
        Vec v2(M[i]);
        
        for (int n = 0; n < v2.size(); n++){
            
            if(n!=i){
                a += fabs(v2[n]);
            }
        }
        
        if (fabs(v[j]/a) > b){
            max = i;
            b= fabs(v[j]/a);
        }
    }
    
    return max;
}

/////////////////////////////////////////////

double FCmatrixFull::Determinant() const 
{

    if (GetColN() == GetRowN()){  //matriz quadrada
        double det = 1;
        int dim=GetColN(); //dimensao da matriz

        if (dim == 2){
        	det=(M[0][0] * M[1][1]) - (M[1][0] * M[0][1]);
        }
        else{
        
	        FCmatrixFull M2=M;
	        FCmatrixAlgorithm::GaussElimination(M2);

	        for (int i=0; i<dim;i++){
	        	det=det*M2[i][i];
	        }
        }
    return det;
    }
    else{
    	cout << "ERRO! Matriz não Quadrada! Impossível calcular determinante!" << endl;
        return -1;
    }

}

FCmatrixFull FCmatrixFull::getTranspose(const FCmatrixFull& matrix1) {

    //Transpose-matrix: height = width(matrix), width = height(matrix)
    FCmatrixFull solution(matrix1);

    //Filling solution-matrix
    for(int i = 0; i < matrix1.GetRowN(); i++) {
        for(int j = 0; j < matrix1[0].size(); j++) {
            solution[j][i] = matrix1[i][j];
        }
    }
    return solution;
}

FCmatrixFull FCmatrixFull::getCofactor(const FCmatrixFull& vect) {

    FCmatrixFull solution(vect);

    int n_mat = vect.GetColN();

    //double a[n_mat - 1][n_mat - 1];   
    double **a = new double *[n_mat - 1];
    for (int i = 0; i < n_mat - 1; ++i)
              a[i] = new double[n_mat - 1];

    FCmatrixFull subVect(a, n_mat - 1, n_mat - 1);

    for(int i = 0; i < vect.GetRowN(); i++) {
        for(int j = 0; j < vect[0].size(); j++) {

            int p = 0;
            for(int x = 0; x < vect.GetRowN(); x++) {
                if(x == i) {
                    continue;
                }
                int q = 0;

                for(int y = 0; y < vect.GetRowN(); y++) {
                    if(y == j) {
                        continue;
                    }

                    subVect[p][q] = vect[x][y];
                    q++;
                }
                p++;
            }
            solution[i][j] = pow(-1, i + j+1) * subVect.Determinant();
        }
    }
    return solution;
}

FCmatrixFull FCmatrixFull::getInverse(const FCmatrixFull& vect) {

    double d = 1.0/vect.Determinant();
    FCmatrixFull solution(vect);

    solution = getTranspose(getCofactor(solution));
    
    for(int i = 0; i < vect.GetRowN(); i++) {
        for(int j = 0; j < vect.GetRowN(); j++) {

            solution[i][j] = solution[i][j]*d;
        }
    }
    
    return solution;
}




/////////////////////////////////////////////

void FCmatrixFull::swapRows(int m1, int m2) //linhas 1 e 2 a trocar
{
	if (m1 >= 0 && m2 >= 0)
    {
    	Vec gaveta = M[m1];
   		M[m1]= M[m2];
   		M[m2]= gaveta;
   	}else{
   		int nrows=GetRowN()+1;
        cout << "ERRO! Numeração Incorreta das linhas! Insira numeros inteiros de 0 a " << nrows<<endl;
    }
}

/////////////////////////////////////////////

void FCmatrixFull::Print() const  //prints the matrix
{
    Vec v1;
    for (int i = 0; i < GetRowN(); i++)
    {
        cout << setw(5) << "||";
        v1 = GetRow(i);

        for (int j = 0; j < GetColN(); j++)
        {
            cout << setw(14) << std::right << std::setprecision(9) << std::fixed <<  v1[j]<<setprecision(9) << fixed<<setw(5);
        }
        cout <<"||"<< endl;
    }
    cout<<"\n"<<endl; 
}



 FCmatrixFull operator*(double d, const FCmatrixFull &m) { return m*d; }

// friend methods
std::ostream& operator<<(std::ostream& s, const FCmatrixFull& matrix) { 
 Vec v1;
    for (int i = 0; i < matrix.GetRowN(); i++)
    {
        s << setw(5) << "||";
        v1 = matrix.GetRow(i);

        for (int j = 0; j < matrix.GetColN(); j++)
        {
            s << setw(14) << std::right << std::setprecision(9) << std::fixed <<  v1[j]<<setprecision(9) << fixed<<setw(5);
        }
        s <<"||"<< endl;
    }
    s<<"\n"<<endl; 
     return s;
}


 