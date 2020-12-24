#include <string>
using namespace std;

template <typename V>
class MapNode {
    public:
        string key;
        V value;
        MapNode* next;

        MapNode(string key, V value) {
            this->key = key;
            this->value = value;
            next = nullptr;
        }
        ~MapNode() {
            delete next;
        }
};

template <typename V> 
class ourmap {
    // bucket array
    MapNode<V>* *buckets; // we are creating a 2-D array in heap of type MapNode<V>*
    int count;
    int numBuckets;

    public:
    ourmap() {
        count = 0;
        numBuckets = 5;
        buckets = new MapNode<V>*[numBuckets];
        for(int i = 0; i < numBuckets; i++) {
            buckets[i] = nullptr;
        }
    }

    ~ourmap() {
        for(int i = 0; i < numBuckets; i++) {
            delete buckets[i];
        }
        delete[] buckets;
    }

    int size() {
        return count;
    }

    V getValue(string key) {
        int bucketIndex = getBucketIndex(key);
        MapNode<V>* head = buckets[bucketIndex];
        while(head != nullptr) {
            if(head->key == key) {
                return head->value;
            }
            head = head->next;
        }
        return 0;
    }

    private:
    int getBucketIndex(string key) {
        int hashCode = 0;

        int currentCoeff = 1;
        // transform the string into a base of p to get the hashCode, where p is any prime number
        for(int i = key.length() - 1; i >= 0; i--) {
            hashCode += key[i] * currentCoeff;
            // to make sure that our hashCode does not go out of range, so,
            hashCode = hashCode % numBuckets; // property of modulus is to keep things in a particular a
            currentCoeff *= 37; // 37 is p here
            // to make sure that our currentCoeff does not go out of range, so,
            currentCoeff = currentCoeff % numBuckets; // through modular operator, we make sure that currentCoef
        }

        return hashCode % numBuckets;
    }

    void rehash() {
        MapNode<V>** temp = buckets;
        buckets = new MapNode<V>*[2 * numBuckets];
        for(int i = 0; i < 2*numBuckets; i++) {
            buckets[i] = nullptr;
        }
        int oldBucketCount = numBuckets;
        numBuckets *= 2;
        count = 0;
        for(int i = 0; i < oldBucketCount; i++) {
            MapNode<V>* head = temp[i];
            while(head != nullptr) {
                string key = head->key;
                V value = head->value;
                insert(key, value);
                head = head->next;
            }
        }
        for(int i = 0; i < oldBucketCount; i++) {
            MapNode<V>* head = temp[i];
            delete head;
        }
        delete[] temp;
    }

    public:
    double getLoadFactor() {
        return (1.0*count)/numBuckets;
    }

    void insert(string key, V value) {
        int bucketIndex = getBucketIndex(key);
        MapNode<V>* head = buckets[bucketIndex]; // linkedlist corresponding to the buckedIndexth element in buckets array in heap
        while(head != nullptr) {
            if(head->key == key) {
                head->value = value;
                return;
            }
            head = head->next;
        }
        MapNode<V>* node = new MapNode<V>(key, value);
        node->next = head;
        buckets[bucketIndex] = node;
        count++;
        double loadFactor = (1.0*count)/numBuckets;
        if(loadFactor > 0.7) {
            rehash();
        }
    }

    V remove(string key) {
        int bucketIndex = getBucketIndex(key);
        MapNode<V>* head = buckets[bucketIndex]; // buckets is pointing to the array in heap, so it's a pointer
        MapNode<V>* prev = nullptr;
        while(head != nullptr) {
            if(head->key == key) {
                if(prev == nullptr) {
                    buckets[bucketIndex] = head->next; 
                    // now the bucketIndexth element in the buckets array in heap is pointing towards head->next
                } else {
                    prev->next = head->next;
                }
                V value = head->value;
                head->next = nullptr;
                // we need to make the next nullptr. Because we defined the destructor recusive. 
                // So, if head is deleted, the whole linkedlist will be deleted
                delete head;
                count--;
                return value;
            }
            prev = head;
            head = head->next;
        }
        return 0;
    }

};

/*
 * Bucket Array Stores the keys.
 * 
 * Hash function gives the index where a particular key will be stored in the Bucket Array.
 * Hash function has two parts: Hash code and Compression.
 * Hash code gives the index and compression function function keeps the hash code inside a particular range, 
 * so that our bucket array does not increase too much and stays within a particular size.
 * 
 * Due to the compression function, it is likely that more than one key will go to the same index which causes collisions in the Hashmap.
 * So, we need to do collision handling. We can do it in two ways:
 * 1. Closed Hashing (Separate Chaining)
 * 2. Open Addressing
 * 
 * Closed Hashing means that both the keys will go to the same index and the bucket must be able to handle more than one entry.
 * A very easy way to implement closed hashing is by making the bucket a array of linked list. i.e, each index in the bucket points to the head of a linked list 
 * and each node of the linked list stores the key-value pairs of each new key.
 * 
 * In open addressing we find the index of the key and check if there is already a key stored at that index. If there is already a key in that address,
 * then we will find an alternate index for our key. There are many ways to find an alternate index for our key.
 * In general we can say,
 * hi(a) = hf(a) + f(i)
 * where, 
 * hi(a) means the ith attempt to relocate our key
 * hf(a) means original hash function or 0th attempt.
 * f(i) is some function of i and f(0) = 0, i.e. for 0th attempt f(i) should be zero.
 * 
 * We need to find f(i). Different kind of open addressing techniques means different f(i).
 * Some open addressing techniques are:
 * 1. Linear Probing [f(i)=i. It probes each index linearly for relocating]
 * 2. Quadratic probing [f(i)=i^2]
 * 3. Double Hashing [f(i)=i*h'(a). Where h'(i) is a different hash function]
 * 
 * In practice, separate chaining works as well as addressing technique. Separate chaining just creates linked list in each index of the bucket.
 * 
 * Load factor means how much load is there on our hashmap.
 * Load factor is defined as (n/b) which means n entries(load) in b boxes. Due to load factor, the time taken is O(n/b).
 * We should keep, n/b < 0.7. Which means that each box must not have very large number of entries.
 * As n/b < 0.7, we can assume that O(n) ~ 1. So, we can say that the time complexity of hashmap is O(1).
 * 
 * To keep n/b < 0.7, i.e. to make sure that the load on the hashmap is not more than 0.7, we need to increase the bucket(b) along with the load(n), so that the number of
 * entries in a single bucket is not much.
 * 
 * The way of making sure that n/b < 0.7, we will do Rehashing. i.e. we will double the bucket size and then again hash all the entries in our new increased size bucket.
 * This will decrease the load factor again as we must keep the load factor small, so that the time complexity remains O(1).
 * 
 * Time complexity is proportional to the size of the linked list in the boxes of the bucket. And to keep the size of the linked list we do rehashing.
 * 
 */