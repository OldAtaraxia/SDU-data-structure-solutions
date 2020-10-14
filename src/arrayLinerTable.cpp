#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string>
#include<cstring>

using namespace std;

struct student{
    public:
        std::string name;
        std::string phoneNum;
        std::string className;
        std::string dorm;
};



int getNumber(std::string &s){
    int idx = 0, ans = 0;
    while(idx < s.length()){
        ans *= 10;
        ans += s[idx] - '0';
        idx++;
    }
    return ans;
}

class arrayList{
    private:
        int arrayLen;//数组长度
        int number;//学生人数
        student *ptr;

    public:
        arrayList() { 
            number = 0;
            arrayLen = 0;
        }
        arrayList(int n) {
            number = 0;
            arrayLen = n;
            ptr = new student[n];
        }
        ~arrayList(){
            if(ptr) delete[] ptr;
        }
        //void insert(int index, const student &T);
        void push_back(const student &T);
        int find(std::string &str);
        void erase(int index);
        void edit(int index, int id, std::string &str);
        void output(const std::string & className);
        int size() { return number; }
        void test();
};

void arrayList::push_back(const student &T){
    if(!ptr){
        ptr = new student[arrayLen];
        ptr[0] = T;
    }else{
        if(arrayLen == number){
            student *newPtr = new student[2 * arrayLen];
            arrayLen *= 2;
            for (int i = 0; i < number; i++){
                newPtr[i] = ptr[i];
            }
            
            //copy(ptr, ptr + number, newPtr);
            newPtr[number] = T;
            delete[] ptr;
            ptr = newPtr;
        }else{
            ptr[number] = T;
        }
    }
    number++;
}

int arrayList::find(std::string &str){
    for (int i = 0; i < number; i++){
        if(str == ptr[i].name){
            return i;
        }
    }
    return -1;
}

void arrayList::erase(int index){
    if(index < 0 || index >= number){
        throw "invalid index";
    }else{
        for (int i = index + 1; i < number; i++){
            ptr[i - 1] = ptr[i];
        }
        number--;
    }
}

void arrayList::edit(int index, int id, std::string &str){
    if(index < 0 || index >= number){
        throw "invalid index";
    }
    if(id == 1){
        ptr[index].phoneNum = str;
    }else if(id == 2){
        ptr[index].className =  str;
    }else if(id == 3){
        ptr[index].dorm = str;
    }
}

void arrayList::output(const std::string &str){
    int ans = 0;
    for (int i = 0; i < number; i++){
        if(ptr[i].className == str){
            ans ^= getNumber(ptr[i].dorm);
        }
    }
    std::cout << ans << std::endl;
}


arrayList studentList(20002);
std::string str, Name;
student T;
int id;

void arrayList::test(){
    for (int i = 0; i < number; i++){
        cout << ptr[i].name << " ";
    }
    cout << endl;
}

int main(){
    ios::sync_with_stdio(0);
    int n, k;
    std::cin >> n;
    
    while(n--){
      std::cin >> k;
        if(k == 0){
            std::cin >> T.name >> T.phoneNum >> T.className >> T.dorm;
            studentList.push_back(T);
        }else if(k == 1){
            std::cin >> Name;
            studentList.erase(studentList.find(Name));

        }else if(k == 2){
            
            int id;
            std::cin >> Name >> id >> str;
            studentList.edit(studentList.find(Name), id, str);
            
            
        }else if(k == 3){
            
            std::cin >> str;
            if(studentList.find(str) == -1){
                std::cout << 0 << std::endl;
            }else{
                std::cout << 1 << std::endl;
            }
            
           
        }else if(k == 4){

            std::cin >> str;
            studentList.output(str);
            
            
        }else if(k == 5){
            studentList.test();
        }
    }
}