#include <iostream>
using namespace std;
struct NODE{
    int key;
    int height;
    NODE* left;
    NODE* right;
};

NODE* createNode(int data){
    NODE* node = new NODE;
    node->key = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

int height(NODE* pRoot){
    if (!pRoot) return 0;
    return pRoot->height;
}

int getBalance(NODE* pRoot){
    if (!pRoot) return 0;
    return height(pRoot->left) - height(pRoot->right);
}

void leftRotate(NODE* &pRoot){
    NODE* y = pRoot->right;
    NODE* sub = y->left;

    y->left = pRoot;
    pRoot->right = sub;

    pRoot->height = 1 + max(height(pRoot->left), height(pRoot->right));
    y->height = 1 + max(height(y->left), height(y->right));

    pRoot = y;
}

void rightRotate(NODE* &pRoot){
    NODE* y = pRoot->left;
    NODE* sub = y->right;

    y->right = pRoot;
    pRoot->left = sub;

    pRoot->height = 1 + max(height(pRoot->left), height(pRoot->right));
    y->height = 1 + max(height(y->left), height(y->right));

    pRoot = y;
}

void Insert(NODE* &pRoot, int x){
    if (!pRoot) {
        pRoot = createNode(x);
        return;
    }
    if (x > pRoot->key) Insert(pRoot->right, x);
    else if (x < pRoot->key) Insert(pRoot->left, x);
    else return;

    pRoot->height = 1 + max(height(pRoot->left), height(pRoot->right));

    int balance = getBalance(pRoot);

    if (balance > 1){
        if (getBalance(pRoot->left) >= 0){
            rightRotate(pRoot);
        }
        else{
            leftRotate(pRoot->left);
            rightRotate(pRoot);
        }
    }

    if (balance < -1){
        if (getBalance(pRoot->right) <= 0){
            leftRotate(pRoot);
        }
        else{
            rightRotate(pRoot->right);
            leftRotate(pRoot);
        }
    }
}

//void Remove(NODE* pRoot, int x){
//    if (pRoot->key < x){
//
//    }
//}


void Inorder(NODE* pRoot){
    if (!pRoot) return;
    Inorder(pRoot->left);
    cout << pRoot->key << ' ' ;
    Inorder(pRoot->right);
}

void postOrder(NODE* pRoot){
    if (!pRoot) return;
    postOrder(pRoot->left);
    postOrder(pRoot->right);
    cout << pRoot->key << ' ';
}

NODE* getInSuc(NODE* pRoot){
    NODE* cur = pRoot;
    while (cur->left){
        cur = cur->left;
    }
    return cur;
}

void Remove(NODE* &pRoot, int x){
    cout << pRoot->key << endl;
    if (!pRoot) return;
    if (pRoot->key > x){
        Remove(pRoot->left, x);
    }else if (pRoot->key < x){
        Remove(pRoot->right, x);
    }else{
            if (!pRoot->left || !pRoot->right){
                if (!pRoot->left && !pRoot->right){
                    delete pRoot;
                    pRoot = NULL;
                }
                else{
                    if (!pRoot->left){
                        NODE* tmp = pRoot;
                        pRoot = pRoot->right;
                        delete tmp;
                    }
                    if (!pRoot->right){
                        NODE* tmp = pRoot;
                        pRoot = pRoot->left;
                        delete tmp;
                    }
                }
        }else{
            NODE* p = getInSuc(pRoot->right);
            pRoot->key = p->key;
            Remove(pRoot->right, p->key);
        }
    }

    if (!pRoot) return;

    pRoot->height = 1 + max(height(pRoot->left), height(pRoot->right));

    int balance = getBalance(pRoot);

    if (balance > 1){

        if (getBalance(pRoot->left) >= 0){
            rightRotate(pRoot);
        }
        else{
            leftRotate(pRoot->left);
            rightRotate(pRoot);
        }
    }

    if (balance < -1){

        if (getBalance(pRoot->right) <= 0){

            leftRotate(pRoot);
        }
        else{
            rightRotate(pRoot->right);
            leftRotate(pRoot);
        }
    }



}

int main(){
    NODE* pRoot = NULL;
    Insert(pRoot, 1);
    Insert(pRoot, 4);
    Insert(pRoot, 2);
    Insert(pRoot, 6);
    Insert(pRoot, 3);
//    Insert(pRoot, 4);
//    Insert(pRoot, 5);
    Inorder(pRoot);
    cout << endl;
    postOrder(pRoot);
    cout << endl;
    Remove(pRoot,1);
    Remove(pRoot,6);
    cout << endl;
    Inorder(pRoot);
    cout << endl;
    postOrder(pRoot);
}

