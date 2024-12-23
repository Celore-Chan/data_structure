#include <iostream>

using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// 构建二叉树的函数
TreeNode* buildTree(const int* preorder, const int* inorder, int preStart, int preEnd, int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) {
        return nullptr;
    }

    // 前序遍历的第一个节点是根节点
    int rootValue = preorder[preStart];
    TreeNode* root = new TreeNode(rootValue);

    // 在中序遍历中找到根节点的位置
    int rootIndexInOrder = inStart;
    while (inorder[rootIndexInOrder] != rootValue) {
        rootIndexInOrder++;
    }

    // 计算左子树的节点数
    int leftSubtreeSize = rootIndexInOrder - inStart;

    // 构建左子树和右子树
    root->left = buildTree(preorder, inorder, preStart + 1, preStart + leftSubtreeSize, inStart, rootIndexInOrder - 1);
    root->right = buildTree(preorder, inorder, preStart + leftSubtreeSize + 1, preEnd, rootIndexInOrder + 1, inEnd);

    return root;
}

// 后序遍历输出
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
    postOrder(root);  // 输出后序遍历
    cout << endl;

    return 0;
}
