
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap : virtual public PQ<Data>, 
               virtual public  HeapVec<Data> {
  // Must extend PQ<Data>,
  // Could extend HeapVec<Data>

private:

  // ...

protected:

  // using Container::???;
  using HeapVec<Data>::size;
  using HeapVec<Data>::elements;
  using HeapVec<Data>::Heapify;

  // ...

public:

  // Default constructor
  PQHeap() = default;

  /* ************************************************************************ */

  // Specific constructors
  PQHeap(const TraversableContainer<Data>& container); // A priority queue obtained from a TraversableContainer
  PQHeap(const MappableContainer<Data>& container); // A priority queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  PQHeap(const PQHeap& other);

  // Move constructor
  PQHeap(PQHeap&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~PQHeap() = default;

  /* ************************************************************************ */

  // Copy assignment
  PQHeap& operator=(const PQHeap& other);

  // Move assignment
  PQHeap& operator=(PQHeap&& other) noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  const Data& Tip() const override; // Override PQ member (must throw std::length_error when empty)
  void RemoveTip() override; // Override PQ member (must throw std::length_error when empty)
  Data TipNRemove() override; // Override PQ member (must throw std::length_error when empty)

  void Insert(const Data& data) override; // Override PQ member (Copy of the value)
  void Insert(Data&& data) override; // Override PQ member (Move of the value)

  void Change(const ulong index, const Data& newval) override; // Override PQ member (Copy of the value)
  void Change(const ulong index, Data&& newval) override; // Override PQ member (Move of the value)

protected:

  // Auxiliary functions, if necessary!
  void FloatUp(ulong index) noexcept;
};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
