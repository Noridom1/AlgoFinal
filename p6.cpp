#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

// Struct to hold the value and where it came from
struct Element {
    int val;
    int array_idx; // Which sequence it belongs to
    int elem_idx;  // Its index within that sequence
    
    // We want a Min-Heap, so we reverse the default comparison.
    // The Priority Queue puts the "greatest" element at the top,
    // so we say element A is "greater" if its value is smaller.
    bool operator>(const Element& other) const {
        return val > other.val;
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k;
    if (!(cin >> k)) return 0;
    
    // Crucial Step: cin leaves a newline character '\n' in the input buffer.
    // We must ignore it before using getline(), otherwise the first getline reads empty.
    cin.ignore(); 

    vector<vector<int>> sequences(k);
    
    // 1. Read the input line by line
    for (int i = 0; i < k; ++i) {
        string line;
        getline(cin, line);
        
        stringstream ss(line);
        int num;
        while (ss >> num) {
            sequences[i].push_back(num);
        }
    }

    // 2. Initialize the Min-Heap
    // Syntax: priority_queue<Type, Container, Comparator>
    priority_queue<Element, vector<Element>, greater<Element>> minHeap;

    // 3. Push the first element of every non-empty sequence into the heap
    for (int i = 0; i < k; ++i) {
        if (!sequences[i].empty()) {
            minHeap.push({sequences[i][0], i, 0}); // sequences[i][0] = val, i = arr_index, 0 = elem_index. We push an Element struct to minHeap
        }
    }

    // 4. Process the heap
    /*
    Create a Min-Heap.
    Look at the very first element of all K sequences. Push the first elements of these K sequences into the heap. 
    Pop the smallest element from the heap and print it (or add to result array).
    Look at which array that popped element came from. Grab the next element from that specific array and push it into the heap.
    Repeat until the heap is empty.
    */
    bool first_print = true;
    while (!minHeap.empty()) {
        // Get the minimum element
        Element curr = minHeap.top();
        minHeap.pop();

        // Print it (formatting with spaces)
        if (!first_print) cout << " ";
        cout << curr.val;
        first_print = false;

        // Push the next element from the same sequence (if it exists)
        int next_elem_idx = curr.elem_idx + 1;
        int arr_idx = curr.array_idx;
        
        if (next_elem_idx < sequences[arr_idx].size()) {
            minHeap.push({sequences[arr_idx][next_elem_idx], arr_idx, next_elem_idx});
        }
    }
    
    cout << "\n";
    return 0;
}