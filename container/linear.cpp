namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool lasd::LinearContainer<Data>::operator == (const LinearContainer<Data>& other) const noexcept {
    if (size != other.Size()) { 
        return false;
    }
    for (ulong i = 0; i < size; i++) {
        if (operator[](i) != other.operator[](i)) 
            return false;
    }
    return true;
}

template <typename Data>
bool lasd::LinearContainer<Data>::operator != (const LinearContainer<Data>& other) const noexcept {
    return !(*this == other);
}

template <typename Data>
const Data& LinearContainer<Data>::Front() const {
    if (this->Empty()) {
        throw std::length_error("La Struttura è vuota");
    }
    return operator[](0);
}

template <typename Data>
const Data& LinearContainer<Data>::Back() const {
    if (this->Empty()) {
        throw std::length_error("La Struttura è vuota");
    }
    return operator[](size - 1);
}

template <typename Data>
void LinearContainer<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
}

template <typename Data>
void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
    if(!(this->Empty())) {
        for (ulong i = 0; i < this->Size(); i++) {
            fun(operator[](i));
        }
    }    
}

template <typename Data>
void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
    if(!(this->Empty())) {
        for (ulong i = this->Size(); i > 0; i--) {
            fun(operator[](i - 1));
        }
    }
}

// ...

template <typename Data>
Data& MutableLinearContainer<Data>::Front() {
    if (this->Empty()) {
        throw std::length_error("La Struttura è vuota");
    }
    return operator[](0);
}

template <typename Data>
Data& MutableLinearContainer<Data>::Back() {
    if (this->Empty()) {
        throw std::length_error("La Struttura è vuota");
    }
    return operator[](size - 1);
}

template <typename Data>
void MutableLinearContainer<Data>::Map(MapFun fun) {
    for (ulong i = 0; i < size; i++) {
        fun(operator[](i));
    }
}

template <typename Data>
void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
    for (ulong i = 0; i < size; i++) {
        fun(operator[](i));
    }
}

template <typename Data>
void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
    for (ulong i = size; i > 0; i--) {
        fun(operator[](i - 1));
    }
}

// ...

template <typename Data>
void SortableLinearContainer<Data>::Sort() {
    if(this->Empty()) {
        throw std::length_error("La Struttura è vuota");
    }
    InsertionSort();
}

template <typename Data>
void SortableLinearContainer<Data>::InsertionSort() noexcept {
    for (ulong i = 1; i < size; i++) {
        ulong j = i;
        while (j > 0 && this->operator[](j) < this->operator[](j - 1)) {
            std::swap(this->operator[](j), this->operator[](j - 1));
            j--;
        }
    }
}

/* ************************************************************************** */

}

