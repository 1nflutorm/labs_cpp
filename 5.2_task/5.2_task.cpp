#include <iostream>

void initMatrix(int**& matrix, const int& rows, const int& cols)
{
    matrix = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols];
    }
}

void deleteMatrix(int**& matrix, const int& rows)
{
    if (!matrix)
    {
        return;
    }

    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;
}

void fillMatrixByConsole(int**& matrix, const int& rows, const int& cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << "Введите (" << (i + 1) << "," << (j + 1) << ") элемент матрицы: ";
            std::cin >> matrix[i][j];
        }
    }
}

void printMatrix(int**& matrix, const int& rows, const int& cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void matrixSqr(int**& A, int**& B, int**& C, const int& size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < size; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void copy(int**& dst, int**& src, const int& rows, const int& cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            dst[i][j] = src[i][j];
        }
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    int** A = nullptr;
    int** B = nullptr;
    int** C = nullptr;
    int size;
    int pow;

    std::cout << "Введите размерность матрицы: ";
    std::cin >> size;

    initMatrix(A, size, size);
    std::cout << "Заполнение исходной матрицы:\n";
    fillMatrixByConsole(A, size, size);

    std::cout << "Введите степень в которую надо возвести матрицу: ";
    std::cin >> pow;

    initMatrix(C, size, size);
    initMatrix(B, size, size);

    copy(B, A, size, size);

    while ((pow--) > 1)
    {
        matrixSqr(A, B, C, size);
        copy(A, C, size, size);
    }

    printMatrix(C, size, size);

    deleteMatrix(A, size);
    deleteMatrix(B, size);
    deleteMatrix(C, size);
}