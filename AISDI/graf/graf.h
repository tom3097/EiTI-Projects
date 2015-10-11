#ifndef GRAF_H
#define GRAF_H

#include <iostream>     /// wypisywanie komunikatow
#include <fstream>      /// praca z plikami
#include <string>       /// nazwa pliku wejsciowego
#include <cctype>       /// isspace()
#include <vector>       /// wektor
#include <list>         /// lista
#include <stack>        /// stos

/// struktura wierzcholka
struct vertex
{
    float x, y;
    unsigned number;
    vertex(float mx, float my, unsigned mnumber): x(mx), y(my), number(mnumber) {};
    ~vertex() {};
};

/// struktura krawedzi
struct edge
{
    unsigned endNum;
    float weight;
    edge(unsigned mendNum, float mweight): endNum(mendNum), weight(mweight) {};
    ~edge() {};
};

class graf
{
    public:
        graf();
        virtual ~graf();
        graf(const graf& mgraf);
        graf& operator=(const graf& mgraf);
        void completeKeyboard();
        void completeFile(std::string fileName);
        graf getTransposedGraf()const;
        void clear();
        void printGraf()const;
        void printStronglyConnectedComponents()const;
    private:
        void DFSstack(unsigned v, bool * visited, std::stack<unsigned>& S)const;
        void DFSprint(unsigned v, bool * visited, std::vector<unsigned>& V)const;
        bool findEdgeAndUpdate(unsigned beginNum, edge wantedEdge);
        std::vector<vertex> Vertexes;       /// informacje o wierzcholkach
        std::list<edge> *Edges;             /// wskazanie na tablice list sasiedztwa grafu
};

#endif // GRAF_H
