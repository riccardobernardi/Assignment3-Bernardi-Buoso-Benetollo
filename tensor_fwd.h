#ifndef TENSOR_FWD_H
#define TENSOR_FWD_H


namespace Tensor {


// policy for dynamically ranked tensors
struct dynamic {
    typedef std::vector<size_t> index_type;
    typedef std::vector<size_t> width_type;
};

// policy for fixed-rank tensors
template<size_t R> struct rank {
    //typedef std::array<size_t,R> index_type;
    //typedef std::array<size_t,R> width_type;
    typedef std::vector<size_t> index_type;
    typedef std::vector<size_t> width_type;
};



// tensor type
template<typename T, class type=dynamic> class tensor;


};

#endif // TENSOR_FWD_H
