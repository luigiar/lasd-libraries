
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public MutableLinearContainer<Data>,
             virtual public ClearableContainer {
  // Must extend MutableLinearContainer<Data>,
  //             ClearableContainer

private:

  // ...

protected:

  // using Container::???;
  using Container::size;

  struct Node {

    // Data
    Data element;
    Node* next = nullptr;
    // ...

    /* ********************************************************************** */

    Node() = default;

    // Specific constructors 
    // ...
    Node(const Data&);
    Node(Data&&) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    // ...
    Node(const Node&);

    // Move constructor
    // ...
    Node(Node&&) noexcept;

    /* ********************************************************************** */

    // Destructor
    // ...
    virtual ~Node(){
      delete next;
    };

    /* ********************************************************************** */

    // Comparison operators
    // ...
    bool operator == (const Node&) const noexcept;

    inline bool operator != (const Node&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions
    // ...

  };

  Node* head = nullptr;
  Node* tail = nullptr;

  // ...

public:

  // Default constructor
  // List() specifiers;
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  // List(argument) specifiers; // A list obtained from a TraversableContainer
  List(const TraversableContainer<Data>&);
  // List(argument) specifiers; // A list obtained from a MappableContainer
  List(MappableContainer<Data>&&);

  /* ************************************************************************ */

  // Copy constructor
  // List(argument) specifiers;
  List(const List&);

  // Move constructor
  // List(argument) specifiers;
  List(List&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~List() specifiers;
  virtual ~List(){
    delete head;
  };

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  List& operator=(const List&);

  // Move assignment
  // type operator=(argument) specifiers;
  List& operator=(List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  inline bool operator==(const List&) const noexcept;
  // type operator!=(argument) specifiers;
  inline bool operator!=(const List&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // type InsertAtFront(argument) specifier; // Copy of the value
  void InsertAtFront(const Data&);
  // type InsertAtFront(argument) specifier; // Move of the value
  void InsertAtFront(Data&&);
  // type RemoveFromFront() specifier; // (must throw std::length_error when empty)
  void RemoveFromFront();
  // type FrontNRemove() specifier; // (must throw std::length_error when empty)
  Data FrontNRemove();

  // type InsertAtBack(argument) specifier; // Copy of the value
  void InsertAtBack(const Data&);
  // type InsertAtBack(argument) specifier; // Move of the value
  void InsertAtBack(Data&&);
  //type RemoveFromBack() specifier; //(must throw std::length_error when empty)
  void RemoveFromBack();
  //type BackNRemove() specifier; //(must throw std::length_error when empty)
  Data BackNRemove();

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // type operator[](argument) specifiers; // Override LinearContainer member (must throw std::out_of_range when out of range)
  const Data& operator[](const ulong) const override;
  Data& operator[](const ulong) override;

  // type Front() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
  const Data& Front() const override;
  inline Data& Front() override;

  // type Back() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
  const Data& Back() const override;
  inline Data& Back() override;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  // using typename MappableContainer<Data>::MapFun;
  using typename MappableContainer<Data>::MapFun;

  // type Map(argument) specifiers; // Override MappableContainer member
  void Map(MapFun MapFunction) override {
    PreOrderMap(MapFunction);
  };

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  // type PreOrderMap(argument) specifiers; // Override PreOrderMappableContainer member
  void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  // type PostOrderMap(argument) specifiers; // Override PostOrderMappableContainer member
  void PostOrderMap(MapFun MapFunction) override {
    PostOrderMap(MapFunction, head);
  };

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  // using typename TraversableContainer<Data>::TraverseFun;
  using typename TraversableContainer<Data>::TraverseFun;

  // type Traverse(arguments) specifiers; // Override TraversableContainer member
  void Traverse(TraverseFun TraverseFunction) const override {
    PreOrderTraverse(TraverseFunction);
  };

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  // type PreOrderTraverse(arguments) specifiers; // Override PreOrderTraversableContainer member
  void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  // type PostOrderTraverse(arguments) specifiers; // Override PostOrderTraversableContainer member
  void PostOrderTraverse(TraverseFun TraverseFunction) const override {
    PostOrderTraverse(TraverseFunction, head);
  };

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member
  void Clear() override;

protected:

  //From MappableContainer
  //void PreOrderMap(MapFun, Node*);
  void PostOrderMap(MapFun, Node*);

  //From TraversableContainer
  //void PreOrderTraverse(TraverseFun, const Node*) const;
  void PostOrderTraverse(TraverseFun, const Node*) const;

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
