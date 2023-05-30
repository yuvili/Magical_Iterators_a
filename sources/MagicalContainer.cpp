#include "MagicalContainer.hpp"

namespace ariel
{
    // --------------------------------------
    //          MagicalContainer
    // --------------------------------------
    void MagicalContainer::addElement(int element)
    {
        if (this->elements.empty())
        {
            this->elements.push_back(element); // Add the first element
        }
        else
        {
            // Find the position to insert the element using binary search
            int left = 0;
            int right = this->elements.size() - 1;
            int mid = 0;

            while (left <= right)
            {
                mid = (left + right) / 2;

                if (element == this->elements.at(static_cast<std::vector<int>::size_type>(mid)))
                {
                    // Element already exists in the vector, no need to insert
                    return;
                }
                else if (element < this->elements.at(static_cast<std::vector<int>::size_type>(mid)))
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }

            // Insert the element at the appropriate position
            this->elements.insert(this->elements.begin() + left, element);
        }
    }

    void MagicalContainer::removeElement(int element)
    {
        this->elements.erase(std::remove(this->elements.begin(), this->elements.end(), element), this->elements.end());
    }

    size_t MagicalContainer::size() const
    {
        return this->elements.size();
    }

    std::vector<int> MagicalContainer::getElements() const
    {
        return this->elements;
    }

    int MagicalContainer::getElementAt(size_t possition) const
    {
        return this->elements.at(possition);
    }

    // --------------------------------------
    //          AscendingIterator
    // --------------------------------------
    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &cont, size_t pos)
        : container(cont), position(pos) {}

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        ++position;
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
    {
        return this->position == other.position;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
    {
        return this->position != other.position;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        return this->position > other.position;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        return this->position < other.position;
    }

    int MagicalContainer::AscendingIterator::operator*() const
    {
        if (this->position < this->container.size())
        {
            return this->container.getElementAt(position);
        }
        else
        {
            throw std::out_of_range("Iterator out of range.");
        }
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    {
        return AscendingIterator(this->container);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
    {
        return AscendingIterator(this->container, this->container.size());
    }

    // --------------------------------------
    //          SideCrossIterator
    // --------------------------------------
    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &cont)
        : container(cont), left(0), right(cont.size()), leftToRight(true) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &cont, size_t newLeft, size_t newRight, bool lToR)
        : container(cont), left(newLeft), right(newRight), leftToRight(lToR) {}

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {
        if (this->leftToRight)
        {
            if (this->left < this->right)
                this->right--;
            this->leftToRight = false;
        }
        else
        {
            if (this->left < this->right)
            {
                this->left++;
            }
            this->leftToRight = true;
        }
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {
        return (this->left == other.left) && (this->right == other.right) && (this->leftToRight == other.leftToRight);
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        return (this->left > other.left) && (this->right > other.right) && (this->leftToRight == other.leftToRight);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        return (this->left < other.left) && (this->right < other.right) && (this->leftToRight == other.leftToRight);
    }

    int MagicalContainer::SideCrossIterator::operator*() const
    {
        if (this->leftToRight)
        {
            if (this->left < this->right)
                return this->container.getElementAt(left);
        }
        else
        {
            if (this->right < this->container.size())
                return this->container.getElementAt(this->right);
        }
        throw std::out_of_range("Iterator out of range.");
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {
        return SideCrossIterator(this->container);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
    {
        return SideCrossIterator(this->container, container.size() / 2, this->container.size() / 2, false);
    }

    // --------------------------------------
    //          PrimeIterator
    // --------------------------------------
    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &cont, size_t pos)
        : container(cont), position(pos)
    {
        while (position < container.size() && !isPrime(container.getElementAt(position)))
            ++position;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        ++position;
        while (position < container.size() && !isPrime(container.getElementAt(position)))
            ++position;
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
    {
        return this->position == other.position;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        return this->position > other.position;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
    {
        return this->position < other.position;
    }

    int MagicalContainer::PrimeIterator::operator*() const
    {
        if (this->position < this->container.size())
            return this->container.elements[this->position];
        else
            throw std::out_of_range("Iterator out of range.");
    }

    bool MagicalContainer::PrimeIterator::isPrime(int number) const
    {
        if (number < 2)
            return false;
        if (number < 4)
            return true;
        if (number % 2 == 0)
            return false;

        int sqrtNumber = static_cast<int>(std::sqrt(number));
        for (int i = 3; i <= sqrtNumber; i += 2)
        {
            if (number % i == 0)
                return false;
        }
        return true;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
    {
        return PrimeIterator(this->container);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
    {
        return PrimeIterator(this->container, this->container.size());
    }

}