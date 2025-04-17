#include <iostream>

bool isPrime(const int& n)
{
    if (n == 1 || n == 2) return true;

    if (n % 2 == 0) return false;

    for (int i = 3; i <= sqrt(n) + 1; i += 2) 
    {
        if (n % i == 0) 
        {
            return false;
        }
    }

    return true;
}

int main()
{
    setlocale(LC_ALL, "rus");

    int trigger = 0;

    int n = 0;
    std::cout << "Введите целое положительное число: ";
    std::cin >> n;
    for (int i = 1; i < n; i++)
    {
        if (i % 10 == 0)
        {
            std::cout << std::endl;
        }

        if (isPrime(i))
        {
            std::cout << i << " ";
        }
    }
}
