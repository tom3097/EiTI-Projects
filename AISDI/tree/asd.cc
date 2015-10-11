/**
@file asd.cc

Plik do modyfikacji w w ramach cwiczenia 4 z AISDI.
Zawiera niekompletne implementacje metod klasy TreeMap.
Jest tez prosta funkcja testujaca (void test()), ktora
jest wolana w funkcji main. Mozna w niej zaimplementowac
wlasne testy.
NALEZY ZMODYFIKOWAC I UZUPELNIC CIALA METOD KLASY TreeMap.

@author
Pawel Cichocki, Michal Nowacki

@date
last revision
- 2005.12.01 Pawel Cichocki: TreeNodeDetail class
- 2005.12.01 Michal Nowacki: lab #4
- 2005.11.17 Michal Nowacki: lab #3, copy operator and constructor
- 2005.11.04 Pawel Cichocki: copied comments from the header
- 2005.11.03 Pawel Cichocki: const_iterator done properly now
- 2005.10.27 Pawel Cichocki: cosmetic changes
- 2005.10.26 Michal Nowacki: removed some method bodies
- 2005.10.25 Pawel Cichocki: wrote it

COPYRIGHT:
Copyright (c) 2005 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include <assert.h>
#include <algorithm>

#include <iostream>

#ifdef _SUNOS
#include "/materialy/AISDI/tree/TreeMap.h"
#else
#include "TreeMap.h"
#endif

/// A helper class.
class TreeMapDetail //Helper
{
protected:
   friend class TreeMap;
   typedef TreeNode/*<Key, Value>*/ Node;
   typedef size_t size_type;

   size_type tree_size;

    ///rekurencyjna funkcja do czyszczenia drzewa
   void clearTree(Node *toDeleteNode, Node *endNode)
   {
        if(toDeleteNode->left != NULL && toDeleteNode->left != endNode)
            clearTree(toDeleteNode->left, endNode);
        if(toDeleteNode->right != NULL && toDeleteNode->right != endNode)
            clearTree(toDeleteNode->right, endNode);

        delete toDeleteNode;
   }

    ///rekurencyjna funkcja do kopiowania drzewa
   Node* copyTree(Node *source, Node *parent)
   {
        if(source != NULL && source->parent != NULL)
        {
            Node *newNode = new Node(source->data, parent);

            newNode->left = copyTree(source->left, newNode);
            newNode->right = copyTree(source->right, newNode);

            return newNode;
        }
        else
            return NULL;
   }

    ///rekurencyjna funkcja do porownywania wezlow drzewa
   bool struct_eq(Node *firstTreeNode, Node*secondTreeNode)
   {
        if(firstTreeNode == NULL || secondTreeNode == NULL)
            return (firstTreeNode == NULL && secondTreeNode == NULL);

        if(firstTreeNode->parent == NULL || secondTreeNode->parent == NULL)
            return (firstTreeNode->parent == NULL && secondTreeNode->parent == NULL);

        if(firstTreeNode->data != secondTreeNode->data)
            return false;

        return (struct_eq(firstTreeNode->left,secondTreeNode->left) && struct_eq(firstTreeNode->right, secondTreeNode->right));
   }
};

//////////////////////////////////////////////////////////////////////////////
// TreeMap and TreeMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

TreeMap::TreeMap()
{
    Node *Guardian;

    /// :::parent wskazuje na korzen:::left/right wskazuje na kolejnego straznika::: ///
    Guardian = new Node(std::make_pair(Key(),Val()));
    root = Guardian;

    /// :::parent wynosi NULL:::left wskazuje na begin():::right wskazuje na end()::: ///
    Guardian = new Node(std::make_pair(Key(),Val()));

    root->left = Guardian;
    root->right = Guardian;

    Guardian->left = Guardian;
    Guardian->right = Guardian;

    detail = new TreeMapDetail;
    detail->tree_size = 0;
};

/// Content of existing TreeMap object is copied into the new object.
TreeMap::TreeMap( const TreeMap& m )
{
    Node *Guardian;

    /// :::parent wskazuje na korzen:::left/right wskazuje na kolejnego straznika::: ///
    Guardian = new Node(std::make_pair(Key(),Val()));
    root = Guardian;

    /// :::parent wynosi NULL:::left wskazuje na begin():::right wskazuje na end()::: ///
    Guardian = new Node(std::make_pair(Key(),Val()));

    root->left = Guardian;
    root->right = Guardian;

    Guardian->left = Guardian;
    Guardian->right = Guardian;

    detail = new TreeMapDetail;
    detail->tree_size = 0;

    *this = m;
};

TreeMap::~TreeMap()
{
    ///usuwam wszystkie elementy
    if(!empty())
    {
        detail->clearTree(root->parent,root->left);
    }

    ///usuwam dwoch pozostalych straznikow
    delete root->left;
    delete root;
};

// Inserts an element into the map.
// @returns A pair whose bool component is true if an insertion was
//          made and false if the map already contained an element
//          associated with that key, and whose iterator component coresponds to
//          the address where a new element was inserted or where the element
//          was already located.
std::pair<TreeMap::iterator, bool> TreeMap::insert(const std::pair<Key, Val>& entry)
{
    ///jesli istnieje juz element o podanym kluczu to zwracam pare
    ///(iterator tego elementu, false)
    iterator i = find(entry.first);
    if(i != end())
        return std::make_pair(i,(bool)false);

    ///w przeciwnym wypadku zwracam pare (iterator nowo wstawionego elementu, true)
    i = unsafe_insert(entry);
    return std::make_pair(i,(bool)true);
}

// Inserts an element into the map.
// This method assumes there is no value asociated with
// such a key in the map.

TreeMap::iterator TreeMap::unsafe_insert(const std::pair<Key, Val>& entry)
{
    Node *newNode = new Node(entry);

    Node *currentParent = root->parent;

    ///przypadek gdy wstawiamy pierwszy element do pustego drzewa
    if(currentParent == NULL)
    {
        root->parent = newNode;
        newNode->parent = root;

        Node *tempGuard = root->left;

        tempGuard->left = newNode;
        newNode->left = tempGuard;

        tempGuard->right = newNode;
        newNode->right = tempGuard;
        return iterator(newNode);
    }

    while(true)
    {
        ///szukamy odpowiedniego miejsca w przypadku gdy klucz jest mniejszy od klucza elementu obecnie rozpatrywanego
        if(newNode->data.first < currentParent->data.first)
        {
            if(currentParent->left == NULL)
            {
                currentParent->left = newNode;
                break;
            }
            else if(currentParent->left == root->left)
            {
                currentParent->left = newNode;
                newNode->left = root->left;
                root->left->left = newNode;
                break;
            }
            else
                currentParent = currentParent->left;
        }
        ///szukamy odpowiedniego miejsca w przypadku gdy klucz jest wiekszy od klucza elementu obecnie rozpatrywanego
        else
        {
            if(currentParent->right == NULL)
            {
                currentParent->right = newNode;
                break;
            }
            else if(currentParent->right == root->right)
            {
                currentParent->right = newNode;
                newNode->right = root->right;
                root->right->right = newNode;
                break;
            }
            else
                currentParent = currentParent->right;
        }
    }

    newNode->parent = currentParent;

    ///inkrementuje rozmiar drzewa
    ++detail->tree_size;

    return iterator(newNode);
}

// Returns an iterator addressing the location of the entry in the map
// that has a key equivalent to the specified one or the location succeeding the
// last element in the map if there is no match for the key.
TreeMap::iterator TreeMap::find(const Key& k)
{
    Node *auxiliary = root->parent;

    ///dopoki auxiliary nie jest wskaznikiem pustym, wskaznikiem end(), wskaznikiem o kluczu rownym k
    ///zmieniamy wskaznik odpowiednio od relacji miedzy kluczem w nim przechowywanym a kluczem k
    while(auxiliary != NULL && auxiliary != root->left && auxiliary->data.first != k)
        auxiliary = (k < auxiliary->data.first) ? auxiliary->left : auxiliary->right;

    ///jesli wskaznik jest pusty lub wskazuje na end(), to znaczy ze element o podanym kluczu nie istnieje
    if(auxiliary == NULL || auxiliary == root->left)
        return end();

    ///w przeciwnym przypadku zwracamy iterator do znalezionego elementu
    return iterator(auxiliary);
}

TreeMap::const_iterator TreeMap::find(const Key& k) const
{
    Node *auxiliary = root->parent;

    while(auxiliary != NULL && auxiliary != root->left && auxiliary->data.first != k)
        auxiliary = (k < auxiliary->data.first) ? auxiliary->left : auxiliary->right;

    if(auxiliary == NULL || auxiliary == root->left)
        return end();

    return iterator(auxiliary);
}

// Inserts an element into a map with a specified key value
// if one with such a key value does not exist.
// @returns Reference to the value component of the element defined by the key.
TreeMap::Val& TreeMap::operator[](const Key& k)
{
    return insert(std::make_pair(k,Val())).first->second;
}

// Tests if a map is empty.
bool TreeMap::empty( ) const
{
    ///gdy root->parent == NULL to znaczy ze drzewo jest puste
    return root->parent == NULL;
}

// Returns the number of elements in the map.
TreeMap::size_type TreeMap::size( ) const
{
    ///zwracamy liczbe ktora informuje aktualnej ilosci elementow
    ///jest ona inkrementowana przy wstawieniu i dekrementowana przy usuwaniu
    return detail->tree_size;
}

// Returns the number of elements in a map whose key matches a parameter-specified key.
TreeMap::size_type TreeMap::count(const Key& _Key) const
{
    ///jesli element o podanym kluczu istnieje to na pewno wystepuje 1 raz
    if(find(_Key) == end())
        return (size_type) 0;
    ///w przeciwnym wypadku element o podanym kluczu wystepuje 0 razy
    else
        return (size_type) 1;
}

// Removes an element from the map.
// @returns The iterator that designates the first element remaining beyond any elements removed.
TreeMap::iterator TreeMap::erase(TreeMap::iterator i)
{
    Node *auxiliary = i.node;
    Node *toDelete = NULL;
    Node *descendant = NULL;

    bool beginTheSame = true;
    bool befEndTheSame = true;

    --detail->tree_size;

    ///pomocnicze iteratory wskazujace na element nastepny i poprzedni
    iterator incremI = i;
    ++incremI;
    iterator decremI = i;
    --decremI;

    ///przypadek gdy pierwszy element jest zarowno ostatni, czyli gdy usuwamy jedyny element
    if(auxiliary->left == root->left && auxiliary->right == root->right)
    {
        root->left->left = root->left;
        root->right->right = root->right;

        root->parent = NULL;

        delete auxiliary;

        ///w tym przypadku zwracamy po prostu end()
        return end();
    }

    ///iterator toReturn przechowuje iterator ktory zostanie zwrocony
    iterator toReturn;

    ///przypadek gdy usuwany element jest elementem pierwszym, korygujemy wskazanie na begin()
    if(i == begin())
    {
        root->left->left = incremI.node;
        auxiliary->left = NULL;
        beginTheSame = false;
    }

    ///przypadek gdy usuwany elelent jest elementem ostatnim, korygujemy element wskazujacy na end()
    else if(i == --end())
    {
        root->right->right = decremI.node;
        auxiliary->right = NULL;
        befEndTheSame = false;
    }

    ///ustawiam wskaznik ktory realnie bedzie usuwany

    ///w przypadku gdy usuwany wezel ma dwoch potomkow bedziemy usuwac jego nastepnik
    ///a jego zawartosc przeniesiemy do wezla poczatkowego
    if(auxiliary->left != NULL && auxiliary->right != NULL)
    {
        toDelete = incremI.node;

        ///w tym przypadku takze zwrocimy ten sam iterator
        toReturn = i;

        ///gdy iterator(nowoUsuwany) to iterator ostatniego elementu, korygujemy element wskazujacy na end()
        if(iterator(toDelete) == --end())
        {
            root->right->right = i.node;
            toDelete->right = NULL;
            befEndTheSame = false;
        }
    }
    ///w przeciwnym przypadku usuwamy pierwotny wezel
    else
    {
        toDelete = auxiliary;
        ///jesli pierwotnie usuwanym elementem byl element ostatni to zwracamy iterator end()
        if(befEndTheSame == false)
            toReturn = end();
        ///w przeciwnym przypadku zwracamy iterator nastepny po pierwotnym iteratorze
        else
            toReturn = incremI;
    }

    if(toDelete->left != NULL)
        descendant = toDelete->left;
    else
        descendant = toDelete->right;

    ///jesli syn istnieje to przypisujemy mu ojca
    if(descendant != NULL)
        descendant->parent = toDelete->parent;

    ///przypisujemy nowego syna
    if(toDelete->parent == root)
        root->parent = descendant;
    else if(toDelete->parent->left == toDelete)
        toDelete->parent->left = descendant;
    else
        toDelete->parent->right = descendant;

    ///jesli realnie usuwany nie jest rowny pierwotnie usuwanemu, to przenosimy dane
    if(toDelete != auxiliary)
        auxiliary->data = toDelete->data;

    ///w razie potrzeby konczymy korygowac wskazniki w przypadku zmiany begin() lub ostatniego elementu
    if(beginTheSame == false)
    {
        Node *newBegin = root->left->left;
        newBegin->left = root->left;
    }

    if(befEndTheSame == false)
    {
        Node *befEndNode = root->right->right;
        befEndNode->right = root->right;
    }

    delete toDelete;
    return toReturn;
}


// Removes a range of elements from the map.
// The range is defined by the key values of the first and last iterators
// first is the first element removed and last is the element just beyond the last elemnt removed.
// @returns The iterator that designates the first element remaining beyond any elements removed.
TreeMap::iterator TreeMap::erase(TreeMap::iterator f, TreeMap::iterator l)
{
    while(f != l)
        f = erase(f);

    return l;
}

// Removes an element from the map.
// @returns The number of elements that have been removed from the map.
//          Since this is not a multimap itshould be 1 or 0.
TreeMap::size_type TreeMap::erase(const Key& key)
{
    iterator i = find(key);

    ///gdy element o podanym kluczu nie istnieje to nic nie usuwamy, zwracamy 0
    if(i == end())
        return  (size_type) 0;

    ///w przeciwnym wypadku usuwamy ten element, zwracamy 1
    erase(i);
    return (size_type) 1;
}

// Erases all the elements of a map.
void TreeMap::clear( )
{
    ///usuwam od begin() wlacznie do ostatniego elementu
    //erase(begin(),end());
    if(!empty())
    {
        detail->clearTree(root->parent,root->left);
        root->left->left = root->left;
    root->right->right = root->right;

    root->parent = NULL;

    detail->tree_size = 0;
    }
}

bool TreeMap::struct_eq(const TreeMap& another) const
{
    ///wywolanie funkcji rekurencyjnej porownujacej
    return detail->struct_eq(root->parent, another.root->parent);
}

bool TreeMap::info_eq(const TreeMap& another) const
{
    if(size() != another.size())
        return false;

    ///gdy rozmiary sa takie same to elementy o odpowiednich kluczach jesli istnieja to znajduja sie
    ///pod odpowiadajacymi sobie iteratorami
    iterator firstTree = begin();
    iterator secondTree = another.begin();

    while(firstTree != end())
    {
        if(firstTree->first != secondTree->first)
            return false;
        ++firstTree;
        ++secondTree;
    }
    return true;
}

// preincrement
TreeMap::const_iterator& TreeMap::const_iterator::operator ++()
{
    ///w przypadku gdy iterator nie jest ustawiony na end()
    if(node->parent != NULL)
    {
        ///sprawdzam czy node jest wskaznikiem ostatniego elementu, gdy tak to przechodze na end()
        if(node->right != NULL && node->right->parent == NULL)
            node = node->right;
        ///w przeciwnym przypadku przesuwam sie o 1 w prawo i do konca w lewo (do momentu az brak lewego potomka)
        else if(node->right != NULL)
        {
            node = node->right;
            while(node->left != NULL)
                    node = node->left;
        }
        ///w przeciwnym przypadku aby dostac sie do nastepnego elementu musze pojsc w gore drzewa
        else
        {
            Node *tempParent = node->parent;
            while(tempParent != NULL && tempParent->right == node)
            {
                node = node->parent;
                tempParent = node->parent;
            }
            node = tempParent;
        }
    }

    return *this;
}

// postincrement
TreeMap::const_iterator TreeMap::const_iterator::operator++(int)
{
    const_iterator auxiliary = *this;
    ++*this;
    return auxiliary;
}

// predecrement
TreeMap::const_iterator& TreeMap::const_iterator::operator--()
{
    ///w przypadku gdy iterator znajduje sie na end()
    if(node->parent == NULL)
    {
        node = node->right;
        return *this;
    }

    ///w przypadku gdy nie jestesmy obecnie w iteratorze begin()
    if(node->left == NULL || (node->left != NULL && node->left->parent != NULL))
    {
        ///w przypadku gdy istnieje lewy potomek
        if(node->left != NULL)
        {
            node = node->left;
            while(node->right != NULL)
                node = node->right;
        }
        ///w przeciwnym przypadku musimy przejsc w gore drzewa
        else
        {
            Node *tempParent = node->parent;
            ///dopoki istnieje lewy potomek, rodzic lewego potomka nie wynosi NULL(jest tak gdy osoagamy begin()
            ///node jest lewym potomkiem
            while(tempParent->left != NULL && tempParent->left->parent != NULL && tempParent->left == node)
            {
                node = node->parent;
                tempParent = node->parent;
            }
            node = tempParent;
        }
    }

    return *this;
}

// postdecrement
TreeMap::const_iterator TreeMap::const_iterator::operator--(int)
{
    const_iterator auxiliary = *this;
    --*this;
    return auxiliary;
}

/// Assignment operator copy the source elements into this object.
TreeMap& TreeMap::operator=(const TreeMap& other)
{

    if(&other == this)
        return *this;

    clear();

    if(other.empty())
        return *this;

    detail->tree_size = other.detail->tree_size;

    root->parent = detail->copyTree(other.root->parent, root);

    Node *beginNode, *befEndNode;
    beginNode = root->parent;
    befEndNode = root->parent;

    while(beginNode->left != NULL)
        beginNode = beginNode->left;

    while(befEndNode->right != NULL)
        befEndNode = befEndNode->right;

    root->left->left = beginNode;
    beginNode->left = root->left;

    root->right->right = befEndNode;
    befEndNode->right = root->right;

    return *this;
}

/// Returns an iterator addressing the first element in the map
TreeMap::iterator TreeMap::begin()
{
    return iterator(root->left->left);
}

/// Returns an iterator addressing the first element in the map
TreeMap::const_iterator TreeMap::begin() const
{
    return iterator(root->left->left);
}

/// Returns an iterator that addresses the location succeeding the last element in a map
TreeMap::iterator TreeMap::end()
{
    return iterator(root->left);
}

/// Returns an iterator that addresses the location succeeding the last element in a map
TreeMap::const_iterator TreeMap::end() const
{
    return iterator(root->left);
}

//////////////////////////////////////////////////////////////////////////////
// Tests
//////////////////////////////////////////////////////////////////////////////

/// A helper function that outputs a key-value pair.
void print(const std::pair<int, std::string>& p)
{
   std::cout<<p.first<<", "<<p.second<<std::endl;
}

#include <map>

/// The big mean test function ;)
void test()
{
   // A typedef used by the test.
   typedef std::map<int, std::string> TEST_MAP;
   //typedef SmallMap<int, std::string> TEST_MAP;
   //typedef TreeMap TEST_MAP;

   std::cout << "Testy uzytkownika" << std::endl;

        TEST_MAP m;

   m[2] = "Merry";
   m[4] = "Jane";
   m[8] = "Korwin";
   m[4] = "Magdalena";

   for_each(m.begin(), m.end(), print );
   //system("PAUSE");

}

//////////////////////////////////////////////////////////////////////////////
// main - jest w pliku /materialy/AISDI/z2/main.cc
//////////////////////////////////////////////////////////////////////////////

//int main()
//{
//   std::cout << "AISDI cwiczenie 4: wchodze do funkcji main." << std::endl;

//   test();
//   // Biblioteka z bardziej rygorystyczna wersja tych testow bedzie udostepniona na nastepnych zajeciach.
//   Test2();
//   //system("PAUSE");
//   return EXIT_SUCCESS;
//}
