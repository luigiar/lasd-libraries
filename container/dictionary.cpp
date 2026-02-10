namespace lasd {

/* ************************************************************************** */

template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& container) {
    bool AllInserted = true;
    container.Traverse([this, &AllInserted](const Data& element) { AllInserted &= Insert(element); });
    return AllInserted;
} 

template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& container) {
    bool AllInserted = true; 
    container.Map([this, &AllInserted](Data& element) { AllInserted &= Insert(std::move(element)); });
    return AllInserted;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& container) {
    bool SomeInserted = false;
    container.Traverse([this, &SomeInserted](const Data& element) { SomeInserted |= Insert(element); });
    return SomeInserted;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& container) {
    bool SomeInserted = false;
    container.Map([this, &SomeInserted](Data& element) { SomeInserted |= Insert(std::move(element)); });
    return SomeInserted;
}

template <typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& container) {
    bool AllRemoved = true; 
    container.Traverse([this, &AllRemoved](const Data& element) { AllRemoved &= Remove(element); });
    return AllRemoved;
}

template <typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& container) {
    bool SomeRemoved = false; 
    container.Traverse([this, &SomeRemoved](const Data& element) { SomeRemoved |= Remove(element); });
    return SomeRemoved;
}

// ...

template <typename Data>
inline Data OrderedDictionaryContainer<Data>::MinNRemove() {
    if(this->Empty()) {
        throw std::length_error("La Struttura risulta vuota");
    }
    Data min = Min();
    this->Remove(min);
    return min;
}

template <typename Data>
inline void OrderedDictionaryContainer<Data>::RemoveMin() {
    if(this->Empty()) {
        throw std::length_error("La Struttura risulta vuota");
    }
    this->Remove(Min());
}

template <typename Data>
inline Data OrderedDictionaryContainer<Data>::MaxNRemove() {
    if(this->Empty()) {
        throw std::length_error("La Struttura risulta vuota");
    }
    Data max = Max();
    this->Remove(max);
    return max;
}

template <typename Data>
inline void OrderedDictionaryContainer<Data>::RemoveMax() {
    if(this->Empty()) {
        throw std::length_error("La Struttura risulta vuota");
    }
    this->Remove(Max());
}

template <typename Data>
inline Data OrderedDictionaryContainer<Data>::PredecessorNRemove(const Data& element) {
    if(this->Empty()) {
        throw std::length_error("La Struttura risulta vuota");
    }
    Data predecessor = Predecessor(element);
    this->Remove(predecessor);
    return predecessor;
}

template <typename Data>
inline void OrderedDictionaryContainer<Data>::RemovePredecessor(const Data& element) {
    if(this->Empty()) {
        throw std::length_error("La Struttura risulta vuota");
    }
    this->Remove(Predecessor(element));
}

template <typename Data>
inline Data OrderedDictionaryContainer<Data>::SuccessorNRemove(const Data& element) {
    if(this->Empty()) {
        throw std::length_error("La Struttura risulta vuota");
    }
    Data successor = Successor(element);
    this->Remove(successor);
    return successor;
}

template <typename Data>
inline void OrderedDictionaryContainer<Data>::RemoveSuccessor(const Data& element) {
    if(this->Empty()) {
        throw std::length_error("La Struttura risulta vuota");
    }
    this->Remove(Successor(element));
}

/* ************************************************************************** */

}
