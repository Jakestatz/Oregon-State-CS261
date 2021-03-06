/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Jake Statz
 * Email: Statzj@oregonstate.edu
 */

#include <stdlib.h>
#include <stdbool.h>
#include "bst.h"
#include "stack.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node{
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst{
  struct bst_node* root;
};

void free_bst(struct bst_node* node);
int getSize(struct bst_node* node);

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create(){
    struct bst* tree = malloc(sizeof(struct bst));
    return tree;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */


void bst_free(struct bst* bst) {
    free_bst(bst->root);
    free(bst);
}

void free_bst(struct bst_node* node) {
    if (node == NULL)
        return;
    free_bst(node->right);
    free_bst(node->left);
    free(node);

}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */

int bst_size(struct bst* bst){
    return getSize(bst->root);
}


int getSize(struct bst_node* node){
    if (node == NULL)
        return 0;
    else
        return (1 + getSize(node->left) + getSize(node->right));
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */

void bst_insert(struct bst* bst, int key, void* value){
    struct bst_node* parent = NULL;
    struct bst_node* curr = bst->root;
    struct bst_node* new_leaf = malloc(sizeof(struct bst_node));

    while (curr != NULL) {
        parent = curr;
        if (key < curr->key) {
            curr = curr->left;
        }
        else
            curr = curr->right;
    }
    new_leaf->key = key;
    new_leaf->value = value;
    new_leaf->left = NULL;
    new_leaf->right = NULL;

    if (parent == NULL)
        bst->root = new_leaf;
    else if (key < parent->key)
        parent->left = new_leaf;
    else if (key > parent->key)
        parent->right = new_leaf;
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */


void bst_remove(struct bst* bst, int key){
    struct bst_node* parent = NULL;
    struct bst_node* curr = bst->root;

    struct bst_node* parent_successor = NULL;
    struct bst_node* successor = NULL;

    bool trueorfalse;

    while (curr->key != key) {
        parent = curr;
        if (key < curr->key) {
            curr = curr->left;
            trueorfalse = 1;
        }
        else
            curr = curr->right;
        trueorfalse = 0;
    }

    if (curr->left == NULL && curr->right == NULL) {
        if (trueorfalse == 1)
            parent->left = NULL;
        else if (trueorfalse == 0)
            parent->right = NULL;
    }

    else if (curr->left != NULL && curr->right != NULL) {
        successor = curr->right;
        while (successor->left != NULL) {
            parent_successor = successor;
            successor = successor->left;
        }
        successor->left = curr->left;
        if (successor != curr->right) {
            parent_successor->left = successor->right;
            successor->right = curr->right;
        }
        if (parent == NULL) {
            bst->root = successor;
        }
        else if (trueorfalse = 1)
            parent->left = successor;
        else if (trueorfalse = 0) {
            parent->right = successor;
        }

    }
    else if (curr->left != NULL) {
        if (curr == parent->left)
            parent->left = curr->left;
        else if (curr == parent->right)
            parent->right = curr->left;

        curr = NULL;

    }
    else if (curr->right != NULL) {
        if (curr == parent->left)
            parent->left = curr->right;
        else if (curr == parent->right)
            parent->right = curr->right;

        curr = NULL;
    }

    free(curr);
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key){
    struct bst_node* curr = bst->root;

    while (curr != NULL) {
        if (key == curr->key)
            return curr->value;
        else if (key < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }

    return NULL;
}