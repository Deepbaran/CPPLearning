#include <iostream>
#include <deque>
using namespace std;

int main() {
    deque<int> dq;

    // Push
    dq.push_back(1); //Pushes element at the end
    dq.push_front(2); //Pushes element at the beginning

    // size
    cout << dq.size(); // 2

    // Pop
    dq.pop_back(); //Pops element from the end
    dq.pop_front(); //Pops element from the beginning

    // Empty
    cout << dq.empty(); // true
}