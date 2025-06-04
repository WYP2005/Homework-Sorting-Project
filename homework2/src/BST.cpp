#include <iostream>
#include <random>
#include <cmath>
#include <utility>
#include <vector>
#include <chrono>

using namespace std;

template <class K, class E> class TreeNode;

template <class K, class E>
class Dictionary {
public:
    virtual bool IsEmpty() const = 0;
    virtual pair<K, E>* Get(const K&) const = 0;
    virtual void Insert(const pair<K, E>&) = 0;
    virtual void Delete(const K&) = 0;
    virtual TreeNode<K, E>* findMin(TreeNode<K, E>*) = 0;
};

template <class K, class E>
class TreeNode {
public:
    TreeNode* leftChild;
    TreeNode* rightChild;
    pair<K, E> data;
    TreeNode(pair<K, E> e) {
        this->data.first = e.first;
        this->data.second = e.second;
        this->leftChild = NULL;
        this->rightChild = NULL;
    }
};

template <class K, class E>
class BST : public Dictionary<K, E> {
private:
    TreeNode<K, E>* root;
    int height(TreeNode<K, E>* node) const;

public:
    int count = 0;
    double total = 0;
    BST() { root = 0; }
    bool IsEmpty() const override;
    pair<K, E>* Get(const K&) const override;
    void Insert(const pair<K, E>&) override;
    void Delete(const K&) override;
    TreeNode<K, E>* findMin(TreeNode<K, E>*) override;
    int getHeight() const;
};

template <class K, class E>
int BST<K, E>::height(TreeNode<K, E>* node) const {
    if (!node) return 0;
    return 1 + max(height(node->leftChild), height(node->rightChild));
}

template <class K, class E>
bool BST<K, E>::IsEmpty() const {
    return root == 0;
}

template <class K, class E>
pair<K, E>* BST<K, E>::Get(const K& k) const {
    TreeNode<K, E>* currentNode = root;
    while (currentNode) {
        if (k < currentNode->data.first)
            currentNode = currentNode->leftChild;
        else if (k > currentNode->data.first)
            currentNode = currentNode->rightChild;
        else
            return &(currentNode->data);
    }
    return 0;
}

template <class K, class E>
void BST<K, E>::Insert(const pair<K, E>& thePair) {
    TreeNode<K, E>* p = root, * pp = 0;
    while (p) {
        pp = p;
        if (thePair.first < p->data.first)
            p = p->leftChild;
        else if (thePair.first > p->data.first)
            p = p->rightChild;
        else {
            p->data.second = thePair.second;
            return;
        }
    }
    p = new TreeNode<K, E>(thePair);
    if (root) {
        if (thePair.first < pp->data.first)
            pp->leftChild = p;
        else
            pp->rightChild = p;
    }
    else
        root = p;
}

template <class K, class E>
TreeNode<K, E>* BST<K, E>::findMin(TreeNode<K, E>* node) {
    if (node == 0 || node->leftChild == 0) return node;
    return findMin(node->leftChild);
}

template <class K, class E>
void BST<K, E>::Delete(const K& k) {
    TreeNode<K, E>* p = root, * pp = 0;
    while (p && p->data.first != k) {
        pp = p;
        if (k < p->data.first)
            p = p->leftChild;
        else
            p = p->rightChild;
    }
    if (!p) return;

    if (p->leftChild && p->rightChild) {
        TreeNode<K, E>* successor = findMin(p->rightChild);
        p->data = successor->data;
        Delete(successor->data.first);
    }
    else {
        TreeNode<K, E>* nodeToDelete = p;
        if (pp) {
            if (p->leftChild)
                p = p->leftChild;
            else
                p = p->rightChild;
            if (nodeToDelete == pp->leftChild)
                pp->leftChild = p;
            else
                pp->rightChild = p;
        }
        else {
            root = p->leftChild ? p->leftChild : p->rightChild;
        }
        delete nodeToDelete;
    }
}

template <class K, class E>
int BST<K, E>::getHeight() const {
    return height(root);
}

void permute(vector<int>& arr, int n, mt19937& gen) {
    for (int i = n - 1; i >= 1; --i) {
        int j = gen() % (i + 1); 
        swap(arr[i], arr[j]);
    }
}

int main() {
    random_device rd;
    mt19937 gen(rd());

    BST<int, int> bst;

    cout << "n,Ratio\n"; 
        int n = 10000;
        vector<int> keys(n);
        for (int j = 0; j < n; j++) {
            keys[j] = j + 1;
        }
        permute(keys, n, gen);
        for (int j = 0; j < n; j++) {
            int value = gen() % 1000000 + 1; 
            pair<int, int> p(keys[j], value);
            bst.Insert(p);
        }
        int key_to_delete = keys[gen() % n]; 
        auto start = chrono::high_resolution_clock::now();
        bst.Delete(key_to_delete);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        double delete_time_ms = duration / 1000.0; 

        int h = bst.getHeight();
        double ratio = (double)h / log2(n);
        cout << n << "," << h << "," << ratio << "," << delete_time_ms << endl;   
        return 0;
}
