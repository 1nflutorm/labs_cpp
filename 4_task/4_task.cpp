#include <iostream>
#include <unordered_map>

template<class T>
void bubbleSort(T* arr, const int& size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {

            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template<class T>
int getMinVal(T* arr, const int& start, const int& end)
{
    int result = arr[start];
    for (int i = start + 1; i < end; i++)
    {
        if (result > arr[i])
        {
            result = arr[i];
        }
    }

    return result;
}


int main()
{
    setlocale(LC_ALL, "rus");

    int arr[15];
    for (int i = 0; i < 15; i++)
    {
        std::cout << "Введите " << i << " число: ";
        std::cin >> arr[i];
    }

    std::cout << "Минимальное значение первой пятерки:" << getMinVal(arr, 0, 5) << std::endl;
    std::cout << "Минимальное значение второй пятерки:" << getMinVal(arr, 5, 10) << std::endl;
    std::cout << "Минимальное значение третьей пятерки:" << getMinVal(arr, 10, 15) << std::endl;

    int lastPow = 1;
    int firstIndex = 0;
    for (int i = 0; i < 15; i++)
    {
        bool isPow = arr[i] && !(arr[i] & (arr[i] - 1));
        if (!isPow || arr[i] <= lastPow)
        {
            firstIndex = i;
            lastPow = 1;
        }
        lastPow = arr[i];
    }

    std::cout <<    "Номер элемента, начиная с которого в массиве непрерывно"
                    "идут степени числа 2 в порядке возрастания: ";
    if (firstIndex == 14)
    {
        std::cout << "Нет последовательности\n";
    }
    else
    {
        std::cout << firstIndex << std::endl;
    }

    std::cout << "Отсортированный массив:\n";
    bubbleSort(arr, 15);
    for (int i = 0; i < 15; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Элементы которые встречаются в массиве более 1 раза:\n";
    std::unordered_map<int, int> valuesCount;
    for (int i = 0; i < 14; i++)
    {
        valuesCount[arr[i]]++;
    }

    std::unordered_map<int, int>::iterator it = valuesCount.begin();
    for (it; it != valuesCount.end(); it++)
    {
        if (it->second > 1)
        {
            std::cout << it->first << " ";
        }
    }
    std::cout << std::endl;
}
