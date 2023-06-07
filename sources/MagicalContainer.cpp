#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <climits>

#include "MagicalContainer.hpp"
using namespace ariel;

bool isPrime(int num)
{
    if (num <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= num; ++i)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

bool compareIntPointers(int *first, int *second)
{
    return *first < *second;
}

// ***************************************//
// MagicalContainer                       //
// ***************************************//

MagicalContainer::MagicalContainer() {}

MagicalContainer::~MagicalContainer() {}

void MagicalContainer::addElement(int element)
{
    auto iter = lower_bound(this->mContainer.begin(), this->mContainer.end(), element);
    this->mContainer.insert(iter, element);

    if (isPrime(element))
    {
        int *prime_element = new int(element);
        auto it_prime = lower_bound(this->pPrime.begin(), this->pPrime.end(), prime_element, compareIntPointers);
        this->pPrime.insert(it_prime, prime_element);
    }
}

void MagicalContainer::removeElement(int element)
{
    int flag = 0;
    for (auto it = mContainer.begin(); it != mContainer.end(); ++it)
    {
        if (*it == element)
        {
            mContainer.erase(it);
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        throw std::runtime_error("The element is not in the container");
}

int MagicalContainer::size()
{
    return mContainer.size();
}

// ***************************************//
// AscendingIterator                      //
// ***************************************//
MagicalContainer::AscendingIterator::AscendingIterator()
    : container(nullptr), index(0)
{
}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
    : container(other.container), index(other.index)
{
}

MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &other)
    : container(&other), index(0)
{
}

MagicalContainer::AscendingIterator::~AscendingIterator()
{
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
{
    if (this->container != other.container)
    {
        throw runtime_error("You try to pointing at different containers");
    }
    if (this != &other)
    {
        container = other.container;
        index = other.index;
    }
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
{
    return (container == other.container) && (index == other.index);
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
{
    return (container == other.container) && (index < other.index);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
{
    return (container == other.container) && (index > other.index);
}

int MagicalContainer::AscendingIterator::operator*()
{
    return container->mContainer[index];
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (index == this->end().index)
    {
        throw std::runtime_error("You are in the last element");
    }
    ++index;
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
{
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    AscendingIterator iter(*container);
    iter.index = container->mContainer.size();
    return iter;
}

// ***************************************//
// SideCrossIterator                      //
// ***************************************//

MagicalContainer::SideCrossIterator::SideCrossIterator()
    : container(nullptr), index(0)
{
}

ariel::MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
    : container(other.container), index(other.index)
{
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &other)
    : container(&other), index(0)
{
}

MagicalContainer::SideCrossIterator::~SideCrossIterator()
{
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    if (this->container != other.container)
    {
        throw runtime_error("You try to pointing at different containers");
    }
    if (this != &other)
    {
        container = other.container;
        index = other.index;
    }
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    return (container == other.container) && (index == other.index);
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    return (container == other.container) && (index < other.index);
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    return (container == other.container) && (index > other.index);
}

int MagicalContainer::SideCrossIterator::operator*()
{
    return container->mContainer[index];
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (index == container->mContainer.size())
    {
        throw std::runtime_error("You are in the last element");
    }
    if (index == (container->mContainer.size() / 2))
    {
        index = container->mContainer.size();
        return *this;
    }

    if (index < (container->mContainer.size() / 2))
    {
        index = container->mContainer.size() - index - 1;
        return *this;
    }

    else if (index > (container->mContainer.size() / 2))
    {
        index = container->mContainer.size() - index;
        return *this;
    }

    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    index = 0;
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    SideCrossIterator iter(*container);
    iter.index = (container->mContainer.size());
    return iter;
}

// ***************************************//
// PrimeIterator                          //
// ***************************************//

MagicalContainer::PrimeIterator::PrimeIterator()
    : container(nullptr), index(0)
{
}

ariel::MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
    : container(other.container), index(other.index)
{
}

MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &other)
    : container(&other), index(0)
{
}

MagicalContainer::PrimeIterator::~PrimeIterator()
{
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (this->container != other.container)
    {
        throw runtime_error("You try to pointing at different containers");
    }

    if (this != &other)
    {
        container = other.container;
        index = other.index;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    return (container == other.container) && (index == other.index);
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
{
    return (container == other.container) && (index < other.index);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
{
    return (container == other.container) && (index > other.index);
}

int MagicalContainer::PrimeIterator::operator*()
{
    return *this->container->pPrime[index];
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    if (index == this->end().index)
    {
        throw std::runtime_error("You are in the last element");
    }
    ++index;
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    PrimeIterator iter(*container);
    iter.index = container->pPrime.size();
    return iter;
}
