#include "graf.h"

graf::graf()
{
    Edges = NULL;
}

graf::~graf()
{
    if(Edges != NULL)
        delete [] Edges;
}

graf::graf(const graf& mgraf)
{
    for(unsigned v = 0; v < mgraf.Vertexes.size(); ++v)
        Vertexes.push_back(mgraf.Vertexes[v]);

    if(mgraf.Edges != NULL)
        Edges = new std::list<edge> [Vertexes.size()];

    for(unsigned v = 0; v < Vertexes.size(); ++v)
    {
        for(std::list<edge>::iterator iter = mgraf.Edges[v].begin(); iter != mgraf.Edges[v].end(); ++iter)
            Edges[v].push_back(*iter);
    }
}

graf& graf::operator=(const graf& mgraf)
{
    if(this == &mgraf)
        return *this;

    clear();

    for(unsigned v = 0; v < mgraf.Vertexes.size(); ++v)
        Vertexes.push_back(mgraf.Vertexes[v]);

    if(mgraf.Edges != NULL)
        Edges = new std::list<edge> [Vertexes.size()];

    for(unsigned v = 0; v < Vertexes.size(); ++v)
    {
        for(std::list<edge>::iterator iter = mgraf.Edges[v].begin(); iter != mgraf.Edges[v].end(); ++iter)
            Edges[v].push_back(*iter);
    }

    return *this;
}

void graf::completeKeyboard()
{
    /// uwzglednione EOF aby mozna bylo bezproblemowo korzystac z przekierowania
    /// pliku do standardowego strumienia w konsoli
    bool vertexLoaded = false;
    bool edgesLoaded = false;
    unsigned vertexNumber = 0;
    bool xLoaded = false;
    bool yLoaded = false;
    float x,y;
    int c;

    /// wczytywanie wspolrzednych wierzcholkow
    while(vertexLoaded == false)
    {
        c = std::cin.peek();
        while(isspace(c) && c != '\n' && c != EOF)
        {
            std::cin.ignore();
            c = std::cin.peek();
        }
        if(c == '\n' || c == EOF)
        {
            if(xLoaded == false)
            {
                vertexLoaded = true;
                edgesLoaded = true;
                std::cin.ignore();
            }
            else if(yLoaded == false)
            {
                std::cerr<<"Podano bledne dane.\n";
                std::cin.clear();
                std::cin.ignore();
                clear();
                return;
            }
            else
            {
                Vertexes.push_back(vertex(x,y,vertexNumber++));
                xLoaded = false;
                yLoaded = false;
                std::cin.ignore();
            }
        }
        else
        {
            if(xLoaded == false)
            {
                xLoaded = true;
                std::cin>>x;
            }
            else if(yLoaded == false)
            {
                yLoaded = true;
                std::cin>>y;
            }
            else
                vertexLoaded = true;

            if(std::cin.good() == false)
            {
                std::cerr<<"Podano bledne dane.\n";
                std::cin.clear();
                while((c = std::cin.peek()) != '\n' && c != EOF)
                    std::cin.ignore();
                std::cin.ignore();
                clear();
                return;
            }
        }
    }

    if(Vertexes.empty() == false)
        Edges = new std::list<edge> [Vertexes.size()];

    if(edgesLoaded == true)
    {
        std::cout<<"Wczytywanie zakonczone powodzeniem.\n";
        return;
    }

    /// wczytywanie krawedzi
    unsigned beginNum = static_cast<unsigned>(x);
    unsigned endNum = static_cast<unsigned>(y);
    float mweight = 0;

    if(beginNum != x || endNum != y || beginNum >= Vertexes.size() || endNum >= Vertexes.size())
    {
        std::cerr<<"Podano bledne dane.\n";
        std::cin.clear();
        while((c = std::cin.peek()) != '\n' && c != EOF)
            std::cin.ignore();
        std::cin.ignore();
        clear();
        return;
    }

    bool beginLoaded = true;
    bool endLoaded = true;
    bool mweightLoaded = false;

    while(edgesLoaded == false)
    {
        c = std::cin.peek();
        while(isspace(c) && c != '\n' && c != EOF)
        {
            std::cin.ignore();
            c = std::cin.peek();
        }

        if(c == '\n' || c == EOF)
        {
            if(beginLoaded == false)
            {
                edgesLoaded = true;
                std::cin.ignore();
            }
            else if(endLoaded == false || mweightLoaded == false)
            {
                std::cerr<<"Podano bledne dane.\n";
                std::cin.clear();
                std::cin.ignore();
                clear();
                return;
            }
            else
            {
                if(findEdgeAndUpdate(beginNum, edge(endNum,mweight)) == false)
                    Edges[beginNum].push_back(edge(endNum,mweight));
                beginLoaded = false;
                endLoaded = false;
                mweightLoaded = false;
                std::cin.ignore();
            }
        }
        else
        {
            if(beginLoaded == false)
            {
                beginLoaded = true;
                std::cin>>beginNum;
                if(std::cin.good() == false || beginNum > Vertexes.size())
                {
                    std::cerr<<"Podano bledne dane.\n";
                    std::cin.clear();
                    while((c = std::cin.peek()) != '\n' && c != EOF)
                        std::cin.ignore();
                    std::cin.ignore();
                    clear();
                    return;
                }
            }
            else if(endLoaded == false)
            {
                endLoaded = true;
                std::cin>>endNum;
                if(std::cin.good() == false || endNum > Vertexes.size())
                {
                    std::cerr<<"Podano bledne dane.\n";
                    std::cin.clear();
                    while((c = std::cin.peek()) != '\n' && c != EOF)
                        std::cin.ignore();
                    std::cin.ignore();
                    clear();
                    return;
                }
            }
            else if(mweightLoaded == false)
            {
                mweightLoaded = true;
                std::cin>>mweight;
                if(std::cin.good() == false)
                {
                    std::cerr<<"Podano bledne dane.\n";
                    std::cin.clear();
                    while((c = std::cin.peek()) != '\n' && c != EOF)
                        std::cin.ignore();
                    std::cin.ignore();
                    clear();
                    return;
                }
            }
            else
            {
                std::cerr<<"Podano bledne dane.\n";
                std::cin.clear();
                while((c = std::cin.peek()) != '\n' && c != EOF)
                    std::cin.ignore();
                std::cin.ignore();
                clear();
                return;
            }
        }
    }
    std::cout<<"Wczytywanie zakonczone powodzeniem.\n";
}

void graf::completeFile(std::string fileName)
{
    std::ifstream fin(fileName.c_str());

    bool vertexLoaded = false;
    bool edgesLoaded = false;
    unsigned vertexNumber = 0;
    bool xLoaded = false;
    bool yLoaded = false;
    float x,y;
    int c;

    if(!fin.is_open())
    {
        std::cerr<<"Nie udalo sie otworzyc pliku.\n";
        fin.clear();
        return;
    }

    while(vertexLoaded == false)
    {
        c = fin.peek();
        while(isspace(c) && c != '\n' && c != EOF)
        {
            fin.ignore();
            c = fin.peek();
        }
        if(c == '\n' || c == EOF)
        {
            fin.ignore();
            if(xLoaded == false)
            {
                vertexLoaded = true;
                edgesLoaded = true;
            }
            else if(yLoaded == false)
            {
                std::cerr<<"Podano bledne dane.\n";
                fin.clear();
                fin.close();
                clear();
                return;
            }
            else
            {
                Vertexes.push_back(vertex(x,y,vertexNumber++));
                xLoaded = false;
                yLoaded = false;

                if(c == EOF)
                {
                    vertexLoaded = true;
                    edgesLoaded = true;
                }
            }
        }
        else
        {
            if(xLoaded == false)
            {
                xLoaded = true;
                fin>>x;
            }
            else if(yLoaded == false)
            {
                yLoaded = true;
                fin>>y;
            }
            else
                vertexLoaded = true;

            if(fin.good() == false)
            {
                std::cerr<<"Podano bledne dane.\n";
                fin.clear();
                fin.close();
                clear();
                return;
            }
        }
    }

    if(Vertexes.empty() == false)
        Edges = new std::list<edge> [Vertexes.size()];

    if(edgesLoaded == true)
    {
        std::cout<<"Wczytywanie zakonczone powodzeniem.\n";
        return;
    }

    unsigned beginNum = static_cast<unsigned>(x);
    unsigned endNum = static_cast<unsigned>(y);
    float mweight = 0;

    if(beginNum != x || endNum != y || beginNum >= Vertexes.size() || endNum >= Vertexes.size())
    {
        std::cerr<<"Podano bledne dane.\n";
        fin.clear();
        fin.close();
        clear();
        return;
    }

    bool beginLoaded = true;
    bool endLoaded = true;
    bool mweightLoaded = false;

    while(edgesLoaded == false)
    {
        c = fin.peek();
        while(isspace(c) && c != '\n' && c != EOF)
        {
            fin.ignore();
            c = fin.peek();
        }

        if(c == '\n' || c == EOF)
        {
            fin.ignore();
            if(beginLoaded == false)
                edgesLoaded = true;
            else if(endLoaded == false || mweightLoaded == false)
            {
                std::cerr<<"Podano bledne dane.\n";
                fin.clear();
                fin.close();
                clear();
                return;
            }
            else
            {
                if(findEdgeAndUpdate(beginNum, edge(endNum,mweight)) == false)
                    Edges[beginNum].push_back(edge(endNum,mweight));
                beginLoaded = false;
                endLoaded = false;
                mweightLoaded = false;

                if(c == EOF)
                    edgesLoaded = true;
            }
        }
        else
        {
            if(beginLoaded == false)
            {
                beginLoaded = true;
                fin>>beginNum;
                if(fin.good() == false || beginNum > Vertexes.size())
                {
                    std::cerr<<"Podano bledne dane.\n";
                    fin.clear();
                    fin.close();
                    clear();
                    return;
                }
            }
            else if(endLoaded == false)
            {
                endLoaded = true;
                fin>>endNum;
                if(fin.good() == false || endNum > Vertexes.size())
                {
                    std::cerr<<"Podano bledne dane.\n";
                    fin.clear();
                    fin.close();
                    clear();
                    return;
                }
            }
            else if(mweightLoaded == false)
            {
                mweightLoaded = true;
                fin>>mweight;
                if(fin.good() == false)
                {
                    std::cerr<<"Podano bledne dane.\n";
                    fin.clear();
                    fin.close();
                    clear();
                    return;
                }
            }
            else
            {
                std::cerr<<"Podano bledne dane.\n";
                fin.clear();
                fin.close();
                clear();
                return;
            }
        }
    }
    fin.close();
    std::cout<<"Wczytywanie zakonczone powodzeniem.\n";
}

graf graf::getTransposedGraf()const
{
    graf transGraf;

    for(std::vector<vertex>::const_iterator iter = Vertexes.begin(); iter != Vertexes.end(); ++iter)
        transGraf.Vertexes.push_back(*iter);

    if(transGraf.Vertexes.empty() == false)
    {
        transGraf.Edges = new std::list<edge> [transGraf.Vertexes.size()];

        for(unsigned v = 0; v < Vertexes.size(); ++v)
            for(std::list<edge>::const_iterator iter = Edges[v].begin(); iter != Edges[v].end(); ++iter )
                transGraf.Edges[iter->endNum].push_back(edge(v,iter->weight));
    }

    return transGraf;
}

void graf::clear()
{
    Vertexes.clear();

    if(Edges != NULL)
    {
        delete [] Edges;
        Edges = NULL;
    }
}

void graf::printGraf()const
{
    if(Vertexes.empty() == true)
    {
        std::cout<<"Graf jest pusty\n";
        return;
    }

    std::cout<<"...:::WIERZCHOLKI:::...\n";
    for(unsigned v = 0; v < Vertexes.size(); ++v)
        std::cout<<Vertexes[v].number<<": "<<Vertexes[v].x<<"  "<<Vertexes[v].y<<std::endl;

    if(Edges == NULL)
        return;

    std::cout<<"...:::KRAWEDZIE:::...\n";
    for(unsigned v = 0; v < Vertexes.size(); ++v)
    {
        if(Edges[v].empty() == false)
        {
            std::cout<<v<<"  : ";
            for(std::list<edge>::const_iterator iter = Edges[v].begin(); iter != Edges[v].end(); ++iter)
                std::cout<<iter->endNum<<" ("<<iter->weight<<")  ";
            std::cout<<std::endl;
        }
    }
    std::cout<<std::endl;
}

void graf::printStronglyConnectedComponents()const
{
    std::stack<unsigned> S;
    bool visited[Vertexes.size()];

    for(unsigned v =0; v< Vertexes.size(); ++v)
        visited[v] = false;

    for(unsigned v = 0; v < Vertexes.size(); ++v)
    {
        if(visited[v] == false)
            DFSstack(v, visited, S);
    }

    graf transposed = getTransposedGraf();

    for(unsigned v =0; v< Vertexes.size(); ++v)
        visited[v] = false;

    unsigned SCC = 0;
    unsigned v;

    std::vector<unsigned> V;

    while(S.empty() == false)
    {
        v = S.top();
        S.pop();
        if( visited[v] == false )
        {
            transposed.DFSprint(v, visited, V);

            if(V.size()%2 == 0)
            {
                V.clear();
                continue;
            }

            ++SCC;
            std::cout<<"SCC "<<SCC<<" : ";
            for(unsigned e = 0; e < V.size(); ++e)
                std::cout<<V[e]<<" ";
            std::cout<<std::endl;
            V.clear();
        }
    }
    std::cout<<std::endl;
}

void graf::DFSstack(unsigned v, bool * visited, std::stack<unsigned>& S)const
{
    visited[v] = true;

    for(std::list<edge>::const_iterator iter = Edges[v].begin(); iter != Edges[v].end(); ++iter)
    {
        if( visited[iter->endNum] == false)
            DFSstack(iter->endNum, visited, S);
    }

    S.push(v);
}

void graf::DFSprint(unsigned v, bool * visited, std::vector<unsigned>& V)const
{
    visited[v] = true;

    V.push_back(v);

    for( std::list<edge>::const_iterator iter = Edges[v].begin(); iter != Edges[v].end(); ++iter )
    {
        if( visited[iter->endNum] == false )
            DFSprint(iter->endNum, visited, V);
    }
}

bool graf::findEdgeAndUpdate(unsigned beginNum, edge wantedEdge)
{
    if(Edges == NULL)
        return false;

    for(std::list<edge>::iterator iter = Edges[beginNum].begin(); iter != Edges[beginNum].end(); ++iter)
        if(iter->endNum == wantedEdge.endNum)
        {
            iter->weight = wantedEdge.weight;
            return true;
        }

    return false;
}


