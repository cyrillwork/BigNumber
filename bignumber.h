#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>

/**
@brief Class for working with big numbers
*/
class BigNumber
{
public:

    using numType = unsigned char;

    enum class NumbSystem
    {
        DEC = 0,
        BIN,
        HEX
    };

    BigNumber() = default;

    BigNumber(const std::string& str1, NumbSystem system = NumbSystem::DEC);

    BigNumber(int numb);

    BigNumber(const BigNumber &v1);

    BigNumber(int *b1, int c);

    BigNumber(BigNumber && b) { swap(b); }

    ~BigNumber();

    void setData(const numType *ptr, int len);

    void setString(char *str1);

    std::string getDecString() const;

    std::string getBinString() const;

    std::string getHexString() const;

    void print() const;

    int size() const noexcept { return count_num; }

    BigNumber& operator*(const BigNumber &v1);

    BigNumber& operator=(const BigNumber &v1);

    BigNumber& operator=(BigNumber && b)
    {
        swap(b);
        return *this;
    }

    BigNumber& operator^(int range);

    BigNumber::numType& operator[] (int i)
    {
        return (*pNumber)[i];
    }

    const BigNumber::numType& operator[] (int i) const
    {
        return (*pNumber)[i];
    }

    void swap(BigNumber &b) noexcept
    {
        std::swap(count_num, b.count_num);
        std::swap(pNumber, b.pNumber);
    }

    const BigNumber & operator ++ ();
    const BigNumber operator ++ (int);

    const BigNumber& operator += (const BigNumber &v1);


    friend bool operator < (const BigNumber &v1, const BigNumber &v2);
    friend bool operator > (const BigNumber &v1, const BigNumber &v2);
    friend bool operator == (const BigNumber &v1, const BigNumber &v2);
    friend bool operator != (const BigNumber &v1, const BigNumber &v2);
    friend bool operator >= (const BigNumber &v1, const BigNumber &v2);
    friend bool operator <= (const BigNumber &v1, const BigNumber &v2);

    friend BigNumber operator+(const BigNumber &v1, const BigNumber &v2);

    friend BigNumber operator/(const BigNumber &v1, const int &n);

    friend std::ostream& operator << (std::ostream &s, const BigNumber &b);

    friend int operator%(const BigNumber &v1, const int &n);

    void setPrintFormat(const NumbSystem&value);

private:
    int count_num{0};
    //numType *pNumber = nullptr;
    std::shared_ptr<std::vector<numType>> pNumber;

    NumbSystem printFormat = NumbSystem::DEC;
};



#endif // BIGNUMBER_H
