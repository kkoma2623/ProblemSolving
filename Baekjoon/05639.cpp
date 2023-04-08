#include <iostream>

using namespace std;

struct node{
  int val;
  node* left;
  node* right;
};

node* insert(node* root, int val){
  if (root == NULL){
    root = new node;
    root->val = val;
    root->left = NULL;
    root->right = NULL;
    return root;
  }
  if (val < root->val) {
    root->left = insert(root->left, val);
  }
  if (val > root->val) {
    root->right = insert(root -> right, val);
  }

  return root;
}

void postOrder(node* root){
  if (root == NULL) {
    return;
  }
  if(root->left != NULL) {
    postOrder(root->left);
  }
  if(root-> right != NULL){
    postOrder(root->right);
  }
  cout << root->val << "\n";
}

void solve(){
  node* root = NULL;
  int val;
  while(cin >> val){
    if (val == EOF)
      break;
    if (root == NULL)
      root = insert(root, val);
    else
      insert(root, val);
  }

  postOrder(root);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}