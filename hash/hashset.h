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
    uint32_t count;
    uint32_t conflicts_count;
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
        uint32_t new_conflicts_count = 0;
        uint32_t new_count = 0;
        int i = 0;
        while (count > 0) {
            if (filled_spots[i]) {
                insert_internal(elements[i], new_elements, new_filled_spots, new_conflicts_count, new_count);
                count--;
            }
            i++;
        }
        count = new_count;
        conflicts_count = new_conflicts_count;
        elements = new_elements;
        filled_spots = new_filled_spots;
        high_water_mark = false;
        low_water_mark = false;
    };

    bool highWaterCheck() {
        return count == elements.size() || conflicts_count > 0 && (float) count / elements.size() > 0.75f;
    }

    bool lowWaterCheck() {
        return (float) count / elements.size() < 0.25f;
    }

    void rehash(uint32_t emptied_spot) {
        // check spot behind just emptied spot
        auto to_check = (emptied_spot + 1) % elements.size();
        if (!filled_spots[to_check])
            return;
        auto true_hash = hash<T>{}(elements[to_check]) % elements.size();
        if (true_hash != to_check) {
            uint32_t i = true_hash;
            while(i != to_check) { // naive approach, may make too many iterations
                if (!filled_spots[i]) {
                    filled_spots[i] = true;
                    elements[i] = elements[to_check];
                    elements[to_check] = {};
                    filled_spots[to_check] = false;
                    i = (i + 1) % elements.size();
                }
            }
            rehash(to_check);
        }
    }
    static void
    insert_internal(const T &element, vector<T> &collection, vector<bool> &filled_spots, uint32_t &conflicts_count,
                    uint32_t &filled_spots_count) {
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
    HashSet() : elements(primes[0]), filled_spots(primes[0]), count(0), low_water_mark(false), high_water_mark(false),
                primes_spot(0) {}

    void insert(const T &element) {
        if (high_water_mark)
            resize(true);
        insert_internal(element, elements, filled_spots, conflicts_count, count);
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
                count--;
                low_water_mark = lowWaterCheck();
                high_water_mark = false;
                rehash(key);
                break;
            }
            key = (key + 1) % elements.size();
        }
    }

    void print() {
        cout << "Number of conflicts:" << conflicts_count << " total size: " << elements.size() << " elements count: " << count << endl;
        for (int i = 0; i < elements.size(); ++i) {
            if (filled_spots[i])
                cout << elements[i] << endl;
        }
    }
    // TODO: Lock collection for adding/removing elements while iterator is alive OR make copy of collection
    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using referece = T&;
        Iterator(HashSet<T> const *ptr) : current(nullptr), current_pos(0), set_ptr(ptr) { // TODO: consider if passing raw pointer is harmful
            moveForward();
        }
        static Iterator End(HashSet<T> const *ptr) {
            Iterator end(ptr);
            // find first filled spot starting from end
            for (size_t i = ptr->filled_spots.size() - 1; i >= 0; --i)
                if (ptr->filled_spots[i]) {
                    end.current = ptr->elements.data() + i;
                    end.current_pos = i;
                }
            return end;
        }
        referece operator*() const { return *current; }
        pointer operator->() { return current; };
        Iterator& operator++() {
            moveForward();
            return *this;
        }
        Iterator& operator++(int) {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.current == b.current; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.current != b.current; };

    private:
        T* current;
        size_t current_pos;
        const HashSet<T> *set_ptr; // TODO: Try to avoid naked pointer
        void moveForward() {
            if (current_pos >= set_ptr->filled_spots.size()) {
                current_pos = set_ptr->filled_spots.size() - 1;
                return;
            }
            for (size_t i = current_pos + 1; i < set_ptr->filled_spots.size(); ++i)
                if (set_ptr->filled_spots[i]) {
                    current_pos = i;
                    current = set_ptr->elements + current_pos;
                }
        };
    };

    Iterator begin() { return Iterator(this); };
    Iterator end() { return Iterator::End(this); };
};

#endif //ALGORYTMY_2_HASHSET_H
