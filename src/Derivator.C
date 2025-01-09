#include "Derivator.h"

double Derivator::Deriv_1(double x0, double h, int type){

    if (type == 0) //central
        return ( Eval(x0 + h) - Eval(x0 - h) ) / (2*h);

    if (type == 1) //forward
        return ( 4*Eval(x0 + h) - Eval(x0 + 2*h) - 3*Eval(x0) ) / (2*h);
    
    if (type == 2) //backward
        return ( Eval(x0 - 2*h) - 4*Eval(x0 - h) + 3*Eval(x0) ) / (2*h); 

    return -1;  


}

double Derivator::Deriv_2(double x0, double h, int type){

    if (type == 0) //central
        return ( 16*Eval(x0 - h) - Eval(x0 - 2*h) - 30*Eval(x0) + 16*Eval(x0 + h) - Eval(x0 + 2*h) ) / (12*h*h);
    
    if (type == 1) //forward 
        return ( Eval(x0 + 2*h) - 2*Eval(x0 + h) + Eval(x0) ) / (h*h);
    
    if (type == 2) //backward
        return ( Eval(x0) - 2*Eval(x0 - h) + Eval(x0 - 2*h) ) / (h*h);

    return -1;
} 

double Derivator::Deriv_3(double x0, double h, int type){

    if (type == 0) //central
        return ((Eval(x0 + 3*h) - 3*Eval(x0 + h) + 3*Eval(x0 - h) - Eval(x0 - 3*h)) / (8*h*h*h)); //type == 0
    
    if (type == 1) //forward
        return ((Eval(x0 + 3*h) - 3*Eval(x0 + 2*h) + 3*Eval(x0 + h) - Eval(x0)) / (h*h*h));
    
    if (type == 2) //backward
        return ((Eval(x0) - 3*Eval(x0 - h) + 3*Eval(x0 - 2*h) - Eval(x0 - 3*h)) / (h*h*h));
    
    return -1;
}