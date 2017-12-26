#include <cstdlib> // malloc
#include <cstdint> // uint8_t problem
#include "openedu.hpp"

/// A cache-friendly hash set with open addressing, linear probing and power-of-two capacity
template <typename KeyT>
class HashSet {
    enum class State : uint8_t {
        INACTIVE, // Never been touched
        ACTIVE,   // Is inside a search-chain, but is empty
        FILLED    // Is set with key/value
    };

    std::hash<KeyT>   _hasher;
    State*  _states           = nullptr;
    KeyT*   _keys             = nullptr;
    size_t  _num_buckets      =  0;
    size_t  _num_filled       =  0;
    int     _max_probe_length = -1; // Our longest bucket-brigade is this long. ONLY when we have zero elements is this ever negative (-1).
    size_t  _mask             = 0;  // _num_buckets minus one


    // Can we fit another element?
    void check_expand_need() {
        reserve(_num_filled + 1);
    }

    // Find the bucket with this key, or return (size_t)-1
    size_t find_filled_bucket(const KeyT& key) const {
        if (_num_filled==0 /* empty() */) { return (size_t)-1; } // Optimization

        auto hash_value = _hasher(key);
        for (int offset=0; offset<=_max_probe_length; ++offset) {
            auto bucket = (hash_value + offset) & _mask;
            if (_states[bucket] == State::FILLED) {
                if (_keys[bucket] == key) {
                    return bucket;
                }
            } else if (_states[bucket] == State::INACTIVE) {
                return (size_t)-1; // End of the chain!
            }
        }
        return (size_t)-1;
    }

    // Find the bucket with this key, or return a good empty bucket to place the key in.
    // In the latter case, the bucket is expected to be filled.
    size_t find_or_allocate(const KeyT& key) {
        auto hash_value = _hasher(key);
        size_t hole = (size_t)-1;
        int offset=0;
        for (; offset<=_max_probe_length; ++offset) {
            auto bucket = (hash_value + offset) & _mask;

            if (_states[bucket] == State::FILLED) {
                if (_keys[bucket] == key) {
                    return bucket;
                }
            } else if (_states[bucket] == State::INACTIVE) {
                return bucket;
            } else {
                // ACTIVE: keep searching
                if (hole == (size_t)-1) {
                    hole = bucket;
                }
            }
        }

        // No key found - but maybe a hole for it

        if (hole != (size_t)-1) {
            return hole;
        }

        // No hole found within _max_probe_length
        for (; ; ++offset) {
            auto bucket = (hash_value + offset) & _mask;

            if (_states[bucket] != State::FILLED) {
                _max_probe_length = offset;
                return bucket;
            }
        }
    }

    // key is not in this map. Find a place to put it.
    size_t find_empty_bucket(const KeyT& key) {
        auto hash_value = _hasher(key);
        for (int offset=0; ; ++offset) {
            auto bucket = (hash_value + offset) & _mask;
            if (_states[bucket] != State::FILLED) {
                if (offset > _max_probe_length) {
                    _max_probe_length = offset;
                }
                return bucket;
            }
        }
    }

public:

    HashSet() = default;

    ~HashSet() {
        for (size_t bucket=0; bucket<_num_buckets; ++bucket) {
            if (_states[bucket] == State::FILLED) {
                _keys[bucket].~KeyT();
            }
        }
        free(_states);
        free(_keys);
    }


    bool contains(const KeyT& k) const {
        return find_filled_bucket(k) != (size_t)-1;
    }

    bool insert(const KeyT& key) {
        check_expand_need();

        auto bucket = find_or_allocate(key);

        if (_states[bucket] == State::FILLED) {
            return false;
        } else {
            _states[bucket] = State::FILLED;
            new(_keys + bucket) KeyT(key);
            _num_filled++;
            return true;
        }
    }

    /// Same as above, but contains(key) MUST be false
    void insert_unique(const KeyT& key) {
        check_expand_need();
        auto bucket = find_empty_bucket(key);
        _states[bucket] = State::FILLED;
        new(_keys + bucket) KeyT(key);
        _num_filled++;
    }

    /// Erase an element from the hash set.
    /// return false if element was not found.
    bool erase(const KeyT& key) {
        auto bucket = find_filled_bucket(key);
        if (bucket != (size_t)-1) {
            _states[bucket] = State::ACTIVE;
            _keys[bucket].~KeyT();
            _num_filled -= 1;
            return true;
        } else {
            return false;
        }
    }

    /// Remove all elements, keeping full capacity.
    void clear() {
        for (size_t bucket=0; bucket<_num_buckets; ++bucket) {
            if (_states[bucket] == State::FILLED) {
                _states[bucket] = State::INACTIVE;
                _keys[bucket].~KeyT();
            }
        }
        _num_filled = 0;
        _max_probe_length = -1;
    }

    /// Make room for this many elements
    void reserve(size_t num_elems) {
        size_t required_buckets = num_elems + num_elems/2 + 1;
        if (required_buckets <= _num_buckets) {
            return;
        }
        size_t num_buckets = 4;
        while (num_buckets < required_buckets) { num_buckets *= 2; }

        auto new_states = (State*)malloc(num_buckets * sizeof(State));
        auto new_keys  = (KeyT*)malloc(num_buckets * sizeof(KeyT));

        if (!new_states || !new_keys) {
            free(new_states);
            free(new_keys);
            throw std::bad_alloc();
        }

        // auto old_num_filled  = _num_filled;
        auto old_num_buckets = _num_buckets;
        auto old_states      = _states;
        auto old_keys        = _keys;

        _num_filled  = 0;
        _num_buckets = num_buckets;
        _mask        = _num_buckets - 1;
        _states      = new_states;
        _keys        = new_keys;

        std::fill_n(_states, num_buckets, State::INACTIVE);

        _max_probe_length = -1;

        for (size_t src_bucket=0; src_bucket<old_num_buckets; src_bucket++) {
            if (old_states[src_bucket] == State::FILLED) {
                auto& src = old_keys[src_bucket];

                auto dst_bucket = find_empty_bucket(src);
                _states[dst_bucket] = State::FILLED;
                new(_keys + dst_bucket) KeyT(std::move(src));
                _num_filled += 1;

                src.~KeyT();
            }
        }

        free(old_states);
        free(old_keys);
    }
};


int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int N; long long X, A, B;
    long long Ac, Bc, Ad, Bd;
    input >> N >> X >> A >> B >> Ac >> Bc >> Ad >> Bd;

    int pow3 = 1000;
    long long pow15 = 1000000000000000L;

    HashSet<long long> s;

    for (int i = 0; i < N; ++i) {
        if (s.contains(X)) {
            A = (A + Ac) % pow3;
            B = (B + Bc) % pow15;
        } else {
            s.insert_unique(X);
            A = (A + Ad) % pow3;
            B = (B + Bd) % pow15;
        }
        X = (X*A + B) % pow15;
    }

    output << X << " " << A << " " << B;
}
