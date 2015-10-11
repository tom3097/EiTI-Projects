/**
@file asd.cc

Plik do modyfikacji w ramach cwiczenia z AISDI.
Zawiera niekompletne implementacje metod klasy ListMap,
oraz mape podobna koncepcyjnie do tej z cwicznia 1 (SmallMap)
zaimplementowana w jescze bardziej szczatkowy sposob.
Jest tez prosta funkcja testujaca (void test()), ktora
jest wolana w funkcji main. Mozna w niej zaimplementowac
wlasne testy.
NALEZY ZMODYFIKOWAC I UZUPELNIC CIALA METOD KLASY LISTMAP.

@author
Pawel Cichocki, Michal Nowacki

@date
last revision
- 2006.01.06 Michal Nowacki: wersja polska
- 2005.11.17 Michal Nowacki: constructor
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
#include "/materialy/AISDI/liniowe/ListMap.h"
#else
#include "ListMap.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// ListMap and ListMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

ListMap::ListMap()
{
   //tworzy straznika, jego key ustawia na 0 - licznik elem. w liscie
   // wskazniki na siebie, jest pierwszym elementem
   // internal data pointer jako wskazanie na siebie
   // wykorzystywane do odnalezienia straznika
   std::pair<int,std::string> listGuard(0,"listGuard");
   //first = new Node(listGuard, first, first);
   first = new Node(listGuard, NULL, NULL);
   first->prev = first;
   first->next = first;
   first->internalDataPointer = NULL;
};

ListMap::ListMap( const ListMap& m )
{
   ///@todo Zaimplementowaæ metode
   const_iterator i, k; // i-iterator, k- koncowy
   i = m.begin();
   k = m.end();
   first = new ListNode(*i, NULL, NULL);
   for(; i!=k; i++)
        unsafe_insert(*i);
};

ListMap::~ListMap()
{
   clear();
   delete first;
};

// Wstawienie elementu do mapy.
// @returns Para, której komponent bool jest równy true gdy wstawienie zosta³o
//          dokonane, równy false gdy element identyfikowany przez klucz
//          ju¿ istnia³ w mapie. Iterator ustawiony jest na ten wstawiony
//          lub istniej¹cy ju¿ w mapie element.
std::pair<ListMap::iterator, bool> ListMap::insert(const std::pair<Key, Val>& entry)
{
   ///@todo Uzupe³niæ kod
   iterator i;

   i = find(entry.first);
   if( i!= end()) //cos znalazl
        return std::make_pair(i, (bool)false);
   else
   {
       i = unsafe_insert(entry);
       return std::make_pair(i, (bool)true);
   }

}

// Wstawienie elementu do mapy.
// Matoda zak³ada, ¿e w mapie nie wystêpuje element identyfikowany przez key
ListMap::iterator ListMap::unsafe_insert(const std::pair<Key, Val>& entry)
{
   ///@todo Uzupe³niæ kod
   Node* temp;

   temp = new Node(entry, first, first->prev);
   first->prev->next = temp;
   first = temp;
   first->next->prev = first;
   int help = 1;
   first->internalDataPointer = &help;

   //key straznika zwiekszamy o 1
   (end()->first)++;

   return iterator(first);
}

// Zwraca iterator addresuj¹cy element w mapie dla którego klucz jest równy
// szukanemu kluczowi lub element za ostatnim gdy szukanego klucza brak w mapie.
ListMap::iterator ListMap::find(const Key& k)
{
   ///@todo Zaimplementowaæ metode
   iterator i;
   i = begin();

   for(; i != end(); ++i)
        if(i->first == k) return i;

   return end();
}

ListMap::const_iterator ListMap::find(const Key& k) const
{
   ///@todo Zaimplementowaæ metode
   const_iterator i;
   i = begin();

   for(; i != end(); ++i)
        if(i->first == k) return i;

   return end();
}

// Udostêpnia wartoœæ powi¹zan¹ z kluczem key. Wstawia element do mapy jeœli
// nie istnia³.
// @returns Referencje do wartoœci powi¹zanej z kluczem.
ListMap::Val& ListMap::operator[](const Key& k)
{
   ///@todo Zaimplementowaæ metode

   iterator i;
   i = find(k);

   if( i == end())
   {
       std::pair<int, std::string> new_insert(k, "new");
       i = unsafe_insert(new_insert);
   }
   return i->second;
}

// Sprawdzenie czy mapa jest pusta.
bool ListMap::empty( ) const
{
    const_iterator k;
    k = end();
    if( k->first == 0) //w key straznika mam liczbe elementow
        return true;
    else
        return false;
}

// Zwraca iloœæ elementów w mapie.
ListMap::size_type ListMap::size( ) const
{
   return (end()->first);
}

// Zwraza iloœæ elementów skojarzonych z kluczem key.
ListMap::size_type ListMap::count(const Key& _Key) const
{
   ///@todo Zaimplementowaæ metode
   const_iterator i;

   i = find(_Key);
   if (i != end()) return 1;
   else
   return 0;  // this is not a multimap
}

// Usuwa element z mapy.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator i)
{
   ///@todo Zaimplementowaæ metode
   iterator next;
   next = i;

   if(empty()) return i; // pusty wiec nic nie usuwam
   else
   {
       next++;
       next.node->prev = i.node->prev;
       i.node->prev->next = next.node;

       delete i.node;
       (end()->first)--;
       return next;
   }
}

// Usuwa zakres elementów z mapy.
// Zakres jest zdefiniowany poprzez iteratory first i last
// first jest okreœla pierwszy element do usuniêcia, a last okreœla element
// po ostatnim usuniêtym elemencie.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator f, ListMap::iterator l)
{
   ///@todo Zaimplementowaæ metode
   iterator temp;
   temp = f;

   while (temp != l)
        temp = erase(temp);

   return l;
}

// Usuwa element z mapy.
// @returns Iloœæ usuniêtych elementów.
//          (nie jest to multimapa, wiêæ mo¿e byæ to wartoœæ 1 lub 0 )
ListMap::size_type ListMap::erase(const Key& key)
{
   ///@todo Zaimplementowaæ metode
   iterator i;
   i = find(key);

   if(i == end())return 0;
   else
   {
    erase(i);
    return 1;
   }

}

// Usuniêcie wszystkich elementów z mapy.
void ListMap::clear( )
{
   ///@todo Zaimplementowaæ metode
   erase(begin(), end());
}

// Porównanie strukturalne map.
// Czy reprezentacja danych jest identyczna.
// Zwraca true jeœli wewnêtrzne struktury map s¹ identyczne.
bool ListMap::struct_eq(const ListMap& another) const
{
   ///@todo Zaimplementowaæ metode
    const_iterator i, a, i_end;
	a = another.begin();
	i = begin();
    i_end = end();

	if (size() != another.size()) return false;
    else
	for (; i != i_end; ++i, ++a)
	{
		if ((a->first) != (i->first)) return false;
		if ((a->second) != (i->second))  return false;
	}
	return true;
}

// Porównanie informacyjne map.
// Czy informacje trzymane w mapach s¹ identyczne.
// Zwraca true jeœli mapy zwieraj¹ takie same pary klucz-wartoœæ.
bool ListMap::info_eq(const ListMap& another) const
{
   ///@todo Zaimplementowaæ metode
    const_iterator i, a, i_end, a_end, temp;

	i = begin();
	a = another.begin();
	i_end = end();
	a_end = another.end();

	if (size() != another.size()) return false;
	else
	for (; i != i_end; ++i)
	{
		temp = another.find(i->first);
		if (temp == a_end) return false;
	}

	return true;

}

// preincrementacja
ListMap::const_iterator& ListMap::const_iterator::operator++()
{
   ///@todo Zaimplementowaæ metode

    if (node->internalDataPointer == NULL) return *this;
	node = node->next;
	return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator++(int)
{
   ///@todo Zaimplementowaæ metode
   const_iterator i;

    i = *this;
	++*this;
	return i;
}

ListMap::const_iterator& ListMap::const_iterator::operator--()
{
   ///@todo Zaimplementowaæ metode

    if (node->prev->internalDataPointer == NULL) return *this;
	node = node->prev;
	return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator--(int)
{
   ///@todo Zaimplementowaæ metode
    const_iterator i;

    i = *this;
	--*this;
	return i;
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::iterator ListMap::begin()
{
   ///@todo Zaimplementowaæ metode
   return iterator(first);
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::const_iterator ListMap::begin() const
{
   ///@todo Zaimplementowaæ metode
   return iterator(first);
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.
ListMap::iterator ListMap::end()
{
   ///@todo Zaimplementowaæ metode
   return iterator(first->prev);
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.
ListMap::const_iterator ListMap::end() const
{
   ///@todo Zaimplementowaæ metode
   return iterator(first->prev);
}

//////////////////////////////////////////////////////////////////////////////
// SmallMap
//////////////////////////////////////////////////////////////////////////////

/// Przyk³ad map'y z implementacj¹ podobn¹ do std::map.
/// To jest jedynie przyk³ad!!!
/// Normalnie implementacja powinna opieraæ siê o drzewo lub tablicê haszuj¹c¹.
template <class Key, class Val>
class SmallMap
{
   std::pair<Key, Val> tab[2];
   int isOcupied[2];
public:

   SmallMap()
   {
      for(unsigned i=0; i<2; ++i)
      {
         isOcupied[i]=0;
      }
   }

   typedef std::pair<Key, Val>* iterator;   ///< Ka¿dy wskaŸnik jest te¿ iteratorem.

   iterator begin() { return tab; }
   iterator end() { return tab+2; }

   Val& operator[](const Key& k)
   {
      static Val val;
      for(unsigned i=0; i<2; ++i)
      {
         if(isOcupied[i]&&tab[i].first==k)
            return tab[i].second;
      }
      // create
      for(unsigned i=0; i<2; ++i)
      {
         if(!isOcupied[i])
         {
            tab[i].first=k;
            isOcupied[i]=1;
            return tab[i].second;
         }
      }
      //std::cout<<"Out of space! You should not put more than two Key-Value pairs into the SmallMap.\n";
      std::cerr<<"Out of space! You should not put more than two Key-Value pairs into the SmallMap.\n";
      //assert(0);
      return val;   // Ma³o sensowne, ale to jest tylko przyk³¹d
   }
};


//////////////////////////////////////////////////////////////////////////////
// Testy
//////////////////////////////////////////////////////////////////////////////

/// Funckcja pomocnicza do wypisania elementów.
void print(const std::pair<int, std::string>& p)
{
   std::cout<<p.first<<", "<<p.second<<std::endl;
}

#include <map>

/// Testy u¿ytkownika
void test()
{
   // A typedef used by the test.
   typedef std::map<int, std::string> TEST_MAP;
   //typedef SmallMap<int, std::string> TEST_MAP;
   //typedef ListMap TEST_MAP;

   std::cout << "Testy uzytkownika" << std::endl;

        TEST_MAP m;


   m[2] = "Merry";
   m[4] = "Jane";
   m[8] = "Korwin";
   m[4] = "Magdalena";

   TEST_MAP n=m;
   for_each(m.begin(), m.end(), print );
   for_each(n.begin(), n.end(), print );
   //system("PAUSE");
   //assert(0);
}

