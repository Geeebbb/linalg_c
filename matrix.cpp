#include "matrix.h"
using namespace std;
namespace linalg
{

    Matrix::Matrix(int rows, int columns ){
        m_columns = columns;
        m_rows = rows;
        m_ptr = new double[rows * columns];
    }
    Matrix::Matrix(int rows) : Matrix(rows, 1){}
    Matrix :: Matrix()
    {
        // Инициализация переменных
        m_rows = 0;
        m_columns = 0;
        m_ptr = nullptr;
    }
    //Е.reshape(rows, cols)
    void Matrix::reshape(int rows,int columns) //REWRITE
    {

        if ((this->m_rows)*(this->m_columns) == (rows*columns))
        {
            (*this).m_rows = rows;
            (*this).m_columns = columns;
        }
        else
            throw runtime_error("impossible operation");

    }
// онструктор копировани:
    Matrix:: Matrix(const Matrix& M)
    {
        m_rows=M.m_rows;
        m_columns=M.m_columns;
        m_ptr=new double[m_rows*m_columns];
        for(int i=0;i<m_rows*m_columns;i++)
        {
            m_ptr[i]=M.m_ptr[i];
        }
    }
//  онструктор перемещени:
    Matrix:: Matrix(Matrix&& M)
    {
        this->m_columns = M.m_columns;
        this->m_rows = M.m_rows;
        this->m_ptr = M.m_ptr;

        M.m_ptr = nullptr;
        M.m_columns = 0;
        M.m_rows = 0;
    }

// ”нифицированна€ инициализаци€ (использовать std::initializer_list)
    Matrix::Matrix(const initializer_list<double> lst)
    {
        m_rows=lst.size();
        m_columns=1;
        m_ptr=new double[m_rows];
        copy(lst.begin(),lst.end(),m_ptr);

    }

    Matrix::Matrix(const initializer_list<initializer_list<double>> lst)
    {
        m_rows = lst.size();
        m_columns = lst.begin()->size();
        m_ptr = new double [lst.size() * lst.begin()->size()];
        int i = 0;
        for (auto ptr_i = lst.begin(); ptr_i != lst.end(); ptr_i++, i++)
        {
            int j = 0;
            for (auto ptr_i_j = (*ptr_i).begin(); ptr_i_j != (*ptr_i).end(); ptr_i_j++, j++)
                m_ptr[(i * m_columns) + j] = *ptr_i_j;
        }
    }

//  опирующее присваивание
// копирование без учета размерностей
    Matrix& Matrix::operator=(const Matrix& M)
    {
        for (int i = 0 ; i<M.m_rows; ++i)
        {
            for (int j = 0; j < M.m_columns;j++)
                (*this)(i, j) = M(i, j);
        }
        return *this;
    }

    Matrix& Matrix::operator=(Matrix& M)
    {
        this->~Matrix();                 //delete[] (*this).m_ptr;
        (*this).m_rows = M.m_rows;
        (*this).m_columns = M.m_columns;
        (*this).m_ptr = M.m_ptr;
        M.m_ptr = nullptr;
        M.m_rows = 0;
        M.m_columns = 0;
        return *this;
    }
    //ќператор вызова функции, чтобы обращатьс€ к элементам (с возможностью их изменени€, если это не константна€ матрица):
    double& Matrix::operator()(int i,int j )
    {
        return *(m_ptr + i * m_columns + j);
    }

    double& Matrix::operator()(int i, int j) const
    {
        return *(m_ptr + i * m_columns + j);
    }

    // оператор вывода
    ostream& operator<<(ostream& out, const Matrix& M )
    {
        double max_element = 0;
        for (int i = 0; i < M.m_rows; i++)
        {
            for (int j = 0; j < M.m_columns; j++)
                max_element = max(max_element, M.m_ptr[i*M.m_columns+j]);
        }
        int element_width = to_string(max_element).length() + 1;
        for (int i = 0; i < M.m_rows;i++)
        {
            for (int j = 0; j < M.m_columns; j++)
            {
                out<<setw(element_width)<<M.m_ptr[i*M.m_columns+j]<<" ";
            }
            out<<endl;
        }
        return out;
    }

    //ѕоэлементное сложение матриц (true)
    Matrix Matrix:: operator+(const Matrix &M) const
    {
        if (((*this).m_columns == M.m_columns) && ((*this).m_rows == M.m_rows))
            {
            Matrix Mcopy = *this;
            return Mcopy+=M;
            }
        else
            throw runtime_error("impossible operation");


    }
    //ѕоэлементное сложение матриц
    Matrix& Matrix::operator+=(const Matrix& M)
    {
        if ((this->m_columns == M.m_columns) && (this->m_rows == M.m_rows))
        {
            for (int i = 0; i < M.m_rows * M.m_columns; i++)
            {
                m_ptr[i] += M.m_ptr[i];
            }
            return *this;

        }
        else
            throw runtime_error("impossible operation");
    }

    //ѕоэлементное вычитание матриц

    Matrix Matrix:: operator- (const Matrix& M) const
    {
         if (((*this).m_columns == M.m_columns) && ((*this).m_rows == M.m_rows))
        {
            Matrix Mcopy = *this;

        Matrix minus_M = M * (-1);
        return (Mcopy += minus_M);

        }
        else
            throw runtime_error("impossible operation");
    }

    //ѕоэлементное вычитание матриц
    Matrix& Matrix::operator-=(const Matrix& M)
    {
        if ((this->m_columns == M.m_columns) && (this->m_rows == M.m_rows))
        {
            for (int i = 0; i < M.m_rows * M.m_columns; i++)
            {
                m_ptr[i] -= M.m_ptr[i];
            }
            return *this;
        }
        else
            throw runtime_error("impossible operation");
    }

    //ѕеремножение матриц *= lvalue

    Matrix& Matrix::operator*=(const Matrix & M)
    {
        if (this->m_columns == M.m_rows)
        {
            double a = 0;
            for (int i = 0; i < this->m_rows; i++)
            {
                for (int j = 0; j <M.m_columns; j++)
                {
                    for (int r = 0;  r< M.m_rows; r++)
                        a += (*this)(i,r) * M(r,j);
                    (*this)(i,j) = a;
                    a = 0;
                }
            }
            return (*this);
        }
        else
            throw runtime_error("impossible operation");
    }

    //pеремножение совместимых матриц * rvalue
    Matrix Matrix::operator*(const Matrix & M) const
    {
        Matrix Mcopy= (*this);
        if ((*this).m_columns == M.m_rows)
            return (Mcopy *= M);
        else
            throw runtime_error("impossible operation");

    }


    //ѕоэлементное перемножение на число *= lvalue
    Matrix& Matrix::operator*=(double x)
    {
        for (int i = 0; i < m_rows * m_columns; i++)
            m_ptr[i] *= x;
        return (*this);
    }

    //ѕоэлементное перемножение на число справа * rvalue
    Matrix Matrix::operator*(double x) const
    {
        Matrix Mcopy = *this;
        return (Mcopy *= x);
    }

    //ѕоэлементное перемножение на число слева (rvalue)
    Matrix operator*(double x,const Matrix& M){
        Matrix Mcopy = M;
        return (Mcopy*= x);
    }
    // operator ==

    bool Matrix::operator==(const Matrix& M )
    {
        if ((m_columns == M.m_columns) && (m_rows == M.m_rows))
        {
            for (int i = 0; i < m_rows * m_columns; i++)
            {
                if (m_ptr[i] != M.m_ptr[i])

                    return false;

            }
            return true;
        }

        else
            throw runtime_error("impossible operation");

    }
    // != operator
    bool Matrix::operator!=(const Matrix& M )
    {
        return 1-(*this==M);
    }


    //Ќорма
    double Matrix::norm()
    {
        double norm = 0;
        for (int i = 0; i < this->m_rows; i++)
        {
            for (int j = 0; j < this->m_columns; j++)
                norm += (*this)(i,j)*(*this)(i,j);
        }
        return sqrt(norm);
    }

    //sled матрицы
    double Matrix::trace()
    {
        if (this->m_rows == this->m_columns)
        {
            double trace = 0;
            for (int i = 0; i < m_columns; i++)
                trace += (*this)(i, i);
            return trace;
        }
        else
            throw runtime_error("impossible operation");
    }

    double Matrix::det()const
    {
        if (m_rows == m_columns) {
            for (int i = 0; i < m_columns; i++) {
                int nonZeroIndex = -1;
                for (int j = i; j < m_rows; j++) {
                    if ((*this)(j, i) != 0) {
                        nonZeroIndex = j;
                        break;
                    }
                }
                if (nonZeroIndex != -1) {
                    if (nonZeroIndex != i) {
                        for (int k = 0; k < m_columns; k++) {
                            swap((*this)(i, k), (*this)(nonZeroIndex, k));
                        }
                    }
                    double diagonalElement = (*this)(i, i);
                    for (int j = i + 1; j < m_rows; j++) {
                        double factor = (*this)(j, i) / diagonalElement;
                        for (int k = 0; k < m_columns; k++) {
                            (*this)(j, k) -= (*this)(i, k) * factor;
                        }
                    }
                }
            }
            double determinant = 1;
            for (int i = 0; i < m_rows; i++) {
                determinant *= (*this)(i, i);
            }
            return determinant;
        } else {
            throw runtime_error("impossible operation");
        }
    }

    //ѕр€мой ход метода √аусса

    Matrix& Matrix::gauss_forward()
    {
        for (int i = 0; i < m_columns; i++)
        {
            // ѕоиск ненулевого элемента в текущем столбце, начина€ с текущей строки
            int nonzero_row = -1; // »ндекс строки с ненулевым элементом
            for (int j = i ; j < m_rows; j++)
            {
                if ((*this)(j, i) != 0)
                {
                    nonzero_row = j;
                    break;
                }
            }

            if (nonzero_row != -1)
            {
                // ≈сли найден ненулевой элемент, мен€ем местами текущую строку с строкой, содержащей ненулевой элемент
                for (int k = 0; k < m_columns; k++)
                {
                    double temp = (*this)(i, k);
                    (*this)(i, k) = (*this)(nonzero_row, k);
                    (*this)(nonzero_row, k) = temp;
                }

                // ƒелаем текущий элемент равным 1 путем делени€ всей строки на него
                double number = (*this)(i, i);
                for (int j = 0; j < m_columns; j++)
                    (*this)(i, j) /= number;
                // ¬ычитаем текущую строку, умноженную на число, из всех следующих строк
                for (int j = i + 1; j < m_rows; j++)
                {
                    number = (*this)(j, i);
                    for (int k = 0; k < m_columns; k++)
                        (*this)(j, k) -= (*this)(i, k) * number;

                }
            }
        }
        return (*this);
    }
    Matrix& Matrix::gauss_backward()
    {
        // мы начинаем с последней строки и идем вверх
        for (int i = m_columns-1; i >=0  ; i--) {

            // ƒл€ каждой строки ищем не нулевой элемент в этом столбце
            for (int j = 0; j <m_rows ; j++)
            {
                if ((*this)(j, i) != 0)
                {
                    double temp;
                    // ћен€ем строки местами
                    for (int k = m_columns-1; k >= 0; k--)
                    {
                        temp = (*this)(i, k);
                        (*this)(i, k) = (*this)(j, k);
                        (*this)(j, k) = temp;
                    }
                    break;
                }
            }

            // ≈сли элемент по диагонали не равен нулю
            if ((*this)(i, i) != 0) {
                double number = (*this)(i, i);

                // ƒелим все элементы строки на диагональный дл€ получени€ единицы в верхнетреугольной матрице
                for (int j = 0; j < m_columns; j++)
                    (*this)(i, j) /= number;

                // ¬ычитаем из верхних строк текущую строку (умноженную на соответствующий элемент), чтобы занулить остальные элементы в текущем столбце
                for (int j = i-1; j >= 0; j--) {
                    number = (*this)(j, i);
                    for (int k = m_columns-1; k >= 0; k--)
                        (*this)(j, k) -= (*this)(i, k) * number;
                }
            }
        }
        return (*this);
    }
// ‘ункци€ дл€ нахождени€ ранга матрицы
    int Matrix::  rank()
    {
        Matrix Mcopy = *this;

        // ѕримен€ем метод √аусса
        Mcopy.gauss_backward(); // ѕредполагаетс€, что этот метод уже реализован

        // —читаем количество ненулевых строк из преобразованной матрицы
        int rank = 0;
        for (int i = 0; i < Mcopy.m_rows; ++i) {
            bool allZeros = true;
            for (int j = 0; j < Mcopy.m_columns; ++j) {
                if (Mcopy(i, j) != 0.0) { // ѕредполагаетс€, что метод (i, j) возвращает значение €чейки
                    allZeros = false;
                    break;
                }
            }
            if (!allZeros) {
                rank++;
            }
        }

        return rank;
    }


//соединить матриц
      Matrix concatenate(Matrix& m1, Matrix& m2)
      {

    if (m1.rows() != m2.rows()) {
        throw runtime_error("Operation is impossible");
    }
    else {
        Matrix conc_m(m1.m_rows, m1.m_columns + m2.m_columns);
        for (int i = 0; i < m1.rows(); ++i) {
            for (int j = 0; j < m1.columns(); ++j) {
                conc_m(i,j) = m1(i, j);
            }
        }
        for (int i = 0; i < m1.rows(); ++i) {
            for (int j = m1.columns(); j < m1.columns() + m2.columns(); ++j) {
                conc_m(i, j) = m2(i, j - m1.columns());
            }
        }

        return conc_m;
    }

      }
      //транспонирование
Matrix transpose(Matrix& M)
    {
        Matrix T(M.columns(), M.rows());
        for (int i = 0; i < M.rows(); i++) {
            for (int j = 0; j < M.columns(); j++) {
                T(j, i) = M(i, j);
            }
        }
        return T;
    }
    //Обратная матрица
    Matrix invert( Matrix& m)
    {
    int size = m.rows();
    // Проверяем, является ли матрица квадратной
    if (size != m.columns())
        throw std::runtime_error("Matrix must be square");

    // Создаем единичную матрицу того же размера
    Matrix I(size, size);
    for (int i = 0; i < size; ++i)
        I(i, i) = 1.0;

    for (int i = 0; i < size; ++i) {
        double diag = m(i, i);
        for (int j = 0; j < size; ++j) {
            m(i, j) /= diag;
            I(i, j) /= diag;
        }

        for (int j = 0; j < size; ++j) {
            if (i != j) {
                double ratio = m(j, i);

                for (int k = 0; k < size; ++k) {
                    m(j, k) -= ratio * m(i, k);
                    I(j, k) -= ratio * I(i, k);
                }
            }
        }
    }
    return I;
}
//POW
Matrix power(Matrix &m, int p)
{
    if (m.rows() != m.columns()) {
        throw runtime_error("Operation is impossible");
    }

    Matrix result(m.rows(),m.columns());
    if (p < 0) {
        m = invert(m);
        p = -p;
    }

    for (int i = 0; i < m.rows(); ++i) {
        result(i, i) = 1;
    }

    while (p) {
        if (p %2== 1)
            result = result * m;
        m = m * m;
        p = p/2;
    }

    return result;
}
Matrix solve(Matrix& A, Matrix& f)
{
    if (A.rows() != f.rows() || f.columns() > 1)
        {
        throw runtime_error("Invalid sizes of the input matrices.");
    }

    Matrix P = concatenate(A, f);
    P.gauss_forward();

    Matrix tmp_matr(A.rows(), 1);

    for (int i = 0; i < A.rows(); ++i) {

        tmp_matr(i, 0) = P(i, A.columns());

    }


    return tmp_matr;
}


Matrix ToDiagonal(Matrix &M)
{
    if(M.rows()==M.columns())
    {
        Matrix result=M;
        result=transpose(result.gauss_forward());
        return result.gauss_forward();

    }
else
    throw runtime_error("Invalid sizes of the input matrices.");

}
}



