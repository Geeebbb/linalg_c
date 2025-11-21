#include <iostream>
#include "matrix.h" // Подключение заголовочного файла
#include "test.h"
void test ()
{
    using namespace linalg;

    Matrix m0;
    cout << "m0.rows(): " << m0.rows() << endl;
    cout << "m0.columns(): " << m0.columns() << endl;
    cout << "m0.empty(): " << m0.empty() << endl;
    cout << endl;

    Matrix m1(4);
    cout << "m1.rows(): " << m1.rows() << endl;
    cout << "m1.columns(): " << m1.columns() << endl;
    cout << "m1.empty(): " << m1.empty() << endl;
    cout << endl;

    Matrix m21 = {{1, 2, 2},{3, 4, 22}};
    Matrix m22 = {{6, 3,   23},{3, 11.2, 13},{9, 0,   8},{3, 4,   2}};

    cout << "Copy constructor" << endl;
    Matrix m3(m21);
    cout << m3 << endl;

    cout << "copy constructor2" << endl;
    Matrix m4(move(m22));
    cout << m4 << endl;
    cout<<m2<<endl;

    Matrix m5 = {{1, 2, 3},{4, 5, 6}};

    Matrix m6 = {{1, 2, 3, 4, 5, 6}};

    Matrix m51 = m5;
    cout << m51 << endl;
    cout << m5 << endl;

;
    cout << m6 << endl;

    const Matrix m = {{2,4,6},{1,3,5}};
    cout << m << endl;

    double mi = m(1, 2);
    cout<<mi<<endl;

    cout << "+operator" << endl;
    Matrix m7 = {{1, 2, 3},{4, 4, 1}};
    Matrix m8 = {{1, 1, 1},{1, 1, 1}};
    cout << m7 << endl;
    cout << m8 << endl;
    Matrix summa = (m7 + m8);
    cout << summa << endl;

    cout << "+=operator" << std::endl;
    Matrix m9 = {{3, 10, 3},
                 {1, 10, 3},
                 {4, 10, 1}};

    cout << m9 << endl;
    m9 += m9;
    cout << m9 << endl;

    cout << "-operator" << std::endl;
    Matrix sub = m7 - m8;
    cout << sub << endl;

    cout << "-=operator" << endl;
    m9 -= m9;
    cout << m9 << endl;

    cout << "*_operator" << endl;
    Matrix m10 = m8 * 2;
    cout << m10 << endl;

    cout << "*_operator" << endl;
    Matrix m102 = 2 * m8;
    cout << m102 << endl;

    cout << "m*m_operator" << endl;
    Matrix    m12={{1,1},{2,2}};
    Matrix m13={{1,1},{1,1}};
    Matrix m11 =m12*m13;
    cout <<  m11 << endl;

    cout << "*=" << endl;
    m12 *= m13;
    cout << m12 << endl;

    cout << "== and != " << endl;
    Matrix m14 = {{4, 2, 11},
                  {1, 2, 3},
                  {3, 1, 9}};
    cout << m9 << '\n';
    cout << m14 << endl;
    cout << (m9 == m14) << endl;
    cout << (m9 != m14) << endl;

    cout << "Norm" << endl;
    cout << m14.norm() << endl;

    cout << "Trace" << endl;
    cout << m14.trace() << endl;
    cout<<m14<<endl;

    cout << "Det" << endl;
    cout << m14.det() << endl;

    cout << "Gauss_forward" << endl;
    cout << m14.gauss_forward() << endl;

    cout << "Gauss_backward" << endl;
    cout << m14.gauss_backward() << endl;

    cout << "Rank" << endl;
    cout << m14.rank() << endl;

    Matrix m15={{1,1,1},{1,1,1},{1,1,1}};
    Matrix CON=concatenate(m14,m15);
    cout << "Matrix concatenate" << endl;
    cout << CON<< endl;

    Matrix T = transpose(m14);
    cout<< "Transpose" << endl;
    cout<< T << endl;

    Matrix I = invert(m14);
    cout << "Invert" << endl;
    cout << I<< endl;

    cout << "Power" << endl;
    Matrix P=power(m9, 1);
    cout << P <<endl;

    Matrix D={{999,29},{3,4}};
    Matrix Di=ToDiagonal(D);
    cout<<"Diagonal type"<<'\n'<<Di<<endl;
}

void test2(){
    using namespace linalg;
    Matrix A = { {1,2,3},{2,3,4}, {1, 2, 7} };
    Matrix f1 = { 6,8,9 };
    cout << "Solve" << endl;
    cout << solve(A, f1) << endl;

}

