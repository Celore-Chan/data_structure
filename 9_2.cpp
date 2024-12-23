#include <iostream>

using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// �����������ĺ���
TreeNode* buildTree(const int* preorder, const int* inorder, int preStart, int preEnd, int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) {
        return nullptr;
    }

    // ǰ������ĵ�һ���ڵ��Ǹ��ڵ�
    int rootValue = preorder[preStart];
    TreeNode* root = new TreeNode(rootValue);

    // ������������ҵ����ڵ��λ��
    int rootIndexInOrder = inStart;
    while (inorder[rootIndexInOrder] != rootValue) {
        rootIndexInOrder++;
    }

    // �����������Ľڵ���
    int leftSubtreeSize = rootIndexInOrder - inStart;

    // ������������������
    root->left = buildTree(preorder, inorder, preStart + 1, preStart + leftSubtreeSize, inStart, rootIndexInOrder - 1);
    root->right = buildTree(preorder, inorder, preStart + leftSubtreeSize + 1, preEnd, rootIndexInOrder + 1, inEnd);

    return root;
}

// ����������
void postOrder(TreeNode* root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->value << " ";
}

int main() {
    int n;
    cin >> n;
    int* preorder=new int[n];
    int* inorder = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> preorder[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> inorder[i];
    }

    TreeNode* root = buildTree(preorder, inorder, 0, n - 1, 0, n - 1);
    postOrder(root);  // ����������
    cout << endl;

    return 0;
}
