#include <iostream>  
#include <string>
#include <complex> 
#include <math.h>

using namespace std;  

#define N_MAX 512
#define MAX_PRECISION 32


string decToBinary(int n);
string decToBinary(double n);
string decToBinary(complex<float> n);

complex<float> binaryToDec(string str);

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
complex<float> converge(string strB);
string divComplex(string strA, string strB);
string divComplex(complex<float> strA, complex<float> strB);

string adjustComplex(string str);
void complexOp(complex<float> A, char op, complex<float> B);
complex<float> adjFPComplex(complex<float> Num);

template <typename T> string tostr(const T& t);
string print(complex<float> A, complex<float> B, string Res, string operation);


void complexOp(complex<float> A, char op, complex<float> B){
    
    string Res;
    
    if (op == 'x' || op == '*')
        Res = multiComplex(A, B);
    else if (op == '/')
        Res = divComplex(A, B);
    else if (op == '+')
        Res = addComplex(A, B);
    else if (op == '-')
        Res = subComplex(A, B);
    else {
        cout << "Incorrect Operation" << endl << endl;
        return;
    }

    cout << A << " " << op  << " " << B << " = " << decToBinary(A)  << " " << op << " " <<  decToBinary(B) << " = " << Res << " = " << binaryToDec(Res) << endl << endl;
}

template <typename T> string tostr(const T& t) { 
   ostringstream os; 
   os<<t; 
   return os.str(); 
} 


string print(complex<float> A, complex<float> B, string Res, string operation)
{

    string op = " " + operation + " ";
    complex<float> ResComplex = binaryToDec(Res);

    string ResStr = "(" + tostr(A.real()) + "," + tostr(A.imag()) + "j)" + op + "(" + tostr(B.real()) + "," + tostr(B.imag()) + "j) = "
                            + decToBinary(A) + op + decToBinary(B) + " = "
                            + Res + " = (" + tostr(ResComplex.real()) + "," + tostr(ResComplex.imag()) + "j)" + "\n\n";

    return ResStr;

}

string printToCBNS(complex<float> C)
{

    string ResStr = "(" + tostr(C.real()) + "," + tostr(C.imag()) + "j) = " + decToBinary(C) + "\n\n";
    
    return ResStr;

}

string printToComplex(string str)
{

    if (str == "") str = "0";
    complex<float> C = binaryToDec(str);

    string ResStr = str + " = (" + tostr(C.real()) + "," + tostr(C.imag()) + "j)" + "\n\n";
    
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

int DivK(string str) {

    int posDot = (signed long int) str.find_first_of('.');

    if (posDot == -1){
        for (int i = 0; i < (int) str.size(); i++)
            if (str[i] == '1') return (str.size()-1-i);

    } else {

        for (int i = 0; i < posDot; i++)
            if (str[i] == '1') return (posDot-1-i);

        for (int i = posDot+1; i < (int) str.size(); i++)
            if (str[i] == '1') return (posDot-i);

    }
    return 0;
}

complex<float> converge(string strB){

    int k = DivK(strB);
    complex<float> NumB = binaryToDec(strB);
    complex<float> origNum = (complex<float>) pow(complex<float>(-1, 1), -k);

    complex<float> Num = origNum;
    complex<float> newNum = origNum ;

    for (int i=0; i < 20; i++){

        Num = newNum;
        newNum = newNum * (complex<float>(2,0) - NumB * newNum);

        if (isinf(newNum.real()) || isnan(newNum.real()) || isinf(newNum.imag()) || isnan(newNum.imag())) break;
        if (abs(abs(newNum) - abs(Num)) < 1e-6) return adjFPComplex(newNum);
    }

    //cout << "Switch to decision rule" << endl;
    Num = binaryToDec(multiComplex(origNum, complex<float>(0,1)));
    newNum = Num;

    for (int i=0; i < 20; i++){
        Num = newNum;
        newNum = newNum * (complex<float>(2,0) - NumB * newNum);

        //cout << i << " - " << newNum << " - " << Num << endl;

        if (abs(abs(newNum) - abs(Num)) < 1e-6) return adjFPComplex(newNum);
    }

    return origNum;
}

string divComplex(complex<float> strA, complex<float> strB){

    return divComplex( decToBinary(strA), decToBinary(strB) );
}

string divComplex(string strA, string strB){

    return multiComplex(strA, decToBinary(converge(strB)));
}


string multiHelp(string res, string A, string B){

    if (B.size() == 0)
        return res;

    char C = B.back();
    A = A + string(1, '0');


    if (C == '1') return multiHelp(addComplex(res, A) , A, B.substr(0, B.size()-1));
    else          return multiHelp(addComplex(res, ""), A, B.substr(0, B.size()-1));
}


string multiComplex(complex<float> A, complex<float> B){
    return multiComplex(decToBinary(A), decToBinary(B));
}

string multiComplex(double A, double B){
    return multiComplex(decToBinary(A), decToBinary(B));
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

    // Multiply two floating points work only for small numbers
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


void toArr(string str, int *A) {
    int size = str.size();

    if (str.size() > N_MAX){
        //cout << endl << "WARRNING: The number inserted is larger than N_MAX" << endl;
        exit(0);
    }

    for (int i = 0; i < N_MAX; i++) A[i] = 0;

    for (int i = 0; i < size; i++)
        A[size - 1 - i] = (str[i] == '1') ? 1 : 0;
}

string addComplex(complex<float> A, complex<float> B){
    return addComplex(decToBinary(A), decToBinary(B));
}


string addComplex(double A, double B){
    return addComplex(decToBinary(A), decToBinary(B));
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


string addComplexAlg(string strA, string strB) {
    int A[N_MAX]; int B[N_MAX];
    toArr(strA, A);
    toArr(strB, B);

    for (int i = 0; i < N_MAX; i++) {

        for (int j = i; j < N_MAX; j++) {

            if (A[j] > 0 && A[j + 1] > 0 && B[j] > 0 && B[j + 1] > 0 && B[j + 2] > 0 ) {
                A[j]--;
                A[j + 1]--;
                B[j]--;
                B[j + 1]--;
                B[j + 2]--;
            }
            else if (A[j] > 0 && A[j + 1] > 0 && A[j + 2] > 0 && B[j] > 0 && B[j + 1] > 0) {
                A[j]--;
                A[j + 1]--;
                A[j + 2]--;
                B[j]--;
                B[j + 1]--;
            }
        }

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
            A[i + 1] += 0;
            A[i + 2] += 1;
            A[i + 3] += 1;
        }
        else if (A[i] + B[i] == 3) {
            A[i] = 1;
            B[i] = 0;
            A[i + 1] += 0;
            A[i + 2] += 1;
            A[i + 3] += 1;
        }
        else if (A[i] + B[i] == 4) {
            A[i] = 0;
            B[i] = 0;

            A[i + 1] += 0;
            A[i + 2] += 0;
            A[i + 3] += 0;
            A[i + 4] += 1;
            A[i + 5] += 2;
            A[i + 6] += 1;
        } else if (A[i] + B[i] == 5) {
            A[i] = 1;
            B[i] = 0;

            A[i + 1] += 0;
            A[i + 2] += 0;
            A[i + 3] += 0;
            A[i + 4] += 1;
            A[i + 5] += 2;
            A[i + 6] += 1;
        }


    }

    string resultStr = "";
    for (int i = N_MAX; i > 0; i--){
        resultStr = resultStr + to_string(A[i - 1]);
    }

    return adjustComplex(resultStr);
}

string subComplex(int A, int B){
    return subComplex(decToBinary(A), decToBinary(B));
}

string subComplex(complex<float> A, complex<float> B){
    return subComplex(decToBinary(A), decToBinary(B));
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
        //cout << strInt << " - "  << endl;
        strB = strB.substr(posDotB+1, strB.size());
        strDec = subComplexAlg("0", strB);

        int diff = strDec.size() - strB.size();
        //cout << strDec << " - " << diff << endl;
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

            A[i+2]++;
            A[i+3]++;
            A[i+4]++;

            for (int j = i+1; j < N_MAX-2; j++) {
                if (A[j] == 1 && B[j] == 1){
                    A[j] = 0;
                    B[j] = 0;
                } else if (A[j] == 2){
                    A[j] = 0;
                    A[j+2]++;
                    A[j+3]++;
                } else if (A[j] == 3){
                    A[j] = 1;
                    A[j+2]++;
                    A[j+3]++;
                }
            }
        }
    }

    string resultStr = "";
    for (int i = N_MAX; i > 0; i--){
        resultStr = resultStr + to_string(A[i - 1]);
    }
    return adjustComplex(resultStr);
}


complex<float> binaryToDec(string str){

    int posDot = (signed long int) str.find_first_of('.');
    complex<float> Num(0,0);

    if (posDot == -1){
        for (int i = 0; i < (int)str.size(); i++)
            if (str[i] == '1') Num = Num + (complex<float>) pow(complex<float>(-1, 1), (str.size()-1-i));

    } else {

        for (int i = 0; i < posDot; i++)
            if (str[i] == '1') Num = Num + (complex<float>) pow(complex<float>(-1, 1), (posDot-1-i));

        for (int i = posDot+1; i < (int)str.size(); i++)
            if (str[i] == '1') Num = Num + (complex<float>) pow(complex<float>(-1, 1), (posDot-i));
    }

    return adjFPComplex(Num);
}

string decToBinary(double n) {

    if (n == (int)n) return decToBinary((int)n);

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
    string resultStr = addComplexAlg(decToBinary(intN), ROM[binaryNum[0]]) + '.';
    for (int j = 1; j < MAX_PRECISION; j++) {
        resultStr = resultStr + ROM[binaryNum[j]];
    }

    return adjustComplex(resultStr);
}


string decToBinary(int n)
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


string decToBinary(complex<float> n)
{
    string strReal, strImag;

    if (n.real() >= 0)
        strReal = decToBinary(n.real());
    else
        strReal = multiComplex(decToBinary(-n.real()), "11101");

    if (n.imag() >= 0)
        strImag = multiComplex(decToBinary(n.imag()), "11");
    else
        strImag = multiComplex(decToBinary(-n.imag()), "111");

    return adjustComplex(addComplex(strReal, strImag));

}