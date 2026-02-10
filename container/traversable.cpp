namespace lasd {

    /* ************************************************************************** */
    
    template <typename Data>
    template <typename Accumulator>
    inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const {
        Traverse([foldFunction, &accumulator](const Data& elem) { accumulator = foldFunction(elem, accumulator); });
        return accumulator;
    }
    
    template <typename Data>
    inline bool TraversableContainer<Data>::Exists(const Data& elem) const noexcept {
        bool ExistsData = false;
        Traverse([&ExistsData, elem](const Data& value) {
            if (value == elem) {
                ExistsData |= (elem == value);
            } });

        return ExistsData;
    }
    
    /* ************************************************************************** */
    
    template <typename Data>
    template <typename Accumulator>
    inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const {
        PreOrderTraverse([foldFunction, &accumulator](const Data& elem) {
            accumulator = foldFunction(elem, accumulator); });
        
        return accumulator;
    }
    
    template <typename Data>
    inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFunction) const {
        PreOrderTraverse(traverseFunction);
    }
    
    /* ************************************************************************** */
    
    template <typename Data>
    template <typename Accumulator>
    inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const {
        PostOrderTraverse([foldFunction, &accumulator](const Data& elem) {
            accumulator = foldFunction(elem, accumulator); });
        
        return accumulator;
    }
    
    template <typename Data>
    inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFunction) const {
        PostOrderTraverse(traverseFunction);
    }
    
    }

/* ************************************************************************** */