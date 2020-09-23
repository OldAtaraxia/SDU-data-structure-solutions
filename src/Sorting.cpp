#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

//实现简单的动态数组
template<class T>
class arrayList{
    public:
        int len; //长度
        arrayList(int s = 0);
        ~arrayList();
        int size() { return len; } //得到数组的长度
        void push_back(const T &y);//添加元素
        T & operator[](int i){
            return ptr[i];
        }

    private: 
        T *ptr; //指向数组位置
};

template <class T> arrayList<T>::arrayList(int s) {
    len = 0;
    if (s == 0) ptr = NULL;
    else
        ptr = new T[s];
}

template<class T>
arrayList<T>::~arrayList(){
    if(ptr){
        delete[] ptr;
    }
}
template<class T>
void arrayList<T>::push_back(const T &x){
    if(ptr){
        len++;
        T *newPtr = new T[len];
        for (int i = 0; i < len - 1; i++) {
            newPtr[i] = ptr[i];
        }
        newPtr[len - 1] = x;
        delete[] ptr;
        ptr = newPtr;
        newPtr = 0;
    }else{
        ptr = new T[1];
        ptr[len++] = x;
    }
}

//实现排序类,封装名次排序,及时终止的选择排序,及时终止的冒泡排序,插入排序
template<class T>
class Sorting{
    public:
        Sorting(){};
        //名次排序
        void rearrange(arrayList<T> &a){
            T *u = new T[a.size()];
            int *r = new int[a.size()]; //名次
            for (int i = 0; i < a.size(); i++){
                r[i] = 0;
            }
            //比较所有元素对
            for (int i = 1; i < a.size(); i++){
                for (int j = 0; j < i; j++){
                    if (a[j] <= a[i])
                        r[i]++;
                    else
                        r[j]++;
                }
            }

            for (int i = 0; i < a.size(); i++){
                u[r[i]] = a[i];
            }
            for (int i = 0; i < a.size(); i++){
                a[i] = u[i];
            }
            delete[] u;
    }

    //及时终止的选择排序
    void selectionSort(arrayList<T> &a){
        bool sorted = false;//指示排序是否完成
        for (int s = a.size(); !sorted && (s > 1); s--){
            int indexOfMax = 0;
            sorted = true;
            //查找最大元素
            for (int i = 1; i < s; i++){
                if(a[indexOfMax] <= a[i])
                    indexOfMax = i;
                else
                    sorted = false;//无序
            }
            swap(a[indexOfMax], a[s - 1]);
        }
    }

    //及时终止的冒泡排序
    void bubbleSort(arrayList<T> & a){
        for (int k = a.size(); k > 1; k--){
            bool swapped = false;
            for (int i = 0; i < k - 1; i++){
                if(a[i] > a[i + 1]){
                    swap(a[i], a[i + 1]);
                    swapped = true;
                }
            }
            if(!swapped) break;
        }
    }
    //插入排序
    void insertionSort(arrayList<T>&a){
        for (int i = 1; i < a.size(); i++){
            T t = a[i];
            int j;
            for (j = i - 1; j >= 0 && t < a[j]; j--){
                a[j + 1] = a[j];
            }
            a[j + 1] = t;
        }
    }
};

int main(){
    int n, temp;
    cin >> n;
    arrayList<int> arr;
    for (int i = 0; i < n; i++){
        cin >> temp;
        arr.push_back(temp);
    }
    Sorting<int> sorting;
    sorting.insertionSort(arr);
    for (int i = 0; i < arr.size(); i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}