#ifndef MAGICALCONTAINER_H
#define MAGICALCONTAINER_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdexcept>
using namespace std;

namespace ariel
{
    class MagicalContainer
    {
    private:
        std::vector<int> elements;

    public:
        void addElement(int element);    // Add an int number to the container
        void removeElement(int element); // Remove the inputed number from the container
        size_t size() const;             // Return the number of elements in the container

        // Getters
        std::vector<int> getElements() const;
        int getElementAt(size_t possition) const;

        // Iterator classes
        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;
    };

    class MagicalContainer::AscendingIterator
    {
    private:
        const MagicalContainer &container;
        size_t position; // cell index position is the container

    public:
        AscendingIterator(const MagicalContainer &cont, size_t pos = 0);
        AscendingIterator &operator++();
        bool operator==(const AscendingIterator &other) const;
        bool operator!=(const AscendingIterator &other) const;
        bool operator>(const AscendingIterator &other) const;
        bool operator<(const AscendingIterator &other) const;
        int operator*() const;

        AscendingIterator begin(); // Returns an AscendingIterator pointing to the first element of the container
        AscendingIterator end();   // Returns an AscendingIterator pointing one position past the last element of the container
    };

    class MagicalContainer::SideCrossIterator
    {
    private:
        const MagicalContainer &container;
        size_t left;      // The current left cell postion
        size_t right;     // The current right cell position
        bool leftToRight; // if true - point at a left cell, else - point at a right cell

    public:
        SideCrossIterator(const MagicalContainer &cont);
        SideCrossIterator(const MagicalContainer &cont, size_t newLeft, size_t newRight, bool lToR = true);
        SideCrossIterator &operator++();
        bool operator==(const SideCrossIterator &other) const;
        bool operator!=(const SideCrossIterator &other) const;
        bool operator>(const SideCrossIterator &other) const;
        bool operator<(const SideCrossIterator &other) const;
        int operator*() const;

        SideCrossIterator begin(); // Returns an AscendingIterator pointing to the first element of the container
        SideCrossIterator end();   // Returns an AscendingIterator pointing one position past the last element of the container
    };

    class MagicalContainer::PrimeIterator
    {
    private:
        const MagicalContainer &container;
        size_t position; // cell index position is the container

        bool isPrime(int number) const; // Returns true if number is prime and false otherwise

    public:
        PrimeIterator(const MagicalContainer &cont, size_t pos = 0);
        PrimeIterator &operator++();
        bool operator==(const PrimeIterator &other) const;
        bool operator!=(const PrimeIterator &other) const;
        bool operator>(const PrimeIterator &other) const;
        bool operator<(const PrimeIterator &other) const;
        int operator*() const;

        PrimeIterator begin(); // Returns an AscendingIterator pointing to the first element of the container
        PrimeIterator end();   // Returns an AscendingIterator pointing one position past the last element of the container
    };
};

#endif