
#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : virtual public Set<Data>,
               virtual public ResizableContainer {
  // Must extend Set<Data>,
  //ResizableContainer

private:

  // ...

protected:

  // using Container::???;
  using Container::size; //numero effettivo di dati
  ulong head = 0;
  ulong capacity = 0; //numero di celle
  Data* Elements = nullptr;

  // ...

public:

  // Default constructor
  // SetVec() specifiers;
  SetVec();

  /* ************************************************************************ */

  // Specific constructors
  // SetVec(argument) specifiers; // A set obtained from a TraversableContainer
  SetVec(const TraversableContainer<Data>& con);
  // SetVec(argument) specifiers; // A set obtained from a MappableContainer
  SetVec(MappableContainer<Data>&& con) noexcept;

  /* ************************************************************************ */

  // Copy constructor
  // SetVec(argument) specifiers;
  SetVec(const SetVec&);

  // Move constructor
  // SetVec(argument) specifiers;
  SetVec(SetVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~SetVec() specifiers;
  virtual ~SetVec(){
    delete[] Elements;
  };

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  SetVec& operator = (const SetVec&);

  // Move assignment
  // type operator=(argument) specifiers;
  SetVec& operator = (SetVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator == (const SetVec&) const noexcept;

  // type operator!=(argument) specifiers;
  bool operator != (const SetVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  // type Min(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  const Data& Min() const override; //Back
  // type MinNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MinNRemove() override;
  // type RemoveMin(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMin() override;
  // type Max(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  const Data& Max() const override; //Front
  // type MaxNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MaxNRemove() override;
  // type RemoveMax(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMax() override;
  // type Predecessor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  const Data& Predecessor(const Data&) const override;
  // type PredecessorNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&) override;
  // type RemovePredecessor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&) override;
  // type Successor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  const Data& Successor(const Data&) const override;
  // type SuccessorNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&) override;
  // type RemoveSuccessor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&) override;
  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  // type Insert(argument) specifiers; // Override DictionaryContainer member (copy of the value)
  bool Insert(const Data&) override;
  // type Insert(argument) specifiers; // Override DictionaryContainer member (move of the value)
  bool Insert(Data&&) noexcept override;
  // type Remove(argument) specifiers; // Override DictionaryContainer member
  bool Remove(const Data&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // type operator[](argument) specifiers; // Override LinearContainer member (must throw std::out_of_range when out of range)
  const Data& operator[](const ulong) const override;

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  // type Exists(argument) specifiers; // Override TestableContainer member
  bool Exists(const Data&) const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member
  void Clear() override;

  /* ************************************************************************ */

  //Specific member function (inherited from ResizableContainer)
  
  void Resize(ulong) override;
  bool Empty() const noexcept override;
  ulong Size() const noexcept override;

protected:

  // Auxiliary functions, if necessary!
  //From Container
  long BinarySearch(const Data& value) const;

};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif

