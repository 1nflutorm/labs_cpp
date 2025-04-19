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

int** multiplication(int**& A, int**& B, const int& rowsA, const int& colsA, const int& rowsB, const int& colsB)
{
    if (colsA != rowsB)
    {
        return nullptr;
    }

    int** C;
    initMatrix(C, rowsA, colsB);

    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < colsA; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
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

int main()
{
    setlocale(LC_ALL, "rus");

    int** A = nullptr;
    int** B = nullptr;

    int rowsA, colsA, rowsB, colsB;
    std::cout << "Введите количетво строк матрицы A: ";
    std::cin >> rowsA;
    std::cout << "Введите количетво столбцов матрицы A: ";
    std::cin >> colsA;

    std::cout << "Введите количетво строк матрицы B: ";
    std::cin >> rowsB;
    std::cout << "Введите количетво столбцов матрицы B: ";
    std::cin >> colsB;

    if (colsA != rowsB)
    {
        std::cout << "Количество столбцов матрицы А должно быть равно количеству строк матрицы В\n"
            << "Перемножение невозможно\n";

        return 0;
    }

    initMatrix(A, rowsA, colsA);
    std::cout << "Заполнение матрицы А: ";
    fillMatrixByConsole(A, rowsA, colsA);

    initMatrix(B, rowsB, colsB);
    std::cout << "Заполнение матрицы B: ";
    fillMatrixByConsole(B, rowsB, colsB);

    int** C = multiplication(A, B, rowsA, colsA, rowsB, colsB);
    if (C)
    {
        printMatrix(C, rowsA, colsB);
        deleteMatrix(C, rowsA);
    }

    deleteMatrix(A, rowsA);
    deleteMatrix(B, rowsB);

    return 0;
}
