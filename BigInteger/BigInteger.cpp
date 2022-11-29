#include "BigInteger.h"

BigInteger::BigInteger() {
	data.push_back(0);
	minus = false;
}

BigInteger::BigInteger(const std::string& str) {
	if (str.empty()) {
		data.push_back(0);
		minus = false;
		return;
	}
	if (str[0] == '-') {
		minus = true;
	}
	for (int i = str.size(); i > minus; i -= LEN) {
		if (i < LEN) {
			data.push_back(stoi(str.substr(minus, i)));
		} else {
			data.push_back(stoi(str.substr(i - LEN, LEN)));
		}
	}
	trim();
}

BigInteger::BigInteger(const BigInteger& other) {
	data = other.data;
	minus = other.minus;
}

std::istream& operator>>(std::istream& in, BigInteger& a) {
	std::string str;
	in >> str;
	a = BigInteger(str);
	return in;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& a) {
	if (a.minus) {
		out << '-';
	}
	out << a.data.back();
	for (int i = a.data.size() - 2; i >= 0; i--) {
		out << std::setfill('0') << std::setw(a.LEN) << a.data[i];
	}
	return out;
}

const BigInteger BigInteger::operator-() const {
	BigInteger res = *this;
	res.minus = !minus;
	res.trim();
	return res;
}

bool operator<(const BigInteger& a, const BigInteger& b) {
	if (a.minus) {
		if (!b.minus) {
			return true;
		}
		return -b < -a;
	}
	if (b.minus) {
		return false;
	}
	if (a.data.size() != b.data.size()) {
		return a.data.size() < b.data.size();
	}
	for (int i = a.data.size() - 1; i >= 0; --i) {
		if (a.data[i] != b.data[i]) {
			return a.data[i] < b.data[i];
		}
	}
	return false;
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
	if (minus && !other.minus) {
		return *this = other - (-(*this));
	}
	if (!minus && other.minus) {
		return *this = *this - (-other);
	}
	if (minus && other.minus) {
		return *this = -(-(*this) + (-other));
	}

	int carry = 0;
	for (int i = 0; i < std::max(data.size(), other.data.size()) || carry; ++i) {
		if (i == data.size()) {
			data.push_back(0);
		}
		data[i] += (i < other.data.size() ? other.data[i] : 0) + carry;
		carry = data[i] / BASE;
		data[i] %= BASE;
	}
	return *this;
}

const BigInteger BigInteger::operator+(const BigInteger& other) const {
	BigInteger res = *this;
	res += other;
	return res;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
	if (other.minus) {
		return *this = *this + (-other);
	}
	if (minus) {
		return *this = other + (-(*this));
	}
	if (*this < other) {
		return *this = -(other - *this);
	}
	
	int carry = 0;
	for (int i = 0; i < std::max(data.size(), other.data.size()) || carry; ++i) {
		data[i] -= (i < other.data.size() ? other.data[i] : 0) + carry;
		carry = data[i] < 0;
		data[i] = (data[i] + BASE) % BASE;
	}

	return *this;
}

const BigInteger BigInteger::operator-(const BigInteger& other) const {
	BigInteger res = *this;
	res -= other;
	return res;
}

void BigInteger::trim() {
	while (data.size() > 1 && data.back() == 0) {
		data.pop_back();
	}
	if (data.size() == 1 && data[0] == 0) {
		minus = false;
	}
}
