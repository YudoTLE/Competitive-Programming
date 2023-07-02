template <typename _Type>
class segment_tree
{
    using _Function = function<_Type(_Type, _Type)>;

private:
    int           m_base_index;
    size_t        m_size, m_height;
    vector<_Type> m_raw_data;
    vector<_Type> m_data;
    vector<int>   m_raw_index;
    _Function     m_func;
    
    const void construct(const size_t &_lower, const size_t &_upper, const size_t &_id) {
        if (_lower == _upper) {
            m_data[_id] = m_raw_data[_lower];
            m_raw_index.emplace_back(_id);
            return;
        }
        
        const size_t mid = _lower + (_upper - _lower) / 2;
        construct(_lower, mid, _id * 2 + 1);
        construct(mid + 1, _upper, _id * 2 + 2);
        m_data[_id] = m_func(m_data[_id * 2 + 1], m_data[_id * 2 + 2]);
    }

    const pair<_Type, bool> get(const size_t& _lindex, const size_t& _rindex, const size_t&  _lower, const size_t&  _upper, const size_t& _index) const
    {
        if (_lindex <= _lower && _upper <= _rindex)
            return { m_data[_index], true };
        if (_upper < _lindex || _rindex < _lower)
            return { m_data[_index], false };
        
        const size_t mid = _lower + (_upper - _lower) / 2;
        
        const auto& [left_result,  left_exist ] = get(_lindex, _rindex, _lower, mid, _index * 2 + 1);
        const auto& [right_result, right_exist] = get(_lindex, _rindex, mid + 1, _upper, _index * 2 + 2);
        
        if (!left_exist)
            return { right_result, true };
        if (!right_exist)
            return { left_result, true };
        return { m_func(left_result, right_result), true };
    }

public:
    template <typename _Iterator>
    segment_tree(_Iterator _begin, _Iterator _end, const _Function& _func, const int& _base_index=0)
        : m_raw_data(vector<_Type>(_begin, _end)), m_size(_end - _begin), m_height(33 - __builtin_clz(_end - _begin - 1)), m_func(_func), m_base_index(_base_index)
    {
        m_data = vector<_Type>((1 << m_height) - 1);
        construct(0, m_size - 1, 0);
    }

    template <typename _Container>
    segment_tree(const _Container& _container, const _Function& _func, const int& _base_index=0)
        : segment_tree(_container.begin(), _container.end(), _func, _base_index)
    {}

    template <typename _Container, size_t _Size>
    segment_tree(const _Container (&_container)[_Size], const _Function& _func, const int& _base_index=0)
        : segment_tree(_container, _container + _Size, _func, _base_index)
    {}
    

    void update(const int &_index, const _Type& _new_value)
    {
        int ptr = m_raw_index[_index - m_base_index];
        m_raw_data[_index - m_base_index] = m_data[ptr] = _new_value;
        while (ptr)
        {
            ptr = (ptr - 1) / 2;
            m_data[ptr] = m_func(m_data[ptr * 2 + 1], m_data[ptr * 2 + 2]);
        }
    }


    const inline size_t size() const
        { return m_size; }
    
    const inline size_t height() const
        { return m_height; }

    const inline auto begin() const
        { return m_data.begin(); }

    const inline auto end() const
        { return m_data.end(); }

    const inline auto rbegin() const
        { return m_data.rbegin(); }

    const inline auto rend() const
        { return m_data.rend(); }


    const auto operator[] (const int &_index) const
        { return m_raw_data[_index - m_base_index]; }

    const auto operator() (const int &_lindex, const int &_rindex) const
        { return get(_lindex - m_base_index, _rindex - m_base_index, 0, m_size - 1, 0).first; }


    operator vector<_Type>() const
        { return m_data; }


    friend ostream& operator<<(ostream& _os, const segment_tree<_Type>& _segment_tree)
        { return _os << static_cast<vector<_Type>>(_segment_tree); }
};
