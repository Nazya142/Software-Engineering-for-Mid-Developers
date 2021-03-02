#include <vector>
#include <unordered_map>
#include <functional>
#include <cstdlib>
#include <iostream>


#define MIN_GAP 10
#define BUCKET_COUNT 10000

template<typename T, class Hash = std::hash<int>>
struct JSArray
{
public:
    JSArray(const Hash& hash = Hash()) : m_hashFun(hash), m_type(structType::vector){

    };
    void addElement(size_t index, T value)
    {
        if (m_type == structType::vector && m_NeedHashTable(index))
        {
            m_CreateHashTable();
        }
        m_addElement(index, value);
    };

    T operator[](size_t index) {
        switch (m_type) {
            case structType::vector:
                return m_vector[index];
            case structType::hash:
                return m_hashTable->at(index);
            default:
                return T();
        }
    };

private:
    const Hash m_hashFun;
    std::unordered_map<int, T, Hash> *m_hashTable;
    std::vector<T> m_vector;
    
    size_t m_size = 0;

    enum structType {
        vector,
        hash
    } m_type;

    bool m_NeedHashTable(size_t index)
    {
        size_t gap = index - m_size;

        return (gap < MIN_GAP) ? false : gap > (m_size / 2);
    };

    void m_CreateHashTable() {
        m_hashTable = new std::unordered_map<int, T, Hash>(BUCKET_COUNT, m_hashFun);

        for (size_t i = 0; i < m_vector.size(); ++i) {
            m_hashTable->emplace(i, m_vector[i]);
        }

        m_vector.clear();
        m_type = structType::hash;
    };

    void m_addElement(const size_t &index, const T &value)
    {
        switch (m_type) {
            case structType::vector:
                m_addVectorElement(index, value);
                break;
            case structType::hash:
               m_addHashElement(index, value);
                break;
            default:
                return;
        }
    };

    void m_addVectorElement (size_t index, T value) {
        if (index > m_size) {
            m_vector.resize(index);
        }
        m_vector.insert(m_vector.begin() + index, value);
        m_size = index;
    };

    void m_addHashElement (size_t index, T value) {
        m_hashTable->emplace(index, value);
        m_size++;
    }
};