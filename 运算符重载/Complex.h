#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Complex
{
public:
    Complex() :m_real(0), m_imag(0) {}
    Complex(T x, T y) :m_real(x), m_imag(y) {}
    // ¸´ÖÆ¹¹Ôì
    Complex(const Complex& c) :m_real(c.m_real), m_imag(c.m_imag) {}

    ~Complex() {}



    friend istream& operator>> (istream& input, Complex<T>& c)
    {
        cout << "input m_real m_imag";
        input >> c.m_real >> c.m_imag;
        return input;
    }

    friend ostream& operator<< (ostream& output, Complex<T>& c)
    {
        if (c.m_imag >= 0)
        {
            output << c.m_real << "+" << c.m_imag << "i";
        }
        else
        {
            output << c.m_real << c.m_imag << "i" << endl;
        }
        return output;
    }

public:

protected:
private:
    T m_real;
    T m_imag;
};

//template<typename T>
//istream& operator>>(istream& input, Complex<T>& c) 
//{
//    cout << "input m_real m_imag";
//    input >> c.m_real >> c.m_imag;
//    return input;
//}
//
//template<typename T>
//ostream& operator<<(ostream& output, Complex<T>& c)
//{
//    if (c.m_imag >= 0)
//    {
//        output << c.m_real << "+" << c.m_imag << "i" << endl;
//    }
//    else 
//    {
//        output << c.m_real << c.m_imag << "i" << endl;
//    }
//    return output;
//}