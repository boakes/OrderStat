template<typename T>
class OrderStat {
    struct Node {
        Node* right;
        Node* left; 
        Node* parent; 
        T data; 
        int nodesz; 
        Node(Node* r, Node* l, Node* p, T d,int s){
            right = r;
            left = l;
            parent = p; 
            data = d;
            nodesz = s;
        }
    };

    // TODO: Your data for the tree.
    Node* root; 

public:
    typedef T value_type;

    class const_iterator;

    class iterator {
        // TODO: Your data for the iterator.
    public:
        friend class const_iterator;
        // TODO: constructors

        bool operator==(const iterator &i) const { /* TODO */ }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        T &operator*() { /* TODO */ }
        iterator &operator++() {
            // TODO
            return *this;
        }
        iterator &operator--() {
            // TODO
            return *this;
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
        // TODO: iterator data
    public:
        friend class OrderStat<T>;
        // TODO: constructors

        bool operator==(const const_iterator &i) const { /* TODO */ }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const T &operator*() { /* TODO */ }
        const_iterator &operator++() {
            // TODO
            return *this;
        }
        const_iterator &operator--() {
            // TODO
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
    };

    OrderStat(){
        root = nullptr;
    }
    OrderStat(const OrderStat<T> &that) {
        // TODO
    }
    ~OrderStat() {
        // TODO
    }

    OrderStat &operator=(const OrderStat<T> &that) {
        // TODO
    }


    int nodesize(Node* x){
        if(x==nullptr){
            return 0;
        } else return x->nodesz;
    }
    void fixsize(Node* x){
        while (x != nullptr){
            x->nodesz = nodesize(x->right) + nodesize(x->left) + 1; 
            x = x->parent;
        }
    }
    bool empty() const { return root==nullptr; }

    unsigned size() const {return nodesize(root);}

    value_type &front();
    const value_type &front() const;
    value_type &back();
    const value_type &back() const;

    iterator insert(const_iterator position,const value_type& val);

    template <class InputIterator>
    void insert(const_iterator position,InputIterator first, InputIterator last);

    iterator erase(const_iterator position);

    
    void cleartree(Node* x){  
        if(x!=nullptr){
            if(x->left!=nullptr)cleartree(x->left);
            if(x->right!=nullptr)cleartree(x->right);
            delete x;
        }
    }

    void clear(){
        if(root!= nullptr) cleartree(root);
        sz = 0;
        root = nullptr;
    }

    Node* Select(Node* t, int i){
        if(t == nullptr) return t;
        else {
            int r = nodesize(t->left);
            if(i == r) return t;
            else if (i<r) Select(t->left,i);
            else Select(t->right, i - (r+1));
        }
    }

    value_type &operator[](int index){
        auto thing = Select(root,index);
        if(thing != nullptr) return thing->data;
        value_type x = value_type();
        else return x;
    }

    void push_front(const value_type& val);
    void pop_front();
    void push_back(const value_type& val);
    void pop_back();

    bool operator==(const OrderStat<T>& rhs) const;

    bool operator!=(const OrderStat<T>& rhs) const;

    iterator begin() {
        // TODO
    }
    const_iterator begin() const {
        // TODO
    }

    iterator end() {
        // TODO
    }

    const_iterator end() const {
        // TODO
    }

    const_iterator cbegin() const {
        // TODO
    }

    const_iterator cend() const {
        // TODO
    }
};