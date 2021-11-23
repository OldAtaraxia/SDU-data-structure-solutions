#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;

int *a;
int *b;

void handleOrder(int ast, int aed, int bst, int bed){
    //a是前序遍历,b是中序遍历
    if(ast > aed){
        return;
    }
    int root = a[ast];
    int bRootIdx;
    if(ast == aed){
        cout << root << " ";
        return;
    }

    for (int i = bst; i <= bed; i++){
        if(b[i] == root){
            bRootIdx = i;
            break;
        }
    }
    int len = bRootIdx - bst;
    handleOrder( ast + 1, ast + len, bst, bRootIdx - 1);
    handleOrder(ast + len + 1, aed, bRootIdx + 1, bed);
    cout << root << " ";
}

int main(){
    int n;
    cin >> n;
    a = new int[n + 7];
    b = new int[n + 7];
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++){
        cin >> b[i];
    }

    handleOrder(1, n, 1, n);
    cout << endl;
    return 0;
}