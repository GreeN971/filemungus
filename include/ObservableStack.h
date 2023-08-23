#pragma once 
#include <cassert>
#include <list>
#include <vector>
#include <functional>
#include <stdexcept>

enum class StackEvent
{
    Empty,
    IsNotEmpty
};

template<typename T>
class ObservableStack
{
private: 
    std::vector<std::function<void(StackEvent)>> m_subscribers; 
    using subscriber_t = decltype(m_subscribers)::value_type; 

public: 
    void Push(const T &el)
    {
        bool wasEmpty = m_data.empty(); 
        m_data.push_back(el);
        if(wasEmpty == true)
            for(const subscriber_t &sub : m_subscribers)
                sub(StackEvent::IsNotEmpty);
    }

    T Pop()
    {
        if(m_data.empty()) 
            throw std::out_of_range("ObservableStack is empty");

        T out = std::move(m_data.back()); 
        m_data.pop_back();
        if(m_data.empty()) 
            for(const subscriber_t &sub : m_subscribers)
                sub(StackEvent::Empty);

        return out;
    
    }

    void Subscribe(const std::function<void(StackEvent)> &sub)
    {
        m_subscribers.push_back(sub); 
    }

    void Clear()
    {
        bool wasEmpty = m_data.empty();
        m_data.clear(); 

        if(wasEmpty == false)
            for(const subscriber_t &sub : m_subscribers)
                sub(StackEvent::Empty);
    }
    
    bool IsEmpty()
    {
        return m_data.empty();
    }


private: 
    std::list<T> m_data;
};

