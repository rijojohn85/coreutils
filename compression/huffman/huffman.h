#include "../compress.h"
struct MinHeapNode {
  struct letter_count letter;
  struct MinHeapNode *left, *right;
};

struct MinHeap {
  unsigned size;
  unsigned capacity;
  struct MinHeapNode **array;
};

/*
 * A utility function to allocate a new
 * min heap node with given character
 * and frequency (struct letter count)
 * input -> letter_count
 * output -> new MinHeapNode
 */
struct MinHeapNode *newNode(struct letter_count letter);

/*
 * A utility function to create
 * a minHeap of given capacity
 * Creates a minHeap with array
 * capacity = capacity
 */
struct MinHeap *createMinHeap(unsigned capacity);

/*
 * A utility to sway two
 * min heap nodes
 */
void swapMinHeapNodes(struct MinHeapNode **a, struct MinHeapNode **b);

/*
 * The standard minHeapify function
 *
 */
void minHeapify(struct MinHeap *minHeap, int idx);

/*
 * utility function to check if size of heap
 * is 1.
 */
int isSizeOne(struct MinHeap *minHeap);

/*
 * A standard function to extract
 * minimum value node from heap.
 */
struct MinHeapNode *extractMin(struct MinHeap *minHeap);

/*
 * utility function to insert a new
 * node to min heap
 */
void insertMinHeap(struct MinHeap *minHeap, struct MinHeapNode *minHeapNode);

/*
 * A standard function to build min heap
 */
void buildMinHeap(struct MinHeap *minHeap);

/*
 * Utility function to check if node is leaf
 */
int isLeaf(struct MinHeapNode *root);

/*
 * Creates a mind heap of capacity
 * equal to size and inserts all chars of letter[]
 * in min heap. Initially size of minHeap
 * is equal to capacity.
 */
struct MinHeap *createAndBuildMinHeap(struct hashmap *map);

/*
 *print huffman codes from the root of Huffman tree.
 *it uses arr[] to store codes.
 */
void printCodes(struct MinHeapNode *root, int arr[], int top);

/*
 * A utility function to print an array of size n
 */
void printArr(int arr[], int n);

struct MinHeapNode *builHuffmanTree(struct hashmap *map);

void HuffmanCodes(struct hashmap *map);
