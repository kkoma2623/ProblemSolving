// 길 찾기 게임
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Node{
    public:
        int num;
        int x, y;
        Node *l = nullptr;
        Node *r = nullptr;
};

void insertNode(Node *pare, Node *child){
    if(pare->x < child->x){
        if(pare->r == NULL){
            pare->r = child;
            
            return;
        }
        
        insertNode(pare->r, child);
    } else{
        if(pare->l == NULL){
            pare->l = child;
            
            return;
        }
        insertNode(pare->l, child);
    }
}

bool comp(Node a, Node b){
    if(a.y == b.y){
        return a.x < b.x;
    }
    
    return a.y > b.y;
}

void preOrder(vector<int> &v, Node *n){
    if(n == NULL){
        return;
    }

    v.push_back(n->num);
    preOrder(v, n->l);
    preOrder(v, n->r);
}

void postOrder(vector<int> &v, Node *n){
    if(n == NULL){
        return;
    }
    
    postOrder(v, n->l);
    postOrder(v, n->r);
    v.push_back(n->num);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    vector<Node> n;
    for(int i=0; i<nodeinfo.size(); ++i){
        n.push_back({i+1, nodeinfo[i][0], nodeinfo[i][1]});
    }
    sort(n.begin(), n.end(), comp);
    Node *root = &n[0];
    
    for(int i=1; i<n.size(); ++i){
        insertNode(root, &n[i]);
    }
    vector<int> pre;
    preOrder(pre, root);
    answer.push_back(pre);
    vector<int> post;
    postOrder(post, root);
    answer.push_back(post);
    return answer;
}