#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

template <class T>
struct matrixTerm {
    int row, col;  //行号和列号
    T value;  //元素值
    matrixTerm() : row(0), col(0), value(0) {}
    matrixTerm(int r, int c, const T& v): row(r), col(c), value(v) {}
    operator T() const {return value;}
};

template <class T> class spareMatrix;

//稀疏矩阵类
template <class T>
class spareMatrix {
public:
    //构造函数和复制构造函数
    spareMatrix() {}
    spareMatrix(int r, int c){
        rows = r;
        cols = c;
    }
    spareMatrix(const spareMatrix<T>& m);

    //get和set方法
    T& get(int theRow, int theColumn) const;
    void set(int theRow, int theColumn, const T& theValue);

    //转置
    void transpose(spareMatrix<T> &b);

    //加法
    bool add(spareMatrix<T> &b, spareMatrix<T> &c);

    //乘法
    bool multiply(spareMatrix<T> &b, spareMatrix<T> &c);

    //输出矩阵
    void output(){
        cout << rows << " " << cols << endl;
        if(!terms.empty()){
            auto it = terms.begin();
            for (int i = 1; i <= rows; i++){
                for (int j = 1; j <= cols; j++){
                    if(it == terms.end() || i < (*it).row ||(i == (*it).row && j < (*it).col)){
                        cout << 0 << " ";
                    }else if(j == (*it).col){
                        cout << (*it).value << " ";
                        if(it != terms.end())it++;
                    }
                }
                cout << endl;
            }
        }else{
            for (int i = 1; i <= rows; i++){
                for (int j = 1; j <= cols; j++){
                    cout << 0 << " ";
                }
                cout << endl;
            }
        }
    }
    void reset(int r, int c){
        rows = r;
        cols = c;
        terms.clear();
    }
    void copy(const spareMatrix<T> &m){
        rows = m.rows;
        cols = m.cols;
        terms = vector<matrixTerm<T>>(m.terms);
    }
private:
    int rows, cols;  //矩阵行数和列数
    vector<matrixTerm<T> > terms;  //非0项表
};


template<class T>
T & spareMatrix<T>::get(int theRow, int theCol) const {
    auto i = terms.begin();
    while(i != terms.end() && !((*i).row >= theRow && (*i).col >= theCol))
        i++;
    if((*i).row == theRow && (*i).col == theCol){
        return (*i).value;
    }else{
        return 0;
    }
}

template <class T>
void spareMatrix<T>::set(int theRow, int theCol, const T &theValue) {
    matrixTerm<T> m;
    m.row = theRow;
    m.col = theCol;
    m.value = theValue;
    terms.push_back(m);
}

template <class T> void spareMatrix<T>::transpose(spareMatrix<T> &b) {
    b.cols = rows;
    b.rows = cols;
    b.terms.resize(terms.size());
    if(terms.empty()){
        return;
    }
    int *colSize = new int[cols + 7];
    int *rowNext = new int[cols + 7];

    for (int i = 1; i <= cols; i++){
        colSize[i] = 0;
    }
    for (auto i = terms.begin(); i != terms.end(); i++){
        colSize[(*i).col]++;
    }

    rowNext[1] = 0;
    for (int i = 2; i <= cols; i++){
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];
    }

    matrixTerm<T> m;
    for (auto i = terms.begin(); i != terms.end(); i++){
        int j = rowNext[(*i).col]++;
        m.row = (*i).col;
        m.col = (*i).row;
        m.value = (*i).value;
        b.terms[j] = m;
    }
}


template<class T>
bool spareMatrix<T>::add(spareMatrix<T> &b, spareMatrix<T> &c){
    //cout << "Successfully being in the add function\n";
    if(rows != b.rows || cols != b.cols){
        cout << -1 << endl;
        return false;
    }
    if(terms.empty() || b.terms.empty()){
        if(terms.empty()){
            c = b;
            return true;
        }else{
            c = *this;
            return true;
        }
    }
    c.rows = rows;
    c.cols = cols;
    c.terms.clear();

    auto it = terms.begin(), ib = b.terms.begin();
    auto itEnd = terms.end(), ibEnd = b.terms.end();
    while(it != itEnd && ib != ibEnd){
        int tIndex = (*it).row * cols + (*it).col;
        int bIndex = (*ib).row * cols + (*ib).col;
        //cout << "tIndex == " << tIndex << " and bIndex == " << bIndex << endl;
        if(tIndex < bIndex){
            c.terms.push_back((*it));
            it++;
        }else{
            if(tIndex == bIndex){
                if((*it).value + (*ib).value != 0){
                    matrixTerm<T> m;
                    m.row = (*it).row;
                    m.col = (*it).col;
                    m.value = (*it).value + (*ib).value;
                    c.terms.push_back(m);
                }
                it++;
                ib++;
            }else{
                c.terms.push_back(*ib);
                ib++;
            }
        }
    }
    while(it != itEnd){
        c.terms.push_back(*it);
        it++;
    }
    while(ib != ibEnd){
        c.terms.push_back(*ib);
        ib++;
    }
    return true;
}

template<class T>
bool spareMatrix<T>::multiply(spareMatrix<T> &b, spareMatrix<T> &c){
    if(cols != b.rows){
        cout << -1 << endl;
        return false;
    }
    c.rows = rows;
    c.cols = b.cols;
    c.terms.clear();
    if(terms.empty() || b.terms.empty()){
        return true;
    }
    spareMatrix<T> d;
    b.transpose(d);
    //统计每一行的非零元素个数
    int *rowSizeA = new int[rows + 7], *rowNext = new int[rows + 7];
    for (int i = 1; i <= rows; i++)
        rowSizeA[i] = 0;
    for (auto i = terms.begin(); i != terms.end(); i++){
        rowSizeA[(*i).row]++;
    }
    rowNext[1] = 0;
    for (int i = 2; i <= cols; i++){
        rowNext[i] = rowNext[i - 1] + rowSizeA[i - 1];
    }
    int *rowSizeD = new int[d.rows + 7];
    for (int i = 1; i <= d.rows; i++){
        rowSizeD[i] = 0;
    }
    for (auto i = d.terms.begin(); i != d.terms.end(); i++){
        rowSizeD[(*i).row]++;
    }

    //开始乘
    auto it = terms.begin(), id = d.terms.begin();
    for (int i = 1; i <= rows; i++){
        id = d.terms.begin();
        for (int j = 1; j <= d.rows; j++){
            if(rowSizeA[i] != 0 && rowSizeD[j] != 0){
                it = terms.begin() + rowNext[i]; //复原指针
                int sum = 0, sum_A = rowSizeA[i], sum_D = rowSizeD[j];
                while(sum_A != 0 && sum_D != 0){
                    if((*it).col < (*id).col){
                        it++;
                        sum_A--;
                    }else if((*it).col > (*id).col){
                        id++;
                        sum_D--;
                    }else{
                        sum += ((*it).value * (*id).value);
                        it++;
                        id++;
                        sum_A--;
                        sum_D--;
                    }
                }
                if(sum_D != 0)
                    id += sum_D;
                if(sum != 0){
                    c.terms.push_back(matrixTerm<T>(i, j, sum));
                }
            }
        }
    }
    return true;
}


int w, k, x, y, v, t, tmp;
int N, M;
spareMatrix<int> P, Q, ans;
int main(){
    ios::sync_with_stdio(0);
    //freopen("out.txt", "w", stdout); 
    cin >> w;
    while(w--){
        cin >> k;
        switch(k){
            case 1:
                cin >> N >> M;
                P.reset(N, M);
                for (int i = 1; i <= N; i++){
                    for (int j = 1; j <= M; j++){
                        cin >> tmp;
                        if(tmp){
                            P.set(i, j, tmp);
                        }
                    }
                }
                break;
            case 2:
                cin >> N >> M >> t;
                Q.reset(N, M);
                while(t--){
                  cin >> x >> y >> v;
                  Q.set(x, y, v);
                }
                if(P.multiply(Q, ans)) P.copy(ans);
                else P.copy(Q);
                break;
            case 3:
                cin >> N >> M >> t;
                Q.reset(N, M);
                while(t--){
                  cin >> x >> y >> v;
                  Q.set(x,y,v);
                }
                if(P.add(Q, ans)){
                    P.copy(ans);
                }else{
                    P.copy(Q);
                }
                break;
            case 4:
                P.output();
                break;
            case 5:
                P.transpose(ans);
                P.copy(ans);
                break;
        }
    }
}