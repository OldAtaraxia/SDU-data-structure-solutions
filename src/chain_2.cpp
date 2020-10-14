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
        chain();
        chain(const chain<T> &);
        ~chain();

        bool empty() const { return listSize == 0; }
        int size() const {return listSize;}
        T &get(int theIndex);
        int indexOf(const T &theElement) const;
        void erase(int theIndex);
        void insert(int theIndex, const T &theElement);
        void output();
        void reverse();
        void push_back(const T &theElememt);
        void sort(int l, int r);
        void set(int theIndex, T theElement);

        //迭代器
        class iterator{
        public:
            typedef forward_iterator_tag iterator_category; //向前迭代器
            typedef T value_type;
            typedef T *pointer;   //指针
            typedef T &reference; //引用
            iterator(chainNode<T> *theNode = NULL) { node = theNode; }
            T &operator*() const { return node->element; }
            T *operator->() const { return &node->element; }

            iterator &operator++()
            {
                node = node->next;
                return *this;
            } //前加
            iterator operator++(int)
            { //后加
                iterator old = *this;
                node = node->next;
                return old;
            }
            bool operator!=(const iterator right) const { return node != right.node; }
            bool operator==(const iterator right) const { return node == right.node; }

        protected:
            chainNode<T> *node; //结点指针
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
chain<T>::chain(){
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
    //checkIndex(theIndex);
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
void chain<T>::output(){
    int ans = 0, idx = 0;
    for (iterator currentNode = begin(); currentNode != end(); currentNode++){
        ans += (idx ^ *currentNode);
        idx++;
        //cout << *currentNode << " ";
    }
    //cout << endl;
    cout << ans << endl;
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

template<class T>
void chain<T>::set(int theIndex, T theElement){
    chainNode<T> * currentNode = firstNode;
    for (int i = 0; i < theIndex; i++){
        currentNode = currentNode->next;
    }
    currentNode->element = theElement;

}



template <class T> 
void mesh(chain<T> &a, chain<T> &b, chain<T> &c){
    int a_index = 0, b_index = 0;
    while(a_index < a.size() && b_index < b.size()){
        if(a.get(a_index) <= b.get(b_index)){
            c.push_back(a.get(a_index));
            a_index++;
        }else{
            c.push_back(b.get(b_index));
            b_index++;
        }
    }
    while(a_index < a.size()){
        c.push_back(a.get(a_index));
        a_index++;
    }
    while(b_index < b.size()){
        c.push_back(b.get(b_index));
        b_index++;
    }
}

void quick_sort(int q[],int l,int r){
    if(l >= r) return;

    int i = l - 1, j = r + 1, x = q[(l + r) / 2];
    while(i<j){
        do{
            i++;
        } while (q[i] < x);
        do{
            j--;
        } while (q[j] > x);
        if(i<j)
            swap(q[i], q[j]);
    }
    quick_sort(q,l,j);
    quick_sort(q,j+1,r);
}



int n, m, val;
int main(){
    ios::sync_with_stdio(0);
    cin >> n >> m;
    int *tmp = new int[max(m, n) + 7];
    chain<int> a, b, c;
    for (int i = 0; i < n; i++){
        cin >> tmp[i + 1];
    }
    quick_sort(tmp, 1, n);
    
    for (int i = 0; i < n; i++){
        a.push_back(tmp[i + 1]);
    }
    for (int i = 0; i < m; i++){
        cin >> tmp[i + 1];
    }
    quick_sort(tmp, 1, m);
    for (int i = 0; i < m; i++){
        b.push_back(tmp[i + 1]);
    }
    delete []tmp;
    mesh(a, b, c);
    a.output();
    b.output();
    c.output();
}