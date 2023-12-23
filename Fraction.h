#pragma GCC optimize("Ofast,unroll-loops,mfma,mavx,mavx2")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("03")
#pragma once
#include "BigInt.h"
#include "MegaInt.h"

BigInt gcd(BigInt first_number, BigInt second_number) {
    if (first_number == 0ll) return second_number;
    return gcd(second_number%first_number, first_number);
}

class Fraction {
public:
    Fraction reducing(Fraction& f) {
        BigInt gd = gcd(f.num_, f.den_);
        f.num_ = f.num_/gd;
        f.den_ = f.den_/gd;
        if (!f.den_.sign) {
            f.num_.sign ^= true;
            f.den_.sign ^= true;
        }
        return f;
    }
    Fraction() {
        num_ = 0;
        den_ = 1;
    };
    Fraction(BigInt num, BigInt den) {
        if (den == 0) {
            throw std::overflow_error("Divide by zero exception");
        }
        num_ = num, den_ = den;
        reducing(*this);
    }
    explicit Fraction(BigInt num): num_(num), den_(1) {}

    Fraction(const Fraction& other) {
        num_ = other.num_;
        den_ = other.den_;
    };
    ~Fraction() = default;
    BigInt num() const {
        return num_;
    }
    BigInt den() const {
        return den_;
    }
    Fraction& operator=(Fraction other) {
        num_ = other.num_;
        den_ = other.den_;
        return *this;
    }
    Fraction operator-() {
        Fraction tmpp = *this;
        tmpp.num_ *= -1;
        return tmpp;
    }
    Fraction operator+() {
        return reducing(*this);
    }
    Fraction operator++() {
        num_ += den_;
        return reducing(*this);
    }
    Fraction operator++(int) {
        Fraction tmpp = *this;
        num_ += den_;
        reducing(*this);
        return tmpp;
    }
    Fraction operator--() {
        num_ -= den_;
        return reducing(*this);
    }
    Fraction operator--(int) {
        Fraction tmpp = *this;
        num_ -= den_;
        reducing(*this);
        return tmpp;
    }
    Fraction operator+(Fraction other) {
        BigInt tmpp = num_ * other.den_;
        other.num_ *= den_;
        other.den_ *= den_;
        other.num_ += tmpp;
        reducing(other);
        return other;
    }
    Fraction operator+(BigInt nn) {
        Fraction tmpp = *this;
        nn *= tmpp.den_;
        tmpp.num_ += nn;
        return reducing(tmpp);
    }
    Fraction operator+=(Fraction other) {
        *this = *this + other;
        return *this;
    }
    Fraction operator+=(BigInt nn) {
        *this = *this + nn;
        return *this;
    }
    Fraction operator-(Fraction other) {
        Fraction tmpp;
        tmpp.den_ = other.den_ * den_;
        tmpp.num_ = num_ * other.den_ - other.num_ * den_;
        return reducing(tmpp);
    }
    Fraction operator-(BigInt nn) {
        Fraction tmp = *this;
        nn *= tmp.den_;
        tmp.num_ -= nn;
        return reducing(tmp);
    }
    Fraction operator-=(Fraction other) {
        *this = *this - other;
        return *this;
    }
    Fraction operator-=(BigInt nn) {
        *this = *this - nn;
        return *this;
    }
    Fraction operator*(Fraction other) {
        other.num_ *= num_;
        other.den_ *= den_;
        return reducing(other);
    }
    Fraction operator*(BigInt nn) {
        Fraction tmpp = *this;
        tmpp.num_ *= nn;
        return reducing(tmpp);
    }
    Fraction operator*=(Fraction other) {
        *this = *this * other;
        return *this;
    }
    Fraction operator*=(BigInt nn) {
        *this = *this * nn;
        return *this;
    }
    Fraction operator/(Fraction other) {
        std::swap(other.num_, other.den_);
        other.num_ *= num_;
        other.den_ *= den_;
        return reducing(other);
    }
    Fraction operator/(BigInt nn) {
        Fraction tmpp = *this;
        tmpp.den_ *= nn;
        return reducing(tmpp);
    }
    Fraction operator/=(Fraction other) {
        *this = *this / other;
        return *this;
    }
    Fraction operator/=(BigInt nn) {
        *this = *this / nn;
        return *this;
    }
    bool operator<(Fraction other) {
        return num_*other.den_ < den_*other.num_;
    }
    bool operator>=(Fraction other) {
        return !(*this < other);
    }
    bool operator<=(Fraction other) {
        return *this < other || *this == other;
    }
    bool operator>(Fraction other) {
        return *this >= other && *this != other;
    }
    bool operator==(Fraction other) {
        return num_ == other.num_ && den_ == other.den_;
    }
    bool operator!=(Fraction other) {
        return !(*this == other);
    }
    bool operator<(BigInt nn) {
        return num_ < den_ * nn;
    }
    bool operator>=(BigInt nn) {
        return !(*this < nn);
    }
    bool operator<=(BigInt nn) {
        return *this < nn || *this == nn;
    }
    bool operator>(BigInt nn) {
        return *this >= nn && *this != nn;
    }
    bool operator==(BigInt nn) {
        return num_ == nn && den_ == 1;
    }
    bool operator!=(BigInt nn) {
        return !(*this == nn);
    }
    friend Fraction reducing(Fraction& f);
    friend Fraction operator+(BigInt first, Fraction second);
    friend Fraction operator-(BigInt first, Fraction second);
    friend Fraction operator*(BigInt first, Fraction second);
    friend Fraction operator/(BigInt first, Fraction second);
    friend Fraction operator+=(BigInt first, Fraction second);
    friend Fraction operator-=(BigInt first, Fraction second);
    friend Fraction operator*=(BigInt first, Fraction second);
    friend Fraction operator/=(BigInt first, Fraction second);
    friend bool operator<(BigInt first, Fraction second);
    friend bool operator>(BigInt first, Fraction second);
    friend bool operator<=(BigInt first, Fraction second);
    friend bool operator>=(BigInt first, Fraction second);
    friend bool operator==(BigInt first, Fraction second);
    friend bool operator!=(BigInt first, Fraction second);
    friend bool operator<(const Fraction& first, const Fraction& second);

    friend std::ostream& operator<<(std::ostream& out, const Fraction& fract);

//private:
    BigInt num_, den_;
};

Fraction reducing(Fraction& fr) {
    BigInt gd = gcd(fr.num_, fr.den_);
    fr.num_ = fr.num_/gd;
    fr.den_ = fr.den_/gd;
    if (!fr.den_.sign) {
        fr.num_.sign ^= true;
        fr.den_.sign ^= true;
    }
    return fr;
}

bool operator<(const Fraction& first, const Fraction& second) {
    return first.num_*second.den_ < second.num_*first.den_;
}

Fraction operator+(BigInt first, Fraction second) {
    first *= second.den_;
    second.num_ += first;
    return reducing(second);
}

Fraction operator-(BigInt first, Fraction second) {
    first *= second.den_;
    second.num_ -= first;
    return -reducing(second);
}

Fraction operator*(BigInt first, Fraction second) {
    second.num_ *= first;
    return reducing(second);
}

Fraction operator/(BigInt first, Fraction second) {
    std::swap(second.num_, second.den_);
    second.num_ *= first;
    return second;
}

Fraction operator+=(BigInt first, Fraction second) {
    second += first;
    return reducing(second);
}

Fraction operator-=(BigInt first, Fraction second) {
    second -= first;
    return reducing(second);
}

Fraction operator*=(BigInt first, Fraction second) {
    second *= first;
    return reducing(second);
}

Fraction operator/=(BigInt first, Fraction second) {
    second /= first;
    return reducing(second);
}

bool operator<(BigInt first, Fraction second) {
    return second > first;
}

bool operator>(BigInt first, Fraction second) {
    return second < first;
}

bool operator<=(BigInt first, Fraction second) {
    return second >= first;
}

bool operator>=(BigInt first, Fraction second) {
    return second >= first;
}

bool operator==(BigInt first, Fraction second) {
    return second == first;
}

bool operator!=(BigInt first, Fraction second) {
    return second != first;
}

std::ostream& operator<<(std::ostream& out, const Fraction& fract) {
    out << fract.num_ << '/' << fract.den_;
    return out;
}
