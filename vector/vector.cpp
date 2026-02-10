
namespace lasd {

/* ************************************************************************** */

/* ********************** Vector ****************************** */

//costruttore per dimensione
//creo un vettore di N elementi vuoti 
template <typename Data>
Vector<Data>::Vector(ulong dimension) {
    size = dimension;
    elements = new Data[size]; //allocazione dinamica. Se Data è int, i valori sono random, se string sono vuoti
}

//costruttore da TraversableContainer
//crea un vettore che contenga gli stessi dati del container
template <typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& container) {
    size = container.Size();
    elements = new Data[size];
    ulong i = 0;

    //usiamo la funzione lambda che cattura this e l'indice i per riferimento.
    //per ogni elemento elem trovato nel container, lo copiamo nel vettore e lo incrementiamo
    container.Traverse([this, &i](const Data& elem) { elements[i++] = elem; });
}

//costruttore da MappableContainer
//fa la std::move degli elementi invece di copiarli, piu efficiente per oggetti grandi
template <typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& container) {
    size = container.Size();
    elements = new Data[size];
    ulong i = 0;
    container.Map([this, &i](Data& elem) {this->elements[i++] = std::move(elem);}); // std::move svuota l'originale dentro il container
}

//Copy Constructor
//crea un clone perfetto (deep copy) del vettore passato come argomento
template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vec) {
    size = vec.size;
    elements = new Data[size]; //nuova allocazione separata
    //copia manuale per elemento
    for (ulong i = 0; i < size; ++i)
        elements[i] = vec.elements[i];
}

//Move Constructor
//"sposta" le risorse dal vettore passato come argomento a this. Costo O(1)
template <typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept {
    //scambio i puntatori
    std::swap(size, vec.size);
    std::swap(elements, vec.elements);
}

//Destructor
template <typename Data>
Vector<Data>::~Vector() {
    delete[] elements;
}

/* ************************************************************************** */

/* ********************** Copy/Move Assignment **************** */

//Copy Assignment
// a = b copia gli elementi di b in a
template <typename Data>
Vector<Data>& Vector<Data>::operator = (const Vector<Data>& vec) {
    //evitare self-assignment v = v
    if (this != &vec) {
        // distruggo la vecchia copia
        delete[] elements;

        //alloco nuova dimensione
        size = vec.size;
        elements = new Data[size];

        //copio elemento per elemento
        for (ulong i = 0; i < size; ++i)
            elements[i] = vec.elements[i];
    }
    return *this;
}

//Move Assignment
// a = std::move(b) sposta le risorse di b in a
template <typename Data>
Vector<Data>& Vector<Data>::operator = (Vector<Data>&& vec) noexcept {
    //basta fare lo scambio, il distruttore di vec si occuperà di liberare le risorse precedenti
    std::swap(size, vec.size);
    std::swap(elements, vec.elements);
    return *this;
}

/* ************************************************************************** */

/* ********************** Comparison Operators *********************** */

template <typename Data>
bool lasd::Vector<Data>::operator == (const Vector<Data>& other) const noexcept {
    if (size != other.size) return false;
    for (ulong i = 0; i < size; ++i) {
        if (elements[i] != other.elements[i]) return false;
    }
    return true;
}

template <typename Data>
bool lasd::Vector<Data>::operator!=(const Vector<Data>& other) const noexcept {
    return !(*this == other);
}

/* ************************************************************************** */

/* ********************** Access to elements *********************** */

//Accesso con [] (Bounds checking)
//Accesso rapido O(1) ma sicuro
template <typename Data>
Data& Vector<Data>::operator[](const ulong index) {
    if (index >= size) //controllo se l'indice è valido
        throw std::out_of_range("Invalid Index");
    return elements[index];
}


template <typename Data>
const Data& Vector<Data>::operator[](const ulong index) const {
    if (index >= size)
        throw std::out_of_range("Invalid Index");
    return elements[index];
}

template <typename Data>
inline Data& Vector<Data>::Front() {
    if (this->Empty())
        throw std::length_error("Empty Structure");
    return elements[0];
}

template <typename Data>
inline Data& Vector<Data>::Back() {
    if (this->Empty())
        throw std::length_error("Empty Structure");
    return elements[size - 1];
}

template <typename Data>
const Data& Vector<Data>::Front() const {
    if (this->Empty())
        throw std::length_error("Empty Structure");
    return elements[0];
}

template <typename Data>
const Data& Vector<Data>::Back() const {
    if (this->Empty())
        throw std::length_error("Empty Structure");
    return elements[size - 1];
}

//Ridimensionamento, cambiare dimensione dell'array mantenendo i dati esistenti
template <typename Data>
void Vector<Data>::Resize(ulong newSize) {
    if (newSize == 0 ) {
        Clear(); //se la nuova dimensione è 0, svuoto il vettore
        return;
    }
    if (size == newSize) return; //se la dimensione è uguale, non faccio nulla

    //alloco un nuovo array della nuova dimensione
    Data* newVec = new Data[newSize];

    // calcolo quanti elementi da copiare (il minimo tra size e newSize)
    //se riduco, taglio gli elementi in eccesso
    //se allargo (newSize > size), i nuovi elementi rimangono con il valore di default
    ulong limit = (size < newSize) ? size : newSize;

    // sposto i dati
    for (ulong i = 0; i < size && i < limit; ++i)
        newVec[i] = std::move(elements[i]); //move per efficienza 

    // dealloco il vecchio array e aggiorno i puntatori
    delete[] elements;
    elements = newVec;
    size = newSize;
}

//clear, porta il vettore a dimensione 0
template <typename Data>
void Vector<Data>::Clear() noexcept {
    delete[] elements;
    elements = nullptr;
    size = 0;
}

/* ************************************************************************** */

/* ********************** SortableVector *************** */

template <typename Data>
SortableVector<Data>::SortableVector(const ulong dimension) : Vector<Data>(dimension) {}

template <typename Data>
SortableVector<Data>::SortableVector(const TraversableContainer<Data>& container) : Vector<Data>(container) {}

template <typename Data>
SortableVector<Data>::SortableVector(MappableContainer<Data>&& container) : Vector<Data>(std::move(container)) { this->Sort(); }

template <typename Data>
SortableVector<Data>::SortableVector(const SortableVector<Data>& other) : Vector<Data>(other) {}

template <typename Data>
SortableVector<Data>::SortableVector(SortableVector<Data>&& other) noexcept : Vector<Data>(std::move(other)) {}

/* ************************************************************************** */

/* ********************** Copy/Move *************** */

template <typename Data>
SortableVector<Data>& SortableVector<Data>::operator = (const SortableVector<Data>& other) {
    Vector<Data>::operator=(other);
    return *this;
}

template <typename Data>
SortableVector<Data>& SortableVector<Data>::operator = (SortableVector<Data>&& other) noexcept {
    Vector<Data>::operator=(std::move(other));
    return *this;
}

}