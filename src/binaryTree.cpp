#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int MAX_N = 1e5 + 7;

template<class T>
struct Node{
	T element;
	Node<T> *leftChild = NULL, *rightChild = NULL;
	Node<T> *parent = NULL;
	bool isLeave = false;
	int nodeNumber = 1, height = 1;
	bool used = false;
	Node() { leftChild = NULL;
		rightChild = NULL;
	}

	Node(const T & theElement){
		element = theElement;
		leftChild = rightChild = NULL;
	}
	Node(const T & theElement, Node* theLeftChild, Node* theRightChild){
		element = theElement;
		leftChild = theLeftChild;
		rightChild = theRightChild;
		leftChild->parent = this;
		rightChild->parent = this;
	}
};

template<class T>
void visit(Node<T> * t){
	cout << t->element << " ";
}

template <class T>
void levelOrder(Node<T> *t) {
	queue<Node<T>*> que;
	while(t != NULL){
		visit(t);

		if(t -> leftChild != NULL){
			que.push(t->leftChild);
		}
		if(t -> rightChild != NULL){
			que.push(t->rightChild);
		}
		if(!que.empty()){
			t = que.front();
			que.pop();
		}else{
			break;
		}
	}
	cout << endl;
}



int n;
int a, b;
vector<int> leave;
queue<int> qq;
Node<int> node[MAX_N];


void getNodeNumber(){
	while(!qq.empty()){
		int idx = qq.front();
		qq.pop();
		Node<int> uper = node[idx];
		node[idx].used = true;
		while(uper.parent != NULL){
			(*uper.parent).nodeNumber ++ ;
			if(!(*uper.parent).used){
				qq.push((*uper.parent).element);
				(*uper.parent).used = true;
			}
			uper = *uper.parent;
		}
	}
}

void getNodeHeight(){
	for (int i = 0; i < leave.size(); i++){
		int idx = leave[i];
		node[idx].height = 1;
		Node<int> uper = node[idx];
		while(uper.parent != NULL){
			(*uper.parent).height = max(uper.height + 1, (*uper.parent).height);
			uper = *uper.parent;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin >> n;
	Node<int> *root = &node[1];
	for (int i = 1; i <= n; i++){
		node[i].element = i;
		cin >> a >> b;
		if(a != -1){
			node[i].leftChild = &node[a];
			node[a].parent = &node[i];
		}
		if(b != -1){
			node[i].rightChild = &node[b];
			node[b].parent = &node[i];
		}
		if(a == -1 && b == -1){
			node[i].isLeave = true;
			leave.push_back(i);
			qq.push(i);
		}
	}
	levelOrder(root);
	getNodeNumber();
	getNodeHeight();
	for (int i = 1; i <= n; i++){
		cout << node[i].nodeNumber << " ";
	}
	cout << endl;
	for (int i = 1; i <= n; i++){
		cout << node[i].height << " ";
	}
	cout << endl;
	return 0;
}
