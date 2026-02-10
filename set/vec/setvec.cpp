
namespace lasd {

/* ************************************************************************** */

/* ************************** Constructors ******************************/

template <typename Data>
SetVec<Data>::SetVec() {
  capacity = 2;
  size = 0;
  head = 0;
  Elements = new Data[capacity];
}

template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& container) {
  size = 0;
  head = 0;
  capacity = 2;
  Elements = new Data[capacity];
  container.Traverse([this](const Data& elem){this->Insert(elem);});
}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& container) noexcept {
  size = 0;
  head = 0;
  capacity = 2;
  Elements = new Data[capacity];
  container.Map([this](Data& elem){this->Insert(std::move(elem));});
}

/* ************************************************************************** */

/* ********************* Copy/Move Constructors ******************************/

template <typename Data>
SetVec<Data>::SetVec(const SetVec& other) {
  capacity = other.capacity;
  size = other.size;
  head = 0;
  Elements = new Data[capacity];
  for (ulong i = 0; i < size; ++i)
    Elements[i] = other.Elements[(other.head + i) % other.capacity];
}

template <typename Data> 
  SetVec<Data>::SetVec(SetVec&& other) noexcept {
  capacity = other.capacity;
  size = other.size;
  head = other.head;
  Elements = other.Elements;
  other.capacity = 0;
  other.size = 0;
  other.head = 0;
  other.Elements = nullptr;
}

/* **************************************************************************** */

/* ************************** Copy/Move Assignment ***************************** */

template <typename Data>
SetVec<Data> &SetVec<Data>::operator = (const SetVec &other) {
  if (this != &other) {
    delete[] Elements;          
    capacity = other.capacity;
    size = other.size;
    head = 0;
    Elements = new Data[capacity];  
    for (ulong i = 0; i < size; ++i) {
      Elements[i] = other.Elements[(other.head + i) % other.capacity];
    }
  }
  return *this;
}

template <typename Data>
SetVec<Data> &SetVec<Data>::operator = (SetVec&& other) noexcept {
  if (this != &other){
  delete[] Elements;
  capacity = other.capacity;
  size = other.size;
  head = other.head;
  Elements = other.Elements;
  other.capacity = 0;
  other.size = 0;
  other.head = 0;
  other.Elements = nullptr;
  }
  return *this;
}

/* ************************************************************************** */

/* ********************** Comparison Operators ***************************** */

template <typename Data>
bool SetVec<Data>::operator == (const SetVec& other) const noexcept {
  if (size != other.size)
    return false;
  for (ulong i = 0; i < size; ++i)
    if (Elements[(head + i) % capacity] != other.Elements[(other.head + i) % other.capacity])
      return false;
  return true;
}

template <typename Data>
bool SetVec<Data>::operator != (const SetVec& other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

/* ***************** OrderedDictionaryContainer Methods ********************* */


template <typename Data>
const Data& SetVec<Data>::Min() const {
  if (size == 0) 
    throw std::length_error("Access to empty SetVec");
  return Elements[head];
}

template <typename Data>
Data SetVec<Data>::MinNRemove() {
  if (size == 0) 
    throw std::length_error("Access to empty SetVec");
  Data ret = Min();
  RemoveMin();
  return ret;
}

template <typename Data>
void SetVec<Data>::RemoveMin() {
  if (size == 0) 
    throw std::length_error("Access to empty SetVec");
  head = (head + 1) % capacity;
  --size;
}

template <typename Data>
const Data& SetVec<Data>::Max() const {
  if (size == 0) 
    throw std::length_error("Access to empty SetVec");
  return Elements[(head + size - 1) % capacity];
}

template <typename Data>
Data SetVec<Data>::MaxNRemove(){
  if (size == 0)
    throw std::length_error("Empty set");
  Data ret = Max();
  RemoveMax();
  return ret;
}

template <typename Data>
void SetVec<Data>::RemoveMax() {
  if (size == 0) 
    throw std::length_error("Access to empty SetVec");
  --size;
}

/* ************************************************************************** */

/* *********************** LinearContainer Methods ******************* */

//trovare la posizione di un elemento in O(log n) usando la ricerca binaria
//Ritorna l'indice logicodell'elemento se trovato, altrimenti ritorna - (inserimento_posizione + 1)
template <typename Data>
long SetVec<Data>::BinarySearch(const Data& elem) const {
  long low = 0;
  long high = size - 1;

  if (size == 0) return -1; 


  while (low <= high) {
    long mid = low + (high - low) / 2;

    //l'elemento logico a metà si trova in posizione (head + mid) % capacity
    const Data& midElem = Elements[((this->head) + mid) % (capacity)];


    if (elem == midElem)
      return mid;
    else if (elem < midElem)
      high = mid - 1;
    else
      low = mid + 1;
  }

  //se non trovato, ritorna la posizione di inserimento negativa
  return -(low + 1);
}

//trovare l'elemento immediatamente più piccolo (predecessore) di elem
template <typename Data>
const Data& SetVec<Data>::Predecessor(const Data& elem) const {
  if (this->Empty())
    throw std::length_error("Empty SetVec");

  //cerchiamo l'elemento
  long index = BinarySearch(elem);

  //se l'elemento è trovato, il predecessore è l'elemento prima di esso
  if (index > 0) {
    return Elements[(head + index - 1) % capacity];
  } 
  //se l'elemento non è trovato, il predecessore è l'elemento prima della posizione di inserimento
  
  else {
    ulong pos = static_cast<ulong>(-index - 1);
    if (pos > 0) {
      return Elements[(head + pos - 1) % capacity];
    }
  }
  //se pos è 0, non c'è predecessore (elem è il più piccolo)
  throw std::length_error("No predecessor found");
}

template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& val) {
  long index = BinarySearch(val);
  if (index > 0) {
    const Data& pred = Elements[(head + index - 1) % capacity];
    Data chiave = Elements[(head + index - 1) % capacity];
    Remove(pred); 
    return chiave;
  } else if (index < 0) {
    ulong pos = static_cast<ulong>(-index - 1);
    if (pos == 0) {
      throw std::length_error("No predecessor found");
    } else {
      const Data& pred = Elements[(head + pos - 1) % capacity];
      Remove(pred); 
      return pred;
    }
  } else {
    throw std::length_error("No predecessor found");
  }
}

template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& val) {
  long index = BinarySearch(val);

  if (index > 0) {
    const Data& pred = Elements[(head + index - 1) % capacity];
    Remove(pred);
  } else if (index < 0) {
    ulong pos = static_cast<ulong>(-index - 1);
    if (pos == 0) {
      throw std::length_error("No predecessor found");
    } else {
      const Data& pred = Elements[(head + pos - 1) % capacity];
      Remove(pred);
    }
  } else {
    throw std::length_error("No predecessor found");
  }
}

template <typename Data>
const Data& SetVec<Data>::Successor(const Data& elem) const {
  if (this->Empty()) 
    throw std::length_error("Empty SetVec");
  long index = BinarySearch(elem);
  if (index >= 0 && static_cast<ulong>(index) < size - 1)
    return Elements[(head + index + 1) % capacity];
  else if (index < 0) {
    ulong pos = -index - 1;
    if ((ulong)pos < size)
      return Elements[(head + pos) % capacity];
  }
  throw std::length_error("No successor found");
}

template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& value) {
  long pos = BinarySearch(value);
  if (pos >= 0 && static_cast<ulong>(pos) < size - 1) {
    ulong succPos = (head + static_cast<ulong>(pos) + 1) % capacity;
    Data ret = std::move(Elements[succPos]);
    for (ulong i = static_cast<ulong>(pos) + 1; i + 1 < size; ++i) {
      Elements[(head + i) % capacity] = std::move(Elements[(head + i + 1) % capacity]);
    }
    --size;
    return ret;
  }
  else if (pos < 0) {
    ulong insertPos = static_cast<ulong>(-pos - 1);
    if (insertPos < size) {
      ulong succPos = (head + insertPos) % capacity;
      Data ret = std::move(Elements[succPos]);
      for (ulong i = insertPos; i + 1 < size; ++i) {
        Elements[(head + i) % capacity] = std::move(Elements[(head + i + 1) % capacity]);
      }
      --size;
      return ret;
    }
  }
  throw std::length_error("No successor found");
}

template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& value) {
  long pos = BinarySearch(value);
  if (pos >= 0 && static_cast<ulong>(pos) < size - 1) {
    for (ulong i = static_cast<ulong>(pos) + 1; i + 1 < size; ++i) {
      Elements[(head + i) % capacity] = std::move(Elements[(head + i + 1) % capacity]);
    }
    --size;
  }
  else if (pos < 0) {
    ulong insertPos = static_cast<ulong>(-pos - 1);
    if (insertPos < size) {
      for (ulong i = insertPos; i + 1 < size; ++i) {
        Elements[(head + i) % capacity] = std::move(Elements[(head + i + 1) % capacity]);
      }
      --size;
    }
  }
  throw std::length_error("No successor found");
}

/* ************************************************************************** */

/* *********************** DictionaryContainer Methods ******************* */

template <typename Data>
bool SetVec<Data>::Insert(const Data& elem) {
  //cerchiamo dove inserire l'elemento
    long index = BinarySearch(elem);

    //se index >= 0, l'elemento è già presente ed i set non permettono duplicati
    if (index >= 0)
        return false;

    //decodifichiamo la posizione di inserimento 
    ulong pos = static_cast<ulong>(-index - 1);

    //resize se necessario
    if (size == capacity)
        Resize(capacity * 2);

    // calcoliamo l'indice fisico di inserimento
    ulong insertIndex = (head + pos) % capacity;

    //shift degli elementi (O(n) nel caso peggiore)
    //bisogna fare spazio, spostiamo tutti gli elementi in avanti che stanno dopo la posizione di inserimento
    //stiamo copiando da i-1 a i 
    for (ulong i = size; i > pos; --i)
        Elements[(head + i) % capacity] = std::move(Elements[(head + i - 1) % capacity]);

    //inseriamo l'elemento e incrementiamo la size
    Elements[insertIndex] = elem; 
    ++size;
    return true;
}

template <typename Data>
bool SetVec<Data>::Insert(Data&& elem) noexcept {
    long index = BinarySearch(elem);
    if (index >= 0)
        return false;
    ulong pos = static_cast<ulong>(-index - 1);
    if (size == capacity)
        Resize(capacity * 2);
    ulong insertIndex = (head + pos) % capacity;
    for (ulong i = size; i > pos; --i)
        Elements[(head + i) % capacity] = std::move(Elements[(head + i - 1) % capacity]);
    Elements[insertIndex] = std::move(elem);
    ++size;
    return true;
}

template <typename Data>
bool SetVec<Data>::Remove(const Data& elem) {
  long index = BinarySearch(elem);
  if (index < 0) 
    return false;
  if (index == 0) {
    head = (head + 1) % capacity;
  } else {
    for (ulong i = index; i < size - 1; ++i)
      Elements[(head + i) % capacity] = std::move(Elements[(head + i + 1) % capacity]);
  }
  --size;
  return true;
}

template <typename Data>
bool SetVec<Data>::Exists(const Data& elem) const noexcept {
  return BinarySearch(elem) >= 0;
}

/* ************************************************************************** */

/* *********************** LinearContainer Methods ******************* */

template <typename Data>
const Data& SetVec<Data>::operator[](const ulong i) const {
  if (i >= size) 
    throw std::out_of_range("Index out of range");
  return Elements[(head + i) % capacity];
}

template <typename Data>
  void SetVec<Data>::Clear(){
  delete[] Elements;
  capacity = 2; 
  size = 0;
  head = 0;
  Elements = new Data[capacity];
}

//espande o riduce la capacità dell'array circolare
template <typename Data>
void SetVec<Data>::Resize(ulong newcapacity) {
  if (newcapacity == 0) 
    newcapacity = 2;
  if (newcapacity < size) 
    newcapacity = size; //non possiamo perdere dati
  Data* newElements = new Data[newcapacity];

  //copiamo i dati dal vecchio array circolare al nuovo buffer lineare
  for (ulong i = 0; i < size; ++i)
    newElements[i] = std::move(Elements[(head + i) % capacity]);

  delete[] Elements;
  Elements = newElements;
  head = 0; //reset della testa, l'indice fisico ora coincide con quello logico
  capacity = newcapacity;
}

template <typename Data>
inline bool SetVec<Data>::Empty() const noexcept {
  return size == 0;
}

 template <typename Data>
 ulong SetVec<Data>::Size() const noexcept {
    return size;
}

/* ************************************************************************** */

} 