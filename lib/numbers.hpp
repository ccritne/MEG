#pragma once
#include<bits/stdc++.h>
using namespace std;

class number
{
    private:

        bool condDen;
        double n, d;
        double value;

    public:
        number(double num) {
            n = num; d = 1; condDen = false; value = n;
        };
        number(double num, double den) {
            n = num; d = den; 
            value = num/den;
            if(d == 1) condDen = false; else condDen = true;
        };
        number operator +(number num){
            number res(0);
            res.n = num.n*d + n*num.d;
            res.d = num.d*d;

            res.toFrac();

            if(res.d == 1) 
                res.condDen = false; 
            else 
                res.condDen = true;

            return res;
        };
        friend ostream& operator<<(ostream &os, number num){
            if(num.condDen)
                os << num.n << '/'<< num.d << endl;
            else
                os << num.n << endl;

            return os;
        };
        void toFrac(){
            
            int pI = value;

            double pD = value - pI;
            int i = to_string(pD).size() - 2;

            int num = int(value*pow(10,i));
            int den = int(pow(10,i));
            
            int g_c_d = gcd(num,den);
            num /= g_c_d;
            den /= g_c_d;
        
            n = num;
            d = den;

            if(d==1) 
                condDen = false;
            else
                condDen = true;
        }
};