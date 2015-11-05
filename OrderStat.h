#ifndef ORDERSTAT 
#define ORDERSTAT

#include <algorithm>
#include <iostream>
using std::cout;
template<typename T>
class OrderStat {
    struct Node {
        Node* right;
        Node* left; 
        Node* parent; 
        T data; 
        int ht; 
        int size; 
        Node(Node* r, Node* l, Node* p, T d,int h){
            right = r;
            left = l;
            parent = p; 
            data = d;
            ht = h;
        }
    };

    // TODO: Your data for the tree.
    Node* root; 

public:
    typedef T value_type;

    class const_iterator;

    class iterator{
        Node* loc;
        bool itrend;
    public:
        friend class const_iterator;
        iterator(Node* l,bool b):loc(l),itrend(b){}
            
        Node* Successor(Node* x){
         if (x->right != nullptr){
            return OrderStat<T>::minNode(x->right);
         } 
          Node* y = x->parent;
          while (y != nullptr && x == y->right){
                x = y;
                y = y->parent;
            }
            return y;
        }

        Node* Predecessor(Node* x){
         if (x->left != nullptr){
            return OrderStat<T>::maxNode(x->left);
         } 
         Node* y = x->parent;
         while (y != nullptr && x == y->left){
                x = y;
                y = y->parent;
         }
            return y;
        }

        bool operator==(const iterator &i) const { 
            return (loc == i.loc && itrend == i.itrend); 
        }

        bool operator!=(const iterator &i) const { return !(*this==i); }

        T &operator*() { return loc -> data; }

        iterator &operator++() {
            Node* tmp = Successor(loc);
            if(tmp == nullptr){
                itrend = true;
            }else{
                loc = tmp;
                itrend =false;
            }
            return *this;
        }
        iterator &operator--(){
            if(itrend){
                itrend = false;
                return *this;
            }else{
                loc = Predecessor(loc);
                return *this;
            }
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };


    class const_iterator {
        Node* loc;
        bool itrend;
    public:
        friend class OrderStat<T>;
        const_iterator(Node* l,bool b):loc(l),itrend(b) {}
        const_iterator(const iterator &iter):loc(iter.loc),itrend(iter.itrend){}
        
        Node* Successor(Node* x){
         if (x->right != nullptr){
            return OrderStat<T>::minNode(x->right);
         } 
          Node* y = x->parent;
          while (y != nullptr && x == y->right){
                x = y;
                y = y->parent;
            }
            return y;
        }
        Node* Predecessor(Node* x){
         if (x->left != nullptr){
            return OrderStat<T>::maxNode(x->left);
         } 
         Node* y = x->parent;
         while (y != nullptr && x == y->left){
                x = y;
                y = y->parent;
         }
         return y;
        }

        bool operator==(const const_iterator &i) const { return (loc == i.loc && itrend == i.itrend); }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const T &operator*() { return loc->data;}
        const_iterator &operator++() {
            Node* tmp = Successor(loc);
            if(tmp == nullptr){
                itrend = true;
            }else{
                loc = tmp;
                itrend=false;
            }
            return *this;
        }

        const_iterator &operator--() {
            if(itrend){
                itrend = false;
            }else{
                loc = Predecessor(loc);
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        const_iterator operator--(int) {
            const_iterator tmp(*this);
            --(*this);
            return tmp;
        }

        Node* getNode(){
            return loc;
        }
        bool getBool(){
            return itrend;
        }
    };

    OrderStat(){
        root = nullptr;
    }

    ~OrderStat() {
       clear();
    } 

   Node* helpCopier(Node *x,Node* prt){
        Node* tmp; 
        if(x!=nullptr){
            tmp = new Node(nullptr,nullptr,nullptr,x->data,x->ht);
            tmp->parent = prt;
            tmp->left = helpCopier(x->left,tmp);
            tmp->right = helpCopier(x->right,tmp);
            return tmp;
        } else return nullptr; 
    }

    OrderStat(const OrderStat<T> &that) {
        root = nullptr;
        root = helpCopier(that.root,root);
    }

    OrderStat &operator=(const OrderStat<T> &that) {
        clear();
        root=nullptr;
        helpCopier(that.root,root);
        return *this;
    }

    static Node* maxNode(Node* x){
        if(x!= nullptr){
            while (x->right != nullptr){
             x = x->right;
            } 
        }
        return x;
    }

    static Node* minNode(Node* x){
       if(x!= nullptr){
       while (x->left != nullptr){
            x = x->left;
        } 
      }
        return x;
    }

    void transplant(Node* u, Node* v){
        if(u->parent == nullptr){
            root = v;
        } else if (u == u->parent->left){
            u->parent->left = v;
        } else u->parent->right = v;
        if (v != nullptr){
            v->parent = u->parent;
        }
    }

    void LeftRotate(Node* x){
        Node* y = x->right;
        transplant(x,y);
        x->right = y->left;
        if(y->left != nullptr){
            y->left->parent = x;
        }
        y->left = x;
        x->parent = y;
    }

    void RightRotate(Node* x){
        Node* y = x->left;
        transplant(x,y);
        x->left = y->right;
        if(y->right != nullptr){
            y->right->parent = x;
        }
        y->right = x;
        x->parent = y;
    }

    void balance(Node* t){
         Node* rover = t;
         while((rover != nullptr) && (std::abs((height(rover->right) - height(rover->left))) < 2) ){
            rover = rover -> parent;
         }   
         if(rover != nullptr){
            if(height(rover -> left) > height(rover -> right)){
                if(height(rover->left->left) < height(rover->left->right)){
                    LeftRotate(rover->left);
                    RightRotate(rover);
                    rover->ht = 1 + height(rover->right) + height(rover->left);
                    fixheight(rover->parent->left);
                }
                else{
                    RightRotate(rover);
                    fixheight(rover);
                }
            } else{
                 if(height(rover -> right -> right) < height(rover -> right -> left)){
                    RightRotate(rover->right);
                    LeftRotate(rover);
                    rover->ht = 1 + height(rover->right) + height(rover->left);
                    fixheight(rover->parent->right);
                 } else {
                    LeftRotate(rover);
                    fixheight(rover);
                 }
            }
         }
    }  

    int height(Node* x) const{
        if(x==nullptr){
            return 0;
        } else return x->ht;
    }
    void fixheight(Node* x){
        while (x != nullptr){
            x->ht = height(x->right) + height(x->left) + 1; 
            x = x->parent;
        }
    }

    bool empty() const {return root==nullptr;}
    
    unsigned size() const {return height(root);}

    value_type &front(){
        return minNode(root)->data;
    }
    const value_type &front() const{
        return minNode(root)->data;
    }
    value_type &back(){
        return maxNode(root)->data;
    }
    const value_type &back() const{
        return maxNode(root)->data;
    }

    iterator insert(const_iterator position,const value_type& val){
         iterator tmp = iterator(position.loc,position.itrend);
        if(position == cbegin()){
            push_front(val);
            fixheight(cbegin().loc);
            balance(cbegin().loc);
        } else {
            position--;
            Node* thingish = position.loc->right;
            position.loc->right = new Node(thingish,nullptr,position.loc,val,1);
            if(thingish != nullptr) {
                thingish->parent = position.loc->right;
                fixheight(thingish);
                balance(thingish);
            } else {
                fixheight(position.loc->right);
                balance(position.loc->right);
            }
            
        }
        tmp--;
        return tmp; 
    }

    template <class InputIterator>
    void insert(const_iterator position,InputIterator first, InputIterator last){
        for(auto iter = first; iter!=last; ++iter) {
            insert(position,*iter);
        }
    }

    iterator erase(const_iterator position){
        Node* z = position.loc;
        if(z->left == nullptr){
                iterator itertmp = iterator(position.getNode(),position.getBool());
                ++itertmp;
                Node* tmp = z->right;
                transplant(z,z->right);
                fixheight(z);
                delete z;
                balance(tmp);
                return itertmp;
        }else if(z->right == nullptr){
                iterator itertmp = iterator(position.getNode(),position.getBool());
                ++itertmp;
                Node* tmp = z->left;
                transplant(z,z->left);
                delete z; 
                fixheight(minNode(tmp));
                balance(tmp);
                return itertmp;
        }else { 
                iterator itertmp = iterator(position.getNode(),position.getBool());
                ++itertmp;
                Node* y = minNode(z->right);
                if(y->parent != z){
                  transplant(y,y->right);
                  y->right = z->right;
                  y->right->parent = y;
                }
                transplant(z,y);
                y->left = z->left;
                y->left->parent = y;
                delete z; 
                fixheight(minNode(y->right));
                balance(minNode(y->right));
                return itertmp;
        }
    }

    void cleartree(Node* x){  
        if(x!=nullptr){
            if(x->left!=nullptr)cleartree(x->left);
            if(x->right!=nullptr)cleartree(x->right);
            delete x;
        }
    }

    void clear(){
        if(root!= nullptr) cleartree(root);
        root = nullptr;
    }

    Node* Select(Node* t, int i){
        if(t == nullptr) return t;
        else {
            int r = height(t->left);
            if(i == r) return t;
            else if (i<r) return Select(t->left,i);
            else return Select(t->right, i - (r+1));
        }
    }

    value_type &operator[](int index){
        auto thing = Select(root,index);
        if(thing != nullptr) return thing->data;
    }

    void push_front(const value_type& val){
        if(root==nullptr){root = new Node(nullptr,nullptr,nullptr,val,1);
            return;}
        Node* x = root;
        while(x->left != nullptr){
            x = x->left;
        }
        x->left = new Node(nullptr,nullptr,x,val,1);
        fixheight(x);
        balance(x);
    }

   void pop_front(){
        //Use AVLMap's erase on the min node
        //fixheightSize(minNode(root));
        erase(const_iterator(minNode(root),false));
        fixheight(minNode(root));
        balance(minNode(root));
    }
    void push_back(const value_type& val){
        if(root==nullptr){
            root = new Node(nullptr,nullptr,nullptr,val,1);
            return;
        }
        Node* x = root;
        while(x->right != nullptr){
            x = x->right;
        }
        x->right = new Node(nullptr,nullptr,x,val,1);
        fixheight(x);
        balance(x);
    }

    void pop_back(){
        //use AVLMap's erase on the max node
        //fixheightSize(maxNode(root));
        erase(const_iterator(maxNode(root),false));
        fixheight(maxNode(root));
        balance(maxNode(root));
    }

   bool operator==(const OrderStat<T>& rhs) const{
        if(size() != rhs.size()){        
            return false;
        }
        const_iterator rsitr = rhs.cbegin();
        for(auto x = cbegin(); x!= cend(); ++x){
            if(x.loc->data != rsitr.loc->data){
                return false;
            }
            ++rsitr;
        }
        return true;
    } 

    bool operator!=(const OrderStat<T>& rhs) const{
        return !(*this==rhs);
    }

    iterator begin() {
        if(root==nullptr){
            return end();
        }else {
            return iterator(minNode(root),false);
        }
    }
    
    const_iterator begin() const {return cbegin();}
    
    iterator end() {
        if(root==nullptr){
            return iterator(root,true); 
        }else {
            return iterator(maxNode(root),true); 
        }
    }

    const_iterator end() const {return cend();}

    const_iterator cbegin() const { 
        if(root==nullptr){
            return cend();
        }else {
            return const_iterator(minNode(root),false); 
        }
    }
    const_iterator cend() const { 
        if(root==nullptr){
            return const_iterator(root,true);
        } else {
            return const_iterator(maxNode(root),true);
        }
    }

    void printPreOrder(Node* x){
        if (x == nullptr){
            std::cout << "NONE ";
            return;
        }
        std::cout << x->data << "\n";
        std::cout << x->data << "'s left : ";
        printPreOrder(x->left);
        std::cout << x->data  << "'s right : ";
        printPreOrder(x->right);       
    }

    Node* getroot(){
        return root;
    }


};

#endif