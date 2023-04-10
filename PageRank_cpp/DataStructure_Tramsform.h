#include <vector>
#include <string>
#include "Naive_MV_Multi_AR.h"
#include "Naive_MV_Multi_CSRF.h"

using namespace std;

CSRF_TM AR_TM_to_CSRF_TM(AR_TM S){
    CSRF_TM S_CSRF;
    S_CSRF.Node_num = S.Node_num;
    S_CSRF.Edge_num = S.Edge_num;
    S_CSRF.col = S.col;
    S_CSRF.Network_name = S.Network_name;
    S_CSRF.NZI_first = vector<int> (S.Node_num, 0);
    int *NZI_first_i = S_CSRF.NZI_first.data();
    int *NZ_num_i = S.NZ_num.data();

    for(int i=1; i<(S_CSRF.Node_num); i++){
        // calculating NZI_first_{i+1} with NZI_first_{i} and the number of the non-zero elements of the row i
        *(NZI_first_i+1) = ((*NZI_first_i)+(*NZ_num_i));
        NZI_first_i++;
        NZ_num_i++;
    }
    return S_CSRF;
}