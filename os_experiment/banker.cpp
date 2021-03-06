#include <iostream>
#include<iomanip>
using namespace std;

#define MAXN 100
/*writter 朱威煌 2701180235
Max
4 6 3 8
3 3 5 2
6 6 0 9
3 4 8 7
4 3 2 5
used
1 1 0 1
2 2 4 1
0 5 0 1
1 1 1 5
2 0 2 2

*/

int Available[MAXN];	//各资源未分配的资源数
int Max[MAXN][MAXN];	//每个进程最多所需的资源数
int Allocation[MAXN][MAXN];	//每个进程已占有的资源数
int Need[MAXN][MAXN];	//每个进程还需的资源数
int Request[MAXN];	//进程请求的各资源数
int Finish[MAXN];
int path[MAXN] = { 0 };	//安全序列
int PNum, RNum;	//进程数，资源数
 int number[MAXN];//各类资源的总数
int Available_copy1[MAXN][MAXN];//available 
int finish1[MAXN];
void input(int PNum,int RNum)
 {
    cout << "请输入资源数量：\n";
    for (int i = 0; i < RNum; i++){
        cin >> number[i];
    }
    cout << "请输入最大需求矩阵Max\n";
    for (int i = 0; i < PNum; i++) {
        for (int j = 0; j < RNum; j++)
            cin >> Max[i][j];
    }
    cout << "请输入当前分配矩阵Used：\n";
    for (int i = 0; i < PNum; i++) {
        for (int j = 0; j < RNum; j++) {
            cin >> Allocation[i][j];
			//每个进程还需的资源数Need
            Need[i][j] = Max[i][j] - Allocation[i][j];
            if (Need[i][j] < 0) {
                cout << "输入的进程P" << i+1 << "所拥有的第" << j + 1 << "个资源数不能小于0，请重新输入：\n";
                j--;
                continue;
            }
        }
    }
    //已经用的各资源的数量
    int sum[MAXN]={0};//used各类资源的总数
    for(int i=0;i<PNum;i++){
        for(int j=0;j<RNum;j++){
            sum[j]=sum[j]+Allocation[i][j];
        }
    }
    cout<<endl;
      for (int i = 0; i < RNum; i++){
        Available[i]=number[i]-sum[i];//
    }
    cout<<"可使用资源为 ";
    for (int i = 0; i < RNum; i++){
        cout<<Available[i]<<" "; 
    } 
    cout<<endl;
     
}

//判断是否存在安全序列
int Safe() {
    int i, j, jj, k = 0;
    int Available_copy[MAXN];	//未分配的资源数
    int Allocation_copy[MAXN][MAXN];	//已占有的资源数
    int Need_copy[MAXN][MAXN];	//进程还需的资源数
    
    for (i = 0; i < RNum; i++) 
		Available_copy[i] = Available[i];
	for (i = 0; i < PNum; i++) {
        for (j = 0; j < RNum; j++)
            Allocation_copy[i][j] = Allocation[i][j];
    }
    for (i = 0; i < PNum; i++) {
        for (j = 0; j < RNum; j++)
            Need_copy[i][j] = Need[i][j];
    }
    for (i = 0; i < PNum; i++) 
		Finish[i] = 0;
    int a=0;
	//遍历每个进程
    for (i = 0; i < PNum; i++) {
        if (Finish[i] == 1)
            continue;
        else {				
			//前提：需要的资源<未分配的资源
            for (j = 0; j < RNum; j++) {
                if (Need_copy[i][j] > Available_copy[j])
                    break;
            }
			//若找到一个进程的所有资源请求满足要求，更新
            if (j == RNum) {
                Finish[i] = 1;
                for (jj = 0; jj < RNum; jj++){
                	Available_copy[jj] += Allocation[i][jj];
                	Allocation_copy[i][jj] = 0;
                	Need_copy[i][jj] = 0;
				}
    			for (jj = 0; jj < RNum; jj++){
                    Available_copy1[i][jj]= Available_copy[jj];
                }

        	
    				
                path[k++] = i + 1;	//写入安全序列 
                finish1[i]=k;
                i = -1;	//NOTE
            }
            else 
				continue;
        }
        if (k == PNum) {	//存在安全序列
            return 1;
        }
    }
    return 0;
}

//输出安全序列
void outPath() {
    cout << "安全序列：P" << path[0] ;
    for (int i = 1; path[i] != 0; i++) {
        cout << "->P" << path[i] ;
    }
    
	//清空path，为下次存入安全序列做准备
    for (int j = 0; j < PNum; j++) 
		path[j] = 0;
    cout << endl;
}
void print() {
    int i, j;
cout<<"\tMax\tUsed\tNeed\t   Available\tFinished"<<endl;
for(int i=0;i<PNum;i++){
    cout<<"P"<<i+1<<"    ";
    for(int j=0;j<RNum;j++){
        cout<<Max[i][j]<<" ";
    }
    cout<<" ";
    for(int j=0;j<RNum;j++){
        cout<<Allocation[i][j]<<" ";
    }
    cout<<" ";
    for(int j=0;j<RNum;j++){
        cout<<Need[i][j]<<" ";
    }
    cout<<" ";
    for(int j=0;j<RNum;j++){
        cout<<setw(3)<<Available_copy1[i][j];
    }
    cout<<"  \t";
    cout<<finish1[i]<<endl;
}	
} 

int requestP() {
    int n,i;
    cout << "输入要申请资源的进程号：";
    cin >> n;
    cout << "输入进程请求的各资源数：";
    for (i = 0; i < RNum; i++)
        cin >> Request[i];
    for (i = 0; i < RNum; i++) {
        if (Request[i] > Need[n][i]) {
            cout << "Error：请求的资源数大于进程所需的资源数！\n";
            return 1;
        }
        if (Request[i] > Available[i]) {
            cout << "请求资源数大于未分配的资源数，系统无足够资源，进程P" << n << "阻塞等待...\n";
            return 1;
        }
    }
	//更新未分配、已分配和还需的资源数
    for (i = 0; i < RNum; i++) {
        Available[i] -= Request[i];
        Allocation[n-1][i] += Request[i];
        Need[n-1][i] -= Request[i];
    }
    if (Safe()) {
        cout << "存在安全序列，系统处于安全状态，同意分配请求！\n";
		outPath();
        print();
    }
	//若不存在安全序列，还原未分配、已分配和还需的资源数
    else {
        for (i = 0; i < RNum; i++) {
            Available[i] += Request[i];
            Allocation[n-1][i] -= Request[i];
            Need[n-1][i] += Request[i];
        }
        cout << "不存在安全序列，系统处于不安全状态，拒绝请求！\n";
    }
    return 0;
}




int main(){
	cout<<"----------银行家算法----------\n";
    cout << "输入进程数：";
    cin >> PNum;
    cout << "输入资源种类：";
    cin >> RNum;
    input(PNum, RNum);	//读取输入
    if (Safe()) {
        cout << "存在安全序列，系统处于安全状态！\n";
        outPath();
		cout<<endl;
        print();
    }
    else {
        cout << "不存在安全序列，系统处于不安全状态！\n";
        return 0;
    }
    cout << endl;
    while (true) {
        requestP();
       
        string s;
        cout << "是否再次请求分配？请输入yes或no：\n";
        while (true) {
            cin >> s;
            if (s == "yes" || s == "no")
                break;
            else {
                cout << "请按要求重新输入：\n";
                continue;
            }
        }
        if (s == "yes")
            continue;
        else 
			break;
    }
    return 0;
}
