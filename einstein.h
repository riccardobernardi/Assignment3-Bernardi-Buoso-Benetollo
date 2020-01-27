#ifndef EINSTEIN
#define EINSTEIN
#include<map>

namespace Tensor {
/*
//old index with explicitly specified char symbol
template<char C> struct CIndex { static constexpr char symbol=C; };
#define char_index(symb) CIndex<(#symb)[0]>()
*/


//struct holding dynamic info about index (using an unsigned to guarantee as many indices as we want)
struct Index {
    Index(unsigned i) : idx(i) {}
    unsigned   idx;
};

bool operator < (Index i, Index j) { return i.idx<j.idx; }
bool operator == (Index i, Index j) { return i.idx==j.idx; }

//class with static (snd dynamic) info about index
template<unsigned I> struct StaticIndex : public Index
{
    static constexpr unsigned num=I;
    StaticIndex() : Index(I) {}
};

// some compilers define the __COUNTER__ macro giving a new value each time it is expanded. use it to create a new index id every tiem we create a new index.
#ifdef __COUNTER__
#define new_index StaticIndex<__COUNTER__>()
#else
//in alternative we use __LINE__ which gives the line number at which it is expanded. it is a bit of a hack, but creating unique compile-time ids without __COUNTER__ is hard and overly complex
#define new_index StaticIndex<__LINE__>()
#endif

//structure used to hold a list of index ids
template<unsigned... ids> struct Index_Set {};

//metaprogramming trait to append a new id to an existing Index_Set
template<unsigned id, class T> struct append;
template<unsigned id, unsigned... ids> struct append<id,Index_Set<ids...>> { typedef Index_Set<id, ids...> type; };

//metaprogramming trait to remove all instances of a given id from an Index_Set
template<unsigned id, class T> struct remove_all;
template<unsigned id> struct remove_all<id,Index_Set<>> {typedef Index_Set<> type; };
template<unsigned id, unsigned head, unsigned... tail> struct remove_all<id,Index_Set<head,tail...>> {
    typedef typename append<head, typename remove_all<id,Index_Set<tail...>>::type>::type type;
};
template<unsigned id, unsigned... tail> struct remove_all<id,Index_Set<id,tail...>> {
    typedef typename remove_all<id,Index_Set<tail...>>::type type;
};

//metaprogramming trait co compute setdifferences (T1\T2)
//assumes no repetitions
template<class T1, class T2> struct set_diff;
template<class T> struct set_diff<T,Index_Set<>> { typedef T type; };
template<class T, unsigned head, unsigned...tail> struct set_diff<T,Index_Set<head,tail...>> {
    typedef typename set_diff<typename remove_all<head,T>::type,Index_Set<tail...>>::type type;
};


//metaprogramming trait to merge two Index_Set
template< class T1, class T2 > struct merge;
template< unsigned... ids> struct merge<Index_Set<>,Index_Set<ids...>> { typedef Index_Set<ids...> type; };
//template< class T> struct merge<Index_Set<>,T> { typedef T type; };
template< unsigned id, unsigned... ids, class T> struct merge<Index_Set<id,ids...>,T> {
    typedef typename merge<Index_Set<ids...>,typename append<id,T>::type>::type type;
};

//metaprogramming trait to check wether an id is present in an Index_Set
template<unsigned id, class T> struct find;
template<unsigned id> struct find<id, Index_Set<>> {static constexpr bool value=false;};
template<unsigned id, unsigned... tail> struct find<id, Index_Set<id, tail...>> {static constexpr bool value=true;};
template<unsigned id, unsigned head, unsigned... tail> struct find<id, Index_Set<head, tail...>> {
    static constexpr bool value = find<id,Index_Set<tail...>>::value;
};

//metaprogramming utility to choose between two types baed on a compile-time boolean constant
template<bool, class IF, class ELSE> struct choose_if { typedef ELSE type; };
template<class IF, class ELSE> struct choose_if<true,IF,ELSE> { typedef IF type; };

//metaprogramming trait to return the non-repeating elements in a Index_Set
template<class T> struct non_repeat;
template<> struct non_repeat<Index_Set<>> { typedef Index_Set<> set; };
template<unsigned head, unsigned... tail> struct non_repeat<Index_Set<head, tail...>> {
    typedef typename choose_if<find<head,Index_Set<tail...>>::value,
    typename non_repeat<typename remove_all<head,Index_Set<tail...>>::type >::set,
    typename append<head, typename non_repeat<Index_Set<tail...>>::set>::type>::type set;
};




//metaprogramming tool to count the number of ids in an Index_Set
template<class T> struct index_count;
template<unsigned... ids> struct index_count<Index_Set<ids...>> { static constexpr unsigned value = sizeof...(ids); };

//metaprogramming trait to check whether two sets are identical
//assumes index sets without repetitions
template<class T, class U> struct is_same_nonrepeat;
template<> struct is_same_nonrepeat<Index_Set<>,Index_Set<>> { static constexpr bool value=true; };
template<unsigned... ids> struct is_same_nonrepeat<Index_Set<>,Index_Set<ids...>> { static constexpr bool value=false; };
template<unsigned head, unsigned...tail, class U> struct is_same_nonrepeat<Index_Set<head,tail...>,U> {
    static constexpr bool value = find<head,U>::value && is_same_nonrepeat<Index_Set<tail...>,typename remove_all<head,U>::type>::value;
};











struct einstein_proxy;
template<class T, class U> struct einstein_binary;
template<class T, class U> struct einstein_multiplication;
template<class T, class U> struct einstein_addition;
template<class T, class U> struct einstein_subtraction;

template<typename T, class IDX, class type=einstein_proxy> class einstein_expression;


struct index_data {
    size_t width;
    size_t stride;
    bool repeated;
};

/* Proxy class for a tensor with Einstein indices applied
 * can be both l-value and r-value. operator = triggers evaluation and accumulation
 * internally it works a an iterator (code shared from the generic iterator of the tensor)
 * iterating according to the index specification (computes correct stride per index)
 * provides only the dynaqmic behavior: static check is made by another class inheriting from this
 */
template<typename T> class einstein_expression<T,dynamic,einstein_proxy> {
public:

    einstein_expression(const einstein_expression<T,dynamic,einstein_proxy>&) = default;

    // generic assignment operator does most of the magic
    template<class T2, class TYPE2>
    einstein_expression<T,dynamic>& operator =(einstein_expression<T2,dynamic,TYPE2>&& x) {
        std::map<Index,index_data>& x_index_map=x.get_index_map();
        assert(repeated_num==0);

        // set all entries of dest tensor to 0
        setup();
        while(!end()) {
            eval()=0;
            next();
        }

        //align index maps + sanity checking
        for (auto i=x_index_map.begin(); i!=x_index_map.end(); ++i) {
            auto j=index_map.find(i->first);
            if (i->second.repeated) {
                assert(j==index_map.end());
                add_index(i->first, i->second.width);
            } else {
                assert(j!=index_map.end());
            }
        }
        assert(index_map.size()==x_index_map.size());
        setup();
        x.setup();


        while(!end()) {
            eval() += x.eval();
            next();
            x.next();
        }

        return *this;
    }

    //conversion to a dynamic tensor computes the widths, creates the tensor and then uses operator = to fill it.
    operator tensor<T,dynamic> () {
        widths.clear();
        for (auto i=index_map.begin(); i!=index_map.end(); ++i) {
            if(!(i->second.repeated)) widths.push_back(i->second.width);
        }
        strides.resize(widths.size());
        strides[widths.size()-1]=1;
        for (int i=widths.size()-1; i!=0; --i) {
            strides[i-1]=strides[i]*widths[i];
        }
        tensor<T,dynamic>  result(widths);
        einstein_expression<T,dynamic> dest(result.start_ptr);
        int count=0;
        for (auto i=index_map.begin(); i!=index_map.end(); ++i ) {
            if(!(i->second.repeated)) {
                assert(widths[count]==i->second.width);
                dest.add_index(i->first,i->second.width,strides[count]);
                ++count;
            }
        }

        dest = std::move(*this);

        return result;
    }

    template<size_t R>
    operator tensor<T,rank<R>>() {
        return operator tensor<T,dynamic> ();
    }

    template<typename T2, class type2> friend class tensor;
    template<typename T2, class IDX2, class type2> friend class einstein_expression;

protected:

    einstein_expression(T*ptr) :  repeated_num(0), start_ptr(ptr) {}

    std::map<Index,index_data>& get_index_map() { return index_map; }

    void setup() {
        widths.clear();
        strides.clear();
        idxs.clear();
        for (auto i=index_map.begin(); i!=index_map.end(); ++i) {
            widths.push_back(i->second.width);
            strides.push_back(i->second.stride);
            idxs.push_back(0);
        }
        current_ptr=start_ptr;
    }

    void reset() {
        for (auto i=idxs.begin(); i!=idxs.end(); ++i) *i=0;
        current_ptr=start_ptr;
    }

    bool end() { return idxs[0]==widths[0]; }

    T& eval() { return *current_ptr; }

    void next() {
        unsigned index = idxs.size()-1;
        ++idxs[index];
        current_ptr += strides[index];

        while(idxs[index]==widths[index] && index>0) {
            idxs[index]=0;
            current_ptr -= widths[index]*strides[index];

            --index;
            ++idxs[index];
            current_ptr += strides[index];
        }
    }

    void add_index(Index idx, unsigned width, unsigned stride=0) {
        auto iter=index_map.find(idx);
        if(iter==index_map.end()) {
            index_map[idx]={width,stride,false};
        } else {
            iter->second.repeated=true;
            ++repeated_num;
            iter->second.stride += stride;
            assert(width=iter->second.width);
        }
    }



    unsigned repeated_num;
    std::vector<size_t> widths;
    std::vector<size_t> strides;
    std::vector<size_t> idxs;

    T* const start_ptr;
    T* current_ptr;

    std::map<Index,index_data> index_map;
};






//Using composite for the expressions.
template<typename T, class E1, class E2> class einstein_expression<T,dynamic,einstein_multiplication<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>> {
public:

    //I am aligning all the Index_sets of all the expressions at all times so that each acn iterate independently andthey will be synchronized
    einstein_expression(einstein_expression<T,dynamic,E1> &&e1, einstein_expression<T,dynamic,E2> &&e2) : exp1(std::move(e1)), exp2(std::move(e2)) {
        std::map<Index,index_data> &map1=exp1.get_index_map();
        std::map<Index,index_data> &map2=exp2.get_index_map();

        index_map=map1;
        for(auto i=map2.begin();i!=map2.end();++i) {
            auto iter1=index_map.find(i->first);
            if(iter1==index_map.end()) index_map[i->first]=i->second;
            else {
                assert(i->second.width==iter1->second.width);
                iter1->second.repeated=true;
            }
        }

        for(auto i=index_map.begin();i!=index_map.end();++i) {
            auto iter1=map1.find(i->first);
            if (iter1==map1.end()) {
                exp1.add_index(i->first,i->second.width);
                if(i->second.repeated) exp1.add_index(i->first,i->second.width);
            } else {
                iter1->second.repeated=i->second.repeated;
            }

            auto iter2=map2.find(i->first);
            if (iter2==map2.end()) {
                exp2.add_index(i->first,i->second.width);
                if(i->second.repeated) exp2.add_index(i->first,i->second.width);
            } else {
                iter1->second.repeated=i->second.repeated;
            }
        }
    }


    operator tensor<T,dynamic> () {

        std::pair<tensor<T,dynamic>,einstein_expression<T,dynamic>> result=prepare_conversion();

        result.second = std::move(*this);

        return result.first;
    }

    template<size_t R>
    operator tensor<T,rank<R>>() {
        return operator tensor<T,dynamic> ();
    }


    template<typename T2, class IDX2, class type2> friend class einstein_expression;

protected:
    void add_index(Index idx, unsigned width, unsigned stride=0) {
        auto iter=index_map.find(idx);
        if (iter==index_map.end()) {
            index_data d={width,stride,false};
            index_map[idx]=d;
        } else {
            iter->second.repeated=true;
            assert(width==iter->second.width);
        }

        exp1.add_index(idx,width,stride);
        exp2.add_index(idx,width,stride);
    }

    void setup() {
        exp1.setup();
        exp2.setup();
    }

    void reset() {
        exp1.reset();
        exp2.reset();
    }

    bool end() { return exp1.end(); }



    void next() {
        exp1.next();
        exp2.next();
    }

    T eval() { return exp1.eval() * exp2.eval(); }

    std::map<Index,index_data>& get_index_map() { return index_map; }

    std::pair<tensor<T,dynamic>,einstein_expression<T,dynamic>> prepare_conversion() {
        std::map<Index,index_data> &index_map=get_index_map();
        std::vector<size_t> widths,strides;
        for (auto i=index_map.begin(); i!=index_map.end(); ++i) {
            if(!(i->second.repeated)) widths.push_back(i->second.width);
        }
        strides.resize(widths.size());
        strides[widths.size()-1]=1;
        for (int i=widths.size()-1; i!=0; --i) {
            strides[i-1]=strides[i]*widths[i];
        }
        tensor<T,dynamic>  result(widths);
        einstein_expression<T,dynamic> dest(result.start_ptr);
        int count=0;
        for (auto i=index_map.begin(); i!=index_map.end(); ++i ) {
            if(!(i->second.repeated)) {
                assert(widths[count]==i->second.width);
                dest.add_index(i->first,i->second.width,strides[count]);
                ++count;
            }
        }
        return std::pair<tensor<T,dynamic>,einstein_expression<T,dynamic>>(result,dest);
    }


    einstein_expression<T,dynamic,E1> exp1;
    einstein_expression<T,dynamic,E2> exp2;
    std::map<Index,index_data> index_map;
};



//Using composite for the expressions. This is the base for addition and subtraction, so as to avoid code duplication since only eval() changes between them
template<typename T, class E1, class E2> class einstein_expression<T,dynamic,einstein_binary<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>> {
public:

    //I am aligning all the Index_sets of all the expressions at all times so that each acn iterate independently andthey will be synchronized
    einstein_expression(einstein_expression<T,dynamic,E1> &&e1, einstein_expression<T,dynamic,E2> &&e2) : exp1(std::move(e1)), exp2(std::move(e2)) {
        std::map<Index,index_data> &map1=exp1.get_index_map();
        std::map<Index,index_data> &map2=exp2.get_index_map();

        index_map=map1;
        for(auto i=map2.begin();i!=map2.end();++i) {
            auto iter1=index_map.find(i->first);
            if (i->second.repeated) {
                if(iter1 == index_map.end()) { // non-present/repeated
                    index_map[i->first] = {i->second.width,0,true};
                    exp1.add_index(i->first,i->second.width);
                    exp1.add_index(i->first,i->second.width); //repeated
                } else { // present/repeated
                    assert(iter1->second.repeated);
                    assert(iter1->second.width == i->second.width);
                }

            } else { // ?/non-repeated
                assert(iter1 != index_map.end());
                assert(!(iter1->second.repeated));
                assert(iter1->second.width == i->second.width);
            }
        }

        for(auto i=index_map.begin();i!=index_map.end();++i) {
            auto iter2=map2.find(i->first);
            if (i->second.repeated) {
                if (iter2==map2.end()) {
                    exp2.add_index(i->first,i->second.width);
                    exp2.add_index(i->first,i->second.width); //repeated
                } else {
                    exp2.add_index(i->first,i->second.width); //force repeated and check width
                }
            } else {
                assert(iter2 != map2.end());
                assert(!(iter2->second.repeated));
                assert(iter2->second.width == i->second.width);
            }
        }
    }

    template<typename T2, class IDX2, class type2> friend class einstein_expression;

protected:
    void add_index(Index idx, unsigned width, unsigned stride=0) {
        auto iter=index_map.find(idx);
        if (iter==index_map.end()) {
            index_data d={width,stride,false};
            index_map[idx]=d;
        } else {
            iter->second.repeated=true;
            assert(width==iter->second.width);
        }

        exp1.add_index(idx,width,stride);
        exp2.add_index(idx,width,stride);
    }

    void setup() {
        exp1.setup();
        exp2.setup();
    }

    void reset() {
        exp1.reset();
        exp2.reset();
    }

    bool end() { return exp1.end(); }



    void next() {
        exp1.next();
        exp2.next();
    }

    std::map<Index,index_data>& get_index_map() { return index_map; }

    std::pair<tensor<T,dynamic>,einstein_expression<T,dynamic>> prepare_conversion() {
        std::map<Index,index_data> &index_map=get_index_map();
        std::vector<size_t> widths,strides;
        for (auto i=index_map.begin(); i!=index_map.end(); ++i) {
            if(!(i->second.repeated)) widths.push_back(i->second.width);
        }
        strides.resize(widths.size());
        strides[widths.size()-1]=1;
        for (int i=widths.size()-1; i!=0; --i) {
            strides[i-1]=strides[i]*widths[i];
        }
        tensor<T,dynamic>  result(widths);
        einstein_expression<T,dynamic> dest(result.start_ptr);
        int count=0;
        for (auto i=index_map.begin(); i!=index_map.end(); ++i ) {
            if(!(i->second.repeated)) {
                assert(widths[count]==i->second.width);
                dest.add_index(i->first,i->second.width,strides[count]);
                ++count;
            }
        }
        return std::pair<tensor<T,dynamic>,einstein_expression<T,dynamic>>(result,dest);
    }


    einstein_expression<T,dynamic,E1> exp1;
    einstein_expression<T,dynamic,E2> exp2;
    std::map<Index,index_data> index_map;
};






template<typename T, class E1, class E2> class einstein_expression<T,dynamic,einstein_addition<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>> :
        public einstein_expression<T,dynamic,einstein_binary<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>> {
    using einstein_expression<T,dynamic,einstein_binary<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>::einstein_expression;
    using einstein_expression<T,dynamic,einstein_binary<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>::exp1;
    using einstein_expression<T,dynamic,einstein_binary<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>::exp2;
    using einstein_expression<T,dynamic,einstein_binary<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>::prepare_conversion;
public:

    operator tensor<T,dynamic> () {

        std::pair<tensor<T,dynamic>,einstein_expression<T,dynamic>> result=prepare_conversion();

        result.second = std::move(*this);

        return result.first;
    }

    template<typename T2, class IDX2, class type2> friend class einstein_expression;

protected:

    T eval() { return exp1.eval() + exp2.eval(); }
};


template<typename T, class E1, class E2> class einstein_expression<T,dynamic,einstein_subtraction<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>> :
        public einstein_expression<T,dynamic,einstein_binary<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>> {
    using einstein_expression<T,dynamic,einstein_binary<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>::einstein_expression;
    using einstein_expression<T,dynamic,einstein_binary<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>::exp1;
    using einstein_expression<T,dynamic,einstein_binary<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>::exp2;
    using einstein_expression<T,dynamic,einstein_binary<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>::prepare_conversion;
public:

    operator tensor<T,dynamic> () {

        std::pair<tensor<T,dynamic>,einstein_expression<T,dynamic>> result=prepare_conversion();

        result.second = std::move(*this);

        return result.first;
    }

    template<typename T2, class IDX2, class type2> friend class einstein_expression;

protected:

    T eval() { return exp1.eval() - exp2.eval(); }
};




/* einstein_expression counterparts holding (and checking) static index information
 * they inherit from the base classes as the runtime behavior is the same: they are needed only to add comiletime behavior
 */

template<typename T, unsigned...ids>
class einstein_expression<T,Index_Set<ids...>,einstein_proxy> : public einstein_expression<T,dynamic,einstein_proxy> {
public:

    using einstein_expression<T,dynamic,einstein_proxy>::einstein_expression;

    template<class T2, class TYPE2, unsigned...ids2>
    einstein_expression<T,Index_Set<ids...>,einstein_proxy>& operator =(einstein_expression<T2,Index_Set<ids2...>,TYPE2>&& x) {
        static_assert(is_same_nonrepeat<Index_Set<ids...>,typename non_repeat<Index_Set<ids...>>::set>::value, "Repeated indices in lvalue Einstein expression");
        static_assert(is_same_nonrepeat<Index_Set<ids...>, typename non_repeat<Index_Set<ids2...>>::set>::value, "Non-repeated indices in lvalue and rvalue Einstein expressions are not the same");
        einstein_expression<T,dynamic,einstein_proxy>::operator = (static_cast<einstein_expression<T2,dynamic,TYPE2>&&>(x));
        return *this;
    }
};


template<typename T, class E1, class E2, unsigned...idx>
class einstein_expression<T,Index_Set<idx...>,einstein_multiplication<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>> :
        public einstein_expression<T,dynamic,einstein_multiplication<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>> {
public:
    using einstein_expression<T,dynamic,einstein_multiplication<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>::einstein_expression;
};


template<typename T, class E1, class E2, unsigned...idx>
class einstein_expression<T,Index_Set<idx...>,einstein_addition<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>> :
        public einstein_expression<T,dynamic,einstein_addition<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>> {
public:
    using einstein_expression<T,dynamic,einstein_addition<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>::einstein_expression;
};


template<typename T, class E1, class E2, unsigned...idx>
class einstein_expression<T,Index_Set<idx...>,einstein_subtraction<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>> :
        public einstein_expression<T,dynamic,einstein_subtraction<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>> {
public:
    using einstein_expression<T,dynamic,einstein_subtraction<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>::einstein_expression;
};


/* The actual binary operators return the composite thus forcing delayed-evaluation */

template<typename T, class IDX1, class E1, class IDX2, class E2>
einstein_expression<T,typename merge<IDX1,IDX2>::type,einstein_multiplication<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>
operator * (einstein_expression<T,IDX1,E1> &&e1, einstein_expression<T,IDX2,E2> &&e2) {
    return einstein_expression<T,typename merge<IDX1,IDX2>::type,
                einstein_multiplication<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>(std::move(e1),std::move(e2));
};

template<typename T, class IDX1, class E1, class IDX2, class E2>
einstein_expression<T,typename merge<IDX1,typename set_diff<IDX2,typename non_repeat<IDX1>::set>::type>::type,
        einstein_addition<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>
operator + (einstein_expression<T,IDX1,E1> &&e1, einstein_expression<T,IDX2,E2> &&e2) {
    static_assert(is_same_nonrepeat<typename non_repeat<IDX1>::set,typename non_repeat<IDX2>::set>::value);
    return einstein_expression<T,typename merge<IDX1,typename set_diff<IDX2,typename non_repeat<IDX1>::set>::type>::type,
                einstein_addition<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>(std::move(e1),std::move(e2));
};

template<typename T, class IDX1, class E1, class IDX2, class E2>
einstein_expression<T,typename merge<IDX1,typename set_diff<IDX2,typename non_repeat<IDX1>::set>::type>::type,
        einstein_subtraction<einstein_expression<T,IDX1,E1>,einstein_expression<T,IDX2,E2>>>
operator - (einstein_expression<T,IDX1,E1> &&e1, einstein_expression<T,IDX2,E2> &&e2) {
    static_assert(is_same_nonrepeat<typename non_repeat<IDX1>::set,typename non_repeat<IDX2>::set>::value);
    return einstein_expression<T,typename merge<IDX1,typename set_diff<IDX2,typename non_repeat<IDX1>::set>::type>::type,
                einstein_subtraction<einstein_expression<T,dynamic,E1>,einstein_expression<T,dynamic,E2>>>(std::move(e1),std::move(e2));
};


};
#endif // EINSTEIN
