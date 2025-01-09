using namespace std;
#include "FCmatrixAlgorithm.h"

void FCmatrixAlgorithm::GaussElimination(FCmatrix& M2) {
		 // printf("[%s]\n", __PRETTY_FUNCTION__);
		 /* for (int i=0; i<MR.GetRowN()-1; ++i) {
		    if (MR[i][i] == 0) {
		      // swap lines: think about...
		    }
		    // not the most effective
		    for (int j=i+1; j<MR.GetRowN(); ++j) {
		      double m = MR[j][i]/MR[i][i];
		      MR[j] += MR[i]*(-m);
		    }
		  }*/

	for(int linha = 0; linha < M2.GetRowN() - 1; linha++){
		if(linha != M2.GetRowN()){
				int linha1 = M2.GetColMax(linha);
				M2.swapRows(linha, linha1);
		}
		for(int i = linha + 1; i < M2.GetRowN(); i++){
			double subtrator_eliminacao=0;
			if(M2[linha].At(linha)!=0){
			subtrator_eliminacao = M2[i].At(linha)/M2[linha].At(linha);
			}
			M2[i] = M2[i] - M2[linha]*subtrator_eliminacao;
		}
	}
}

