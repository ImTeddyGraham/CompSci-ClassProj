// Loop Invariant
// Initialization: The subarry A[1 ... i-1] is sorted. Trivially true when i = 1
// Maintenance: We insert one new item into its correct position. 
// Termination: On termination i = size+1. Ergo the subarray A[1 ... size] is sorted.

// Time complexity: O(n)
    // - Needs to traverse the entire array and traverse backwards for each element to find correct location. 
// Space complexity: O(1), Inplace.

void InsertionSort(int A[], int size) {
    for (int i=0; i<size; ++i) {
        int key = A[i]; // Current item
        int j = i-1; // First item to compare 
        while (-1<j && A[j]>key) { // Comparing with items before it 
            A[j+1] = A[j];
            --j;
        }
        A[j+1] = key; // Inserts to correct location 
    }
}