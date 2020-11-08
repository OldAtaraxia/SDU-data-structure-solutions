#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;



template<class T>
class stack{
    public:
        stack(int init = 10);
        ~stack() { delete[] arr; }
        bool empty() const { return stackTop == -1; }
        T & top(){
            return arr[stackTop];
        }

        void pop(){
            stackTop--;
        }
        void push(const T &theElement);
        private:
            int stackTop;
            int arrayLength;
            T *arr;
}; 

template<class T>
stack<T>::stack(int init){
    stackTop = -1;
    arr = new T[init];
    arrayLength = init;
}

template<class T>
void stack<T>::push(const T& theElement){
    if(stackTop == arrayLength - 1){
        T *newArr = new T[arrayLength * 2];
        for (int i = 0; i <= stackTop; i++){
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        arrayLength *= 2;
    }
    arr[++stackTop] = theElement;
}

stack<char> s;//操作符栈
stack<double> q;//操作数栈
string op, td;
int n;


bool isChar(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/'){
        return true;
    }else{
        return false;
    }
}

//返回符号的优先级
int pro(char c){
    if(c == '+' || c == '-'){
        return 1;
    }else if(c == '*' || c == '/'){
        return 2;
    }else{
        return 0;
    }
}

int main(){
    //ios::sync_with_stdio(0);
    cin >> n;
    while(n--){
        while(!s.empty()){
            s.pop();
        }
        td = "";
        //中缀表达式转后缀表达式
        cin >> op;
        for (int i = 0; i < op.length(); i++){
            if(isdigit(op[i])){
                td += op[i];
            }else{
                if(isChar(op[i])){
                    if(s.empty() || (!s.empty() && pro(op[i]) > pro(s.top()))){
                        s.push(op[i]);
                    }else{
                        while(!s.empty() && pro(s.top()) >= pro(op[i])){
                            td += s.top();
                            s.pop();
                        }
                        s.push(op[i]);
                    }
                }else{
                    if(op[i] == '('){
                        s.push(op[i]);
                    }else{
                        while(s.top() != '('){
                            td += s.top();
                            s.pop();
                        }
                        s.pop();
                    }
                }
            }
        }
        while(!s.empty()){
            td += s.top();
            s.pop();
        }
        //cout << td << endl;
        //算后缀表达式
        for (int i = 0; i < td.length(); i++){
            double temp = 0;
            if(isdigit(td[i])){
                q.push((double)(td[i] - '0'));
            }else{
                double temp2 = q.top();
                q.pop();
                double temp1 = q.top();
                q.pop();
                if(td[i] == '+')
                    temp = temp1 + temp2;
                else if(td[i] == '-')
                    temp = temp1 - temp2;
                else if(td[i] == '*')
                    temp = temp1 * temp2;
                else
                    temp = temp1 / temp2;
                q.push(temp);
            }
            
        }
        //cout << q.top() << endl;
        printf("%.2lf\n", q.top());
        q.pop();
    }
    return 0;
}