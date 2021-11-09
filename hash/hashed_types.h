//
// Created by mateu on 09.11.2021.
//

#ifndef ALGORYTMY_2_HASHED_TYPES_H
#define ALGORYTMY_2_HASHED_TYPES_H

#include <string>
#include "../primes.h"
using namespace std;

struct Int32 {
    int32_t value;
    bool operator ==(const Int32 &s) const {
        return value == s.value;
    }
    bool operator !=(const Int32 &s) const {
        return value != s.value;
    }
};


struct Int64 { // long
    int64_t value;
    bool operator ==(const Int64 &s) const {
        return value == s.value;
    }
    bool operator !=(const Int64 &s) const {
        return value != s.value;
    }
};

struct String {
    string value;
    bool operator ==(const String &s) const {
        return value == s.value;
    }
    bool operator !=(const String &s) const {
        return value != s.value;
    }
};

struct Double {
    double value;
    bool operator ==(const Double &s) const {
        return value == s.value;
    }
    bool operator !=(const Double &s) const {
        return value != s.value;
    }
};

struct Struct {
    Int32 int_value;
    Double float_value;
    Int64 long_value;
};

template<>
struct std::hash<Int32> {
    std::size_t operator() (Int32 const & val) const noexcept {
        return static_cast<std::size_t>(val.value);
    };
};

template<>
struct std::hash<Int64> {
    std::size_t operator() (Int64 const & val) const noexcept {
        auto h = static_cast<size_t>(val.value);
        h ^= val.value >> 32;
        return h;
    };
};

template<>
struct std::hash<Double> {
    std::size_t operator() (Double const & val) const noexcept {
        auto casted =  static_cast<uint64_t>(val.value);
        size_t h = casted;
        h ^= casted >> 32;
        return h;
    };
};

template<>
struct std::hash<String> {
    std::size_t operator() (String const & val) const noexcept {
        size_t h;
        for (int i = 0; i < val.value.size(); ++i)
            h += (val.value[i] - 'a' + 1) * primes[i];
        return h;
    };
};

template<>
struct std::hash<Struct> {
    std::size_t operator() (Struct const &val) const noexcept {
        // naive
        return std::hash<Double>{}(val.float_value) ^ std::hash<Int32>{}(val.int_value) ^ std::hash<Int64>{}(val.long_value);
        // from stack overflow
        size_t result =  std::hash<Int64>{}(val.long_value) + 0x9e3779b9;
        result ^= std::hash<Int32>{}(val.int_value) + 0x9e3779b9 + (result << 6) + (result >> 2);
        result ^= std::hash<Double>{}(val.float_value) + 0x9e3779b9 + (result << 6) + (result >> 2);
        return result;
    }
};
#endif //ALGORYTMY_2_HASHED_TYPES_H
