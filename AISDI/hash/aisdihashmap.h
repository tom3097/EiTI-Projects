/**
@file aisdihashmap.h

AISDIHashMap and related functions interface.

@author
Pawel Cichocki

@date
last revision
- 2006.03.24 Pawel Cichocki: wrote it

COPYRIGHT:
Copyright (c) 2006 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include <utility>

#include <iostream>

/// Default keys' comparing function for AISDIHashMap - it uses
/// operator== by default.
/// @returns true if keys are equal, false otherwise.
/// @param key1 First key to compare.
/// @param key2 Second key to compare.


const unsigned ArraySize = 65538;

/// funkcja porownujaca klucze
template <class Key>
inline bool _compFunc(const Key& key1,const Key& key2)
{
   return (key1==key2);
}

/// funkcja haszujaca, zwraca wartosc z zakresu 1 - 65536
inline unsigned hashF(const std::string& m)
{
    const char* in = m.c_str();

    unsigned hash = 0;
    while(*in)
    {
        hash = hash * 11 + *in++;
    }

	hash = hash % (ArraySize-2);
	return hash+1;
}

/// A map with a similar interface to std::map.
template<class K, class V, unsigned hashFunc(const K&)=&hashF, bool compFunc(const K&,const K&)=&_compFunc<K> >
class AISDIHashMap
{
private:
    static const unsigned BeforeTheFirstIndex = 0;
	static const unsigned PastTheEndIndex = ArraySize - 1;

	struct ListNode
	{
		std::pair<K,V> data;
		ListNode *next;
		ListNode *prev;
		bool lastWithCurrentHash;

		ListNode(): next(NULL), prev(NULL), lastWithCurrentHash(true) {};	///konstruktor stworzony z mysla o straznikach
		ListNode(std::pair<K,V> _data, ListNode *_next = NULL, ListNode *_prev = NULL, bool _lastWithCurrentHash = false):
		data(_data), next(_next), prev(_prev), lastWithCurrentHash(_lastWithCurrentHash) {};
	};
	ListNode *hashTable[ArraySize];	///tablica wskaznikow, czyli tablica list
public:
   typedef K key_type;
   typedef V value_type;
   typedef unsigned size_type;
   typedef std::pair<key_type, value_type> T;

   AISDIHashMap()
   {
	   hashTable[BeforeTheFirstIndex] = new ListNode();		/// straznik na poczatku listy
	   hashTable[PastTheEndIndex] = new ListNode();			/// straznik na koncu listy

	   hashTable[BeforeTheFirstIndex]->next = hashTable[PastTheEndIndex];
	   hashTable[PastTheEndIndex]->prev = hashTable[BeforeTheFirstIndex];
	   hashTable[BeforeTheFirstIndex]->prev = hashTable[BeforeTheFirstIndex];
	   hashTable[PastTheEndIndex]->next = hashTable[PastTheEndIndex];

	   for(unsigned i = BeforeTheFirstIndex + 1; i <= PastTheEndIndex - 1; ++i)		///reszte wskaznikow ustawiam na NULL
		   hashTable[i] = NULL;
   }

   ~AISDIHashMap()
   {
	   clear();
	   delete hashTable[BeforeTheFirstIndex];
	   delete hashTable[PastTheEndIndex];
   }

   /// Coping constructor.
   explicit AISDIHashMap(const AISDIHashMap<K, V, hashFunc, compFunc>& a)
   {
	   hashTable[BeforeTheFirstIndex] = new ListNode();		/// tworze pierwszego straznika

	   ListNode *tempPrev = hashTable[BeforeTheFirstIndex];
	   hashTable[BeforeTheFirstIndex]->prev = hashTable[BeforeTheFirstIndex];

	   for(unsigned i = BeforeTheFirstIndex+1; i <= PastTheEndIndex-1; ++i)
	   {
		   ListNode *aPointer = a.hashTable[i];
		   if(aPointer != NULL)
		   {
			   hashTable[i] = new ListNode(aPointer->data, NULL, tempPrev, aPointer->lastWithCurrentHash);	/// tworze pierwszy element w liscie o podanym haszu
			   tempPrev->next = hashTable[i];
			   ListNode *tempNode = hashTable[i];

			   while(tempNode->lastWithCurrentHash == false)
			   {
				   aPointer = aPointer->next;

				   ListNode *newNode = new ListNode(aPointer->data, NULL, tempNode, aPointer->lastWithCurrentHash);
				   tempNode->next = newNode;
				   tempNode = newNode;
			   }
			   tempPrev = tempNode;
		   }
		   else
			   hashTable[i] = NULL;
	   }

	   hashTable[PastTheEndIndex] = new ListNode();			/// tworzenie drugiego straznika
	   tempPrev->next = hashTable[PastTheEndIndex];
	   hashTable[PastTheEndIndex]->prev = tempPrev;
	   hashTable[PastTheEndIndex]->next = hashTable[PastTheEndIndex];
   }

   /// const_iterator.
   /// implementacja tej klasy stworzona jest w oparciu o klase const_iterator z poprzedniego cwiczenia
   class const_iterator: public std::iterator<std::forward_iterator_tag, T >
   {
   protected:
	   ListNode *listNode;
	   friend class AISDIHashMap;

	   const_iterator(ListNode* x) : listNode(x) {}
   public:
	   const_iterator() {}
	   const_iterator(const const_iterator& a): listNode(a.listNode) {}

	   inline const T& operator*() const
	   {
		   return listNode->data;
	   }

	   inline const T* operator->() const
	   {
		   return &(listNode->data);
	   }

	   ///preinkrementacja
	   inline const_iterator& operator++()
	   {
		   listNode = listNode->next;
		   return *this;
	   }

	   ///postinkrementacja
	   inline const_iterator operator++(int)
	   {
		   const_iterator original(*this);
		   listNode = listNode->next;
		   return original;
	   }

	   ///predekrementacja
	   inline const_iterator& operator--()
	   {
		   if(listNode->prev != listNode->prev->prev)
			   listNode = listNode->prev;
		   return *this;
	   }

	   ///postdekrementacja
	   inline const_iterator operator--(int)
	   {
		   const_iterator original(*this);
		   if(listNode->prev != listNode->prev->prev)
			   listNode = listNode->prev;
		   return original;
	   }

	   ///przeciazenie operatora ==
	   inline bool operator==(const const_iterator& a) const
	   {
		   return listNode == a.listNode;
	   }

	   ///przeciazenie operatora !=
	   inline bool operator!=(const const_iterator& a) const
	   {
		   return listNode != a.listNode;
	   }
   };

   /// iterator.
   /// implementacja tej klasy stworzona jest w oparciu o klase iterator z poprzedniego cwiczenia
   class iterator: public const_iterator
   {
	   iterator(ListNode *x): const_iterator(x) {};
	   friend class AISDIHashMap;

   public:
	   iterator() {};
	   iterator(const iterator& a): const_iterator(a.listNode) {};

	   inline T& operator*() const
	   {
		   return (const_iterator::listNode)->data;
	   }

	   inline T* operator->() const
	   {
		   return &((const_iterator::listNode)->data);
	   }

	   ///preinkrementacja
	   iterator& operator++()
	   {
		   ++(*(const_iterator*)this);
		   return *this;
	   }

	   ///postinkrementacja
	   iterator operator++(int)
	   {
		   iterator temp = *this;
		   ++*this;
		   return temp;
	   }

	   ///predekrementacja
	   iterator& operator--()
	   {
		   if((const_iterator::listNode)->prev != (const_iterator::listNode)->prev->prev)
			   --(*(const_iterator*)this);
		   return *this;
	   }

	   ///postdekrementacja
	   iterator operator--(int)
	   {
		   iterator temp = *this;
		   if((const_iterator::listNode)->prev != (const_iterator::listNode)->prev->prev)
			   --*this;
		   return temp;
	   }
   };

   /// Returns an iterator addressing the first element in the map.
   inline iterator begin()
   {
	   return iterator(hashTable[BeforeTheFirstIndex]->next);
   }

   inline const_iterator begin() const
   {
	   return const_iterator(hashTable[BeforeTheFirstIndex]->next);
   }

   /// Returns an iterator that addresses the location succeeding the last element in a map.
   inline iterator end()
   {
	   return iterator(hashTable[PastTheEndIndex]);
   }

   inline const_iterator end() const
   {
	   return const_iterator(hashTable[PastTheEndIndex]);
   }

   /// Inserts an element into the map.
   /// @returns A pair whose bool component is true if an insertion was
   ///          made and false if the map already contained an element
   ///          associated with that key, and whose iterator component coresponds to
   ///          the address where a new element was inserted or where the element
   ///          was already located.
   std::pair<iterator, bool> insert(const std::pair<K, V>& entry)
   {
	   iterator it = find(entry.first);

	   if(it != end())
		   return std::make_pair(it, (bool)false);

	   unsigned tempHash = hashFunc(entry.first);
	   unsigned tempIndex;
	   bool _lastWithCurrentHash = false;

	   if(hashTable[tempHash] == NULL)
	   {
		   tempIndex = tempHash+1;				/// hashTable[tempIndex] - adres nastepnego elementu po dodawanym
		   while(hashTable[tempIndex] == NULL)
			   ++tempIndex;
		   _lastWithCurrentHash = true;
	   }
	   else
	   {
		   tempIndex = tempHash	;				/// hashTable[tempIndex] - adres nastepnego elementu po dodawanym
	   }

	   ListNode *afterToInsert, *beforeToInsert;
	   afterToInsert = hashTable[tempIndex];
	   beforeToInsert = hashTable[tempIndex]->prev;

	   ListNode *newNode = new ListNode(entry, afterToInsert, beforeToInsert, _lastWithCurrentHash);
	   beforeToInsert->next = newNode;
	   afterToInsert->prev = newNode;

	   hashTable[tempHash] = newNode;

	   return std::make_pair(iterator(newNode), (bool)true);
   }

   /// Returns an iterator addressing the location of the entry in the map
   /// that has a key equivalent to the specified one or the location succeeding the
   /// last element in the map if there is no match for the key.
   iterator find(const K& k)
   {
	   ListNode *tempNode = hashTable[hashFunc(k)];

	   if(tempNode == NULL)		/// gdy nie istnieje element o podanym haszu to nie istnieje element o podanym kluczu
		   return end();

	   while(tempNode->lastWithCurrentHash == false)
	   {
		   if(compFunc(tempNode->data.first,k))
			   return iterator(tempNode);
		   tempNode = tempNode->next;
	   }
	   if(compFunc(tempNode->data.first,k))
		   return iterator(tempNode);

	   return end();
   }

   /// Returns an const iterator
   const_iterator find(const K& k) const
   {
	   ListNode *tempNode = hashTable[hashFunc(k)];

	   if(tempNode == NULL)	/// gdy nie istnieje element o podanym haszu to nie istnieje element o podanym kluczu
		   return end();

	   while(tempNode->lastWithCurrentHash == false)
	   {
		   if(compFunc(tempNode->data.first,k))
			   return iterator(tempNode);
		   tempNode = tempNode->next;
	   }
	   if(compFunc(tempNode->data.first,k))
		   return iterator(tempNode);

	   return end();
   }

   /// Inserts an element into a map with a specified key value
   /// if one with such a key value does not exist.
   /// @returns Reference to the value component of the element defined by the key.
   V& operator[](const K& k)
   {
       return insert(std::make_pair(k, V())).first->second;
   }

   /// Tests if a map is empty.
   bool empty( ) const
   {
	   return begin() == end();
   }

   /// Returns the number of elements in the map.
   size_type size() const
   {
	   size_type listSize = 0;
	   for(const_iterator it = begin(); it != end(); ++it)
		   ++listSize;

	   return listSize;
   }

   /// Returns the number of elements in a map whose key matches a parameter-specified key.
   size_type count(const K& _Key) const
   {
	   /// to nie jest multimapa
	   const_iterator it = find(_Key);

	   return (it == end()) ? 0 : 1;
   }

   /// Removes an element from the map.
   /// @returns The iterator that designates the first element remaining beyond any elements removed.
   iterator erase(iterator i)
   {
	   ListNode *beforeToDelete, *afterToDelete, *toDelete;
	   toDelete = i.listNode;
	   beforeToDelete = i.listNode->prev;
	   afterToDelete = i.listNode->next;

	   beforeToDelete->next = afterToDelete;
	   afterToDelete->prev = beforeToDelete;

	   unsigned tempHash = hashFunc(i->first);

	   if(hashTable[tempHash] == toDelete && toDelete->lastWithCurrentHash == true)
	   {
		   hashTable[tempHash] = NULL;
	   }
	   else if(hashTable[tempHash] == toDelete && toDelete->lastWithCurrentHash == false)
	   {
			hashTable[tempHash] = afterToDelete;
	   }
	   else if(toDelete->lastWithCurrentHash == true && hashTable[tempHash] != toDelete)
	   {
		   beforeToDelete->lastWithCurrentHash = true;
	   }
	   
	   delete toDelete;

	   return iterator(afterToDelete);
   }

   /// Removes a range of elements from the map.
   /// The range is defined by the key values of the first and last iterators
   /// first is the first element removed and last is the element just beyond the last elemnt removed.
   /// @returns The iterator that designates the first element remaining beyond any elements removed.
   iterator erase(iterator first, iterator last)
   {
       iterator it = first;
       while(it != last)
            it = erase(it);

       return last;
   }

   /// Removes an element from the map.
   /// @returns The number of elements that have been removed from the map.
   ///          Since this is not a multimap itshould be 1 or 0.
   size_type erase(const K& key)
   {
	   iterator it = find(key);

	   if(it != end())
	   {
		   erase(it);
		   return 1;
	   }
	   return 0;
   }

   /// Erases all the elements of a map.
   void clear()
   {
	   erase(begin(),end());
   }
};
