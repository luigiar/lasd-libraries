
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& con) : Vector<Data>(con) {
    Heapify();
}

template <typename Data>
HeapVec<Data>::HeapVec(const MappableContainer<Data>& con) : Vector<Data>(con) {
    Heapify();
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data>& other) : Vector<Data>(other) {
}

// Move constructor
template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data>&& other) noexcept : Vector<Data>(std::move(other)) {
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& other) {
    Vector<Data>::operator=(other);
    return *this;
}

// Move assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& other) noexcept {
    Vector<Data>::operator=(std::move(other));
    return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data>& other) const noexcept {
    return Vector<Data>::operator==(other);
}

template <typename Data>
bool HeapVec<Data>::operator!=(const HeapVec<Data>& other) const noexcept {
    return !(*this == other);
}

/* ************************************************************************** */

// Auxiliary functions

template <typename Data>
void HeapVec<Data>::Heapify(ulong index) noexcept {
    Heapify(index, size);
}

template <typename Data>
// si prende un nodo che potrebbe violare la proprieta' di heap e lo si fa scendere fino a ristabilire la proprieta'
void HeapVec<Data>::Heapify(ulong index, ulong limit) noexcept {
    ulong left = 2 * index + 1; //calcolo indice figlio sinistro
    ulong right = 2 * index + 2; // calcolo indice figlio destro
    ulong max = index; //assumo che il massimo sia il nodo corrente

    // confronto con il figlio sinistro
    // se esiste ed e' maggiore del nodo corrente, aggiorno il massimo
    if (left < limit && elements[left] > elements[max]) {
        max = left;
    }
    
    // confronto con il figlio destro
    // se esiste ed e' maggiore del massimo attuale, aggiorno il massimo
    if (right < limit && elements[right] > elements[max]) {
        max = right;
    }

    // se il massimo non e' il nodo corrente, scambio e continuo a fare heapify
    if (max != index) {
        std::swap(elements[index], elements[max]);

        //chiamata ricorsiva per continuare a fare heapify
        Heapify(max, limit);
    }
}

/* ************************************************************************** */

// Specific member functions

//trasformo l'intero vettore disordinato in un heap
template <typename Data>
void HeapVec<Data>::Heapify() noexcept {
    if (size > 0) {
    // partiamo da size/2 - 1 perche' le foglie sono già heap validi
    //l'ultimo nodo che ha figli si trova a meta' dell'array
    // scendiamo verso la radice (indice 0)
        for (long i = (size / 2) - 1; i >= 0; --i) {
            Heapify(i); //ripara ogni sottoalbero
        }
    }
}

template <typename Data>
bool HeapVec<Data>::IsHeap() const noexcept {
    if (size <= 1) return true;
    for (ulong i = 0; i < size / 2; ++i) {
        ulong left = 2 * i + 1;
        ulong right = 2 * i + 2;
        if (left < size && elements[left] > elements[i]) return false;
        if (right < size && elements[right] > elements[i]) return false;
    }
    return true;
}

/* ************************************************************************** */

// SortableLinearContainer
//ordina gli elementi del vettore usando l'algoritmo heapsort
template <typename Data>
void HeapVec<Data>::Sort() {
    //ci assicuriamo che sia un max-heap valido
    Heapify();

    //ciclo dall'ultimo elemento al secondo
    for (ulong i = size - 1; i > 0; --i) {
        //il massimo e' sempre alla radice (indice 0)
        //lo scambiamo con l'elemento in fondo elements[i] che è la sua posizione ordinata
        std::swap(elements[0], elements[i]);

        //ora in elements[0] c'è un elemento che potrebbe violare la proprieta' di heap
        //facciamo heapify solo fino a i (escludendo la parte gia ordinata)
        Heapify(0, i);
    }
}

/* ************************************************************************** */

}