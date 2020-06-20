#ifndef HARD_H
#define HARD_H

#include <iostream>

struct hard {
    int m_fa;
    int m_fi;

    hard(int fa, int fi) : m_fa(fa), m_fi(fi) {};
    hard() = default;

    friend std::ostream& operator<<(std::ostream& os, const hard& obj)
    {
        os << obj.m_fa << " | " << obj.m_fi;
        return os;
    }
    hard(const hard& other) = delete;
    hard(hard&& other) noexcept = delete;
};

#endif // HARD_H
