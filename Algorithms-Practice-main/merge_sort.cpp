#include <iostream>

using namespace std;

void Merge(int A[], int low, int mid, int high) {
    int lSize = mid-low+1, rSize = high-mid;
    int lArr[lSize], rArr[rSize];
    
    for (int i=0; i<lSize; ++i) {
        lArr[i] = A[i+low];
    }
    for (int i=0; i<rSize; ++i) {
        rArr[i] = A[i+mid+1];
    }

    int r = 0, l = 0;
    for (int i=low; i<=high; ++i) {
        if (l >= lSize) {
            A[i] = rArr[r++];
        } else if (r >= rSize) {
            A[i] = lArr[l++];
        } else if (lArr[l]<=rArr[r]) {
            A[i] = lArr[l++];
        } else {
            A[i] = rArr[r++];
        }
    } 
}
void MergeSort(int A[], int low, int high) {
    if (high <= low) {return;}
    int mid = (high+low)/2;
    MergeSort(A, low, mid);
    MergeSort(A, mid+1, high);
    Merge(A, low, mid, high);
}