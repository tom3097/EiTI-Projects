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
   ///@todo Zaimplementowa� metode
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
// @returns Para, kt�rej komponent bool jest r�wny true gdy wstawienie zosta�o
//          dokonane, r�wny false gdy element identyfikowany przez klucz
//          ju� istnia� w mapie. Iterator ustawiony jest na ten wstawiony
//          lub istniej�cy ju� w mapie element.
std::pair<ListMap::iterator, bool> ListMap::insert(const std::pair<Key, Val>& entry)
{
   ///@todo Uzupe�ni� kod
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
// Matoda zak�ada, �e w mapie nie wyst�puje element identyfikowany przez key
ListMap::iterator ListMap::unsafe_insert(const std::pair<Key, Val>& entry)
{
   ///@todo Uzupe�ni� kod
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

// Zwraca iterator addresuj�cy element w mapie dla kt�rego klucz jest r�wny
// szukanemu kluczowi lub element za ostatnim gdy szukanego klucza brak w mapie.
ListMap::iterator ListMap::find(const Key& k)
{
   ///@todo Zaimplementowa� metode
   iterator i;
   i = begin();

   for(; i != end(); ++i)
        if(i->first == k) return i;

   return end();
}

ListMap::const_iterator ListMap::find(const Key& k) const
{
   ///@todo Zaimplementowa� metode
   const_iterator i;
   i = begin();

   for(; i != end(); ++i)
        if(i->first == k) return i;

   return end();
}

// Udost�pnia warto�� powi�zan� z kluczem key. Wstawia element do mapy je�li
// nie istnia�.
// @returns Referencje do warto�ci powi�zanej z kluczem.
ListMap::Val& ListMap::operator[](const Key& k)
{
   ///@todo Zaimplementowa� metode

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

// Zwraca ilo�� element�w w mapie.
ListMap::size_type ListMap::size( ) const
{
   return (end()->first);
}

// Zwraza ilo�� element�w skojarzonych z kluczem key.
ListMap::size_type ListMap::count(const Key& _Key) const
{
   ///@todo Zaimplementowa� metode
   const_iterator i;

   i = find(_Key);
   if (i != end()) return 1;
   else
   return 0;  // this is not a multimap
}

// Usuwa element z mapy.
// @returns iterator adresuj�cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator i)
{
   ///@todo Zaimplementowa� metode
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

// Usuwa zakres element�w z mapy.
// Zakres jest zdefiniowany poprzez iteratory first i last
// first jest okre�la pierwszy element do usuni�cia, a last okre�la element
// po ostatnim usuni�tym elemencie.
// @returns iterator adresuj�cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator f, ListMap::iterator l)
{
   ///@todo Zaimplementowa� metode
   iterator temp;
   temp = f;

   while (temp != l)
        temp = erase(temp);

   return l;
}

// Usuwa element z mapy.
// @returns Ilo�� usuni�tych element�w.
//          (nie jest to multimapa, wi�� mo�e by� to warto�� 1 lub 0 )
ListMap::size_type ListMap::erase(const Key& key)
{
   ///@todo Zaimplementowa� metode
   iterator i;
   i = find(key);

   if(i == end())return 0;
   else
   {
    erase(i);
    return 1;
   }

}

// Usuni�cie wszystkich element�w z mapy.
void ListMap::clear( )
{
   ///@todo Zaimplementowa� metode
   erase(begin(), end());
}

// Por�wnanie strukturalne map.
// Czy reprezentacja danych jest identyczna.
// Zwraca true je�li wewn�trzne struktury map s� identyczne.
bool ListMap::struct_eq(const ListMap& another) const
{
   ///@todo Zaimplementowa� metode
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

// Por�wnanie informacyjne map.
// Czy informacje trzymane w mapach s� identyczne.
// Zwraca true je�li mapy zwieraj� takie same pary klucz-warto��.
bool ListMap::info_eq(const ListMap& another) const
{
   ///@todo Zaimplementowa� metode
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
   ///@todo Zaimplementowa� metode

    if (node->internalDataPointer == NULL) return *this;
	node = node->next;
	return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator++(int)
{
   ///@todo Zaimplementowa� metode
   const_iterator i;

    i = *this;
	++*this;
	return i;
}

ListMap::const_iterator& ListMap::const_iterator::operator--()
{
   ///@todo Zaimplementowa� metode

    if (node->prev->internalDataPointer == NULL) return *this;
	node = node->prev;
	return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator--(int)
{
   ///@todo Zaimplementowa� metode
    const_iterator i;

    i = *this;
	--*this;
	return i;
}

/// Zwraca iterator addresuj�cy pierwszy element w mapie.
ListMap::iterator ListMap::begin()
{
   ///@todo Zaimplementowa� metode
   return iterator(first);
}

/// Zwraca iterator addresuj�cy pierwszy element w mapie.
ListMap::const_iterator ListMap::begin() const
{
   ///@todo Zaimplementowa� metode
   return iterator(first);
}

/// Zwraca iterator addresuj�cy element za ostatnim w mapie.
ListMap::iterator ListMap::end()
{
   ///@todo Zaimplementowa� metode
   return iterator(first->prev);
}

/// Zwraca iterator addresuj�cy element za ostatnim w mapie.
ListMap::const_iterator ListMap::end() const
{
   ///@todo Zaimplementowa� metode
   return iterator(first->prev);
}

//////////////////////////////////////////////////////////////////////////////
// SmallMap
//////////////////////////////////////////////////////////////////////////////

/// Przyk�ad map'y z implementacj� podobn� do std::map.
/// To jest jedynie przyk�ad!!!
/// Normalnie implementacja powinna opiera� si� o drzewo lub tablic� haszuj�c�.
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

   typedef std::pair<Key, Val>* iterator;   ///< Ka�dy wska�nik jest te� iteratorem.

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
      return val;   // Ma�o sensowne, ale to jest tylko przyk��d
   }
};


//////////////////////////////////////////////////////////////////////////////
// Testy
//////////////////////////////////////////////////////////////////////////////

/// Funckcja pomocnicza do wypisania element�w.
void print(const std::pair<int, std::string>& p)
{
   std::cout<<p.first<<", "<<p.second<<std::endl;
}

#include <map>

/// Testy u�ytkownika
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

