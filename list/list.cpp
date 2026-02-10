
  namespace lasd {

//Distruttore del nodo è ricorsiva, quindi elimina tutta la lista a partire dal nodo chiamante 


  /* ************************************************************************** */

  // ********* Node Constructors *********

  template <typename Data>
  List<Data>::Node::Node(Data&& elem) noexcept {
      std::swap(element, elem);
  }

  template <typename Data>
  List<Data>::Node::Node(const Data& elem) {
    element = elem;
  }

  // ********* Node Copy/Move *********

  template <typename Data>
  List<Data>::Node::Node(const List<Data>::Node& other) {
    element = other.element;
  }

  template <typename Data>
  List<Data>::Node::Node(List<Data>::Node&& other) noexcept {
    std::swap(element, other.element);
    std::swap(next, other.next);
  }

  // ********* Node Comparison Operators *********

  template <typename Data>
  bool List<Data>::Node::operator == (const Node& other) const noexcept {
  const Node* a = this;
  const Node* b = &other;
    while (a != nullptr && b != nullptr) {
      if (a->element != b->element)
        return false;
      a = a->next;
      b = b->next;
    }
    return (a == nullptr && b == nullptr);
}


  template <typename Data>
  bool List<Data>::Node::operator != (const Node& other) const noexcept {
    return !(*this == other);
  }

  /* ************************************************************************** */

  // ********* List Constructors *********

  template <typename Data>
  List<Data>::List(const TraversableContainer<Data>& container) {
    container.Traverse([this](const Data& data) { InsertAtBack(data); });
  }

  template <typename Data>
  List<Data>::List(MappableContainer<Data>&& container) {
    container.Map([this](Data& data) { InsertAtBack(std::move(data)); });
  }

  // ********* List Copy/Move Constructors ********* 

// Copy constructor (deep copy)
  template <typename Data>
  List<Data>::List(const List<Data>& other) {
    //scorriamo la lista other e inseriamo in coda ogni elemento nella nuova lista
    //si usa una lambda function per comodità
    other.PreOrderTraverse([this](const Data& data){ InsertAtBack(data); });
  }

//move constructor
//scambiamo i puntatori e la size
  template <typename Data>
  List<Data>::List(List<Data>&& other) noexcept {
    //prendiamo la testa, la coda e la size della lista other
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
    //l'altra lista ora rimane vuota, il suo distruttore non farà nulla
  }

  /* ************************************************************************** */

  // ********* Assignment Operators ********* 

//copy assignment (operator=)
//assegnamento sicuro
  template <typename Data>
  List<Data> & List<Data>::operator = (const List<Data> & other) {
    //creiamo una lista temporanea che è la copia di other(usando il copy constructor)
      List<Data> temp(other);

      //scambiamo i dati di this con quelli di temp (della copia temporanea)
      std::swap(*this, temp);

      //quando la funzione finisce, tempo viene distrutta e libera la memoria precedentemente occupata da this
    return *this;
  }

  template <typename Data>
  List<Data>& List<Data>::operator = (List<Data>&& other) noexcept {
      std::swap(head, other.head);
      std::swap(tail, other.tail);
      std::swap(size, other.size);

    return *this;
  }

  /* ************************************************************************** */

  // ********* List Comparison Operators *********

  template <typename Data>
  bool List<Data>::operator == (const List& other) const noexcept {
    if (size != other.size)
      return false;
    Node* a = head;
    Node* b = other.head;
    while (a != nullptr) {
      if (a->element != b->element)
        return false;
      a = a->next;
      b = b->next;
    }
    return true;
  }

  template <typename Data>
  bool List<Data>::operator != (const List& other) const noexcept {
    return !(*this == other);
  }

  /* ************************************************************************** */

  // ********* Insert/Remove *********

  // InsertAtFront inserimento in testa (O(1))
  template <typename Data>
  void List<Data>::InsertAtFront(const Data& data) {
    Node* newNode = new Node(data); //creazione del nuovo nodo
    newNode->next = head; //nuovo nodo punta alla vecchia testa
    head = newNode; //aggiorniamo la testa alla nuova

    //se la lista era vuota, aggiorniamo anche la coda
    if (tail == nullptr)
      tail = head;
    ++size;
  }

  template <typename Data>
  void List<Data>::InsertAtFront(Data&& data) {
    Node* newNode = new Node(std::move(data));
    newNode->next = head;
    head = newNode;
    if (tail == nullptr)
      tail = head;
    ++size;
  }

  //rimozione in testa (O(1))
  template <typename Data>
  void List<Data>::RemoveFromFront() {
    if (head == nullptr)
      throw std::length_error("Empty structure");
    Node* tmp = head; //salviamo il puntatore per cancellarlo dopo
    head = head->next; //avanziamo la testa al prossimo nodo

    tmp->next = nullptr; //scolleghiamo il nodo da eliminare dalla lista
    delete tmp; //eliminiamo il nodo vecchio

    size--;

    //se la lista è diventata vuota, aggiorniamo anche la coda
    if (head == nullptr)
      tail = nullptr;
  }

  template <typename Data>
  Data List<Data>::FrontNRemove() {
    if (head == nullptr)
      throw std::length_error("Empty structure");
    Data data = std::move(head->element);
    RemoveFromFront();
    return data;
  }

  // InsertAtBack inserimento in coda (O(1)) grazie al puntatore tail
  template <typename Data>
  void List<Data>::InsertAtBack(const Data& data) {
    Node* newNode = new Node(data);
    if (tail != nullptr)
      tail->next = newNode; //la vecchia coda punta al nuovo nodo
    else
      head = newNode; //se la lista era vuota, aggiorniamo anche la testa
    tail = newNode; //aggiorniamo la coda al nuovo nodo
    ++size;
  }

  template <typename Data>
  void List<Data>::InsertAtBack(Data&& data) {
    Node* newNode = new Node(std::move(data));
    if (tail != nullptr)
      tail->next = newNode;
    else
      head = newNode;
    tail = newNode;
    ++size;
  }

//remove from back (O(n)) perchè dobbiamo aggiornare tail facendolo pntare al penultimo nodo
//visto che la lista è singolarmente collegata, dobbiamo scorrere tutta la lista per trovarlo
  template <typename Data>
  void List<Data>::RemoveFromBack() {
    if (head == nullptr)
        throw std::length_error("Empty structure");

    Node* tmp = tail; //nodo da eliminare

    if (head == tail) { 
      //se c'è un solo elemento
        head = tail = nullptr;
    } else {
      //più elementi, scorriamo la lista per trovare il penultimo (O(n))
        Node* prev = head;
        while (prev->next != tail) //cerchiamo chi punta a tail
            prev = prev->next;


        tail = prev; //il penultimo diventa la nuova coda
        tail->next = nullptr;
    }


    delete tmp;
    size--;
  }

  template <typename Data>
  Data List<Data>::BackNRemove() {
    if (head == nullptr)
        throw std::length_error("Empty structure");
    Data data = std::move(tail -> element);
    RemoveFromBack();
    return data;
  }

  /* ************************************************************************** */

  // ********* Accessors *********

//le liste non hanno accesso casuale, bisogna scorrere i nodi 
  template <typename Data>
  const Data& List<Data>::operator[](const ulong index) const {
    if (index >= size)
      throw std::out_of_range("Index out of range");
    Node* current = head;
    for (ulong i = 0; i < index; ++i) //saltiamo di nodo in nodo 
      current = current->next;
    return current->element;
  }

  template <typename Data>
  Data& List<Data>::operator[](const ulong index) {
    if (index >= size)
      throw std::out_of_range("Index out of range");
    Node* current = head;
    for (ulong i = 0; i < index; ++i)
      current = current->next;
    return current->element;
  }

  /* ************************************************************************** */
  
  /* ************** Front/Back ******************* */

  template <typename Data>
  const Data& List<Data>::Front() const {
    if (head == nullptr)
      throw std::length_error("Front: La Lista è vuota");
    return head->element;
  }

  template <typename Data>
  Data& List<Data>::Front() {
    if (head == nullptr)
      throw std::length_error("Front: La Lista è vuota");
    return head->element;
  }

  template <typename Data>
  const Data& List<Data>::Back() const {
    if (tail == nullptr)
      throw std::length_error("Back: La Lista è vuota");
    return tail->element;
  }

  template <typename Data>
  Data& List<Data>::Back() {
    if (tail == nullptr)
      throw std::length_error("Back: La Lista è vuota");
    return tail->element;
  }

  /* ************************************************************************** */

  // ********* Clear *********

  template <typename Data>
  void List<Data>::Clear() {
    delete head; //scatena la distruzione ricorsiva dei nodi
    head = tail = nullptr;
    size = 0;
  }

  /* ************************************************************************** */

  // ********* Map and Traverse *********

//PreOrderMap è iterativa O(n)
// Visita il nodo, poi passa al successivo
  template<typename Data>
  void List<Data>::PreOrderMap(MapFun fun) {
  Node * curr = head;
    while (curr != nullptr) {
    fun(curr->element);
    curr = curr->next;
  }
} 

//postOrderMap è ricorsiva O(n)
//vai fino in fondo alla lista, poi visita i nodi al ritorno dalla ricorsione
//utile per operazioni che richiedono di visitare prima i figli (in questo caso i nodi successivi)
  template <typename Data>
  void List<Data>::PostOrderMap(MapFun fun, List<Data>::Node* node)  {
    if (node != nullptr) {
      PostOrderMap(fun, node->next);
      fun(node->element);
    }
  }

  template<typename Data>
  void List<Data>::PreOrderTraverse(TraverseFun fun) const {
  Node* curr = head;
  while (curr != nullptr) {
    fun(curr->element);
    curr = curr->next;
  }
}

  template <typename Data>
  void List<Data>::PostOrderTraverse(TraverseFun fun, const List<Data>::Node* node) const {
    if (node != nullptr) {
      PostOrderTraverse(fun, node->next);
      fun(node->element);
    }
  }

  /* ************************************************************************** */

}
