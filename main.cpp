#include <iostream>
using namespace std;
struct NODE{
	int key;
	NODE* left;
	NODE* right;
	int height;
};

NODE* createNode(int data){
	NODE* p = new NODE;
	p->left = p->right = nullptr;
	p->key = data;
	p->height = 1;
	return p;
}

int height(NODE* pRoot){
	if (!pRoot) return 0;
	return pRoot->height;
}

int getBalance(NODE* pRoot){
	if (!pRoot) return 0;
	return height(pRoot->left) - height(pRoot->right);
}

void rightRotate(NODE* &pRoot){
	NODE* y = pRoot->left; //left child of pRoot
	NODE* T3 = y->right; //right child of the left child of pRoot
	
	y->right = pRoot;
	pRoot->left = T3;
	
	pRoot->height = 1 + max(height(pRoot->left), height(pRoot->right));
	y->height = 1 + max(height(y->left), height(y->right));
	
	pRoot = y;
}

void leftRotate(NODE* &pRoot){
	NODE* y = pRoot->right; //right child of pRoot
	NODE* T3 = y->left; //right child of the left child of pRoot
	y->left = pRoot;
	pRoot->right = T3;
	
	pRoot->height = 1 + max(height(pRoot->left), height(pRoot->right));
	y->height = 1 + max(height(y->left), height(y->right));
	
	pRoot = y;
}

void insert(NODE* &pRoot, int x){
	// BST insertion 
	if (!pRoot) {
		pRoot = createNode(x);
		return;
	}
	
	if (x < pRoot->key){
		insert(pRoot->left, x);
	}else if (x > pRoot->key){
		insert(pRoot->right, x);
	}else{
		// x has already been in the tree
		return;
	}
	
	pRoot->height = 1 + max(height(pRoot->left), height(pRoot->right));
	int balance = getBalance(pRoot);
	if (balance > 1){
		// left left case
		if (x < pRoot->left->key) rightRotate(pRoot);
		else {
			// left right case
			leftRotate(pRoot->left);
			rightRotate(pRoot);
		}
	}
	
	if (balance < -1){
		// right right case
		if (x > pRoot->right->key) {
			leftRotate(pRoot);
		}
		else {
			// right left case
			rightRotate(pRoot->right);
			leftRotate(pRoot);
		}
	}
		
}

NODE* getInorderSuccessor(NODE* pRoot){
	NODE* cur = pRoot;
	while (cur->left) cur = cur->left;
	return cur;
}

void remove(NODE* &pRoot, int x){
	// bst remove
	if (!pRoot) return;
	if (x > pRoot->key) remove(pRoot->right, x);
	else if (x < pRoot->key) remove(pRoot->left, x);
	else {
		// case 1: node is a leaf
		if (!pRoot->left && !pRoot->right){
			delete pRoot;
			pRoot = nullptr;
		}else{
			// case 2: node has 1 child
			if ((pRoot->left && !pRoot->right)|| (!pRoot->left && pRoot->right)){
				if (pRoot->left){
					pRoot->key = pRoot->left->key;
					delete pRoot->left;
					pRoot->left = nullptr;
				}else{
					pRoot->key = pRoot->right->key;
					delete pRoot->right;
					pRoot->right = nullptr;
				}
			}else{
			// case 3: node has 2 children
				//find the minimun node in the right subtree or find the maximum node in the left subtree
				NODE* tmp = getInorderSuccessor(pRoot->right);
				pRoot->key = tmp->key;
				remove(pRoot->right, tmp->key);
			}
		}
	}
	
	if (!pRoot) return;
	
	// update height for current node
	pRoot->height = 1 + max(height(pRoot->left), height(pRoot->right));
	
	int balance = getBalance(pRoot);
	
	if (balance > 1){
		// left left case
		if (getBalance(pRoot->left) >= 0) rightRotate(pRoot);
		else {
			// left right case
			leftRotate(pRoot->left);
			rightRotate(pRoot);
		}
	}
	else if (balance < -1){
		// right right case
		if (getBalance(pRoot->right) <= 0) {
			leftRotate(pRoot);
		}
		else {
			// right left case
			rightRotate(pRoot->right);
			leftRotate(pRoot);
		}
	}
}

bool isAVL(NODE* pRoot){
	if (!pRoot) return true;
	
	if (abs(getBalance(pRoot)) <= 1 && isAVL(pRoot->left) && isAVL(pRoot->right)) return true;
	return false;
}

void inorder_traverse(NODE* pRoot){
	if (!pRoot) return;
	inorder_traverse(pRoot->left);
	cout << pRoot->key << ' ';
	inorder_traverse(pRoot->right);
}

void preorder_traverse(NODE* pRoot){
	if (!pRoot) return;
	cout << pRoot->key << ' ';
	preorder_traverse(pRoot->left);
	preorder_traverse(pRoot->right);
}

int main(){
	NODE* pRoot = nullptr;
	insert(pRoot, 1);
	insert(pRoot, 2);
	insert(pRoot, 3);
	insert(pRoot, 4);
	insert(pRoot, 5);
	insert(pRoot, 6);
	preorder_traverse(pRoot);
	cout << endl;
	remove(pRoot, 4);
	preorder_traverse(pRoot);
	cout << endl;
	remove(pRoot, 5);
	preorder_traverse(pRoot);
	cout << endl;
	cout << isAVL(pRoot);
}