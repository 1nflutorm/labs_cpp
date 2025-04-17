#include <iostream>

int main()
{
    setlocale(LC_ALL, "rus");

    int count = 0;//количество чисел
    int sum = 0;//сумма всех чисел
    int max = INT_MIN;//максимальное значение
    int min = INT_MAX;//минимальное значение
    int div5Count = 0;//количество чисчел кратных 5
    int pow2count = 0;//количество степеней двойки
    int lastTwoNums[2] = { 0, 0 };//массив, хранящий два последних числа
    int numBiggerThatSum2BeforeCount = 0;//количество чисел, превышающих сумму двух предшествующих членов последовательности.

    int num = 0;
    while (true)
    {
        std::cout << "Введите число: ";
        std::cin >> num;

        if (!num)
        {
            break;
        }

        count++;
        sum += num;

        max = num > max ? num : max;
        min = num < min ? num : min;
        
        div5Count += (num > 0 && num % 5 == 0) ? 1 : 0;

        pow2count += (num && !(num & (num - 1))) ? 1 : 0;

        if (count > 2) 
        {
            numBiggerThatSum2BeforeCount += (lastTwoNums[0] + lastTwoNums[1] < num) ? 1 : 0;
        }

        lastTwoNums[0] = lastTwoNums[1];
        lastTwoNums[1] = num;
    }

    std::cout   << "Среднее арифметическое введенных чисел: " 
                << static_cast<double>(sum) / static_cast<double>(count) << std::endl;

    std::cout << "Разница между максимумом и минимумом: " << max - min << std::endl;

    std::cout << "Количество положительных чисел, кратных числу 5: " << div5Count << std::endl;

    std::cout << "Количество чисел, являющихся степенью двойки: " << pow2count << std::endl;

    std::cout   << "Количество чисел, превышающих сумму двух предшествующих членов последовательности: " 
                << numBiggerThatSum2BeforeCount << std::endl;

    return 0;
}
