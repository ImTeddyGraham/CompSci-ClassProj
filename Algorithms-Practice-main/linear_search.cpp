// Loop Invariant
// Initialization: The subarry A[1 ... i-1] does not contain value. When i = 1 the subarray contains nothing ergo true.
// Maintenance: If A[i] == value return. Otherwise continue. 
// Termination: The loop exits either because the item was found or we are now out of bounds 

//Time complexity: O(n) 
    // - We must traverse the entire array to sort it.
    // Inplace.

int LinearSearch(int A[], int size, int value) {
    for (int i=0; i<size; ++i) {
        if(A[i] == value) {
            return i;
        }
    }
    return -1;
}