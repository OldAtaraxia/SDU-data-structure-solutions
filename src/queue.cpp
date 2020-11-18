#include<iostream>
#include<cstdio>

using namespace std;

template <class T>
class Queue{
public:
    Queue(int initCapacity = 10);
    ~Queue() {delete [] queue;}
    bool empty() const { return (queueFront == queueBack);}
    int size() const { return (queueBack - queueFront + arrayLength) % arrayLength;}
    T& front() {
        //队空，抛出异常
        if (queueFront == queueBack)
			throw "the queue is empty!";
		return queue[(queueFront + 1) % arrayLength];
    }
    T& back() {
        //队空，抛出异常
        if (queueFront == queueBack)
            throw "the queue is empty!";
        return queue[queueBack];
    }
    void pop() {
        if (queueFront == queueBack)
            throw "the queue is empty!";
        queueFront = (queueFront + 1) % arrayLength;
        queue[queueFront].~T();
    };

    //在队尾插入元素
    void push(const T& theElement);
private:
    int queueFront;  //队首元素前一个位置的下标
    int queueBack;  //队尾元素的下标
    int arrayLength;  //队列的容量
    T* queue;  //元素数组
};

//构造函数
template <class T>
Queue<T>::Queue(int initCapacity) {    
	if (initCapacity < 1) {
		throw "init must > 0 ";
	}
    arrayLength = initCapacity;
    queue = new T[arrayLength];
    queueFront = queueBack = 0;
}

//插入元素
template <class T>
void Queue<T>::push(const T &theElement) {
    if ((queueBack + 1) % arrayLength == queueFront) {
        T* newQueue = new T[2 * arrayLength];
        int start = (queueFront + 1) % arrayLength;//首元素的位置
        if (start < 2) copy(queue + start, queue + start + arrayLength - 1, newQueue); //0或1时没有被分成两部分
        else {
            copy(queue + start, queue + arrayLength, newQueue);
            copy(queue, queue + queueBack + 1, newQueue + arrayLength - start);
        }
        queueFront = 2 *arrayLength - 1;
        queueBack = arrayLength - 2;
        arrayLength *= 2;
        delete [] queue;
        queue = newQueue;
    }

    queueBack = (queueBack + 1) % arrayLength;
    queue[queueBack] = theElement;
}

Queue<int> q;
int main(){
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++){
		q.push(i);
	}

	while(q.size() >= 2){
		q.pop();
		int tt = q.front();
		q.pop();
		q.push(tt);
	}
	cout << q.front() << endl;
	return 0;
}