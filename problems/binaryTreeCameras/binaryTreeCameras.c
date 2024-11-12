#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

typedef enum situation {
    UNMONITORED = 0,
    MONITORED = 1,
    CAMERA = 2
} situation;

situation counter(struct TreeNode* root, int *count){
    if (root == NULL) return MONITORED;

    situation left = counter(root->left, count);
    situation right = counter(root->right, count);

    if (left == UNMONITORED || right == UNMONITORED){
        (*count)++;
        return CAMERA;
    } else if (left == CAMERA || right == CAMERA){
        return MONITORED;
    } else {
        return UNMONITORED;
    }
}
int minCameraCover(struct TreeNode* root) {
    int cameras = 0;
    if (counter(root, &cameras) == UNMONITORED){
        cameras++;
    }
    return cameras;
    
}