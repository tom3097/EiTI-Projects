#include "graf.h"
#include <cstdio>
#include <ctime>
#define TESTSACTIVE false
#define KEYBOARDACTIVE true
#define PRINTGRAFS false

void tests();

double calculateSeconds( clock_t czas )
{
    return static_cast < double >( czas ) / CLOCKS_PER_SEC;
}

int main()
{

    if(TESTSACTIVE == true)
    {
        tests();
        std::cout<<"Czas realizacji testow:  "<<calculateSeconds(clock())<<std::endl;
    }


    if(KEYBOARDACTIVE == true)
    {
        graf keyboardGraf;
        keyboardGraf.completeKeyboard();
        if(PRINTGRAFS == true)
            keyboardGraf.printGraf();
        keyboardGraf.printStronglyConnectedComponents();
    }

    return 0;
}

void tests()
{
    graf testGrafs[5];

    std::cout<<"testGraf0:   ";
    testGrafs[0].completeFile("testGraf0.txt");
    std::cout<<"testGraf1:   ";
    testGrafs[1].completeFile("testGraf1.txt");
    std::cout<<"testGraf2:   ";
    testGrafs[2].completeFile("testGraf2.txt");
    std::cout<<"testGraf3:   ";
    testGrafs[3].completeFile("testGraf3.txt");
    std::cout<<"testGraf4:   ";
    testGrafs[4].completeFile("testGraf4.txt");

    std::cout<<"Wypisywanie silnie spojnych skladowych\n";

    std::cout<<"testGraf0:\n";
    if(PRINTGRAFS == true)
        testGrafs[0].printGraf();
    testGrafs[0].printStronglyConnectedComponents();
    std::cout<<"testGraf1:\n";
    if(PRINTGRAFS == true)
        testGrafs[1].printGraf();
    testGrafs[1].printStronglyConnectedComponents();
    std::cout<<"testGraf2:\n";
    if(PRINTGRAFS == true)
        testGrafs[2].printGraf();
    testGrafs[2].printStronglyConnectedComponents();
    std::cout<<"testGraf3:\n";
    if(PRINTGRAFS == true)
        testGrafs[3].printGraf();
    testGrafs[3].printStronglyConnectedComponents();
    std::cout<<"testGraf4:\n";
    if(PRINTGRAFS == true)
        testGrafs[4].printGraf();
    testGrafs[4].printStronglyConnectedComponents();
}
