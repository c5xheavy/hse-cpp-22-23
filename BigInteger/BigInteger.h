#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

class BigInteger {
public:

    BigInteger();
    BigInteger(const std::string&);
    BigInteger(const BigInteger&);
	
    friend std::istream& operator>>(std::istream&, BigInteger&);
    friend std::ostream& operator<<(std::ostream&, const BigInteger&);

    const BigInteger operator-() const;
	
    friend bool operator<(const BigInteger&, const BigInteger&);

    BigInteger& operator+=(const BigInteger&);
    const BigInteger operator+(const BigInteger&) const;
    BigInteger& operator-=(const BigInteger&);
    const BigInteger operator-(const BigInteger&) const;

private:

    static const int BASE = 10000;
    static const int LEN = 4;

    std::vector<int> data;
    bool minus = false;

    void trim();
};
