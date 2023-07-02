template <typename _Type>
class segment_tree
{
    using _Function = function<_Type(_Type, _Type)>;
 
public:
    int                   m_base_index;
    int                   m_size, m_height;
    vector<vector<_Type>> m_data;
    _Function             m_func;
 
public:
    template <typename _Iterator>
    segment_tree(_Iterator _begin, _Iterator _end, const _Function& _func, const int& _base_index=0)
        : m_func(_func), m_base_index(_base_index)
    {
        m_size   = _end - _begin;
        m_height = m_size > 1 ? 33 - __builtin_clz(m_size - 1) : 1;
 
        m_data        = vector<vector<_Type>>(m_height);
        m_data.back() = vector<_Type>(_begin, _end);
 
        int mask = m_size;
        for (int i = m_height - 2; i >= 0; i--)
        {
            m_data[i].resize((mask + 1) >> 1);
            for (int j = (mask >> 1) - 1; j >= 0; j--)
            {
                m_data[i][j] = _func(
                    m_data[i + 1][j << 1],
                    m_data[i + 1][(j << 1) + 1]
                );
            }
            if (mask & 1)
                m_data[i].back() = m_data[i + 1].back();
            
            ++mask >>= 1;
        }
    }
 
    template <typename _Container>
    segment_tree(const _Container& _container, const _Function& _func, const int& _base_index=0)
        : segment_tree(_container.begin(), _container.end(), _func, _base_index)
    {}
 
    template <typename _Container, size_t _Size>
    segment_tree(const _Container (&_container)[_Size], const _Function& _func, const int& _base_index=0)
        : segment_tree(_container, _container + _Size, _func, _base_index)
    {}
    
    const _Type get(const int& _index) const
    {
        return m_data[0][0];
    }

    const _Type get(const int& _lindex, const int& _rindex) const
    {
        int l = _lindex - m_base_index;
        int r = _rindex - m_base_index;
 
        if (l == r)
            return m_data.back()[l];
 
        _Type left  = m_data.back()[l];
        _Type right = m_data.back()[r];
        for (int h = m_height - 1; (l >> 1) < (r >> 1); l >>= 1, r >>= 1, h--)
        {
            if (!(l & 1))
                left = m_func(left, m_data[h][l + 1]);
            if (r & 1)
                right = m_func(m_data[h][r - 1], right);
        }
        return m_func(left, right);
    }
 
    void update(const int &_index, const _Type& _new_value)
    {
        int m = _index - m_base_index;
 
        _Type value = _new_value;
        m_data.back()[m] = value;
        for (int h = m_height - 1, mask = m_size; h > 0; h--, m >>= 1)
        {
            if (!(m & 1)) {
                m_data[h - 1][m >> 1] = m < m_data[h].size() - 1 ? m_func(value, m_data[h][m + 1]) : value;
                value = m_data[h - 1][m >> 1];
            }
            else
            {
                m_data[h - 1][m >> 1] = m_func(m_data[h][m - 1], value);
                value = m_data[h - 1][m >> 1];
            }
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
        { return m_data.back()[_index - m_base_index]; }
 
    operator vector<vector<_Type>>() const
        { return m_data; }
 
 
    friend ostream& operator<<(ostream& _os, const segment_tree<_Type>& _segment_tree)
        { return _os << static_cast<vector<vector<_Type>>>(_segment_tree); }
};
