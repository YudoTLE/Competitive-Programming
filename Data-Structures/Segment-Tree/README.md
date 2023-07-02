# Segment Tree
Segment Tree is a versatile data structure used for various range query operations on an array-like data. It allows efficient querying for range sum, range minimum/maximum, or other user-defined aggregate functions. This Segment Tree uses Bottom-Up method to construct, means it will be easier to debug.


## Constructor
The constructor accepts different types of data sources, including iterators, containers, or plain arrays. Additionally, it allows specifying a custom base index for the data source.

### Declaration 1
```C++
template <typename _Iterator>
segment_tree(_Iterator _begin, _Iterator _end, const _Function& _func, const int& _base_index=0)
```

Accepts ranged iterator as the parameter, followed by custom function, and base index(default is 0-indexed).

|Parameters |Description|
|-----------|-|
|_begin     |Iterator pointing to the beginning of the range of data elements.|
|_end       |Iterator pointing to the end of the range of data elements.|
|_func      |User-provided aggregate function that defines the operation to be applied on the elements when constructing the Segment Tree. It takes two `_Type` parameters and returns an aggregated result.|
|_base_index|Specifies the base index of the data elements. By default, it is set to 0, indicating that the data is zero-based indexed.|

### Declaration 2
```C++
template <typename _Container>
segment_tree(const _Container& _container, const _Function& _func, const int& _base_index=0)
```

Accepts container as the parameter, followed by custom function, and base index(default is 0-indexed).

|Parameters |Description|
|-----------|-|
|_container |Reference to a container that holds the data elements. The constructor accepts any container type that provides the necessary member functions like `begin()` and `end()`.|
|_func      |User-provided aggregate function that defines the operation to be applied on the elements when constructing the Segment Tree. It takes two `_Type` parameters and returns an aggregated result.|
|_base_index|Specifies the base index of the data elements. By default, it is set to 0, indicating that the data is zero-based indexed.|

### Declaration 3
```C++
template <typename _Container, size_t _Size>
segment_tree(const _Container (&_container)[_Size], const _Function& _func, const int& _base_index=0)
```

Accepts primitive array as the parameter, followed by custom function, and base index(default is 0-indexed).

|Parameters |Description|
|-----------|-|
|_container |Reference to a container that holds the data elements. The constructor accepts any container type as long as the size is fixed at compile time.|
|_func      |User-provided aggregate function that defines the operation to be applied on the elements when constructing the Segment Tree. It takes two `_Type` parameters and returns an aggregated result.|
|_base_index|Specifies the base index of the data elements. By default, it is set to 0, indicating that the data is zero-based indexed.|


## Updating Query
The `update` method allows you to modify individual elements of the data and updating the corresponding values in **O(log(n))** time.

### Declaration
```C++
void update(const int& _index, const _Type& _new_value)
```

Modify element at index `_index` to `_new_val`

|Parameters|Description|
|----------|-|
|_index    |The index of the modified element.|
|_new_val  |The new value that will be asigned to the element at index `_index`.| 


## Getting Result from Query
The `get` method allows you to modify individual elements of the data and updating the corresponding values in the **O(log(n))** time.

### Declaration 1
```C++
const _Type get() const
```

Returns the results of type `_Type` from the first to last index.

### Declaration 2
```C++
const _Type get(const int& _lindex, const int& _rindex) const
```

Returns the results of type `_Type` from index `_lindex` to index `_rindex`.

|Parameters|Description|
|----------|-|
|_lindex   |The left index of the element.|
|_rindex   |The right index of the element.|


## Other Methods
|Methods  |Description|
|---------|-----------|
|size()   |Returns the number of leaf of the tree|
|height() |Returns the height of the tree|
|begin()  |Returns the begin iterator of the tree|
|end()    |Returns the end iterator of the tree|
|rbegin() |Returns the reverse begin iterator of the tree|
|rend()   |Returns the reverse end iterator of the tree|
