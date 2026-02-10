
#ifndef HEAP_HPP
#define HEAP_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Heap : virtual public SortableLinearContainer<Data>,
             virtual public ClearableContainer {
  // Must extend SortableLinearContainer<Data>,
  //             ClearableContainer

private:

protected:

public:

  // Destructor
  virtual ~Heap() = default;

  /* ************************************************************************ */

  // Copy assignment
  Heap& operator=(const Heap&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Heap& operator=(Heap&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions
  
  //verifica se la struttura e' un heap
  virtual bool IsHeap() const noexcept = 0;

  //trasforma la struttura in un heap
  virtual void Heapify() noexcept = 0;

};

/* ************************************************************************** */

}

#endif
