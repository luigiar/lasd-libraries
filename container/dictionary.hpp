#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer: virtual public TestableContainer<Data> {
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~DictionaryContainer() specifiers
 virtual ~DictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  DictionaryContainer& operator = (const DictionaryContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  DictionaryContainer& operator = (DictionaryContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  bool operator == (const DictionaryContainer&) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
  bool operator != (const DictionaryContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Insert(argument) specifiers; // Copy of the value
  virtual bool Insert(const Data&) = 0;
  // type Insert(argument) specifiers; // Move of the value
  virtual bool Insert (Data&&) = 0;
  // type Remove(argument) specifiers;
  virtual bool Remove(const Data&) = 0;

  // type InsertAll(argument) specifiers; // Copy of the value; From TraversableContainer; True if all are inserted
  inline virtual bool InsertAll(const TraversableContainer<Data>&); 
  // type InsertAll(argument) specifiers; // Move of the value; From MappableContainer; True if all are inserted
  inline virtual bool InsertAll(MappableContainer<Data>&&);
  // type RemoveAll(argument) specifiers; // From TraversableContainer; True if all are removed
  inline virtual bool RemoveAll(const TraversableContainer<Data>&); 

  // type InsertSome(argument) specifiers; // Copy of the value; From TraversableContainer; True if some is inserted
  inline virtual bool InsertSome(const TraversableContainer<Data>&);
  // type InsertSome(argument) specifiers; // Move of the value; From MappableContainer; True if some is inserted
  inline virtual bool InsertSome(MappableContainer<Data>&&);
  // type RemoveSome(argument) specifiers; // From TraversableContainer; True if some is removed
  inline virtual bool RemoveSome(const TraversableContainer<Data>&);

};

/* ************************************************************************** */

template <typename Data>
class OrderedDictionaryContainer : virtual public DictionaryContainer<Data> {
  // Must extend DictionaryContainer<Data>

private:

protected:

public:

  // Destructor
  // ~OrderedDictionaryContainer() specifiers
  virtual ~OrderedDictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  OrderedDictionaryContainer& operator = (const OrderedDictionaryContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  OrderedDictionaryContainer& operator = (OrderedDictionaryContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  bool operator == (const OrderedDictionaryContainer&) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
  bool operator != (const OrderedDictionaryContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Min(argument) specifiers; // (concrete function must throw std::length_error when empty)
  virtual const Data& Min() const = 0;
  // type MinNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
  inline virtual Data MinNRemove();
  // type RemoveMin(argument) specifiers; // (concrete function must throw std::length_error when empty)
  inline virtual void RemoveMin();

  // type Max(argument) specifiers; // (concrete function must throw std::length_error when empty)
  virtual const Data& Max() const = 0;
  // type MaxNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
  inline virtual Data MaxNRemove();
  // type RemoveMax(argument) specifiers; // (concrete function must throw std::length_error when empty)
  inline virtual void RemoveMax();

  // type Predecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  virtual const Data& Predecessor(const Data&) const = 0;
  // type PredecessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
  inline virtual Data PredecessorNRemove(const Data&);
  // type RemovePredecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  inline virtual void RemovePredecessor(const Data&);

  // type Successor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  virtual const Data& Successor(const Data&) const = 0;
  // type SuccessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
  inline virtual Data SuccessorNRemove(const Data&);
  // type RemoveSuccessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  inline virtual void RemoveSuccessor(const Data&);

};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif
