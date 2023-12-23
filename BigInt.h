#pragma GCC optimize("Ofast,unroll-loops,mfma,mavx,mavx2")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("03")
#pragma once
#include "header.h"

struct BigInt {
    static const long long base_ = 10;
    static const long long size_ = 75;
    int digits[size_];
    bool sign;

    BigInt() {
        sign = true;
        for (int i = 0; i < size_; i++) {
            digits[i] = 0;
        }
    }
    BigInt(long long x) {
        sign = x >= 0;
        if (!sign) {
            x *= -1;
        }
        for (int i = 0; i < size_; i++) {
            digits[i] = 0;
        }

        int next = 0;
        while (x) {
            digits[next++] = x % base_;
            x /= base_;
        }
    }

    BigInt(std::string x) {
        sign = x[0] != '-';
        for (int i = 0; i < size_; ++i) {
            digits[i] = 0;
        }
        int next = 0;
        while (!x.empty() && x.back() != '-') {
            digits[next++] = x.back()-'0';
            x.pop_back();
        }
    }

    BigInt(std::string s, int p) {
        for (int i = 0; i < size_; ++i) {
            digits[i] = 0;
        }
        std::reverse(s.begin(), s.end());
        sign = s.back() != '-';
        if (!sign) {
            s.pop_back();
        }
        while (!s.empty()) {
            *this *= p;
            if (s.back() >='A' && s.back() <='Z') {
                *this += s.back() - 'A' + 10;
            } else if (s.back() == '[') {
                int tmp = 0;
                s.pop_back();
                while (s.back() != ']') {
                    tmp *= 10;
                    tmp += s.back()-'0';
                    s.pop_back();
                }
                *this += tmp;
            } else {
                *this += s.back() - '0';
            }
            s.pop_back();
        }
    }

    BigInt(const BigInt& other) {
        sign = other.sign;
        for (int i = 0; i < other.size_; i++) {
            digits[i] = other.digits[i];
        }
    }

    BigInt& operator=(const BigInt& other) {
        sign = other.sign;
        for (int i = 0; i < size_; i++) {
            digits[i] = other.digits[i];
        }

        return *this;
    }
    bool operator<(const BigInt& other) {
        for (int i = size_-1; i >= 0; --i) {
            if (digits[i] != other.digits[i]) {
                return digits[i] < other.digits[i];
            }
        }
        return false;
    }
    void operator+=(const BigInt& other) {
        for (int i = 0; i < size_; i++)  {
            digits[i] += other.digits[i];
        }

        for (int i = 0; i < size_ - 1; i++) {
            if (digits[i] >= base_) {
                digits[i] -= base_;
                digits[i + 1]++;
            }
        }
    }

    void operator+=(int other) {
        for (int i = 0; i < size_; i++) {
            digits[i] += other % base_;
            other /= base_;
        }

        for (int i = 0; i < size_ - 1; i++) {
            if (digits[i] >= base_) {
                digits[i] -= base_;
                digits[i + 1]++;
            }
        }
    }

    BigInt operator+(const BigInt& other) {
        BigInt n(*this);
        n += other;
        return n;
    }

    BigInt& operator++() {
        *this += 1;
        return *this;
    }

    void operator-=(const BigInt& other) {
        for (int i = 0; i < size_; i++) {
            digits[i] -= other.digits[i];
        }

        for (int i = 0; i < size_ - 1; i++) {
            if (digits[i] < 0) {
                digits[i] += base_;
                digits[i + 1]--;
            }
        }
    }

    BigInt operator-(const BigInt& other) {
        BigInt n(*this);
        n -= other;
        return n;
    }

    BigInt& operator--() {
        *this -= 1;
        return *this;
    }

    void operator*=(const BigInt& other) {
        *this = *this * other;
    }

    void operator*=(int x) {
        *this = *this * x;
    }

    BigInt operator*(const BigInt& other)  {
        BigInt result;
        result.sign = sign ^ other.sign;
        for (int i = 0; i < size_; i++) {
            for (int j = 0; j < other.size_ - i; j++) {
                result.digits[i + j] += digits[i] * other.digits[j];
            }
        }
        for (int i = 0; i < size_ - 1; i++) {
            result.digits[i + 1] += result.digits[i] / base_;
            result.digits[i] %= base_;
        }
        return result;
    }

    BigInt operator*(long long x) {
        BigInt result;
        for (long long i = 0; i < x; ++i) {
            result += *this;
        }
        return result;
    }

    void operator/=(long long x) {
        for (int i = size_ - 1; i >= 0; i--) {
            if (i) {
                digits[i - 1] += (digits[i] % x) * base_;
            }
            digits[i] /= x;
        }
    }

    BigInt operator/(long long x) {
        BigInt n(*this);
        n /= x;
        return n;
    }

    BigInt operator/(const BigInt& x) {
        std::string INF(size_-1, '9');
        BigInt l = 0;
        BigInt r = INF;
        while (r-l-1 != 0) {
            BigInt m = (r + l) / 2;
            if (!(*this < m*x)) {
                l = m;
            } else {
                r = m;
            }
        }
        return l;
    }

    BigInt operator/=(const BigInt& x) {
        *this = *this/x;
        return *this;
    }

    long long operator%(long long x) {
        BigInt t = *this - (*this / x) * x;
        long long ans = 0;
        for (int i = size_-1; i >= 0; --i) {
            ans *= 10;
            ans += t.digits[i];
        }
        return ans;
    }

    BigInt operator%(const BigInt& x) {
        BigInt t = *this - (*this / x) * x;
        BigInt ans = 0;
        for (int i = size_-1; i >= 0; --i) {
            ans *= 10;
            ans += t.digits[i];
        }
        return ans;
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& x);

    bool operator ==(const BigInt& other) {
        if (size_ != other.size_) return false;
        for (int i = 0; i < size_; ++i) {
            if (other.digits[i] != digits[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator !=(const BigInt& other) {
        return !(*this == other);
    }
    bool operator ==(long long x) {
        BigInt y = x;
        return y == *this;
    }
    bool operator !=(long long x) {
        return !(*this == x);
    }
};

BigInt operator*(const BigInt& first, const BigInt& second) {
    BigInt result;
    for (int i = 0; i < first.size_; i++) {
        for (int j = 0; j < first.size_ - i; j++) {
            result.digits[i + j] += first.digits[i] * second.digits[j];
        }
    }
    for (int i = 0; i < first.size_ - 1; i++) {
        result.digits[i + 1] += result.digits[i] / first.base_;
        result.digits[i] %= first.base_;
    }

    return result;
}

std::ostream& operator<<(std::ostream& out, const BigInt& x) {
    bool flag = false;
    if (!x.sign) {
        std::cout << '-';
    }
    for (int i = x.size_-1; i >= 0; --i) {
        flag |= x.digits[i];
        if (flag) {
            out << x.digits[i];
        }
    }
    if (!flag) {
        out << '0';
    }
    return out;
}
