
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TraversableContainer : virtual public TestableContainer<Data> {
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~TraversableContainer() specifiers
  virtual ~TraversableContainer() = default; 

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  TraversableContainer& operator = (const TraversableContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  TraversableContainer& operator = (TraversableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
  bool operator == (const TraversableContainer&) const noexcept;
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.
  bool operator != (const TraversableContainer&) const noexcept;

  /* ************************************************************************ */

  // Specific member function

  // using TraverseFun = std::function<void(const Data &)>;
  using TraverseFun = std::function<void(const Data&)>; 

  // type Traverse(arguments) specifiers;
  virtual void Traverse(TraverseFun) const = 0; 

  // template <typename Accumulator>
  template <typename Accumulator>
  // using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;
  using FoldFun = std::function<Accumulator(const Data&, const Accumulator&)>;

  // template <typename Accumulator>
  template <typename Accumulator>
  // type Fold(arguments) specifiers;
  inline Accumulator Fold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)
  inline bool Exists(const Data&) const noexcept override;
  // type Exists(argument) specifiers; // Override TestableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : virtual public TraversableContainer<Data> {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~PreOrderTraversableContainer() specifiers
  virtual ~PreOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  PreOrderTraversableContainer& operator = (const PreOrderTraversableContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  PreOrderTraversableContainer& operator = (PreOrderTraversableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
  bool operator == (const PreOrderTraversableContainer&) const noexcept;
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.
  bool operator != (const PreOrderTraversableContainer&) const noexcept;

  /* ************************************************************************ */

  // Specific member function

  // using typename TraversableContainer<Data>::TraverseFun;
  using typename TraversableContainer<Data>::TraverseFun;

  // type PreOrderTraverse(arguments) specifiers;
  virtual void PreOrderTraverse(TraverseFun) const = 0; 

  // template <typename Accumulator>
  // using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;
  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  // template <typename Accumulator>
  // type PreOrderFold(arguments) specifiers;
  template <typename Accumulator>
  inline Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  // type Traverse(arguments) specifiers; // Override TraversableContainer member
  inline void Traverse(TraverseFun) const override;

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer : virtual TraversableContainer<Data> { //NON EREDITO COME PUBLIC TRAVERSABLECONTAINER
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~PostOrderTraversableContainer() specifiers
  virtual ~PostOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  PostOrderTraversableContainer& operator = (const PostOrderTraversableContainer&) = delete;  

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  PostOrderTraversableContainer& operator = (PostOrderTraversableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
  bool operator == (const PostOrderTraversableContainer&) const noexcept;
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.
  bool operator != (const PostOrderTraversableContainer&) const noexcept;
  /* ************************************************************************ */

  // Specific member function

  // using typename TraversableContainer<Data>::TraverseFun;
  using typename TraversableContainer<Data>::TraverseFun;

  // type PostOrderTraverse(arguments) specifiers;
  virtual void PostOrderTraverse(TraverseFun) const = 0;

  //template <typename Accumulator>
  template <typename Accumulator>
  // using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  // template <typename Accumulator>
  template <typename Accumulator>
  // type PostOrderFold(arguments) specifiers;
  inline Accumulator PostOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  // type Traverse(arguments) specifiers; // Override TraversableContainer member
  inline void Traverse(TraverseFun) const override;

};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif