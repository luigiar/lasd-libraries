namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data>& container) : Vector<Data>(container), HeapVec<Data>(container) {
}

template <typename Data>
PQHeap<Data>::PQHeap(const MappableContainer<Data>& container) : Vector<Data>(container), HeapVec<Data>(container) {
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data>& other) : Vector<Data>(other), HeapVec<Data>(other) {
}

// Move constructor
template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data>&& other) noexcept : Vector<Data>(std::move(other)), HeapVec<Data>(std::move(other)) {
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap<Data>& other) {
    HeapVec<Data>::operator=(other);
    return *this;
}

// Move assignment
template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(PQHeap<Data>&& other) noexcept {
    HeapVec<Data>::operator=(std::move(other));
    return *this;
}

/* ************************************************************************** */

// Auxiliary functions

//quando si inserisce un nuovo elemento in fondo all'heap, questa funzione lo porta nella posizione corretta
//(l'elemento potrebbe essere troppo grande rispetto al genitore)
template <typename Data>
void PQHeap<Data>::FloatUp(ulong index) noexcept {
    //finché non arrivo alla radice
    while (index != 0) {
        ulong parent = (index - 1) / 2;
        //se padre è più piccolo del figlio, scambio
        if (elements[parent] < elements[index]) {
            std::swap(elements[index], elements[parent]);
            index = parent; //l'elemento ora è nella posizione del padre, continuo a salire
        } else {
            //se il padre è più grande, l'heap property è rispettata
            break;
        }
    }
}

/* ************************************************************************** */

// Specific member functions

template <typename Data>
const Data& PQHeap<Data>::Tip() const {
    if (size == 0) {
        throw std::length_error("Access to empty priority queue.");
    }
    return elements[0];
}

//rimuove il massimo (radice) dall'heap
template <typename Data>
void PQHeap<Data>::RemoveTip() {
    if (size == 0) {
        throw std::length_error("Removal from empty priority queue.");
    }
    
    //non posso cancellare direttamente dalla testa, costerebbe O(n) scalare tutto il vettore
    //scambio la testa con l'ultimo elemento
    std::swap(elements[0], elements[size - 1]);

    // ora il vecchio massimo è in fondo, riduco la dimensione del vettore
    Vector<Data>::Resize(size - 1);

    // ora in testa c'è un elemento che potrebbe non rispettare l'heap property
    // lo sistemo con heapify
    Heapify(0);
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {
    if (size == 0) {
        throw std::length_error("Removal from empty priority queue.");
    }
    Data ret = std::move(elements[0]); // Ottimizzazione con move
    RemoveTip();
    return ret;
}

template <typename Data>
void PQHeap<Data>::Insert(const Data& data) {
    // Aumento la dimensione del vettore
    Vector<Data>::Resize(size + 1);

    //metto l'elemento in fondo
    elements[size - 1] = data;

    // va verso l'alto se è più grande del genitore
    FloatUp(size - 1);
}

template <typename Data>
void PQHeap<Data>::Insert(Data&& data) {
    Vector<Data>::Resize(size + 1);
    elements[size - 1] = std::move(data);
    FloatUp(size - 1);
}

template <typename Data>
void PQHeap<Data>::Change(const ulong index, const Data& newval) {
    Change(index, std::move(Data(newval)));
}

//cambio di priorità di un elemento nell'heap
template <typename Data>
void PQHeap<Data>::Change(const ulong index, Data&& newval) {
    if (index >= size) {
        throw std::out_of_range("Index out of range in Change.");
    }

    Data oldval = elements[index]; //salvo il vecchio valore per confrontare
    elements[index] = std::move(newval); //scrivo il nuovo valore

    // se il nuovo valore è più grande del vecchio, potrebbe dover salire
    if (elements[index] > oldval) {
        FloatUp(index);

    //se il nuovo valore è più piccolo del vecchio, potrebbe dover scendere
    } else if (elements[index] < oldval) {
        Heapify(index);
    }
}

/* ************************************************************************** */

}
