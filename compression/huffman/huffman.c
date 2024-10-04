#include "huffman.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT 150

struct MinHeapNode *newNode(struct letter_count letter) {
  struct MinHeapNode *temp =
      (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
  temp->letter = letter;
  temp->left = NULL;
  temp->right = NULL;

  return temp;
}

struct MinHeap *createMinHeap(unsigned capacity) {
  struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
  // current size is zero;
  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->array = (struct MinHeapNode **)malloc(minHeap->capacity *
                                                 sizeof(struct MinHeapNode));
  return minHeap;
}

void swapMinHeapNodes(struct MinHeapNode **a, struct MinHeapNode **b) {
  struct MinHeapNode *temp = *a;
  *a = *b;
  *b = temp;
}

void minHeapify(struct MinHeap *minHeap, int idx) {
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;
  // checking if left node is smaller than parent.
  if ((left < minHeap->size) && (minHeap->array[left]->letter.count <
                                 minHeap->array[smallest]->letter.count)) {
    smallest = left;
  }
  // checking if right node is smaller than parent.
  if ((right < minHeap->size) && (minHeap->array[right]->letter.count <
                                  minHeap->array[smallest]->letter.count)) {
    smallest = right;
  }
  if (smallest != idx) {
    // swap parent node with child node
    swapMinHeapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

int isSizeOne(struct MinHeap *minHeap) { return (minHeap->size == 1); }

struct MinHeapNode *extractMin(struct MinHeap *minHeap) {
  struct MinHeapNode *temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];
  --minHeap->size;
  minHeapify(minHeap, 0);
  return temp;
}

void insertMinHeap(struct MinHeap *minHeap, struct MinHeapNode *minHeapNode) {
  ++minHeap->size;
  int i = minHeap->size - 1;
  while (i && minHeapNode->letter.count <
                  minHeap->array[(i - 1) / 2]->letter.count) {
    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap *minHeap) {
  int n = minHeap->size - 1;
  int i;
  for (i = (n - 1) / 2; i >= 0; --i)
    minHeapify(minHeap, i);
}

void printArr(int arr[], int n) {
  int i;
  for (i = 0; i < n; i++)
    printf("%d", arr[i]);
  printf("\n");
}

int isLeaf(struct MinHeapNode *root) { return !(root->left) && !(root->right); }

struct MinHeap *createAndBuildMinHeap(struct hashmap *map) {
  size_t size = hashmap_count(map);
  struct MinHeap *minHeap = createMinHeap(size);
  size_t iter = 0;
  void *item;
  while (hashmap_iter(map, &iter, &item)) {
    const struct letter_count *letter = item;
    minHeap->array[iter] = newNode(*letter);
  }
  minHeap->size = size;
  buildMinHeap(minHeap);
  return minHeap;
}

// this main function builds the HuffmanTree
struct MinHeapNode *buildHuffmanTree(struct hashmap *map) {
  struct MinHeapNode *left, *right, *top;
  /*
   * Step1: Create a min heap of capacity equal to size;
   * Initially, there are nodes equal to size.
   */
  struct MinHeap *minHeap = createAndBuildMinHeap(map);
  // Iterate while size of heap does not become 1;
  while (!isSizeOne(minHeap)) {
    /*
     * Step 2: extract the two minimum frequencies
     * iterms from min heap.
     */
    left = extractMin(minHeap);
    right = extractMin(minHeap);
    /*
     * Step 3: create a new internal node
     * with frequency equal to the
     * sum of two nodes frequencies.
     * Make the two extracted node as left and right children of this new node.
     * Add this node to the min heap.
     * '\0'-> null is a special value for internal nodes, not used elsewhere.
     */
    struct letter_count letter = {'\0',
                                  left->letter.count + right->letter.count};
    top = newNode(letter);
    top->left = left;
    top->right = right;
    insertMinHeap(minHeap, top);
  }
  /*
   * Step 4: The reamining node is the root node
   * and the tree is complete.
   */
  return extractMin(minHeap);
}

void printCodes(struct MinHeapNode *root, int arr[], int top) {
  // assign 0 to left edges and recur
  if (root->left) {
    arr[top] = 0;
    printCodes(root->left, arr, top + 1);
  }
  // assign 1 to left edges and recur
  if (root->right) {
    arr[top] = 1;
    printCodes(root->right, arr, top + 1);
  }

  /*
   * If this is a leaf node, then
   * it contains one of the input characters,
   * print the character and it's code from arr[]
   */
  if (isLeaf(root)) {
    printf("%lc: ", root->letter.c);
    printArr(arr, top);
  }
}

void HuffmanCodes(struct hashmap *map) {
  struct MinHeapNode *root = buildHuffmanTree(map);

  // print huffman codes.
  int arr[MAX_TREE_HT], top = 0;
  printCodes(root, arr, top);
}
