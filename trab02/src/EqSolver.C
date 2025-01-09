#include "EqSolver.h"
#include <stdexcept>

#define DEBUG
 
using namespace std;

EqSolver::EqSolver(){
	//printf("[%s]\n", __PRETTY_FUNCTION__);
	FCmatrixFull M2;
	Vec a;
	M1 = M2;
	b = a;
}

EqSolver::~EqSolver() {}

EqSolver::EqSolver(const  FCmatrixFull& M2, const Vec& a): M1(M2), b(a) {
	//printf("[%s]\n", __PRETTY_FUNCTION__);	
}


void EqSolver::SetConstants(const Vec& a){
	b=a;
}

void EqSolver::SetMatrix(const FCmatrixFull& M3){
	M1=M3;
}

//private
void EqSolver::GaussElimination(FCmatrixFull& M1, Vec & b){
	if(M1.GetColN() != M1.GetRowN())
		cout << "ERRO! A matriz tem de ser quadrada." << endl;
	
	if(M1.GetRowN() != b.size())
		cout << "ERRO! É necessário que o nr de colunas seja igual ao nr de elementos do vetor." << endl;
	
				
	
		int n=M1.GetRowN();

		for(int bn = 0; bn < n; bn++){
			double* array1=new double [n+1];

			for(int i=0; i<n; i++){
            	array1[i] = M1[bn][i];
   			}

   			array1[n]=b[bn];
			M1[bn].SetEntries(n+1,array1);
			delete [] array1;
		}

		FCmatrixAlgorithm::GaussElimination(M1);

		for(int bn = 0; bn < n; bn++){
			double* array1=new double [n];

			for(int i=0; i<n; i++){
            	array1[i] = M1[bn][i];
   			}

   			b[bn]=M1[bn][n];
			M1[bn].SetEntries(n,array1);
			delete [] array1;
		}

    for(int i=0; i<n; i++){
        if(M1[i][i]==0 && b[i]!=0) {
            cout << "Sistema Impossível" << endl;
        }
        if(M1[i][i]==0 && b[i]==0) {
            cout << "Sistema Indeterminado" << endl;
        }
	}
}


Vec EqSolver::GaussEliminationSolver(){
    
	GaussElimination(M1, b);
    int n = M1.GetRowN();  //Matriz é quadrada portanto a dimensão pretendida para o ciclo das linhas e das colunas é igual a n que é igual ao número de colunas e também o número de linhas
    Vec solucao(n);
    double a;

    for (int i = n - 1; i >= 0; i--){
        a = 0;
        for (int j = n - 1; j > i; j--){
            a = a + M1[i][j] * solucao[j];  //Valor que para as linhas de indice inferior a n-1 são subtraídos ao 'b' da liha em que o ciclo se encontra. Este valor consiste na soma dos produtos dos valores das soluções das variáveis de indice superior com os coeficientes da matriz A alterada
        }

        solucao[i] = (b[i] - a) / M1[i][i];  //Solução consiste na subtração do valor 'a' ao 'b' alterado após a eliminação de Guass e divido pelo coeficiente do elemento da diagonal principal da linha em que nos encontramos
    }

    return solucao;
}

void EqSolver::LUdecomposition(FCmatrixFull& M1, vector<int>& index){
	
    Vec v(M1.GetColN(), 0.0);
    vector<Vec> vv;
    int n = M1.GetColN();

    if (M1.Determinant() != 0)  //Verificação se a matriz é quadrada, só se vão resolver sistemas possívei e determinados
    {
        
        for (int i = 0; i < M1.GetRowN(); i++)
        {
            vv.push_back(v);
        }

        //Inicialização dos objetos onde vão ser guardadas as matrizes 'L' e 'U'

        FCmatrixFull L(vv);  
        FCmatrixFull U(vv);
    
        //Decomposição da matriz em matrizes triangular superior e triangular inferior

        for (int i = 0; i < n; i++)
        {
            //////////////// Triangular Superior
            for (int k = i; k < n; k++)
            {
                //Acumulação dos produtos entre L[i][j](Futura matriz triangular inferior) * U[j][k](Futura  matriz triangular superior)
                double sum = 0;
                for (int j = 0; j < i; j++)
                    sum = sum + (L[i][j] * U[j][k]);
    
                // Atribuição de valor atualizado aos elementos da matriz triagular superior dados por U[i][k]
                U[i][k] = M1[i][k] - sum;
            }
    
            ///////////////// Triangular Inferior
            for (int k = i; k < n; k++)
            {
                if (i == k)
                    L[i][i] = 1; // Diagonal as 1
                else
                {
    
                    // Summation of L(k, j) * U(j, i)
                    //Acumulação dos produtos entre low[k][j](Futura matriz triangular superior) * up[j][i]  (Futura matriz triangular inferior)
                    double sum = 0;
                    for (int j = 0; j < i; j++)
                        sum = sum + (L[k][j] * U[j][i]);
                    // Atribuição de valor atualizado aos elementos da matriz triagular inferior dados polow[k]   [i]
                    L[k][i] = (M1[k][i] - sum) / U[i][i]; // Divisão pelo coeficiente da diagonal para  garantir que a diagonal da matriz trinagular inferior é constituída puramente por 1's
                }
            }
            
        } 	
      	M= new FCmatrixFull[2];//Armazenamento das matrizes triangulares inferior e superior que  resultaram da aplicação do processo de simplificção de Doolittle num ponteiro de para objetos do tipo   FCmatrixFull
        M[0] = L;
        M[1] = U;
        cout<<"\n////////////Matriz L///////////"<<endl;
        M[0].Print();
        cout<<"\n////////////Matriz U//////////"<<endl;
        M[1].Print();
    }


    else
    {
        //Mensagem de erro dada em caso de matriz não ser quadrada, ou seja, o determinante da matriz ser zero
        cout <<"Não é possível resolver o sistema." << endl;
        M= new FCmatrixFull[2];
  
    }
}


Vec EqSolver::LUdecompositionSolver(){
	
	vector<int> v;
    LUdecomposition(M1,v);   
    cout<<"morangos"<<endl; 
    FCmatrixFull L(M[0]);
    FCmatrixFull U(M[1]);


   /* cout << "Matrizes L e U respetivamente:" << endl;
    L.Print();
    cout << endl;
    U.Print();
    cout << endl;

    //Separação do sistema LUx=b e resolução do mesmo recorrendo a dois Vec's onde são armazenadas soluções temporárias
    Vec y(b.size(), 0.0);
    for (int i = 0; i < L.GetRowN(); i++)
    {
        y[i] = (b[i] - L[i].dot(y)) / 1.;
    }
    Vec x(b.size(), 0.0);

    cout<<"morangos"<<endl; 

    for (int i = U.GetRowN() - 1; i >= 0; i--)
    {
            x[i] = (y[i] - U[i].dot(x)) / U[i][i];
    }
    return x;*/

    EqSolver E1(L, b);

    Vec res1 = E1.GaussEliminationSolver();

    EqSolver E2(U, res1);

    Vec res2 = E2.GaussEliminationSolver();
 
    return res2;
}


void EqSolver::Print(){

	/*FCmatrixFull Msave=M1;
	if (M1.GetRowN()!=M1.GetColN()){

		for(int bn = 0; bn < M1.GetRowN(); bn++){
			double* array1=new double [M1.GetRowN()];

			for(int i=0; i<M1.GetRowN(); i++){
            	array1[i] = M1[bn].At(i);
   			}
			Msave[bn].SetEntries(M1.GetRowN(),array1);
			delete [] array1;
		}
	}*/

    for(int i=0; i<M1.GetRowN(); i++)
    {
    	
             
        for(int j=0; j<M1.GetColN();j++)
        {
            cout << setw(8) << std::right << std::setprecision(3) << std::fixed << M1[i][j]<< fixed<<setw(8);
        }

    cout << setw(4) << std::right  << "|" << fixed<< setw(8) <<b[i]<< fixed << setw(7) <<endl;
    }
}