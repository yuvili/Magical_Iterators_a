#include "MagicalContainer.hpp"

namespace ariel {
    // --------------------------------------
    //          MagicalContainer
    // --------------------------------------
    void MagicalContainer::addElement(int element) {
        elements.push_back(element);
    }

    void MagicalContainer::removeElement(int element) {
        elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
    }

    size_t MagicalContainer::size() const {
        return elements.size();
    }

    std::vector<int> MagicalContainer::getElements() const{
        return this->elements;
    }

    int MagicalContainer::getElementAt(size_t possition) const{
        return this->elements.at(possition);
    }

    // --------------------------------------
    //          AscendingIterator
    // --------------------------------------
    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& cont, size_t pos)
        : container(cont), position(pos) {
            sortedElements = container.getElements();
            std::sort(sortedElements.begin(), sortedElements.end());
        }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
        ++position;
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
        return position == other.position;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
        return *this != other;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
        return position > other.position;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
        return position < other.position;
    }

    int MagicalContainer::AscendingIterator::operator*() const {
        if (position < this->sortedElements.size()){
            return this->sortedElements[position];
        }
        else {
            throw std::out_of_range("Iterator out of range.");
        }
    }       

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return AscendingIterator(this->container);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        return AscendingIterator(this->container, this->container.size());
    }

    // --------------------------------------
    //          SideCrossIterator
    // --------------------------------------
    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& cont)
        : container(cont), left(0), right(cont.size()), leftToRight(true) {}
    
    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& cont, size_t l, size_t r, bool lToR)
        : container(cont), left(l), right(r), leftToRight(lToR) {}

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        if (leftToRight) {
            if(left < right) right--;
            leftToRight = false;
        } 
        else {
            if (left < right) {
                left++;
            }    
            leftToRight = true;
        }
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
        return (left == other.left) && (right == other.right) && (leftToRight == other.leftToRight);
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
        return (left > other.left) && (right > other.right) && (leftToRight == other.leftToRight);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
        return (left < other.left) && (right < other.right) && (leftToRight == other.leftToRight);
    }

    int MagicalContainer::SideCrossIterator::operator*() const {
        if (leftToRight) {
            if (left < right)
                return container.getElementAt(left);
        } else {
            if (right < container.size())
                return container.getElementAt(right);
        }
        throw std::out_of_range("Iterator out of range.");
    }

      MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return SideCrossIterator(this->container);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        return SideCrossIterator(this->container, container.size()/2, container.size()/2, false);
    }

    // --------------------------------------
    //          PrimeIterator
    // --------------------------------------
    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& cont, size_t pos)
        : container(cont), position(pos) {
        while (position < container.size() && !isPrime(container.getElementAt(position)))
            ++position;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
        ++position;
        while (position < container.size() && !isPrime(container.getElementAt(position)))
            ++position;
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
        return position == other.position;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
        return position > other.position;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
        return position < other.position;
    }

    int MagicalContainer::PrimeIterator::operator*() const {
        if (position < container.size())
            return container.elements[position];
        else
            throw std::out_of_range("Iterator out of range.");
    }

    bool MagicalContainer::PrimeIterator::isPrime(int number) const {
        if (number < 2)
            return false;
        if (number < 4)
            return true;
        if (number % 2 == 0)
            return false;
        
        int sqrtNumber = static_cast<int>(std::sqrt(number));
        for (int i = 3; i <= sqrtNumber; i += 2) {
            if (number % i == 0)
                return false;
        }
        return true;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return PrimeIterator(this->container);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        return PrimeIterator(this->container, this->container.size());
    }

}