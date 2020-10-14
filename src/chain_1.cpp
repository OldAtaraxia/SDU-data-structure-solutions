#include<iostream>
#include<cstdio>
#include<algorithm>
#include<sstream>

using namespace std;

template <class T>
struct chainNode{
    T element;
    chainNode<T> *next;

    chainNode() {}
    chainNode(const T& element){
        this->element = element;
    }
    chainNode(const T& element, chainNode<T> *next){
        this->element = element;
        this->next = next;
    }
};

template<class T>
class chain{
    public:
        chain(int initialCapacity = 10);
        chain(const chain<T> &);
        ~chain();

        bool empty() const { return listSize == 0; }
        int size();
        T &get(int theIndex);
        int indexOf(const T &theElement) const;
        void erase(int theIndex);
        void insert(int theIndex, const T &theElement);
        void output(std::ostream &out);
        void reverse();
        void push_back(const T &theElememt);

    //迭代器
    class iterator{
    public:
        typedef forward_iterator_tag iterator_category;  //向前迭代器
        typedef T value_type;
        typedef T* pointer;  //指针
        typedef T& reference;  //引用
        iterator(chainNode<T>* theNode = NULL) {node = theNode;}
        T& operator*() const {return node->element;}
        T* operator->() const {return &node->element;}

        iterator& operator++() {node = node->next; return *this;}  //前加
        iterator operator++(int){  //后加
            iterator old = *this;
            node = node->next;
            return old;
        }
        bool operator!=(const iterator right) const {return node != right.node;}
        bool operator==(const iterator right) const {return node == right.node;}
    protected:
        chainNode<T>* node;  //结点指针
    };

    //首元素的迭代器
    iterator begin() {return iterator(firstNode);}
    //尾元素下一个位置的迭代器
    iterator end() {return iterator(NULL);}

    protected:
        void checkIndex(int theIndex) const;
        chainNode<T> *firstNode;
        int listSize;
};

//构造函数
template<class T>
chain<T>::chain(int initialCapacity){
    if(initialCapacity < 1){
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw s.str();
    }
    firstNode = NULL;
    listSize = 0;
}

//复制构造函数
template<class T>
chain<T>::chain(const chain<T> & theList){
    listSize = theList.size();

    if(listSize == 0){
        firstNode = NULL;
        return;
    }
    chainNode<T> *sourceNode = theList.firstNode;
    firstNode = new chainNode<T>(sourceNode->element);
    sourceNode = sourceNode->next;
    chainNode<T> *targetNode = firstNode;
    while(sourceNode != NULL){
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
}

//析构函数
template<class T>
chain<T>::~chain(){
    while(firstNode != NULL){
        chainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class T>
void chain<T>::checkIndex(int theIndex) const {
    //确定索引theIndex在0 和 listSize - 1之间
    if(theIndex < 0 || theIndex >= listSize){
        ostringstream s;
        s << "index = " << theIndex << "size = " << listSize;
        throw s.str();
    }
}

//get,根据index找元素
template<class T>
T& chain<T>::get(int theIndex){
    checkIndex(theIndex);
    chainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; i++){
        currentNode = currentNode->next;
    }
    return currentNode->element;
}

//indexOf 找某个元素第一次出现的索引
template<class T>
int chain<T>::indexOf(const T& theElement) const{
    chainNode<T> *currentNode = firstNode;
    int index = 0;
    while(currentNode != NULL && currentNode->element != theElement){
        currentNode = currentNode->next;
        index++;
    }
    if(currentNode == NULL)
        return -1;
    else
        return index;
}

//erase
template<class T>
void chain<T>::erase(int theIndex){
    chainNode<T> *deleteNode;
    if(theIndex == 0){
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }else{
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++){
            p = p->next;
        }
        deleteNode = p->next;
        p->next = p->next->next;
    }
    listSize--;
    delete deleteNode;
}

//insert
template<class T>
void chain<T>::insert(int theIndex, const T& theElement){
    if(theIndex < 0 || theIndex > listSize){
        throw "invalid index";
    }

    if(theIndex == 0){
        firstNode = new chainNode<T>(theElement, firstNode);
    }else{
        chainNode<T> *p = firstNode;
        for(int i = 0; i < theIndex - 1; i++){
            p = p->next;
        }
        p->next = new chainNode<T>(theElement, p->next);
    }
    listSize++;
}

template<class T>
void chain<T>::push_back(const T &theElement){
    insert(listSize, theElement);
}


//输出链表
template<class T>
void chain<T>::output(std::ostream& out){
    int ans = 0, idx = 0;
    for (iterator currentNode = begin(); currentNode != end(); currentNode++){
        ans += (idx ^ *currentNode);
        idx++;
    }
    out << ans << endl;
}


template <class T>
void chain<T>::reverse() {
    if(listSize < 2) return;

    chainNode<T>* currentNode = firstNode->next;
    firstNode->next = NULL;
    while(currentNode != NULL){
        chainNode<T>* nextNode = currentNode->next;
        currentNode->next = firstNode;
        firstNode = currentNode;
        currentNode = nextNode;
    }
}


int n, q, k, idx, val, toErase;
int main(){
    ios::sync_with_stdio(0);
    //freopen("out.txt", "w", stdout); 
    cin >> n >> q;
    chain<int> a(n);
    for (int i = 0; i < n;i++){
        cin >> val;
        a.push_back(val);
    }
    while(q--){
        cin >> k;
        
        switch(k){
            case 1:
                cin >> idx >> val;
                a.insert(idx, val);
                break;
            case 2:
                cin >> val;
                toErase = a.indexOf(val);
                if(toErase == -1){
                    cout << -1 << endl;
                }else{
                    a.erase(toErase);
                }
                break;
            case 3:
                a.reverse();
                break;
            case 4:
                cin >> val;
                cout << a.indexOf(val) << endl;
                break;
            case 5:
                a.output(cout);
                break;
            default:
                break;
        }
    }
    return 0;
}