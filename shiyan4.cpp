#include <iostream>
#include<vector>
#include<fstream>

using namespace std;

class Node {
public:
    string Val = " ";
    Node* Child = NULL,*Brother = NULL;
};

//全局tag，判断是域名还是ip地址
int tag = -1;


class SearchTree {
public:
    Node* root;
    SearchTree() {
        Node* root = new Node;
        this->root = root;
        Node* c = new Node;
        this->root->Child = c;
    }
    void CreatSearchTree() {
        ifstream fin;

        fin.open("D:/c++/mine/shiyan4/net_ip.txt", ios::in);

        if (!fin.is_open())
        {
            cerr << "cannot open the file";
            return;
        }
        //end
        Node* end = new Node;
        while (!fin.eof())
        {
            vector<string> net;
            string tmp;
            string input;
            fin >> input;
            tag++;

            if (tag % 2 == 0) {
                for (size_t i = 0; i < input.size(); i++) {
                    if (input[i] != '.') {
                        tmp += input[i];
                    }
                    if (input[i] == '.') {
                        net.push_back(tmp);
                        tmp = "";
                    }
                }
                net.push_back(tmp);
                Node* p = root->Child;
                for (int i = 0; i < net.size(); i++) {
                    while (p->Val != net[i] && p->Brother != NULL) {
                        p = p->Brother;
                    }
                    if (p->Val != net[i]) {
                        Node* b = new Node;
                        Node* c = new Node;
                        b->Val = net[i];
                        b->Child = c;
                        p->Brother = b;
                        p = b;
                    }
                    p = p->Child;
                }
                end = p;
            }
            else {
                //end
                Node* c = new Node;
                c->Val = input;
                end->Child = c;
            }
            
        }
    }
    ~SearchTree() {
        if (this->root->Child != NULL) {
            delete(this->root->Child);
        }
        if (this->root->Brother != NULL) {
            delete(this->root->Brother);
        }
        delete(this->root);
        return;
    }
    void Search(vector<string>& net) {
        Node* tmp = new Node;
        tmp = root->Child;
        for (size_t i = 0; i < net.size(); i++) {
            while (tmp->Val != net[i] && tmp->Brother != NULL) {
                //cout << tmp->Val<<endl;
                tmp = tmp->Brother;
            }
            if (tmp->Val != net[i]) {
                cout << "找不到服务器或者发生dns错误";
                return;
            }
            if (tmp->Child != NULL) {
                tmp = tmp->Child;
            }
        }
        if (tmp->Child == NULL) {
            cout << "找不到服务器或者发生dns错误";
        }
        else {
            cout << tmp->Child->Val;
        }
    }
};

int main()
{
    vector<string> net;
    string input;
    std::cout << "请输入你的网址：";
    std::cin >> input;
    string tmp = "";
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] != '.') {
            tmp += input[i];
        }
        if (input[i] == '.') {
            net.push_back(tmp);
            tmp = "";
        }
    }
    //存入最后一段字符
    net.push_back(tmp);

    SearchTree t;
    t.CreatSearchTree();
    //t.DFS(t.root->Child->Child);
    t.Search(net);

    
}