#include "doctest.h"
#include "sources/MagicalContainer.hpp"
using namespace ariel;

TEST_CASE("MagicalContainer")
{
    SUBCASE("addElement")
    {
        MagicalContainer container;
        container.addElement(5);
        CHECK(container.size() == 1);
        CHECK(container.getElementAt(0) == 5);
    }

    SUBCASE("removeElement")
    {
        MagicalContainer container;
        container.addElement(5);
        container.removeElement(5);
        CHECK(container.size() == 0);
    }

    SUBCASE("size")
    {
        MagicalContainer container;
        container.addElement(5);
        container.addElement(10);
        CHECK(container.size() == 2);
    }

    SUBCASE("getElements")
    {
        MagicalContainer container;
        container.addElement(5);
        container.addElement(10);
        std::vector<int> elements = container.getElements();
        CHECK(elements.size() == 2);
        CHECK(elements[0] == 5);
        CHECK(elements[1] == 10);
    }

    SUBCASE("getElementAt")
    {
        MagicalContainer container;
        container.addElement(5);
        container.addElement(10);
        CHECK(container.getElementAt(0) == 5);
        CHECK(container.getElementAt(1) == 10);
    }
}

TEST_CASE("MagicalContainer::AscendingIterator")
{
    MagicalContainer container;
    container.addElement(5);
    container.addElement(10);
    container.addElement(3);

    MagicalContainer container2;
    container2.addElement(5);
    container2.addElement(-10);
    container2.addElement(3);

    MagicalContainer::AscendingIterator iter1(container);
    MagicalContainer::AscendingIterator iter2(container);
    MagicalContainer::AscendingIterator iter3(container2);

    SUBCASE("operator++")
    {
        CHECK(*iter1 == 3);
        ++iter1;
        CHECK(*iter1 == 5);
        ++iter1;
        CHECK(*iter1 == 10);
    }

    SUBCASE("operator==")
    {
        CHECK(*iter1 == *iter2);
    }

    SUBCASE("operator!=")
    {
        CHECK(*iter1 != *iter3);
    }

    SUBCASE("operator>")
    {
        CHECK(*iter1 > *iter3);
    }

    SUBCASE("operator<")
    {
        CHECK(*iter3 < *iter1);
    }

    SUBCASE("operator*")
    {
        CHECK(*iter1 == 3);
        ++iter1;
        CHECK(*iter1 == 5);
        ++iter1;
        CHECK(*iter1 == 10);
    }

    SUBCASE("begin")
    {
        CHECK(*iter1.begin() == 3);
        CHECK(*iter3.begin() == -10);
    }
}

TEST_CASE("MagicalContainer::SideCrossIterator")
{
    MagicalContainer container;
    container.addElement(5);
    container.addElement(10);
    container.addElement(3);

    MagicalContainer container2;
    container2.addElement(5);
    container2.addElement(-10);
    container2.addElement(3);

    MagicalContainer::SideCrossIterator iter1(container);
    MagicalContainer::SideCrossIterator iter2(container);
    MagicalContainer::SideCrossIterator iter3(container2);

    SUBCASE("operator++")
    {
        CHECK(*iter1 == 3);
        ++iter1;
        CHECK(*iter1 == 10);
        ++iter1;
        CHECK(*iter1 == 5);
    }

    SUBCASE("operator==")
    {
        CHECK(*iter1 == *iter2);
    }

    SUBCASE("operator!=")
    {
        CHECK(*iter1 != *iter3);
    }

    SUBCASE("operator>")
    {
        CHECK(*iter1 > *iter3);
    }

    SUBCASE("operator<")
    {
        CHECK(*iter3 < *iter1);
    }

    SUBCASE("operator*")
    {
        CHECK(*iter1 == 3);
        ++iter1;
        CHECK(*iter1 == 10);
        ++iter1;
        CHECK(*iter1 == 5);
    }

    SUBCASE("begin")
    {
        CHECK(*iter1.begin() == 3);
        CHECK(*iter3.begin() == -10);
    }
}

TEST_CASE("MagicalContainer::PrimeIterator")
{
    MagicalContainer container;
    container.addElement(5);
    container.addElement(10);
    container.addElement(3);

    MagicalContainer::PrimeIterator iter(container);
    MagicalContainer::PrimeIterator iter1(container);
    MagicalContainer::PrimeIterator iter2(container);

    SUBCASE("operator++")
    {
        CHECK(*iter == 3);
        ++iter;
        CHECK(*iter == 5);
    }

    SUBCASE("operator==")
    {
        CHECK(iter1.begin() == iter2.begin());
    }

    SUBCASE("operator!=")
    {
        CHECK(iter1.begin() != iter2.end());
    }

    SUBCASE("operator>")
    {
        CHECK(iter2.end() > iter1.begin());
    }

    SUBCASE("operator<")
    {
        CHECK(iter1.begin() < iter2.end());
    }

    SUBCASE("operator*")
    {
        MagicalContainer::PrimeIterator iter(container);
        CHECK(*iter == 3);
        ++iter;
        CHECK(*iter == 5);
    }

    SUBCASE("begin")
    {
        MagicalContainer::PrimeIterator iter(container);
        CHECK(*iter == 3);
    }
}
