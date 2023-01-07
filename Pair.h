//
// Created by liels on 09/12/2022.
//

#ifndef WET_2_PAIR_H
#define WET_2_PAIR_H

#include <stdexcept>

template<class T, class S>
class Pair
{
    private:
    T first;
    S second;

    public:
    Pair() = default;
    Pair(const T& first, const S& second):
    first(first), second(second) {}
    Pair(const Pair& p) = default;
    ~Pair() = default;

    //const getters
    T getFirst() const {return first;}
    S getSecond() const {return second;}

    //getters
    T& getFirst() {return first;}
    S& getSecond() {return second;}

    //setters
    void setFirst(const T& first) const {this->first;}
    void setSecond(const S& second) const {this->second;}

    bool operator<(const Pair& p) const
    {
        if(first < p.first)
        {
            return true;
        }
        else if(first > p.first)
        {
            return false;
        }
        else
        {
            if(second < p.second)
            {
                return true;
            }
            else if(second > p.second)
            {
                return false;
            }
            throw std::logic_error("cant compare these Pairs");
        }
    }
};

template<class T, class S>
bool operator>(const Pair<T,S>& p1, const Pair<T,S>& p2)
{
    if(p1 < p2)
    {
        return false;
    }
    else if(p2 < p1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T, class S>
bool operator==(const Pair<T,S>& p1, const Pair<T,S>& p2)
{
    try
    {
        if(p1.getSecond() == p2.getSecond())
        {
            return true;
        }
    }
    catch(std::logic_error&)
    {
        return true;
    }
    return false;
}
#endif //WET_2_PAIR_H
