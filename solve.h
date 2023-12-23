#pragma GCC optimize("Ofast,unroll-loops,mfma,mavx,mavx2")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("03")
#pragma once
#include "Fraction.h"
#include "MegaFraction.h"

BigInt power(BigInt n, BigInt k) {
    if (k == 0) return 1;
    if (k % 2 == 0) return power(n * n, k/2);
    return n * power(n, k - 1);
}

MegaInt megapower(MegaInt n, MegaInt k) {
    if (k == 0) return 1;
    if (k % 2 == 0) return megapower(n * n, k/2);
    return n * megapower(n, k - 1);
}

std::string intTOstr(int64_t a) {
    std::string ans;
    while (a) {
        ans.push_back(a % 10 + '0');
        a /= 10;
    }
    if (ans.empty()) {
        ans = "0";
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

int getsize(std::string s) {
    int ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '[') {
            ++ans;
            while (s[i] != ']') {
                ++i;
            }
        } else {
            ans += (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'A' && s[i] <= 'Z');
        }
    }
    return ans;
}

std::string solve(std::string integer, std::string predper, std::string per, int p, int q) {
    if (std::max(std::max(integer.size()*3, predper.size()*3), per.size()*3) > 75) {
        std::string ret;
        MegaInt a(integer, p);
        int b_getsize = getsize(predper);
        MegaInt b(predper, p);
        int c_getsize = getsize(per);
        MegaInt c(per, p);
        MegaFraction x(a);
        MegaFraction y(b, megapower(p, b_getsize));
        MegaInt rr = megapower(p, b_getsize) * (megapower(p, c_getsize) - 1);
        if (rr == 0) rr = 1;
        MegaFraction z(c, rr);
        x += y+z;
        a = x.num_/x.den_;
        x -= a;
        std::vector<long long> ans;
        while (a != 0) {
            ans.push_back(a%q);
            a /= q;
        }
        std::reverse(ans.begin(), ans.end());
        if ((int)ans.size() == 0) {
            ret += "0";
        }
        for (auto e : ans) {
            if (e >= 10 && e <= 'Z'-'A'+10) {
                char tmp = 'A'+e-10;
                ret.push_back(tmp);
            } else if (e > 'Z'-'A'+10) {
                ret += "[" + intTOstr(e) + "]";
            } else {
                ret += intTOstr(e);
            }
        }
        std::map<MegaFraction, int> map;
        int i = 1;
        int r = -5;
        ans.resize(0);
        while (true) {
            if (x == 0) {
                break;
            }
            if (map[x] != 0) {
                r = map[x]-1;
                break;
            }
            map[x] = i;
            x *= q;
            a = x.num_/x.den_;
            x -= a;
            ans.push_back(a%(q*q));
            ++i;
        }
        if (!ans.empty()) {
            ret += '.';
        }
        i = 0;
        for (auto e : ans) {
            if (r == i && r != -5) {
                ret += '(';
            }
            if (e >= 10 && e <= 'Z'-'A'+10) {
                char tmp = 'A'+e-10;
                ret += tmp;
            } else if (e > 'Z'-'A'+10) {
                ret += + "[" + intTOstr(e) + "]";
            } else {
                ret += intTOstr(e);
            }
            ++i;
        }
        if (r != -5) {
            ret += ')';
        }
        return ret;
    } else  {
        std::string ret;
        BigInt a(integer, p);
        int b_getsize = getsize(predper);
        BigInt b(predper, p);
        int c_getsize = getsize(per);
        BigInt c(per, p);
        Fraction x(a);
        Fraction y(b, power(p, b_getsize));
        BigInt rr = power(p, b_getsize) * (power(p, c_getsize) - 1);
        if (rr == 0) rr = 1;
        Fraction z(c, rr);
        x += y+z;
        a = x.num_/x.den_;
        x -= a;
        std::vector<long long> ans;
        while (a != 0) {
            ans.push_back(a%q);
            a /= q;
        }
        std::reverse(ans.begin(), ans.end());
        if ((int)ans.size() == 0) {
            ret += "0";
        }
        for (auto e : ans) {
            if (e >= 10 && e <= 'Z'-'A'+10) {
                char tmp = 'A'+e-10;
                ret.push_back(tmp);
            } else if (e > 'Z'-'A'+10) {
                ret += "[" + intTOstr(e) + "]";
            } else {
                ret += intTOstr(e);
            }
        }
        std::map<Fraction, int> map;
        int i = 1;
        int r = -5;
        ans.resize(0);
        while (true) {
            if (x == 0) {
                break;
            }
            if (map[x] != 0) {
                r = map[x]-1;
                break;
            }
            map[x] = i;
            x *= q;
            a = x.num_/x.den_;
            x -= a;
            ans.push_back(a%(q*q));
            ++i;
        }
        if (!ans.empty()) {
            ret += '.';
        }
        i = 0;
        for (auto e : ans) {
            if (r == i && r != -5) {
                ret += '(';
            }
            if (e >= 10 && e <= 'Z'-'A'+10) {
                char tmp = 'A'+e-10;
                ret += tmp;
            } else if (e > 'Z'-'A'+10) {
                ret += + "[" + intTOstr(e) + "]";
            } else {
                ret += intTOstr(e);
            }
            ++i;
        }
        if (r != -5) {
            ret += ')';
        }
        return ret;
    }
}