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
public: 
    void Push(const T &el)
    {
        bool wasEmpty = m_data.empty(); 
        m_data.push_back(el);
        if(wasEmpty == true) //I pushed in element than I need to change state to IsNotEmpty
            for(const auto &sub : m_subscribers)
                sub(StackEvent::IsNotEmpty);
    }

    T Pop()
    {
        if(m_data.empty()) 
            throw std::out_of_range("ObservableStack is empty"); //well dont want go out of bounds xD 

        T out = std::move(m_data.back()); //sice m_data is allocated and it needs to move and also top has to be specified
        m_data.pop_back();
        if(m_data.empty()) //If pop beforehand was the last element than I have to change state to empty
            for(const auto &sub : m_subscribers)
                sub(StackEvent::Empty);

        return out;
    
    }

    void Subscribe(const std::function<void(StackEvent)> &sub)
    {
        m_subscribers.push_back(sub); //since we subscribed replaces m_subscribers argument with IsNotEmpty
    }

    void Clear()
    {
        bool wasEmpty = m_data.empty(); //check if m_data list is empty
        m_data.clear(); //clears list 

        if(wasEmpty == false) //data are cleared is empty Stack::event is activated so subscribers know its empty, not sure if this check is needed
            for(const auto &sub : m_subscribers)
                sub(StackEvent::Empty);
    }
    
    bool IsEmpty()
    {
        return m_data.empty();
    }


private: 
    std::list<T> m_data;
    std::vector<std::function<void(StackEvent)>> m_subscribers; //std::set doesnt let me insert duplicate elements 
};

