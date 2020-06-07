
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <thread>
#include <mutex>
#include <cstdlib>
#include "functions.h"



void getString()
{
    std::mutex mtx;
    std::string str;
    bool flag = false;
    while (!flag)
    {
        std::cin >> str;
        int tempValue = 0;
        if(str.length() <= 63)
        { 

           for (size_t i = 0; i < str.length(); ++i)
           {
             if (!isdigit(str[i])  )
             {
                //
                 tempValue++;  
             }
           }
           if (tempValue == 0)
           {
               flag = true;
           }
           else std::cout<<"uncorrect data,write again"<<std::endl;
        } else std::cout << "uncorrect data,write again" << std::endl;
    }
    stringSorting(str);
    writeKB(str);

    mtx.lock();

    std::ofstream output("../../buffer.txt");
    output << str;
    output.close();

    mtx.unlock();
}

void analysing(int & a)
{
    std::mutex mtx;
    mtx.lock();

    std::string str;
    std::ifstream input("../../buffer.txt");
    input >> str;
    input.close();
    std::ofstream output("../../buffer.txt");
    output << " ";

    mtx.unlock();

    std::cout << "data after editing : " << str << std::endl;
    int countDigit = 0;
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (isdigit(str[i]))
        {
            ++countDigit;
        }
    }
    std::cout << " count of digit : " << countDigit << std::endl;
    a = countDigit;

}

void stringSorting(std::string& str)
{
    std::vector<unsigned char> stringSorter;
    for (size_t i = 0; i < str.length(); ++i)
    {
        stringSorter.push_back(str[i] - '0');
    }
    std::sort(stringSorter.begin(), stringSorter.end(), std::greater<int>());
    for (size_t i = 0; i < str.length(); ++i)
    {
        str[i] = stringSorter[i] + '0';
    }

}
void insertKB(std::string& str, size_t i)
{
    str.insert(i, "KB");
}
void writeKB(std::string& str)
{
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (str[i] % 2 == 0 && isdigit(str[i]))
        {
            str.erase(i, 1);
            insertKB(str, i);
            str.resize(str.length() + 2);
            ++i;
        }
    }
}

