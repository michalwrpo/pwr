#ifndef GAUSS_HPP
#define GAUSS_HPP

#include <iostream>
#include <vector>

struct Gauss {
    int re{};
    int im{};

    Gauss& operator=(int z);
};

constexpr Gauss i {0, 1};

namespace Gaussian {
    int norm(Gauss z);
    std::vector<std::pair<Gauss, Gauss>> allDivisions(Gauss w, Gauss z);
    std::vector<Gauss> gcd(Gauss w, Gauss z);
    std::vector<Gauss> gcd(std::vector<Gauss> v);
    std::vector<Gauss> lcm(Gauss w, Gauss z);
    std::vector<Gauss> lcm(std::vector<Gauss> v);

}

Gauss operator-(Gauss z);
Gauss operator+(Gauss z);

Gauss operator+(Gauss w, Gauss z);
Gauss operator-(Gauss w, Gauss z);
Gauss operator*(Gauss w, Gauss z);
Gauss operator/(Gauss w, Gauss z);
Gauss operator%(Gauss w, Gauss z);

Gauss operator+(int w, Gauss z);
Gauss operator-(int w, Gauss z);
Gauss operator*(int w, Gauss z);
Gauss operator/(int w, Gauss z);
Gauss operator%(int w, Gauss z);

Gauss operator+(Gauss w, int z);
Gauss operator-(Gauss w, int z);
Gauss operator*(Gauss w, int z);
Gauss operator/(Gauss w, int z);
Gauss operator%(Gauss w, int z);

bool operator==(Gauss w, int z);
bool operator==(int w, Gauss z);

Gauss& operator+=(Gauss& w, Gauss z);
Gauss& operator+=(Gauss& w, int z);
Gauss& operator-=(Gauss& w, Gauss z);
Gauss& operator-=(Gauss& w, int z);
Gauss& operator*=(Gauss& w, Gauss z);
Gauss& operator*=(Gauss& w, int z);
Gauss& operator/=(Gauss& w, Gauss z);
Gauss& operator/=(Gauss& w, int z);
Gauss& operator%=(Gauss& w, Gauss z);
Gauss& operator%=(Gauss& w, int z);

std::ostream& operator<<(std::ostream& out, Gauss z);

#endif // GAUSS_HPP