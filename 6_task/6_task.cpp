#include <iostream>
#include <fstream>
#include <string>

int countWords(std::string s)
{
    int count = 1;
    size_t index = 0;
    while (true)
    {
        index = s.find(' ');
        if (index == -1)
        {
            return count;
        }
        s = s.substr(index + 1);

        count++;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    std::fstream fin("lab6.txt", std::ios_base::in);
    if (!fin.is_open())
    {
        std::cerr << "Ошибка: " << strerror(errno);
        return 0;
    }

    int count = 0;
    std::cout << "Введите количество слов в предложении: ";
    std::cin >> count;

    std::string line;
    while (!fin.eof())
    {
        std::getline(fin, line);
        size_t dot = 0;
        while (true)
        {
            dot = line.find('.');
            if (dot == -1)
            {
                break;
            }

            std::string sentense = line.substr(0, dot + 1);
            int wordCount = countWords(sentense);
            if (count == wordCount)
            {
                std::cout << sentense << std::endl;
            }

            line = line.size() >= dot + 2 ? line.substr(dot + 2) : line.substr(dot + 1);
        }
    }

    fin.close();

    return 0;
}