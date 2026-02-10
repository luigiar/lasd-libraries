namespace lasd {

/* ************************************************************************** */

template <typename Data>
void PreOrderMappableContainer<Data>::Map(MapFun MapFunction) {

    PreOrderMap(MapFunction);
}

// ...

template <typename Data>
void PostOrderMappableContainer<Data>::Map(MapFun MapFunction) {

    PostOrderMap(MapFunction);
}

/* ************************************************************************** */

}

