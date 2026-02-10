
namespace lasd {

/* ************************************************************************ */

/* ************************ Constructor ********************************* */

template<typename Data>
SetLst<Data>::SetLst() : List<Data>() {}

template<typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data>& con) {
  con.Traverse([this](const Data& val) { this->Insert(val); });
}

template<typename Data>
SetLst<Data>::SetLst(MappableContainer<Data>&& con) noexcept {
  con.Map([this](Data& val) { Insert(std::move(val)); });
}

template<typename Data>
SetLst<Data>::SetLst(const SetLst& other) : List<Data>(other) {}

template<typename Data>
SetLst<Data>::SetLst(SetLst&& other) noexcept : List<Data>(std::move(other)) {}

/* ************************************************************************ */

/* ************************ Assignement ***************************** */

template<typename Data>
SetLst<Data>& SetLst<Data>::operator = (const SetLst& other) {
  List<Data>::operator = (other);
  return *this;
}

template<typename Data>
SetLst<Data>& SetLst<Data>::operator = (SetLst&& other) noexcept {
  List<Data>::operator = (std::move(other));
  return *this;
}

/* ************************************************************************ */

/* ************************ Comparison Operator ********************************* */

template<typename Data>
bool SetLst<Data>::operator == (const SetLst& other) const noexcept {
  return List<Data>::operator == (other);
}

template<typename Data>
bool SetLst<Data>::operator != (const SetLst& other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************ */

/* ************************ BinarySearch ********************************* */

template<typename Data>
bool SetLst<Data>::BinarySearch(const Data& value, ulong& position) const {
  long left = 0;
  long right = static_cast<long>(this->size) - 1;

  //puntatore per scorrere la lista
  Node** current = const_cast<Node**>(&this->head); 
  long currentIndex = 0;

  while (left <= right) {
    long mid = (left + right) / 2;

    //se dobbiamo tornare indietro nella lista (mid < currentIndex), resettiamo il puntatore
    //siamo costretti a farlo perché la lista è singolarmente collegata
    if (mid < currentIndex) {
      current = const_cast<Node**>(&this->head);
      currentIndex = 0;
    }

    //avanziamo il puntatore fino a mid
    while (currentIndex < mid) {
      current = &((*current)->next);
      ++currentIndex;
    }

    //confrontiamo l'elemento a mid con il valore cercato
    if ((*current)->element == value) {
      position = mid;
      return true;
    } else if ((*current)->element < value) {
      left = mid + 1; //cerca a destra
    } else {
      right = mid - 1; //cerca a sinistra
    }
  }

  //non trovato, posizione di inserimento
  position = static_cast<ulong>(left);
  return false;
}

/* ************************************************************************ */

/* ************************ Insert ********************************* */ 



template <typename Data>
bool SetLst<Data>::Insert(const Data &value) {
  ulong position = 0;

  //controlliamo se l'elemento è già presente e troviamo la posizione di inserimento
  if (BinarySearch(value, position)) 
    return false; //elemento già presente
  
  //scorrimento della lista fino alla posizione di inserimento (puntatore a puntatore)
  //usiamo Node** per poter modificare il puntatore next del nodo precedente
  Node **current = &(this->head);
  for(ulong i = 0; i < position; ++i)
    current = &((*current)->next);

  //inserimento classico in lista collegata
  Node* newNode = new Node(value);
  newNode->next = *current; //il nuovo nodo punta al successivo
  *current = newNode; //il precedente punta al nuovo nodo

  if (newNode->next == nullptr) //aggiorniamo la coda se necessario
    this->tail = newNode;
  ++(this->size);
  return true;
}

template <typename Data>
bool SetLst<Data>::Insert(Data &&value) noexcept {
  ulong position = 0;
  if (BinarySearch(value, position)) 
    return false;
  
  Node **current = &(this->head);
  for (ulong i = 0; i < position; ++i)
    current = &((*current)->next);

  Node *newNode = new Node(std::move(value));
  newNode->next = *current;
  *current = newNode;
  if (newNode->next == nullptr)
    this->tail = newNode;
  ++(this->size);
  return true;
}

/* ************************************************************************ */

/* ************************ Remove ********************************* */ 

template <typename Data>
bool SetLst<Data>::Remove(const Data &val) {
  ulong position = 0;
  if (!BinarySearch(val, position))
    return false;
    
  Node **current = &(this->head);
  for (ulong i = 0; i < position; ++i)
    current = &((*current)->next);
    
  Node *tmp = *current;
  *current = tmp->next;
  if (tmp == this->tail) {
    if (this->head == nullptr)
      this->tail = nullptr;
    else {
      Node *last = this->head;
      while (last->next != nullptr)
        last = last->next;
      this->tail = last;
    }
  }
  tmp->next = nullptr;
  delete tmp;
  --(this->size);
  return true;
}

/* ************************************************************************ */

/* ************************ Access Operator ********************************* */

template<typename Data>
const Data& SetLst<Data>::operator[](const ulong index) const {
  return List<Data>::operator[](index);
}

/* ************************************************************************ */

/* ************************ Exists/Clear ********************************* */

template <typename Data>
bool SetLst<Data>::Exists(const Data &value) const noexcept {
    ulong position;
    return BinarySearch(value, position);
}

template<typename Data>
void SetLst<Data>::Clear() {
  List<Data>::Clear();
}

/* ************************************************************************ */

/* ************************ OrderedDictionary Min/Max ******************** */

template <typename Data>
const Data& SetLst<Data>::Min() const {
  if(this->Empty())
    throw std::length_error("SetLst is empty");
  return List<Data>::Front();
}

template <typename Data>
Data SetLst<Data>::MinNRemove() {
  if (this->Empty()) 
    throw std::length_error("Min does not exist");
  Data ret = List<Data>::Front();
  List<Data>::RemoveFromFront();
  return ret;
}

template <typename Data>
void SetLst<Data>::RemoveMin() {
  if (this->Empty())
    throw std::length_error("Min does not exist");
  List<Data>::RemoveFromFront();
}

template <typename Data>
const Data& SetLst<Data>::Max() const {
  if(this->Empty())
    throw std::length_error("Max does not exist");
  return List<Data>::Back();
}

template <typename Data>
Data SetLst<Data>::MaxNRemove() {
  if (this->Empty()) 
    throw std::length_error("Max does not exist");
  Data ret = List<Data>::Back();
  List<Data>::RemoveFromBack();
  return ret;
}

template <typename Data>
void SetLst<Data>::RemoveMax() {
  if (this->Empty()) {
    throw std::length_error("Max does not exist");
  }
  List<Data>::RemoveFromBack();
}

/* ************************************************************************ */

/* ****** OrderedDictionary Successor/Predecessor ******* */

template <typename Data>
const Data &SetLst<Data>::Successor(const Data &value) const {
  if (this->Empty())
    throw std::length_error("Successor not found");
  
  ulong position = 0;
  bool found = BinarySearch(value, position);

  Node *current = this->head;
  
  //arriviamo all'elemento (o alla posizione di inserimento)
  for (ulong i = 0; i < position; ++i)
    current = current->next;

  //se trovato, il successore è l'elemento dopo di esso
  if (found) {
    if (current == nullptr || current->next == nullptr)
      throw std::length_error("Successor not found"); //non c'è successore, era l'ultimo elemento
    current = current->next;
  }
  
  //controllo di sicurezza finale
  if (current == nullptr || !(current->element > value))
    throw std::length_error("Successor not found");
  return current->element;
}

template <typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data& value) {
  if (this->Empty())
    throw std::length_error("Successor not found");

  Node** currentPtr = &(this->head);
  Node* last = nullptr; 
  
  while (*currentPtr != nullptr && !((*currentPtr)->element > value)) {
    last = *currentPtr; 
    currentPtr = &((*currentPtr)->next);
  }

  if (*currentPtr == nullptr)
    throw std::length_error("Successor not found");

  Node* toDelete = *currentPtr;
  Data succValue = std::move(toDelete->element);
  *currentPtr = toDelete->next;

  if (toDelete == this->tail) {
    this->tail = (currentPtr == &(this->head)) ? nullptr : last;
  }

  toDelete->next = nullptr;
  delete toDelete;
  --(this->size);
  return succValue;
}


template <typename Data>
void SetLst<Data>::RemoveSuccessor(const Data& value) {
  if (this->Empty())
    throw std::length_error("Empry SetLst");

  Node** currentPtr = &(this->head);
  while (*currentPtr != nullptr && !((*currentPtr)->element == value)) {
    currentPtr = &((*currentPtr)->next);
  }

  if (*currentPtr == nullptr)
    throw std::length_error("Node with requested value not found");

  if ((*currentPtr)->next == nullptr)
    throw std::length_error("The node has no successor to remove");

  Node* toDelete = (*currentPtr)->next;
  (*currentPtr)->next = toDelete->next;

  if (toDelete == this->tail)
    this->tail = *currentPtr;
    
  toDelete->next = nullptr;
  delete toDelete;
  --(this->size);
}

template <typename Data>
const Data &SetLst<Data>::Predecessor(const Data &value) const {
  if (this->Empty())
    throw std::length_error("No predecessor found");

  ulong position = 0;
  BinarySearch(value, position); 

  if (position == 0)
    throw std::length_error("No predecessor found");

  Node *current = this->head;
  for (ulong i = 0; i < position - 1; ++i)
    current = current->next;

  return current->element;
}

template <typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data& value) {
  if (this->Empty())
    throw std::length_error("No predecessor found");

  ulong position = 0;
  BinarySearch(value, position);
  if (position == 0)
    throw std::length_error("No predecessor found");

  Node** currentPtr = &(this->head);
  for (ulong i = 0; i < position - 1; ++i)
    currentPtr = &((*currentPtr)->next);

  Node* toDelete = *currentPtr;
  Data predValue = toDelete->element;
  *currentPtr = toDelete->next;
  toDelete->next = nullptr;
  delete toDelete;
  --(this->size);
  return predValue;
}

template <typename Data>
void SetLst<Data>::RemovePredecessor(const Data &value) {
  if (this->Empty())
    throw std::length_error("No predecessor found");

  ulong position = 0;
  BinarySearch(value, position);

  if (position == 0)
    throw std::length_error("No predecessor found");

  Node **current = &this->head;
  for (ulong i = 0; i < position - 1; ++i)
    current = &((*current)->next);

  Node *tmp = *current;
  *current = (*current)->next;
  tmp->next = nullptr;
  delete tmp;
  --(this->size);
}

/* ************************************************************************ */

}
