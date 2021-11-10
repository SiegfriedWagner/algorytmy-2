//
// Created by mateu on 04.11.2021.
//
#include <vector>
#include <array>
#include <cassert>
#include <iostream>
#include "hashed_types.h"
#include "../primes.h"
using namespace std;

// closed hashing
template<typename T>
class HashSet {
private:
    vector<T> elements;
    vector<bool> filled_spots;
    uint32_t count_;
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
        while (count_ > 0) {
            if (filled_spots[i]) {
                insert_internal(elements[i], new_elements, new_filled_spots, new_conflicts_count, new_count);
                count_--;
            }
            i++;
        }
        count_ = new_count;
        conflicts_count = new_conflicts_count;
        elements = new_elements;
        filled_spots = new_filled_spots;
        high_water_mark = false;
        low_water_mark = false;
    };

    bool highWaterCheck() {
        return count_ == elements.size() || conflicts_count > 0 && (float) count_ / elements.size() > 0.75f;
    }

    bool lowWaterCheck() {
        return (float) count_ / elements.size() < 0.25f;
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
    HashSet() : elements(primes[0]), filled_spots(primes[0]), count_(0), low_water_mark(false), high_water_mark(false),
                primes_spot(0) {}

    void insert(const T &element) {
        if (high_water_mark)
            resize(true);
        insert_internal(element, elements, filled_spots, conflicts_count, count_);
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

    void print() {
        cout << "Number of conflicts:" << conflicts_count << " total size: " << elements.size() << " elements count: " << count_ << endl;
        for (int i = 0; i < elements.size(); ++i) {
            if (filled_spots[i])
                cout << elements[i] << endl;
        }
    }
};

int main(int argc, char **argv) {
    HashSet<int> set;
    set.insert(10);
    set.print();
    set.insert(20);
    set.print();
    set.insert(33);
    set.print();
    set.insert(87);
    set.print();
    set.remove(10);
    set.print();
    set.remove(1);
    set.print();
    set.remove(33);
    set.print();
    set.remove(87);
    set.print();
    set.remove(20);
    set.print();
    return 0;
}