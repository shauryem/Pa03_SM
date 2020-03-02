#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <array>
#include <queue>
#include <stack>
#include <algorithm>


using namespace std;

class BST{

     struct node {
        int data;
        node* left;
        node* right;
    };

    node* root;

    node* makeEmpty(node* t) {
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

    node* insert(int x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
            cout<<"Element inserted\n";
        }
        else if(x < t->data)
            t->left = insert(x, t->left);
        else if(x > t->data)
            t->right = insert(x, t->right);
        else if(x == t->data)
            cout<<"Element already present\n";   

             
        return t;
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t) {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(int x, node* t) {
        node* temp;
        if(t == NULL){
            cout<<"Element not found\n";
            return NULL;
        }
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            cout<<"Element deleted\n";  
            delete temp;
        }

        return t;
    }

    void inorder(node* t) {
    
        stack<node *> s; 
        node *curr = t; 
    
        while (curr != NULL || s.empty() == false) 
        { 

            while (curr !=  NULL) 
            { 
    
                s.push(curr); 
                curr = curr->left; 
            } 
    
    
            curr = s.top(); 
            s.pop(); 
    
            cout << curr->data << " "; 
    
        
            curr = curr->right; 
    
        } 
    }

    void preorder(node* root){

        if (root == NULL) 
        return; 
    
        
        stack<node *> nodeStack; 
        nodeStack.push(root); 
    

        while (nodeStack.empty() == false) 
        { 
        
            node *node = nodeStack.top(); 
            printf ("%d ", node->data); 
            nodeStack.pop(); 
    
            if (node->right) 
                nodeStack.push(node->right); 
            if (node->left) 
                nodeStack.push(node->left); 
        }     
        }

    void postorder(node* root){
        stack<node*> todo;
        node* last = NULL;
        while (root || !todo.empty()) {
            if (root) {
                todo.push(root);
                root = root -> left;
            } else {
                node* node = todo.top();
                if (node -> right && last != node -> right) {
                    root = node -> right;
                } else {
                    cout<<node -> data;
                    cout<<" ";
                    last = node;
                    todo.pop();
                }
            }
        }
    }
    int find(node* t, int x) {
        if(t == NULL){
            cout<<"Element not found\n";
            return 0;
        }
        else if(x < t->data)
            return find(t->left, x);
        else if(x > t->data)
            return find(t->right, x);
        else{
            cout<<"Element accessed\n";
            return 1;
        }
    }

public:
    BST() {
        root = NULL;
    }

    ~BST() {
        root = makeEmpty(root);
    }

    void insert(int x) {
        root = insert(x, root);
    }

    void remove(int x) {
        root = remove(x, root);
    }

    void display() {
        
        if(root == NULL){
            cout<<"Empty tree\n";
        }
        else{
            preorder(root);
            cout<<"\n";
            inorder(root);
            cout <<"\n";
            postorder(root);
            cout<<"\n";
        }
    }

    void search(int x) {
        int temp = find(root, x);
    }
};

void parseCommand(string a){

    
    BST b;
    vector<string> input;
    string temp = "";
    a.push_back(',');

    for(int i = 0; i < a.length(); i++){
        if(a[i] != ','){
           if(a[i] != ' '){
            temp += a[i];
           }
        }
        else {
            input.push_back(temp);
            temp ="";
        }
    }

   
    for(int i = 0; i < input.size(); i++){

        if(input[i].find("insert") != string::npos){
            input[i].erase(0,6);
            b.insert(stoi(input[i]));
        }
        else if (input[i].find("access") != string::npos){
            input[i].erase(0,6);
            b.search(stoi(input[i]));
        }
        else if (input[i].find("delete") != string::npos){
            input[i].erase(0,6);
            b.remove(stoi(input[i]));
        } 
        else if (input[i].find("print") != string::npos){
            b.display();
        }                      
    }
    

}

int main(int argv, char** argc) {

        if( argv != 2)  {
            return 1;
        }

        parseCommand(argc[1]);
        
        return 0;    
    return 0; 
}