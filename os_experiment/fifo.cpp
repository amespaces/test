#include <iostream>
using namespace std;
int Block[3] = { -1,-1,-1 };
int Write;
int Q;
int T;
class FIFO{
private:
    int Block[3];//物理块
    int Write;
    int Q;//是否缺页 Y:1/N:0
    int T;//淘汰的页面
public:
    FIFO() {
        for (int i = 0; i < 3; i++) {
           FIFO::Block[i] = -1;
        }
    }
    void Input(int a, int b[],int c,int d ) {
        Write = a;
        for (int i = 0; i < 3; i++) {
            Block[i] = b[i];
        }
        Q = c;
        T = d;
    }
    int getW() {
        return Write;
    }
    int getBlock0() {
        return Block[0];
    }
    int getBlock1() {
        return Block[1];
    }
    int getBlock2() {
        return Block[2];
    }
    int getQ() {
        return Q;
    }
    int getT() {
        return T;
    }
};
void run(int a,int (&Block)[3],int &Write, int &Q, int &T) {
    Write = a;
    if (Block[0] == -1) {
        Block[0] = Write;
        Q = 1;
        T = -1;
    }else if (Block[1] == -1) {
        if (Block[0] == Write) {
            Q = 0;
            T = -1;
        }else {
            Q = 1;
            T = -1;
            Block[1] = Block[0];
            Block[0] = Write;
        } 
    }else if (Block[2] == -1) {
        if (Block[0] == Write) {
            Q = 0;
            T = -1;
        }else if (Block[1] == Write) {
            Q = 0;
            T = -1;
            Block[1] = Block[0];
            Block[0] = Write;
        }else {
            Q = 1;
            T = -1;
            Block[2] = Block[1];
            Block[1] = Block[0];
            Block[0] = Write;
        }
    }else {
        if (Block[0] == Write) {
            Q = 0;
            T = -1;
        }else if (Block[1] == Write) {
            Q = 0;
            T = -1;
            Block[1] = Block[0];
            Block[0] = Write;
        }else if (Block[2] == Write) {
            Q = 0;
            T = -1;
            Block[2] = Block[1];
            Block[1] = Block[0];
            Block[0] = Write;
        }else {
            Q = 1;
            T = Block[2];
            Block[2] = Block[1];
            Block[1] = Block[0];
            Block[0] = Write;
        }
    }
}
int main(){
    int a[27] = { 0,2,3,1,4,1,2,3,5,2,
        3,1,4,5,0,3,6,9,8,3,6,7,3,6,9,8,7 };
    FIFO Part[27];
    for (int i = 0; i < 27; i++) {
        run(a[i], Block, Write, Q, T);
        Part[i].Input(Write, Block, Q, T);
    }


    cout << "| ";
    for (int i = 0; i < 27; i++) {
        cout << "|" << Part[i].getW();
    }cout << "|" << endl;

    cout << " -";
    for (int i = 0; i < 27; i++) {
        cout << " -";
    }cout << " " << endl;

    cout << "|1";
    for (int i = 0; i < 27; i++) {
        cout << "|" << Part[i].getBlock0();
    }cout << "|" << endl; 

    cout << " -";
    for (int i = 0; i < 27; i++) {
        cout << " -";
    }cout << " " << endl;

    cout << "|2";
    for (int i = 0; i < 27; i++) {
        cout << "|";
        if (Part[i].getBlock1() == -1) cout << " ";
        else cout<< Part[i].getBlock1();
    }cout << "|" << endl;

    cout << " -";
    for (int i = 0; i < 27; i++) {
        cout << " -";
    }cout << " " << endl;

    cout << "|3";
    for (int i = 0; i < 27; i++) {
        cout << "|";
        if (Part[i].getBlock2() == -1) cout << " ";
        else cout << Part[i].getBlock2();
    }cout << "|" << endl;

    cout << " -";
    for (int i = 0; i < 27; i++) {
        cout << " -";
    }cout << " " << endl;

    cout << "|Q";
    for (int i = 0; i < 27; i++) {
        cout << "|"<< Part[i].getQ();
    }cout << "|" << endl;

    cout << " -";
    for (int i = 0; i < 27; i++) {
        cout << " -";
    }cout << " " << endl;

    cout << "|T";
    for (int i = 0; i < 27; i++) {
        cout << "|";
        if (Part[i].getT() == -1) cout << " ";
        else cout << Part[i].getT();
    }cout << "|" << endl;

    cout << " *";
    for (int i = 0; i < 27; i++) {
        cout << " *";
    }cout << " " << endl;
}


