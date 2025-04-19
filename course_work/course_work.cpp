#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

enum EOperation
{
	CONSOLE_INPUT = 1,
	CONSOLE_OUTPUT,
	FILE_INPUT,
	FILE_OUTPUT,
	EDIT,
	PERSONAL_TASK,
	EXIT
};

enum EEditOption
{
	EDIT_ROW = 1,
	EDIT_COLUMN,
	EDIT_ELEMENT,
	REWRITE
};


void printMenu()
{
	std::cout << "Доступные операции:\n";
	std::cout << "1. Консольный ввод матриц.\n";
	std::cout << "2. Консольный вывод матриц.\n";
	std::cout << "3. Файловый ввод матриц.\n";
	std::cout << "4. Файловый вывод матриц.\n";
	std::cout << "5. Редактирование матриц.\n";
	std::cout << "6. Персональное задание.\n";
	std::cout << "7. Выход.\n";
	std::cout << "Выберите операцию: ";
}

void deleteMatrix(int**& matrix, const int& size)
{
	if (!matrix)
	{
		return;
	}

	for (int i = 0; i < size; i++)
	{
		delete[] matrix[i];
		matrix[i] = nullptr;
	}
	delete[] matrix;
	matrix = nullptr;
}

void deleteAllMatix(int**& A, int**& B, int**& C, const int& size)
{
	deleteMatrix(A, size);
	deleteMatrix(B, size);
	deleteMatrix(C, size);
}

void initMatrix(int**& matrix, const int& size)
{
	matrix = new int* [size];
	for (int i = 0; i < size; i++)
	{
		matrix[i] = new int[size];
	}
}

void initAllMatix(int**& A, int**& B, int**& C, const int& size)
{
	initMatrix(A, size);
	initMatrix(B, size);
	initMatrix(C, size);
}

void fillMatrixByConsole(int**& matrix, const int& size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << "Введите (" << (i + 1) << "," << (j + 1) << ") элемент матрицы: ";
			std::cin >> matrix[i][j];
		}
	}
}

void printMatrix(int**& matrix, const int& size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

bool isMatrixValid(int**& A, int**& B, int**& C)
{
	return A && B && C;
}

void writeMatrixToFile(std::fstream& file, int** matrix, const int& size, const char& name)
{
	file << "Matrix " << name << std::endl;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			file << matrix[i][j] << " ";
		}
		file << std::endl;
	}

	file << std::endl;
}

int* splitLine(std::string line, const int& size, const char& sep)
{
	int* arr = new int[size];

	for (int i = 0; i < size - 1; i++)
	{
		size_t space = line.find(' ');
		if (space == -1)
		{
			delete[] arr;
			arr = nullptr;
		}
		std::string num = line.substr(0, space);
		line = line.substr(space + 1);
		arr[i] = std::stoi(num);
	}

	if (line.size() == 0 || line == " ")
	{
		delete[] arr;
		arr = nullptr;
	}
	else
	{
		arr[size - 1] = std::stoi(line);
	}

	return arr;
}

bool readMatrixFromFile(std::fstream& file, int** matrix, const int& size)
{
	std::string line;
	for (int i = 0; i < size; i++)
	{
		std::getline(file, line);
		int* arr = splitLine(line, size, ' ');
		if (!arr)
		{
			return false;
		}
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = arr[j];
		}
		delete[] arr;
	}

	return true;
}

void editRow(int** matrix, const int& size)
{
	int row = 0;
	std::cout << "\nВведите номер строки, которую хотите отредактировать: ";
	std::cin >> row;
	if (row > size || row < 1)
	{
		std::cout << "\nТакой строки не сушествует!\n\n";
		return;
	}
	for (int i = 0; i < size; i++)
	{
		std::cout << "Введите элемент " << row << " строки " << i + 1 << " элемента: ";
		std::cin >> matrix[row - 1][i];
	}
	return;
}

void editColumn(int** matrix, const int& size)
{
	int col = 0;
	std::cout << "\nВведите номер столбца, который хотите отредактировать: ";
	std::cin >> col;
	if (col > size || col < 1)
	{
		std::cout << "\nТакого столбца не сушествует!\n\n";
	}
	for (int i = 0; i < size; i++)
	{
		std::cout << "Введите элемент " << i + 1 << " строки " << col << " элемента: ";
		std::cin >> matrix[i][col - 1];
	}
}

void editElement(int** matrix, const int& size)
{
	int i = 0, j = 0;
	std::cout << "\nВведите номер строки: ";
	std::cin >> i;
	std::cout << "Введите номер элемента: ";
	std::cin >> j;
	if (j > size || j < 1 || i > size || i < 1)
	{
		std::cout << "\nТакого столбца не сушествует!\n\n";
	}
	std::cout << "Введите элемент " << i << " строки " << j << " столбца: ";
	std::cin >> matrix[i - 1][j - 1];
}

void edit(int** matrix, const int& size)
{
	int option;
	std::cout << "\nВыберите вариант редактирования:\n"; // строки 43-48 дают выбор пользователю: что нужно отредактировать
	std::cout << "1. Строку матрицы\n";
	std::cout << "2. Столбец матрицы\n";
	std::cout << "3. Один элемент\n";
	std::cout << "4. Полностью переписать матрицу\n";
	std::cout << "Ваш выбор: ";
	std::cin >> option;

	switch (option)
	{
	case EDIT_ROW:
		editRow(matrix, size);
		break;
	case EDIT_COLUMN:
		editColumn(matrix, size);
		break;
	case EDIT_ELEMENT:
		editElement(matrix, size);
		break;
	case REWRITE:
		fillMatrixByConsole(matrix, size);
		break;
	default:
		std::cout << "\nВыбран неизвестный пункт меню!\n\n";
		break;
	}
}

std::set<int> toSet(int** matrix, const int& size)
{
	std::set<int> set;
	if (!matrix)
	{
		return set;
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			set.insert(matrix[i][j]);
		}
	}

	return set;
}

int main()
{
	setlocale(LC_ALL, "rus");

	//объявление матриц, т.к. с классами не работали, матрицу в класс не выделяю
	int** A = nullptr;
	int** B = nullptr;
	int** C = nullptr;
	int size = 0;//хранит текущую размерность матриц

	while (true)
	{
		printMenu();

		int option = 0;
		std::cin >> option;

		std::fstream file;
		std::string line;

		switch (option)
		{
		case CONSOLE_INPUT:
		{
			deleteAllMatix(A, B, C, size);

			std::cout << "\nВведите размерность матриц: ";
			std::cin >> size;

			initAllMatix(A, B, C, size);

			std::cout << "\nЗаполнение матрицы А:\n";
			fillMatrixByConsole(A, size);
			std::cout << "\nЗаполнение матрицы B:\n";
			fillMatrixByConsole(B, size);
			std::cout << "\nЗаполнение матрицы C:\n";
			fillMatrixByConsole(C, size);

			std::cout << "\nЗаполнение матриц завершено!\n\n";
			break;
		}
		case CONSOLE_OUTPUT:
		{
			if (!isMatrixValid(A, B, C))
			{
				std::cout << "\nМатрицы не валидны!\n\n";
				break;
			}

			std::cout << "Матрица А:\n";
			printMatrix(A, size);
			std::cout << "Матрица В:\n";
			printMatrix(B, size);
			std::cout << "Матрица С:\n";
			printMatrix(C, size);

			std::cout << "\n\n";

			break;
		}
		case FILE_INPUT:
		{
			deleteAllMatix(A, B, C, size);

			file.open("matrix.txt", std::ios_base::in);
			if (!file.is_open())
			{
				std::cerr << "\nОшибка: " << strerror(errno) << "\n\n";
				break;
			}

			std::getline(file, line);
			if (line.size() < 7 && line.find("Size: ") != 0)//"Size: ".size() == 6 + размер 1 символа
			{
				std::cout << "\nНекорректный формат файла!\n\n";
				break;
			}

			size = std::stoi(line.substr(line.find(' ') + 1));

			initAllMatix(A, B, C, size);

			for (int i = 0; i < 3; i++)
			{
				std::getline(file, line);
				if (line.size() != 8 && line.find("Matrix ") != 0)
				{
					deleteAllMatix(A, B, C, size);
					break;
				}

				char name = line.substr(line.find(' ') + 1, 1)[0];
				int** matrix = nullptr;
				if (name == 'A')
				{
					matrix = A;
				}
				else if (name == 'B')
				{
					matrix = B;
				}
				else if (name == 'C')
				{
					matrix = C;
				}
				else
				{
					deleteAllMatix(A, B, C, size);
					break;
				}

				if (!readMatrixFromFile(file, matrix, size))
				{
					deleteAllMatix(A, B, C, size);
					break;
				}

				std::getline(file, line);
			}

			if (!isMatrixValid(A, B, C))
			{
				deleteAllMatix(A, B, C, size);
				std::cout << "\nНекорректный формат файла!\n\n";
				break;
			}

			file.close();

			std::cout << "\nМатрицы успешно прочтаны!\n\n";

			break;
		}
		case FILE_OUTPUT:
		{
			if (!isMatrixValid(A, B, C))
			{
				std::cout << "\nМатрицы не валидны!\n\n";
				break;
			}

			file.open("matrix.txt", std::ios_base::out | std::ios_base::trunc);
			if (!file.is_open())
			{
				std::cerr << "\nОшибка: " << strerror(errno) << "\n\n";
				break;
			}

			file << "Size: " << size << std::endl;
			writeMatrixToFile(file, A, size, 'A');
			writeMatrixToFile(file, B, size, 'B');
			writeMatrixToFile(file, C, size, 'C');

			file.close();

			std::cout << "\nДанные успешно записаны в файл!\n\n";

			break;
		}
		case EDIT:
		{
			if (!isMatrixValid(A, B, C))
			{
				std::cout << "\nМатрицы не валидны!\n\n";
				break;
			}

			char name;
			std::cout << "\nВедите имя редактируемой матрицы: ";
			std::cin >> name;

			int** matrix;
			if (name == 'A') { matrix = A; }
			else if (name == 'B') { matrix = B; }
			else if (name == 'C') { matrix = C; }
			else
			{
				std::cout << "\nТакой матрицы не существует!\n\n";
				break;
			}

			edit(matrix, size);

			std::cout << "\nРедактирование завершено!\n\n";

			break;
		}
		case PERSONAL_TASK:
		{
			if (!isMatrixValid(A, B, C))
			{
				std::cout << "\nМатрицы не валидны!\n\n";
				break;
			}

			std::set<int> ASet = toSet(A, size);
			std::set<int> BSet = toSet(B, size);

			std::vector<int> result;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (ASet.contains(C[i][j]) || BSet.contains(C[i][j]))
					{
						result.push_back(C[i][j]);
					}
				}
			}

			result.erase(std::unique(result.begin(), result.end()), result.end());
			std::sort(result.begin(), result.end());

			std::cout << "\nЭлементы матриц А и В, которые встречаются в матрице С:\n";

			if (!result.size())
			{
				std::cout << "Нет таких элементов!";
			}

			for (int i = 0; i < result.size(); i++)
			{
				std::cout << result[i] << ' ';
			}
			std::cout << "\n\n";
			break;
		}
		case EXIT:
			deleteAllMatix(A, B, C, size);
			break;
		default:
			std::cout << "\nВыбран неизвестный пункт меню!\n\n";
			break;
		}

	}

	return 0;
}