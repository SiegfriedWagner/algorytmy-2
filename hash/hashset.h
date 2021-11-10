//
// Created by mateu on 09.11.2021.
//

#ifndef ALGORYTMY_2_HASHSET_H
#define ALGORYTMY_2_HASHSET_H

#include <vector>
#include <array>
#include <cassert>
#include <iostream>
#include "../primes.h"

using namespace std;

// closed hashing
template<typename T>
class HashSet {
private:
    vector<T> elements;
    vector<bool> filled_spots;
    size_t count_;
    size_t conflicts_count_;
    bool low_water_mark;
    bool high_water_mark;
    uint8_t primes_spot;

    void resize(bool increase_size) {
        if (increase_size && primes_spot == primes.size() - 1 || !increase_size && primes_spot == 0) {
            high_water_mark = false;
            low_water_mark = false;
            return;
        }
        // create new vector and rehash all values
        vector<T> new_elements(increase_size ? primes[++primes_spot] : primes[--primes_spot]);
        vector<bool> new_filled_spots(primes[primes_spot]);
        size_t new_conflicts_count = 0;
        size_t new_count = 0;
        int i = 0;
        while (count_ > 0) {
            if (filled_spots[i]) {
                insert_internal(elements[i], new_elements, new_filled_spots, new_conflicts_count, new_count);
                count_--;
            }
            i++;
        }
        count_ = new_count;
        conflicts_count_ = new_conflicts_count;
        elements = new_elements;
        filled_spots = new_filled_spots;
        high_water_mark = false;
        low_water_mark = false;
    };

    bool highWaterCheck() {
        return count_ == elements.size() || conflicts_count_ > 0 && (float) count_ / elements.size() > 0.75f;
    }

    bool lowWaterCheck() {
        return (float) count_ / elements.size() < 0.25f;
    }

    void rehash(uint32_t emptied_spot) {
        if (count_ == elements.size()) return; // don't rehash full set
        // check spot behind just emptied spot
        auto to_check = (emptied_spot + 1) % elements.size();
        while(filled_spots[to_check]) {
            auto true_hash = hash<T>{}(elements[to_check]) % elements.size();
            if (true_hash == emptied_spot) {
                filled_spots[emptied_spot] = true;
                elements[emptied_spot] = elements[to_check];
                elements[to_check] = {};
                filled_spots[to_check] = false;
                emptied_spot = to_check;
            }
            to_check = (to_check + 1) % elements.size();
        }
    }

    static void
    insert_internal(const T &element, vector<T> &collection, vector<bool> &filled_spots, size_t &conflicts_count,
                    size_t &filled_spots_count) {
        assert(filled_spots_count <= collection.size());
        assert(collection.size() == filled_spots.size());
        auto key = hash<T>{}(element) % collection.size();
        bool has_conflict = false;
        while (filled_spots[key]) {
            if (collection[key] == element) // object already in set
                return;
            key = (key + 1) % collection.size();
            has_conflict = true;
        }
        filled_spots[key] = true;
        collection[key] = element;
        if (has_conflict)
            conflicts_count++;
        filled_spots_count++;
    }

public:
    HashSet() : elements(primes[0]), filled_spots(primes[0]), count_(0), low_water_mark(false), high_water_mark(false),
                primes_spot(0) {}

    void insert(const T &element) {
        if (high_water_mark)
            resize(true);
        insert_internal(element, elements, filled_spots, conflicts_count_, count_);
        high_water_mark = highWaterCheck();
        low_water_mark = false;
    };

    void remove(const T &element) {
        if (low_water_mark)
            resize(false);
        auto baseKey = hash<T>{}(element) % elements.size();
        auto key = baseKey;
        while (filled_spots[key]) {
            if (elements[key] == element) {
                filled_spots[key] = false;
                elements[key] = {};
                count_--;
                low_water_mark = lowWaterCheck();
                high_water_mark = false;
                rehash(key);
                break;
            }
            key = (key + 1) % elements.size();
        }
    }

    bool contains(const T &element) const {
        auto baseKey = hash<T>{}(element) % elements.size();
        auto key = baseKey;
        while (filled_spots[key]) {
            if (elements[key] == element)
                return true;
            key = (key + 1) % elements.size();
            if (key == baseKey)
                return false;
        }
        return false;
    };

    inline size_t count() const {
        return count_;
    }

    inline size_t conflicts_count() const {
        return conflicts_count_;
    }

    void print() {
        cout << "Number of conflicts:" << conflicts_count_ << " total size: " << elements.size() << " elements count: "
             << count_ << endl;
        for (int i = 0; i < elements.size(); ++i) {
            if (filled_spots[i])
                cout << elements[i] << endl;
        }
    }

    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T *;
        using referece = const T &;


        static Iterator Begin(HashSet<T> const *ptr) {
            Iterator begin(ptr);
            uintptr_t i = 0;
            for (; i < begin.set_ptr->filled_spots.size(); ++i)
                if (begin.set_ptr->filled_spots[i]) {
                    break;
                }
            begin.current_pos = i;
            begin.current = begin.set_ptr->elements.data() + i;
            return begin;
        }
        static Iterator End(HashSet<T> const *ptr) {
            Iterator end(ptr);
            // find first filled spot starting from end
            for (size_t i = ptr->filled_spots.size() - 1; i >= 0; --i)
                if (ptr->filled_spots[i]) {
                    end.current = (pointer) (ptr->elements.data() + i + 1);
                    end.current_pos = i + 1;
                    return end;
                }
        }

        referece operator*() const { return *current; }

        pointer operator->() { return current; };

        Iterator &operator++() {
            moveForward();
            return *this;
        }

        Iterator &operator++(int) {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator &a, const Iterator &b) { return a.current == b.current; };

        friend bool operator!=(const Iterator &a, const Iterator &b) { return a.current != b.current; };

    private:
        pointer current;
        size_t current_pos;
        const HashSet<T> *set_ptr; // TODO: Try to avoid naked pointer
        Iterator(HashSet<T> const *ptr) : current(nullptr), current_pos(0),
                                          set_ptr(ptr) { // TODO: consider if passing raw pointer is harmful
        }
        void moveForward() {
            if (current_pos >= set_ptr->filled_spots.size()) {
                current_pos = set_ptr->filled_spots.size() - 1;
                return;
            }
            uintptr_t i = current_pos + 1;
            for (; i < set_ptr->filled_spots.size(); ++i)
                if (set_ptr->filled_spots[i]) {
                    break;
                }
            current_pos = i;
            current = set_ptr->elements.data() + i;
        };
    };

    Iterator begin() { return Iterator::Begin(this); };

    Iterator end() { return Iterator::End(this); };
};

#endif //ALGORYTMY_2_HASHSET_H
