#include <iostream>
#include <vector>

using namespace std;

// The merge step that also counts inversions
long long mergeAndCount(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;    // Starting index for left subarray
    int j = mid + 1; // Starting index for right subarray
    int k = left;    // Starting index to be sorted
    long long inv_count = 0;

    // Merge the two halves into temp[]
    while ((i <= mid) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            // arr[i] > arr[j] means there is an inversion.
            // Since the left subarray is sorted, all elements from arr[i] to arr[mid]
            // will also be greater than arr[j].
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1); // The core trick!
        }
    }

    // Copy the remaining elements of left subarray (if any)
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copy the remaining elements of right subarray (if any)
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copy the sorted subarray back into the original array
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inv_count;
}

// The recursive Merge Sort function
long long mergeSortAndCount(vector<int>& arr, vector<int>& temp, int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Inversions in the left half
        inv_count += mergeSortAndCount(arr, temp, left, mid);
        
        // Inversions in the right half
        inv_count += mergeSortAndCount(arr, temp, mid + 1, right);
        
        // Inversions split across the two halves
        inv_count += mergeAndCount(arr, temp, left, mid, right);
    }
    return inv_count;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Temporary array used for the merge step to save memory allocations
    vector<int> temp(n);

    // Call the function and print the result
    // Note: We use long long because max inversions is N*(N-1)/2
    long long total_inversions = mergeSortAndCount(arr, temp, 0, n - 1);
    
    cout << total_inversions << "\n";

    return 0;
}