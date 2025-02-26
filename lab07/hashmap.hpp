// Implementation of a basic hashmap (unordered container)
// Mikhail Nesterenko: adapted from Proc C++
// 4/15/2014

#include <cstddef>
#include <utility>
#include <functional>
#include <vector>
#include <list>

using std::vector;
using std::list;
using std::pair;
using std::make_pair;

//////////////////////////////////////////
// Hash function implemented as a class
//////////////////////////////////////////

// Any Hash Class must provide two methods: hash() and numBuckets().
template <typename T>
class DefaultHash {
public:
    DefaultHash(size_t numBuckets = defaultNumBuckets);
    size_t hash(const T& key) const;
    size_t numBuckets() const { return numBuckets_; }

private:
    // Default number of buckets in the hash
    static const size_t defaultNumBuckets = 101;
    size_t numBuckets_;
};

template <typename T>
DefaultHash<T>::DefaultHash(size_t numBuckets) : numBuckets_(numBuckets) {}

// Uses the division method for hashing.
// Treats the key as a sequence of bytes, sums the ASCII values of the bytes,
// and mods the total by the number of buckets.
// Note: this function does not work for C++ strings.
template <typename T>
size_t DefaultHash<T>::hash(const T& key) const {
    size_t res = 0;
    for (size_t i = 0; i < sizeof(key); ++i) {
        const unsigned char b = *(reinterpret_cast<const unsigned char*>(&key) + i);
        res += b;
    }
    return res % numBuckets_;
}

////////////////////////////////////////////////
// Container class
////////////////////////////////////////////////

template <typename Key, typename Value, 
          typename Compare = std::equal_to<Key>,
          typename Hash = DefaultHash<Key>>
class hashmap {

public:
    typedef pair<const Key, Value> Element;

    // Constructor invokes constructors for comparison and hash objects
    hashmap(const Compare& comp = Compare(), const Hash& hash = Hash());
    
    void rehash(int);
    Element* find(const Key& x);  // Returns pointer to element with key x, nullptr if not found
    std::pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool>  insert(const Element& x);  // Inserts the key/value pair
    std::pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool>  erase(const Key& x);  // Erases element with key x, if it exists
    Value& operator[] (const Key& x);  // Returns reference to value of element with key, inserts if does not exist

private:
    // Helper function for various searches
    typename list<Element>::iterator findElement(const Key& x, const size_t bucket);

    size_t size_;  // Number of elements in the container
    Compare comp_;  // Comparison functor, equal_to by default
    Hash hash_;  // Hash functor

    // Hash contents: vector of buckets
    // Each bucket is a list containing key->value pairs
    vector<list<Element>> elems_;
};

////////////////////////////////////////////////
// Container member functions
////////////////////////////////////////////////

// Construct elems_ with the number of buckets.
template <typename Key, typename Value, typename Compare, typename Hash>
hashmap<Key, Value, Compare, Hash>::hashmap(const Compare& comp, const Hash& hash) 
    : size_(0), comp_(comp), hash_(hash) {
    elems_ = vector<list<Element>>(hash_.numBuckets());
}

// Helper function
template <typename Key, typename Value, typename Compare, typename Hash>
typename list<pair<const Key, Value>>::iterator  // Return type
hashmap<Key, Value, Compare, Hash>::findElement(const Key& x, size_t bucket) {
    // Look for the key in the bucket
    for (auto it = elems_[bucket].begin(); it != elems_[bucket].end(); ++it)
        if (comp_(it->first, x))
            return it;

    return elems_[bucket].end();  // Element not found
}

// Returns a pointer to the element with key x, returns nullptr if no element with this key
template <typename Key, typename Value, typename Compare, typename Hash>
typename hashmap<Key, Value, Compare, Hash>::Element*  // Return value type
hashmap<Key, Value, Compare, Hash>::find(const Key& x) {
    size_t bucket = hash_.hash(x);
    auto it = findElement(x, bucket);  // Use the findElement() helper

    if (it != elems_[bucket].end())
        // Found the element, return a pointer to it
        return &(*it);  // Dereference the iterator to the list, then take the address of the list element
    else  // Didn't find the element, return nullptr
        return nullptr;
}

// Finds the element with key x, inserts an element with that key if none exists yet.
// Returns a reference to the value corresponding to that key.
template <typename Key, typename Value, typename Compare, typename Hash>
std::pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool> 
hashmap<Key, Value, Compare, Hash>::insert(const Element& x) {
    size_t bucket = hash_.hash(x.first);
    auto it = findElement(x.first, bucket); 

    // If not found, insert a new one.
    if (it == elems_[bucket].end()) {
        ++size_;
        elems_[bucket].push_back(x);
        it = --elems_[bucket].end();  
        return std::make_pair(&(*it), true);
    }
    return std::make_pair(&(*it),false);
}

// Removes the element with key x, if it exists
template <typename Key, typename Value, typename Compare, typename Hash>
std::pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool> 
hashmap<Key, Value, Compare, Hash>::erase(const Key& x) {
    size_t bucket = hash_.hash(x);
    auto it = findElement(x, bucket);  // Try to find the element
    if (it != elems_[bucket].end()) {  // The element exists, erase it
        auto nextIt = std::next(it);

        // if found then return pair {point to next element, true}
        elems_[bucket].erase(it);
        --size_;

        if(nextIt != elems_[bucket].end()){
            return make_pair(&(*nextIt),true);
        }
        // looking for next element in next bucket 
        for(auto i = bucket + 1; i < elems_.size(); ++i){
            if(!elems_[i].empty()){
                return make_pair(&(*elems_[i].begin()), true);
            }
        }
        return make_pair(nullptr,true); // if no more element past what being deleted
        
    }
    return make_pair(nullptr,false);
}

template <typename Key, typename Value, typename Compare, typename Hash>
void hashmap<Key, Value, Compare, Hash>::rehash(int n) {
    if (n <= hash_.numBuckets()) {
        return;
    }

    vector<list<Element>> newElems(n);
    Hash newHash(n);  

    // Rehash existing elements
    for (size_t bucket = 0; bucket < elems_.size(); ++bucket) {
        for (auto& element : elems_[bucket]) {
            size_t newBucket = newHash.hash(element.first);
            newElems[newBucket].push_back(element);  
        }
    }

    elems_ = std::move(newElems);  
    hash_ = newHash;  
}



// Returns reference to value of element with key x, inserts if it does not exist
template <typename Key, typename Value, typename Compare, typename Hash>
Value& hashmap<Key, Value, Compare, Hash>::operator[] (const Key& x) {
    Element* found = find(x);
    if (found == nullptr) {  // If key not found, create new element with empty value
        found = &(*insert(make_pair(x, Value())).first);  // *
    }
    return found->second;
}
