#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Helper function to validate the BST
bool helper(struct TreeNode* node, long min, long max) {
    if (!node) return true;
    if (node->val <= min || node->val >= max) return false;
    return helper(node->left, min, node->val) && helper(node->right, node->val, max);
}

// Function to check if the tree is a valid BST
bool isValidBST(struct TreeNode* root) {
    return helper(root, LONG_MIN, LONG_MAX);
}

// Helper function to create a new tree node
struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper function to build a binary tree from a level-order traversal
struct TreeNode* buildTree(const char** nodes, int size) {
    if (size == 0 || strcmp(nodes[0], "null") == 0) return NULL;

    struct TreeNode** queue = (struct TreeNode**)malloc(size * sizeof(struct TreeNode*));
    int front = 0, rear = 0;

    struct TreeNode* root = createNode(atoi(nodes[0]));
    queue[rear++] = root;

    int i = 1;
    while (i < size) {
        struct TreeNode* current = queue[front++];
        if (i < size && strcmp(nodes[i], "null") != 0) {
            current->left = createNode(atoi(nodes[i]));
            queue[rear++] = current->left;
        }
        i++;
        if (i < size && strcmp(nodes[i], "null") != 0) {
            current->right = createNode(atoi(nodes[i]));
            queue[rear++] = current->right;
        }
        i++;
    }

    free(queue);
    return root;
}

// Helper function to free the memory of the tree
void deleteTree(struct TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

int main() {
    // Example 1
    const char* nodes1[] = {"2", "1", "3"};
    int size1 = sizeof(nodes1) / sizeof(nodes1[0]);
    struct TreeNode* root1 = buildTree(nodes1, size1);
    printf("Input: root = [2,1,3]\n");
    printf("Output: %s\n", isValidBST(root1) ? "true" : "false");
    deleteTree(root1);

    // Example 2
    const char* nodes2[] = {"5", "1", "4", "null", "null", "3", "6"};
    int size2 = sizeof(nodes2) / sizeof(nodes2[0]);
    struct TreeNode* root2 = buildTree(nodes2, size2);
    printf("Input: root = [5,1,4,null,null,3,6]\n");
    printf("Output: %s\n", isValidBST(root2) ? "true" : "false");
    deleteTree(root2);

    return 0;
}
