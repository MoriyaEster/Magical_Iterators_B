#pragma once
#include <stdio.h>
#include <vector>

using namespace std;
namespace ariel
{
    class MagicalContainer
    {
    private:
        vector<int> mContainer;
        vector <int*> pPrime;

    public:
        MagicalContainer();
        ~MagicalContainer();
        void addElement(int element);
        void removeElement(int element);
        int size();

        class AscendingIterator
        {
        public:
            const MagicalContainer *container;
            size_t index;

        public:
            AscendingIterator();
            AscendingIterator(const AscendingIterator &other);
            AscendingIterator(const MagicalContainer &mgcContainer);
            ~AscendingIterator();
            AscendingIterator &operator=(const AscendingIterator &other);
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            bool operator>(const AscendingIterator &other) const;
            int operator*();
            AscendingIterator &operator++();
            AscendingIterator begin();
            AscendingIterator end();
        };

        class SideCrossIterator
        {
        public:
            const MagicalContainer *container;
            size_t index;

        public:
            SideCrossIterator();
            SideCrossIterator(const SideCrossIterator &other);
            SideCrossIterator(const MagicalContainer &mgcContainer);
            ~SideCrossIterator();
            SideCrossIterator &operator=(const SideCrossIterator &other);
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            int operator*();
            SideCrossIterator &operator++();
            SideCrossIterator begin();
            SideCrossIterator end();
        };

        class PrimeIterator
        {
        private:
            const MagicalContainer *container;
            size_t index;

        public:
            PrimeIterator();
            PrimeIterator(const PrimeIterator &other);
            PrimeIterator(const MagicalContainer &mgcContainer);
            ~PrimeIterator();
            PrimeIterator &operator=(const PrimeIterator &other);
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            bool operator>(const PrimeIterator &other) const;
            int operator*();
            PrimeIterator &operator++();
            PrimeIterator begin();
            PrimeIterator end();
        };
    };

}
