#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <random>
#include <set>

struct Random {
  private:
    // Use xoshiro256**
    // References: http://xoshiro.di.unimi.it/xoshiro256starstar.c
    static uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

    std::array<uint64_t, 4> s;

    uint64_t next() {
        const uint64_t result_starstar = rotl(s[1] * 5, 7) * 9;

        const uint64_t t = s[1] << 17;

        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];

        s[2] ^= t;

        s[3] = rotl(s[3], 45);

        return result_starstar;
    }

    // random choice from [0, upper]
    uint64_t next(uint64_t upper) {
        if (!(upper & (upper + 1))) {
            // b = 00..0011..11
            return next() & upper;
        }
        int lg = 63 - __builtin_clzll(upper);
        uint64_t mask = (lg == 63) ? ~0ULL : (1ULL << (lg + 1)) - 1;
        while (true) {
            uint64_t r = next() & mask;
            if (r <= upper)
                return r;
        }
    }

  public:
    Random(uint64_t seed = 0) {
        // Use splitmix64
        // Reference: http://xoshiro.di.unimi.it/splitmix64.c
        for (int i = 0; i < 4; i++) {
            uint64_t z = (seed += 0x9e3779b97f4a7c15);
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            s[i] = z ^ (z >> 31);
        }
    }

    // random choice from [lower, upper]
    template <class T>
    T uniform(T lower, T upper) {
        assert(lower <= upper);
        return T(lower + next(uint64_t(upper - lower)));
    }

    // random choice from false or true
    bool uniform_bool() { return uniform(0, 1) == 1; }

    // random choice from [0.0, 1.0]
    double uniform01() {
        uint64_t v = next(1ULL << 63);
        return double(v) / (1ULL << 63);
    }

    // random choice non-empty sub-interval from interval [lower, upper)
    // equal: random choice 2 disjoint elements from [lower, upper]
    template <class T>
    std::pair<T, T> uniform_pair(T lower, T upper) {
        assert(upper - lower >= 1);
        T a, b;
        do {
            a = uniform(lower, upper);
            b = uniform(lower, upper);
        } while (a == b);
        if (a > b) std::swap(a, b);
        return {a, b};
    }

    // generate random lower string that length = n
    std::string lower_string(size_t n) {
        std::string res = "";
        for (size_t i = 0; i < n; i++) {
            res += uniform('a', 'z');
        }
        return res;
    }

    // random shuffle
    template <class Iter>
    void shuffle(Iter first, Iter last) {
        if (first == last) return;
        // Reference and edit:
        // cpprefjp - C++日本語リファレンス
        // (https://cpprefjp.github.io/reference/algorithm/shuffle.html)
        int len = 1;
        for (auto it = first + 1; it != last; it++) {
            len++;
            int j = uniform(0, len - 1);
            if (j != len - 1)
                iter_swap(it, first + j);
        }
    }

    // generate random permutation that length = n
    template <class T>
    std::vector<T> perm(size_t n) {
        std::vector<T> idx(n);
        std::iota(idx.begin(), idx.end(), T(0));
        shuffle(idx.begin(), idx.end());
        return idx;
    }

    // random choise n elements from [lower, upper]
    template <class T>
    std::vector<T> choice(size_t n, T lower, T upper) {
        assert(T(n) <= upper - lower + 1);
        std::set<T> res;
        while (res.size() < n) res.insert(uniform(lower, upper));
        return {res.begin(), res.end()};
    }

    template <class T>
    std::vector<std::pair<T, T>> tree(size_t n, bool base = false) {
        std::vector<T> perm = this->perm<T>(n);
        if (base)
            for (size_t i = 0; i < n; i++) perm[i] += 1;
        std::vector<std::pair<T, T>> edges;
        for (size_t i = 1; i < n; i++) {
            edges.emplace_back(perm[i], perm[uniform<size_t>(0, i - 1)]);
        }
        return edges;
    }

    template <class T>
    std::vector<std::pair<T, T>> binary_perfect_tree(size_t n, bool base = false) {
        std::vector<T> perm = this->perm<T>(n);
        if (base)
            for (size_t i = 0; i < n; i++) perm[i] += 1;
        std::vector<std::pair<T, T>> edges;
        for (size_t i = 2; i <= n; ++i)
            edges.emplace_back(perm[i - 1], perm[i / 2 - 1]);
        return edges;
    }

    template <class T>
    std::vector<T> gen_sum(T sum, int t, int lower = 1, int upper = 0) {
        assert(t * lower <= sum);
        assert(upper == 0 or sum <= t * upper);
        // Gen x1 + x2 + ... + xt = sum
        // lower <= xi <= upper
        std::vector<T> res(t, lower);
        sum -= t * lower;
        for (int i = 0; i < sum; ++i) {
            int idx = uniform(0, t - 1);
            if (res[idx] == upper) {
                i--;
                continue;
            }
            res[idx] ++;
        }
        return res;
    }

} global_gen;

