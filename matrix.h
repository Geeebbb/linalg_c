#include<iostream>
#include<string.h>
#include<cmath>
#include <iomanip>
#include <sstream>
//#include <vector>
#include<algorithm>
#include <stdexcept>
#ifndef MATRIX_H
#define MATRIX_H
using namespace std;
namespace linalg
{
    class Matrix
    {
    private:
        double* m_ptr=nullptr;
        int m_rows=0;
        int m_columns=0;
    public:

        int rows()
        {
            return m_rows;
        }

        int columns()
        {
            return m_columns;
        }

        bool empty()
        {
            return (m_ptr && m_rows && m_columns);
        }

        void reshape(int rows,int columns);
        // ƒефолтный конструктор
        Matrix();
        //  онструкторы с параметрами:
        Matrix(int rows);
        Matrix(int rows, int columns );
        // онструктор копировани€:
        Matrix(const Matrix& M);
        //  онструктор перемещени€:
        Matrix(Matrix &&M) ;

        // ”нифицированна€ инициализаци€ (использовать std::initializer_list)
        Matrix(const initializer_list<double> lst);
        Matrix(const initializer_list<initializer_list<double>> lst);
        //ƒиструктор
        ~Matrix()
        {
            if(m_ptr!=nullptr)
                delete[] m_ptr;
        }
        //  опирующее присваивание
        // ѕеремещающее присваивание
        Matrix& operator=(const Matrix &M);
        Matrix& operator=(Matrix &M);

         double &operator()(int i, int j) const;
        double &operator()(int i, int j);
        //оператор вывода
        friend ostream& operator<<(ostream& out, const Matrix& M);
        //ѕоэлементное сложение матриц
        Matrix operator+ (const Matrix &M) const;
        // ѕоэлементное сложение матриц
        Matrix& operator+= (const Matrix& M);
        //ѕоэлементное вычитание матриц
        Matrix operator- (const Matrix &M) const;
        // ѕоэлементное вычитание матриц
        Matrix& operator-= (const Matrix& M);
        //ѕеремножение совместимых матриц (rvalue)
        Matrix operator*(const Matrix & M) const;
        //ѕоэлементное перемножение на число(число слева rvalue)
        friend Matrix operator*(double x,const Matrix& M);
        //ѕоэлементное перемножение на число, число справа (rvalue)
        Matrix operator*(double x) const;
        //ѕеремножение совместимых матриц (lvalue)
        Matrix& operator*=(const Matrix & M);
        //ѕоэлементное перемножение на число (lvalue)
        Matrix& operator*=(double x);
        // operators == and !=
        bool operator == (const Matrix& M);
        bool operator != (const Matrix& M);
        //norm
        double norm();
        //trace
        double trace();
        //det
        double det()const;
        //ѕр€мой ход метода √аусса
        Matrix& gauss_forward();
        //ќбраьный ход метода √аусса
        Matrix& gauss_backward();
        //–анг
        int rank();
       friend Matrix concatenate(Matrix &m1, Matrix &m2);
    friend Matrix power(Matrix &m, int p);
   friend  Matrix invert(Matrix &m);
   friend  Matrix transpose(Matrix &M);
   friend  Matrix solve(Matrix &A, Matrix &f);
   friend  Matrix ToDiagonal(Matrix &M);




    };
    Matrix concatenate(Matrix &m1, Matrix &m2);
    Matrix power(Matrix &m, int p);
    Matrix invert( Matrix &m);
    Matrix transpose(Matrix &M);
    Matrix solve(Matrix &A, Matrix &f);
    Matrix ToDiagonal(Matrix &M);

    Matrix operator*(double x,const  Matrix& M);
    ostream& operator<<(ostream &out, const Matrix &M);

}
#endif




