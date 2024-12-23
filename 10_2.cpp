#include <iostream>
using namespace std;

struct TreeNode {
    char character;
    int frequency;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
    TreeNode(int freq) : character('\0'), frequency(freq), left(nullptr), right(nullptr) {}
};

class MinHeap {
    TreeNode* heap[128]; //�ɱ�ʾ���ַ���Χ 
    int size;

public:
    MinHeap() : size(0) {}
    void insert(TreeNode* node);
    TreeNode* top();
    int getSize() { return size; }
};

void MinHeap::insert(TreeNode* node) {
    heap[++size] = node;
    int idx = size;
    while (idx > 1 && heap[idx]->frequency < heap[idx / 2]->frequency) {
        swap(heap[idx], heap[idx / 2]);
        idx /= 2;
    }
}

TreeNode* MinHeap::top() {
    if (size == 0) return nullptr;
    TreeNode* root = heap[1];//����ͷ�ڵ� 
    heap[1] = heap[size--];
    int idx = 1;
    while (2 * idx <= size) {//ɾͷ�ڵ� 
        int child = 2 * idx;
        if (child + 1 <= size && heap[child + 1]->frequency < heap[child]->frequency) {
            child++;
        }
        if (heap[idx]->frequency > heap[child]->frequency) {
            swap(heap[idx], heap[child]);
            idx = child;
        }
        else break;
    }
    return root;
}

TreeNode* buildHuffmanTree(int* frequency) {
    MinHeap heap;
    for (int i = 0; i < 128; i++) {
        if (frequency[i] > 0) {//�Ȱ���Ƶ�ʵĲ��� 
            heap.insert(new TreeNode((char)i, frequency[i]));
        }
    }

    while (heap.getSize() > 1) {
        TreeNode* left = heap.top();
        TreeNode* right = heap.top();
        TreeNode* merged = new TreeNode(left->frequency + right->frequency);//��СƵ�ʵĽ�ϳ��½ڵ� 
        merged->left = left;
        merged->right = right;
        heap.insert(merged);
    }
    return heap.top();
}

int calculateEncodedLength(TreeNode* node, int depth) {
    if (!node) return 0;
    if (!node->left && !node->right) {//û�ӽڵ�������ⲿ�ڵ� 
        return node->frequency * depth;
    }
    return calculateEncodedLength(node->left, depth + 1) + calculateEncodedLength(node->right, depth + 1);
}

int main() {
    char input[1000001];
    cin >> input;

    int frequency[128] = { 0 };
    for (int i = 0; input[i] != '\0'; i++) {//��Ƶ 
        frequency[input[i]]++;
    }

    TreeNode* root = buildHuffmanTree(frequency);

    int encoded_length = calculateEncodedLength(root, 0);
    cout << encoded_length << endl;

    return 0;
}
