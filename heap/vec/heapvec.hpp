
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec : virtual public Vector<Data>,
                virtual public Heap<Data> {
  // Must extend Heap<Data>,
  // Could extend Vector<Data>

private:

  // ...

protected:

  // using Container::???;
  using Vector<Data>::size;
  using Vector<Data>::elements;
  // ...

public:

  // Default constructor
   HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  HeapVec(const TraversableContainer<Data>& con); // A heap obtained from a TraversableContainer
  HeapVec(const MappableContainer<Data>& con); // A heap obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
   HeapVec(const HeapVec& other);

  // Move constructor
  HeapVec(HeapVec&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  HeapVec& operator=(const HeapVec& other);

  // Move assignment
  HeapVec& operator=(HeapVec&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HeapVec& other) const noexcept;
  bool operator!=(const HeapVec& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  bool IsHeap() const noexcept override;

  void Heapify() noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort();

protected:

  // Auxiliary functions, if necessary!
  void Heapify(ulong index) noexcept;
  void Heapify(ulong index, ulong limit) noexcept;

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
