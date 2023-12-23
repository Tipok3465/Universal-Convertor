#pragma GCC optimize("Ofast,unroll-loops,mfma,mavx,mavx2")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("03")
#pragma once
#include "BigInt.h"
#include "MegaInt.h"

MegaInt gcd(MegaInt first_number, MegaInt second_number) {
    if (first_number == 0ll) return second_number;
    return gcd(second_number%first_number, first_number);
}

class MegaFraction {
public:
    MegaFraction reducing(MegaFraction& f) {
        MegaInt gd = gcd(f.num_, f.den_);
        f.num_ = f.num_/gd;
        f.den_ = f.den_/gd;
        if (!f.den_.sign) {
            f.num_.sign ^= true;
            f.den_.sign ^= true;
        }
        return f;
    }
    MegaFraction() {
        num_ = 0;
        den_ = 1;
    };
    MegaFraction(MegaInt num, MegaInt den) {
        if (den == 0) {
            throw std::overflow_error("Divide by zero exception");
        }
        num_ = num, den_ = den;
        reducing(*this);
    }
    explicit MegaFraction(MegaInt num): num_(num), den_(1) {}

    MegaFraction(const MegaFraction& other) {
        num_ = other.num_;
        den_ = other.den_;
    };
    ~MegaFraction() = default;
    MegaInt num() const {
        return num_;
    }
    MegaInt den() const {
        return den_;
    }
    MegaFraction& operator=(MegaFraction other) {
        num_ = other.num_;
        den_ = other.den_;
        return *this;
    }
    MegaFraction operator-() {
        MegaFraction tmpp = *this;
        tmpp.num_ *= -1;
        return tmpp;
    }
    MegaFraction operator+() {
        return reducing(*this);
    }
    MegaFraction operator++() {
        num_ += den_;
        return reducing(*this);
    }
    MegaFraction operator++(int) {
        MegaFraction tmpp = *this;
        num_ += den_;
        reducing(*this);
        return tmpp;
    }
    MegaFraction operator--() {
        num_ -= den_;
        return reducing(*this);
    }
    MegaFraction operator--(int) {
        MegaFraction tmpp = *this;
        num_ -= den_;
        reducing(*this);
        return tmpp;
    }
    MegaFraction operator+(MegaFraction other) {
        MegaInt tmpp = num_ * other.den_;
        other.num_ *= den_;
        other.den_ *= den_;
        other.num_ += tmpp;
        reducing(other);
        return other;
    }
    MegaFraction operator+(MegaInt nn) {
        MegaFraction tmpp = *this;
        nn *= tmpp.den_;
        tmpp.num_ += nn;
        return reducing(tmpp);
    }
    MegaFraction operator+=(MegaFraction other) {
        *this = *this + other;
        return *this;
    }
    MegaFraction operator+=(MegaInt nn) {
        *this = *this + nn;
        return *this;
    }
    MegaFraction operator-(MegaFraction other) {
        MegaFraction tmpp;
        tmpp.den_ = other.den_ * den_;
        tmpp.num_ = num_ * other.den_ - other.num_ * den_;
        return reducing(tmpp);
    }
    MegaFraction operator-(MegaInt nn) {
        MegaFraction tmp = *this;
        nn *= tmp.den_;
        tmp.num_ -= nn;
        return reducing(tmp);
    }
    MegaFraction operator-=(MegaFraction other) {
        *this = *this - other;
        return *this;
    }
    MegaFraction operator-=(MegaInt nn) {
        *this = *this - nn;
        return *this;
    }
    MegaFraction operator*(MegaFraction other) {
        other.num_ *= num_;
        other.den_ *= den_;
        return reducing(other);
    }
    MegaFraction operator*(MegaInt nn) {
        MegaFraction tmpp = *this;
        tmpp.num_ *= nn;
        return reducing(tmpp);
    }
    MegaFraction operator*=(MegaFraction other) {
        *this = *this * other;
        return *this;
    }
    MegaFraction operator*=(MegaInt nn) {
        *this = *this * nn;
        return *this;
    }
    MegaFraction operator/(MegaFraction other) {
        std::swap(other.num_, other.den_);
        other.num_ *= num_;
        other.den_ *= den_;
        return reducing(other);
    }
    MegaFraction operator/(MegaInt nn) {
        MegaFraction tmpp = *this;
        tmpp.den_ *= nn;
        return reducing(tmpp);
    }
    MegaFraction operator/=(MegaFraction other) {
        *this = *this / other;
        return *this;
    }
    MegaFraction operator/=(MegaInt nn) {
        *this = *this / nn;
        return *this;
    }
    bool operator<(MegaFraction other) {
        return num_*other.den_ < den_*other.num_;
    }
    bool operator>=(MegaFraction other) {
        return !(*this < other);
    }
    bool operator<=(MegaFraction other) {
        return *this < other || *this == other;
    }
    bool operator>(MegaFraction other) {
        return *this >= other && *this != other;
    }
    bool operator==(MegaFraction other) {
        return num_ == other.num_ && den_ == other.den_;
    }
    bool operator!=(MegaFraction other) {
        return !(*this == other);
    }
    bool operator<(MegaInt nn) {
        return num_ < den_ * nn;
    }
    bool operator>=(MegaInt nn) {
        return !(*this < nn);
    }
    bool operator<=(MegaInt nn) {
        return *this < nn || *this == nn;
    }
    bool operator>(MegaInt nn) {
        return *this >= nn && *this != nn;
    }
    bool operator==(MegaInt nn) {
        return num_ == nn && den_ == 1;
    }
    bool operator!=(MegaInt nn) {
        return !(*this == nn);
    }
    friend MegaFraction reducing(MegaFraction& f);
    friend MegaFraction operator+(MegaInt first, MegaFraction second);
    friend MegaFraction operator-(MegaInt first, MegaFraction second);
    friend MegaFraction operator*(MegaInt first, MegaFraction second);
    friend MegaFraction operator/(MegaInt first, MegaFraction second);
    friend MegaFraction operator+=(MegaInt first, MegaFraction second);
    friend MegaFraction operator-=(MegaInt first, MegaFraction second);
    friend MegaFraction operator*=(MegaInt first, MegaFraction second);
    friend MegaFraction operator/=(MegaInt first, MegaFraction second);
    friend bool operator<(MegaInt first, MegaFraction second);
    friend bool operator>(MegaInt first, MegaFraction second);
    friend bool operator<=(MegaInt first, MegaFraction second);
    friend bool operator>=(MegaInt first, MegaFraction second);
    friend bool operator==(MegaInt first, MegaFraction second);
    friend bool operator!=(MegaInt first, MegaFraction second);
    friend bool operator<(const MegaFraction& first, const MegaFraction& second);

    friend std::ostream& operator<<(std::ostream& out, const MegaFraction& fract);

//private:
    MegaInt num_, den_;
};

MegaFraction reducing(MegaFraction& fr) {
    MegaInt gd = gcd(fr.num_, fr.den_);
    fr.num_ = fr.num_/gd;
    fr.den_ = fr.den_/gd;
    if (!fr.den_.sign) {
        fr.num_.sign ^= true;
        fr.den_.sign ^= true;
    }
    return fr;
}

bool operator<(const MegaFraction& first, const MegaFraction& second) {
    return first.num_*second.den_ < second.num_*first.den_;
}

MegaFraction operator+(MegaInt first, MegaFraction second) {
    first *= second.den_;
    second.num_ += first;
    return reducing(second);
}

MegaFraction operator-(MegaInt first, MegaFraction second) {
    first *= second.den_;
    second.num_ -= first;
    return -reducing(second);
}

MegaFraction operator*(MegaInt first, MegaFraction second) {
    second.num_ *= first;
    return reducing(second);
}

MegaFraction operator/(MegaInt first, MegaFraction second) {
    std::swap(second.num_, second.den_);
    second.num_ *= first;
    return second;
}

MegaFraction operator+=(MegaInt first, MegaFraction second) {
    second += first;
    return reducing(second);
}

MegaFraction operator-=(MegaInt first, MegaFraction second) {
    second -= first;
    return reducing(second);
}

MegaFraction operator*=(MegaInt first, MegaFraction second) {
    second *= first;
    return reducing(second);
}

MegaFraction operator/=(MegaInt first, MegaFraction second) {
    second /= first;
    return reducing(second);
}

bool operator<(MegaInt first, MegaFraction second) {
    return second > first;
}

bool operator>(MegaInt first, MegaFraction second) {
    return second < first;
}

bool operator<=(MegaInt first, MegaFraction second) {
    return second >= first;
}

bool operator>=(MegaInt first, MegaFraction second) {
    return second >= first;
}

bool operator==(MegaInt first, MegaFraction second) {
    return second == first;
}

bool operator!=(MegaInt first, MegaFraction second) {
    return second != first;
}

std::ostream& operator<<(std::ostream& out, const MegaFraction& fract) {
    out << fract.num_ << '/' << fract.den_;
    return out;
}
