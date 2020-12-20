#ifndef LIB_CBNS_H
#define LIB_CBNS_H

#include <iostream>  
#include <string>
#include <complex> 
#include <math.h>

using namespace std;  

#define N_MAX 512
#define MAX_PRECISION 32


string decToCBNS(int n);
string decToCBNS(double n);
string decToCBNS(complex<float> n);
complex<float> CBNStoDec(string str);

string addComplex(string A, string B);
string addComplex(double A, double B);
string addComplex(complex<float> A, complex<float> B);
string addComplexAlg(string strA, string strB);

string subComplex(string strA, string strB);
string subComplex(int A, int B);
string subComplex(complex<float> A, complex<float> B);
string subComplexAlg(string strA, string strB);


string multiComplex(string A, string B);
string multiComplex(double A, double B);
string multiComplex(complex<float> A, complex<float> B);

int DivK(string str);
string converge(string strB);
string divComplex(string strA, string strB);
string divComplex(complex<float> strA, complex<float> strB);

string adjustComplex(string str);
void complexOp(complex<float> A, string op, complex<float> B);
complex<float> adjFPComplex(complex<float> Num);

template <typename T> string tostr(const T& t);
string print(complex<float> A, complex<float> B, string Res, string operation);
void toArr(string str, int A[]);
string ArrToStr(int A[]);



//--------------------------------------------------------------------------------//
//--------------------------------[Adjust\Print operations]-----------------------//

void complexOp(complex<float> A, string op, complex<float> B){
    
    string Res;
    complex<float> ResNum;
    if (op == "x" || op == "*"){
        Res = multiComplex(A, B); 
        ResNum = A * B;
    }
    else if (op == "/"){
        Res = divComplex(A, B);
        ResNum = A / B;
    }
    else if (op == "+"){
        Res = addComplex(A, B);
        ResNum = A + B;
    }
    else if (op == "-"){
        Res = subComplex(A, B);
        ResNum = A - B;
    }
    else {
        cout << "Incorrect Operation" << endl << endl;
        return;
    }


    cout << "Normal Results = " <<  ResNum << endl;
    cout << print(A, B, Res, op);
}


string ArrToStr(int A[]){
    string resultStr = "";
    for (int i = N_MAX-1; i >= 0; i--){
        resultStr = resultStr + to_string(A[i]);
    }

    return adjustComplex(resultStr);
}


template <typename T> string tostr(const T& t) { 
   ostringstream os; 
   os<<t; 
   return os.str(); 
} 


string print(complex<float> A, complex<float> B, string Res, string operation)
{

    string op = " " + operation + " ";
    complex<float> ResComplex = CBNStoDec(Res);

    string ResStr = "(" + tostr(A.real()) + "," + tostr(A.imag()) + "j)" + op + "(" + tostr(B.real()) + "," + tostr(B.imag()) + "j) = "
                            + decToCBNS(A) + op + decToCBNS(B) + " = "
                            + Res + " = (" + tostr(ResComplex.real()) + "," + tostr(ResComplex.imag()) + "j)" + "\n\n";

    return ResStr;

}

complex<float> adjFPComplex(complex<float> Num){
    if (abs(Num.real()) < 1e-10) Num = complex<float>(0,Num.imag());
    if (abs(Num.imag()) < 1e-10) Num = complex<float>(Num.real(), 0);

    return Num;
}


string adjustComplex(string str){
    //cout << endl << "adjustComplex: " << str << endl;
    if ((signed long int) str.find_first_of("1") == -1 && (signed long int) str.find_first_of('.') == -1)
    {
        return "0";
    }
    else if ((signed long int) str.find_first_of("1") == -1 && (signed long int) str.find_first_of('.') != -1)
    {
        return ("0"+str.substr(str.find_first_of('.')-1, str.size()));
    }
    else if ((signed long int) str.find_first_of('.') != -1)
    {
        // int point = (signed long int) str.find_first_of('.');
        // if ( (str.size() - point) > 64 ) str = str.substr(0, (64+point));
 
        if ((signed long int) str.find_first_of('.') < (signed long int) str.find_first_of("1"))
        {
            //if (str[0] == '.') str = "0" + str;
            str = str.substr(str.find_first_of('.')-1, str.size());
            str = str.substr(0, str.find_last_of('1')+1);
            return str;
        }
        else
        {
            str = str.substr(str.find_first_of('1'), str.size());
            if((signed long int) str.find_first_of('.') < (signed long int) str.find_last_of("1"))
                str = str.substr(0, str.find_last_of('1')+1);
            return str;
        }
    }

    return str.substr(str.find_first_of("1"), str.size());
}




//--------------------------------------------------------------------------------//
//--------------------------------[Addition]--------------------------------------//

string addComplex(complex<float> A, complex<float> B){
    return addComplex(decToCBNS(A), decToCBNS(B));
}


string addComplex(double A, double B){
    return addComplex(decToCBNS(A), decToCBNS(B));
}


string addComplex(string strA, string strB) {

    if (strA.empty()) return strB;
    if (strB.empty()) return strA;
    

    int posDotA = (signed long int) strA.find_first_of('.');
    int posDotB = (signed long int) strB.find_first_of('.');

    string strInt, strDec;
    
    if (posDotA != -1 && posDotB != -1) {
        strInt = addComplexAlg(strA.substr(0, posDotA), strB.substr(0, posDotB));
        strA = strA.substr(posDotA+1, strA.size());
        strB = strB.substr(posDotB+1, strB.size());

        if (strA.size() > strB.size())
            strB = strB + string(strA.size() - strB.size(), '0');
        else 
            strA = strA + string(strB.size() - strA.size(), '0');

        strDec = addComplexAlg(strA, strB);

        int check = (signed long int)(strDec.size() - strA.size()-1);
        if (check < 0) strDec = string(-check, '0') + strDec;

        strDec.insert(strDec.size() - strA.size(), sizeof('.'), '.');
        
        strInt = addComplexAlg(strInt, strDec.substr(0, strDec.find_first_of('.')) );
        strDec = strDec.substr(strDec.find_first_of('.'), strDec.size());

        return adjustComplex(strInt+strDec);

    } else if (posDotA != -1) {
        strInt = addComplexAlg(strA.substr(0, posDotA), strB);
        strDec = strA.substr(posDotA, strA.size());
        
        return (strInt+strDec);

    } else if (posDotB != -1) {
        strInt = addComplexAlg(strA, strB.substr(0, posDotB));
        strDec = strB.substr(posDotB, strB.size());
            
        return (strInt+strDec);
    }
    
    return addComplexAlg(strA, strB);
    
}

void propagate (int A[], int idx) {
    if (idx >= N_MAX) return;
    A[idx]++;

    if (A[idx] == 2){
        A[idx] = 0;
        propagate(A, idx+2);
        propagate(A, idx+3);

    } else if (A[idx] == 3) {
        A[idx] = 1;
        propagate(A, idx+2);
        propagate(A, idx+3);

    }
}


string addComplexAlg(string strA, string strB) {
    int A[N_MAX]; int B[N_MAX];
    toArr(strA, A);
    toArr(strB, B);

    for (int i = 0; i < N_MAX; i++) {

        if (A[i] + B[i] == 0) {
            A[i] = 0;
        }
        else if (A[i] + B[i] == 1) {
            A[i] = 1;
            B[i] = 0;
        }
        else if (A[i] + B[i] == 2) {
            A[i] = 0;
            B[i] = 0;

            propagate(A, i+2);
            propagate(A, i+3);

        }

    }
    

    return ArrToStr(A);
}




//--------------------------------------------------------------------------------//
//--------------------------------[Subtraction]-----------------------------------//

string subComplex(int A, int B){
    return subComplex(decToCBNS(A), decToCBNS(B));
}

string subComplex(complex<float> A, complex<float> B){
    return subComplex(decToCBNS(A), decToCBNS(B));
}

string subComplex(string strA, string strB) {

    if (strA.empty()) return strB;
    if (strB.empty()) return strA;
    

    int posDotA = (signed long int) strA.find_first_of('.');
    int posDotB = (signed long int) strB.find_first_of('.');

    string strInt, strDec;
    
    if (posDotA != -1 && posDotB != -1) {
        strInt = subComplexAlg(strA.substr(0, posDotA), strB.substr(0, posDotB));
        strA = strA.substr(posDotA+1, strA.size());
        strB = strB.substr(posDotB+1, strB.size());

        if (strA.size() > strB.size())
            strB = strB + string(strA.size() - strB.size(), '0');
        else 
            strA = strA + string(strB.size() - strA.size(), '0');

        strDec = subComplexAlg(strA, strB);
        
        int check = (signed long int)(strDec.size() - strA.size()-1);
        if (check < 0) strDec = string(-check, '0') + strDec;

        strDec.insert(strDec.size() - strA.size(), sizeof('.'), '.');
        strInt = addComplexAlg(strInt, strDec.substr(0, strDec.find_first_of('.')) );
        strDec = strDec.substr(strDec.find_first_of('.'), strDec.size());

        return adjustComplex(strInt+strDec);

    } else if (posDotA != -1) {
        strInt = subComplexAlg(strA.substr(0, posDotA), strB);
        strDec = strA.substr(posDotA, strA.size());
        
        return (strInt+strDec);

    } else if (posDotB != -1) {
        strInt = subComplexAlg(strA, strB.substr(0, posDotB));

        strB = strB.substr(posDotB+1, strB.size());
        strDec = subComplexAlg("0", strB);

        int diff = strDec.size() - strB.size();

        if (diff > 0)
        {
            strInt = addComplex(strDec.substr(0, diff), strInt);
            strDec = strDec.substr(diff, strDec.size());
        }

        return (strInt+"."+strDec);
    }
    
    return subComplexAlg(strA, strB);    
}


string subComplexAlg(string strA, string strB) {
    int A[N_MAX]; int B[N_MAX];// int C[N_MAX]; int res[N_MAX];
    toArr(strA, A);
    toArr(strB, B);

    for (int i = 0; i < N_MAX; i++) {
        if (A[i] == 1 && B[i] == 1){
            A[i] = 0;
            B[i] = 0;
        } else if (A[i] == 0 && B[i] == 1){
            A[i] = 1;
            B[i] = 0;

            propagate(A, i+2);
            propagate(A, i+3);
            propagate(A, i+4);

        }
    }

    return ArrToStr(A);
}




//--------------------------------------------------------------------------------//
//--------------------------------[Multiplication]--------------------------------//
string multiHelp(string res, string A, string B){

    if (B.size() == 0)
        return res;
    
    char C = B.back();
    A = A + string(1, '0');


    if (C == '1') return multiHelp(addComplex(res, A) , A, B.substr(0, B.size()-1));
    else          return multiHelp(addComplex(res, ""), A, B.substr(0, B.size()-1));
}


string multiComplex(complex<float> A, complex<float> B){
    return multiComplex(decToCBNS(A), decToCBNS(B));
}

string multiComplex(double A, double B){
    return multiComplex(decToCBNS(A), decToCBNS(B));
}


string multiComplex(string A, string B){

    int posDotA = (signed long int) A.find_first_of('.');
    int posDotB = (signed long int) B.find_first_of('.');

    //cout << endl << "[1] " << A << " - " << B << endl;
    if (posDotA != -1)  A.erase(posDotA, 1);
    if (posDotB != -1)  B.erase(posDotB, 1);
    //cout  << "[2] " << A << " - " << B << endl;


    if (A.empty() || B.empty())
        return "0";

    char C = B.back();

    string res;
    if (C == '1') res = multiHelp(A , A, B.substr(0, B.size()-1));    
    else          res = multiHelp("", A, B.substr(0, B.size()-1));

    // Multiply two doubleing points work only for small numbers
    if (posDotA != -1 && posDotB != -1) {
        if (res.size() < (A.size() + B.size()) ) res = string((A.size()+ B.size()-res.size()) , '0') + res;

        res.insert(res.size()-(A.size()-posDotA)-(B.size()-posDotB), sizeof('.'), '.');

    } else if (posDotA != -1) {
        if (res.size() < A.size()) res = string((A.size()-res.size()) , '0') + res;
        res.insert(res.size()-(A.size()-posDotA), sizeof('.'), '.');

    } else if (posDotB != -1) {
        if (res.size() < B.size()) res = string((B.size()-res.size()) , '0') + res;
        res.insert(res.size()-(B.size()-posDotB), sizeof('.'), '.');
    }

    return adjustComplex(res);
}

//

void toArr(string str, int A[]) {
    int size = str.size();

    if (str.size() > N_MAX){
        cout << endl << "WARRNING: The number inserted is larger than N_MAX" << endl;
        exit(0);
    }

    for (int i = 0; i < N_MAX; i++) A[i] = 0;

    for (int i = 0; i < size; i++)
        A[size - 1 - i] = (str[i] == '1') ? 1 : 0;
}




//--------------------------------------------------------------------------------//
//--------------------------------[Division]--------------------------------------//

//Find the first '1' index for K division operation
int DivK(string str) {

    int posDot = (signed long int) str.find_first_of('.');

    //Check if th number is a decimal number
    if (posDot == -1){ 
        for (int i = 0; i < (signed long int) str.size(); i++)
            if (str[i] == '1') return (str.size()-1-i);

    } else {

        //if the number only has decimal values
        for (int i = 0; i < posDot; i++)
            if (str[i] == '1') return (posDot-1-i);
        
        for (int i = posDot+1; i < (signed long int) str.size(); i++)
            if (str[i] == '1') return (posDot-i);

    }

    return 0;
}


string converge(string strB){

    int k = DivK(strB);
    complex<float> NumB = CBNStoDec(strB);

    //The initial value of the division operation
    complex<float> origNum = (complex<float>) pow(complex<float>(-1, 1), -k);

    complex<float> Num = origNum;
    complex<float> newNum = origNum ;

    for (int i=0; i < 20; i++){
        
        Num = newNum;
        newNum = newNum * (complex<float>(2,0) - NumB * newNum);

        //For tesing
        //cout << i << " - " << newNum << " - " << Num << endl;

        //If the number diverges, switch to decision rule.
        if (isinf(newNum.real()) || isnan(newNum.real()) || isinf(newNum.imag()) || isnan(newNum.imag())) break;

        //If the number converges, retrun value
        if (abs(abs(newNum) - abs(Num)) < 1e-6) return decToCBNS(adjFPComplex(newNum));
    }
    
    //Switch to decision rule
    Num = CBNStoDec(multiComplex(origNum, complex<float>(0,1)));
    newNum = Num;

    for (int i=0; i < 20; i++){
        Num = newNum;
        newNum = newNum * (complex<float>(2,0) - NumB * newNum);

        //For tesing
        //cout << i << " - " << newNum << " - " << Num << endl;

        //If the number converges after switching decision rule, retrun value
        if (abs(abs(newNum) - abs(Num)) < 1e-6) return decToCBNS(adjFPComplex(newNum));
    }

    return decToCBNS(origNum);
}

string divComplex(complex<float> strA, complex<float> strB){
    return divComplex( decToCBNS(strA), decToCBNS(strB));
}

string divComplex(string strA, string strB){

    return multiComplex(strA, converge(strB));
}





//--------------------------------------------------------------------------------//
//--------------------------------[Conversion]------------------------------------//

complex<float> CBNStoDec(string str){

    int posDot = (signed long int) str.find_first_of('.');
    complex<float> Num(0,0);

    if (posDot == -1){ 
        for (int i = 0; i < (signed long int) str.size(); i++)
            if (str[i] == '1') Num = Num + (complex<float>) pow(complex<float>(-1, 1), (str.size()-1-i));

    } else {
        
        for (int i = 0; i < posDot; i++)
            if (str[i] == '1') Num = Num + (complex<float>) pow(complex<float>(-1, 1), (posDot-1-i));

        for (int i = posDot+1; i < (signed long int) str.size(); i++)
            if (str[i] == '1') Num = Num + (complex<float>) pow(complex<float>(-1, 1), (posDot-i));
    }

    return adjFPComplex(Num);
}


string decToCBNS(double n) {

    if (n == (int)n) return decToCBNS((int)n);

    static string ROM[4] = {"0000", "0001", "1100", "1101"};

    int binaryNum[MAX_PRECISION]; 

    //Initializing array
    for (int i = 0; i < MAX_PRECISION; i++) binaryNum[i] = 0;

    int intN = (int) n;
    n = n - intN;

    //Convert from Dec to binary base 4
    int i = 1; double fraction = 0;
    for (i = 1; i < MAX_PRECISION; i++) { 
        fraction = (n * 4.0 >= 4.0)? 0: n * 4.0;
        binaryNum[i] = floor(fraction); 
        n = fraction - binaryNum[i];
    } 

    //Convert to base -4 
    for (int j = MAX_PRECISION-1; j >= 1; j--){
        if (binaryNum[j]!=0 && (j%2) == 1) {
            binaryNum[j] = -binaryNum[j] + 4;
            binaryNum[j-1] = binaryNum[j-1]+1;

            int k = 1;
            while (binaryNum[j-k] > 3 && k < j){
                binaryNum[j-k] = binaryNum[j-k]%4;
                binaryNum[j-k-1] = binaryNum[j-k-1]+1;
                k++;
            }
        }
    }
    

    //printing binary base complex(-1+j)
    string resultStr = addComplexAlg(decToCBNS(intN), ROM[binaryNum[0]]) + '.';
    for (int j = 1; j < MAX_PRECISION; j++) {
        resultStr = resultStr + ROM[binaryNum[j]];
    }

    return adjustComplex(resultStr);
}


string decToCBNS(int n) 
{ 
    static string ROM[4] = {"0000", "0001", "1100", "1101"};
    // array to store binary number 
    int binaryNum[N_MAX]; 

    //Initializing array
    for (int i = 0; i < N_MAX; i++) binaryNum[i] = 0;

    //Convert from Dec to binary base 4
    int i = 0; 
    for (i = 0; n > 0 && i < N_MAX; i++) { 
        binaryNum[i] = n % 4; 
        n = n >> 2; 
    } 


    //Convert to base -4 
    for (int j = 1; j < i; j++){
        if (binaryNum[j]!=0 && (j%2) == 1) {
            binaryNum[j] = -binaryNum[j] + 4;
            binaryNum[j+1] = binaryNum[j+1]+1;
            if (j+1 == i) i++;
        } else if (binaryNum[j] > 3) {

            binaryNum[j] = binaryNum[j]%4;
            binaryNum[j+1] = binaryNum[j+1]+1;
            if (j+1 == i) i++;
        }
    }


    //printing binary base complex(-1+j)
    string str = "";
    for (int j = i-1; j >= 0; j--) {
        str = str + ROM[binaryNum[j]];
    }

    return adjustComplex(str);
    
} 


string decToCBNS(complex<float> n) 
{
    string strReal, strImag;

    if (n.real() >= 0)
        strReal = decToCBNS(n.real());
    else
        strReal = multiComplex(decToCBNS(-n.real()), "11101");    

    if (n.imag() >= 0)
        strImag = multiComplex(decToCBNS(n.imag()), "11");
    else
        strImag = multiComplex(decToCBNS(-n.imag()), "111");

    return addComplex(strReal, strImag);
    
} 


//--------------------------------------------------------------------------------//
//--------------------------------[Functions for web]-----------------------//
string printToCBNS(complex<float> C)
{

    string ResStr = "(" + tostr(C.real()) + "," + tostr(C.imag()) + "j) = " + decToCBNS(C) + "\n\n";
    
    return ResStr;

}

string printToComplex(string str)
{

    if (str == "") str = "0";
    complex<float> C = CBNStoDec(str);

    string ResStr = str + " = (" + tostr(C.real()) + "," + tostr(C.imag()) + "j)" + "\n\n";
    
    return ResStr;

}


#endif