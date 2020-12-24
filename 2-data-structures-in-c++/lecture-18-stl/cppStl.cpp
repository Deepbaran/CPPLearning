#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <climits>
#include <unordered_map>

using namespace std;

bool f(int x, int y) {
    return x > y; // sort in descending order
}

void vectorDemo() {
    vector<int> A = { 11,2,3,14 };

    cout << A[1] << endl;

    sort(A.begin(), A.end()); // O(NlogN) <- Merge Sort

    // 2,3,11,14
    // O(logN) <- Binary Search
    bool present = binary_search(A.begin(), A.end(), 3); // true
    present = binary_search(A.begin(), A.end(), 4); //false

    A.push_back(100);
    present = binary_search(A.begin(), A.end(), 100); //true

    //2,3,11,14,100
    A.push_back(100);
    A.push_back(100);
    A.push_back(100);
    A.push_back(100);
    //2,3,11,14,100,100,100,100,100,123
    A.push_back(123);

    // vector<int>::iterator it = lower_bound(A.begin(), A.end(), 100); // >=
    auto it = lower_bound(A.begin(), A.end(), 100); // >=
    vector<int>::iterator it2 = upper_bound(A.begin(), A.end(), 100); // >

    cout << *it << " " << *it2 << endl;
    cout << it2 - it << endl; // 5

    sort(A.begin(), A.end(), f);
    vector<int>::iterator it3;
    for(it3 = A.begin(); it3 != A.end(); it3++) {
        cout << *it3 << " ";
    }
    cout << endl;

    for(int x : A) {
        cout << x << " ";
    }
    cout << endl;

    for(int &x : A) // reference
    {
        x++;
    }

    for(int x : A) {
        cout << x << " ";
    }
    cout << endl;
}

void setDemo() 
{
    set<int> S; // Set is sorted
    S.insert(1); // O(logN)
    S.insert(2);
    S.insert(-1);
    S.insert(-10);

    for(int x: S) {
        cout << x << " ";
    }
    cout << endl;

    // -10 -1 1 2
    auto it = S.find(-1); // Returns the iterator to -1. After this it will point towards -1
    if(it == S.end()) {
        cout << "not present\n";
    } else {
        cout << "present\n";
        cout << *it << endl;
    }

    auto it2 = S.lower_bound(-1); // >=
    auto it3 = S.upper_bound(0);
    cout << *it2 << " " << *it3 << endl;

    auto it4 = S.upper_bound(2);
    if(it4 == S.end()) {
        cout << "oops! can't find\n";
    }

    S.erase(1); // O(logN)
}

void mapDemo() {
    map<int, int> A; // Sorted. It uses Balanced BST
    A[1] = 100;
    A[2] = -1;
    A[3] = 200;
    A[100000232] = 1;

    map<char, int> cnt;
    string x = "Deepbaran Kar";

    for(char c : x) {
        cnt[c]++;
    }

    cout << cnt['a'] << " " << cnt['z'] << endl;

    auto it = cnt.find('r'); // O(logN)
    if(it != cnt.end()) {
        cout << "found!\n";
    } else {
        cout << "not found!\n";
    }

    cnt.erase('r'); // O(logN)
    if(cnt.find('r') != cnt.end()) {
        cout << "found!\n";
    } else {
        cout << "not found!\n";
    }
}

void unOrderedMap() {
    unordered_map<char, int> U; // Unsorted. It uses Hash Table 
    // add(key, value) - O(1)
    // erase(key) - O(1)

    string x = "Deepbaran Kar";
    for(char c: x) U[c]++;
}

void PowerStl() {
     /*
     [x, y]
     add [2, 3]
     add [10, 20]
     add [20, 400]
     add functions will not overlap the present intervals
     give me the interval 13
     */

    set<pair<int, int>> S;
    /*
    pair {a, b} is smaller than pair {c, d} iff (a < b) or (a == b and c < d)
    */
    S.insert({2, 3});
    S.insert({10, 20});
    S.insert({30, 400});
    S.insert({401, 450});

    // 2, 3
    // 10, 20
    // 30, 400
    // 401, 450

    int point = 400;
 
    auto it = S.upper_bound({point, INT_MAX}); // >
    if(it == S.begin()) {
        cout << "the given point is not lying in any interval...\n";
        return;
    }

    it--;
    pair<int, int> current = *it;
    if(current.first <= point && point <= current.second) { // The values in pair X = {a, b} can be accessed using X.first and X.second
        cout << "yes it's present: " << current.first << " " << current.second << endl;
    } else  {
        cout << "the given point is not lying in any interval...\n";
    }
}

int main() {

    // C++ STL
    // vectorDemo();
    // setDemo();
    // mapDemo();
    // unOrderedMap();
    PowerStl();
}