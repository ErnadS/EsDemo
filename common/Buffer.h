#ifndef BUFFER_H
#define BUFFER_H

#include <QLinkedList>

template <typename T>
class Buffer
{
protected:
    int m_count;
    int m_size;
    QLinkedList<T> m_buffer;

public:
    Buffer(int size) : m_count(0), m_size(size) {}

    virtual void append(const T& value) = 0;

    int count()
    {
        return m_count;
    }

    int size()
    {
        return m_size;
    }

    auto begin() -> decltype(m_buffer.begin())
    {
        return m_buffer.begin();
    }

    auto end() -> decltype(m_buffer.end())
    {
        return m_buffer.end();
    }

    auto cbegin() -> decltype(m_buffer.cbegin())
    {
        return m_buffer.cbegin();
    }

    auto cend() -> decltype(m_buffer.cend())
    {
        return m_buffer.cend();
    }
};

template <typename T>
class LifoBuffer: public Buffer<T>
{
public:
    LifoBuffer(int size) : Buffer<T>(size) {}

    void append(const T& value)
    {
        if (Buffer<T>::m_count == Buffer<T>::m_size)
        {
            Buffer<T>::m_buffer.removeLast();
            Buffer<T>::m_count--;
        }

        Buffer<T>::m_buffer.insert(Buffer<T>::m_buffer.begin(), value);
        Buffer<T>::m_count++;
    }
};

template <typename T>
class FifoBuffer: public Buffer<T>
{
public:
    FifoBuffer(int size) : Buffer<T>(size) {}

    void append(const T& value)
    {
        if (Buffer<T>::m_count == Buffer<T>::m_size)
        {
            Buffer<T>::m_buffer.removeFirst();
            Buffer<T>::m_count--;
        }

        Buffer<T>::m_buffer.append(value);
        Buffer<T>::m_count++;
    }
};

#endif // BUFFER_H
