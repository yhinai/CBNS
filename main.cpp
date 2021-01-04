#include <iostream>  
#include <string>
#include <complex> 
#include <math.h>

#include "libCBNS.h"

using namespace std;  


int main(){

    cout << "|| ------------- Example of CBNS Arithmetic Operations ------------- ||" << endl << endl;
    string strTest = decToCBNS(complex<float>(2.35,0));
    cout << complex<float>(2.35,0) << " x 1     = " << strTest << " x 1     = " << CBNStoDec(multiComplex(strTest, "1")) << endl;
    cout << complex<float>(2.35,0) << " x 11101 = " << strTest << " x 11101 = " << CBNStoDec(multiComplex(strTest, "11101")) << endl;
    cout << complex<float>(2.35,0) << " x 11    = " << strTest << " x 11    = " << CBNStoDec(multiComplex(strTest, "11")) << endl;
    cout << complex<float>(2.35,0) << " x 111   = " << strTest << " x 111   = " << CBNStoDec(multiComplex(strTest, "111")) << endl << endl;

    complexOp(complex<float>(32.5,18.75), "+", complex<float>(12,7.25));
    complexOp(complex<float>(32.5,18.75), "-", complex<float>(12,7.25));
    complexOp(complex<float>(32.5,18.75), "*", complex<float>(12,7.25));
    complexOp(complex<float>(32.5,18.75), "/", complex<float>(12,7.25));


    cout << endl << "|| ---------------------------- Testing ---------------------------- ||" << endl << endl;
    
    complex<float> A, B;
    char operation;
    cout << endl << "Enter the complex arithmetic operation in the following format (i.e. (1,3) + (4,6))" << endl << endl;

    while (1){
        cin >> A >> operation >> B;

        complexOp(A, string(1, operation), B);
    }


    return 0;  

}
