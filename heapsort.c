//George Nassar 1473504

#include <stdio.h>


void heapify(int heap[], int n, int i);
void heapSort(int heap[], int n);
void output(int heap[], int n);


int main(void){
    int n, heap[10000], i = 0;

    printf("Enter the number of integers: ");
    scanf("%d", &n);

    printf("Enter the %d integers to be sorted: ", n);
    while ((scanf("%d",&heap[i++]) != -1) && (i < n)){
    }
 
    heapSort(heap, n);
    output(heap, n);
    printf("\n");
    return 0;
}

void heapify(int heap[], int n, int i){
    int node = i;
    int left = 2*i + 1; 
    int right = 2*i + 2;
 
    if (left < n && heap[left] > heap[node])
        node = left;
 
    if (right < n && heap[right] > heap[node])
        node = right;
 
    if (node != i)
    {
        int temp = heap[i];
        heap[i] = heap[node];
        heap[node] = temp;
        heapify(heap, n, node);
    }
}
 

void heapSort(int heap[], int n){
    for (int i = (n / 2 - 1); i >= 0; i--){
        heapify(heap, n, i);
    }
 
    for (int i = (n - 1); i >= 0; i--){
        int temp = heap[0];
        heap[0] = heap[i];
        heap[i] = temp;

        heapify(heap, i, 0);
    }
}
 
void output(int heap[], int n){
    int i;
    printf("In sorted ascending order: ");
    for(i = 0; i < n; i++){
        printf("%d ", heap[i]);
    }
}
