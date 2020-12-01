#include <iostream>
#include<iomanip>
using namespace std;

#define MAXN 100
/*writter ������ 2701180235
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

int Available[MAXN];	//����Դδ�������Դ��
int Max[MAXN][MAXN];	//ÿ����������������Դ��
int Allocation[MAXN][MAXN];	//ÿ��������ռ�е���Դ��
int Need[MAXN][MAXN];	//ÿ�����̻������Դ��
int Request[MAXN];	//��������ĸ���Դ��
int Finish[MAXN];
int path[MAXN] = { 0 };	//��ȫ����
int PNum, RNum;	//����������Դ��
 int number[MAXN];//������Դ������
int Available_copy1[MAXN][MAXN];//available 
int finish1[MAXN];
void input(int PNum,int RNum)
 {
    cout << "��������Դ������\n";
    for (int i = 0; i < RNum; i++){
        cin >> number[i];
    }
    cout << "����������������Max\n";
    for (int i = 0; i < PNum; i++) {
        for (int j = 0; j < RNum; j++)
            cin >> Max[i][j];
    }
    cout << "�����뵱ǰ�������Used��\n";
    for (int i = 0; i < PNum; i++) {
        for (int j = 0; j < RNum; j++) {
            cin >> Allocation[i][j];
			//ÿ�����̻������Դ��Need
            Need[i][j] = Max[i][j] - Allocation[i][j];
            if (Need[i][j] < 0) {
                cout << "����Ľ���P" << i+1 << "��ӵ�еĵ�" << j + 1 << "����Դ������С��0�����������룺\n";
                j--;
                continue;
            }
        }
    }
    //�Ѿ��õĸ���Դ������
    int sum[MAXN]={0};//used������Դ������
    for(int i=0;i<PNum;i++){
        for(int j=0;j<RNum;j++){
            sum[j]=sum[j]+Allocation[i][j];
        }
    }
    cout<<endl;
      for (int i = 0; i < RNum; i++){
        Available[i]=number[i]-sum[i];//
    }
    cout<<"��ʹ����ԴΪ ";
    for (int i = 0; i < RNum; i++){
        cout<<Available[i]<<" "; 
    } 
    cout<<endl;
     
}

//�ж��Ƿ���ڰ�ȫ����
int Safe() {
    int i, j, jj, k = 0;
    int Available_copy[MAXN];	//δ�������Դ��
    int Allocation_copy[MAXN][MAXN];	//��ռ�е���Դ��
    int Need_copy[MAXN][MAXN];	//���̻������Դ��
    
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
	//����ÿ������
    for (i = 0; i < PNum; i++) {
        if (Finish[i] == 1)
            continue;
        else {				
			//ǰ�᣺��Ҫ����Դ<δ�������Դ
            for (j = 0; j < RNum; j++) {
                if (Need_copy[i][j] > Available_copy[j])
                    break;
            }
			//���ҵ�һ�����̵�������Դ��������Ҫ�󣬸���
            if (j == RNum) {
                Finish[i] = 1;
                for (jj = 0; jj < RNum; jj++){
                	Available_copy[jj] += Allocation[i][jj];
                	Allocation_copy[i][jj] = 0;
                	Need_copy[i][jj] = 0;
				}
    			for (jj = 0; jj < RNum; jj++){
                    Available_copy1[i+1][jj]= Available_copy[jj];
                }

        	
    				
                path[k++] = i + 1;	//д�밲ȫ���� 
                finish1[i]=k;
                i = -1;	//NOTE
            }
            else 
				continue;
        }
        if (k == PNum) {	//���ڰ�ȫ����
            return 1;
        }
    }
    return 0;
}

//�����ȫ����
void outPath() {
    cout << "��ȫ���У�P" << path[0] ;
    for (int i = 1; path[i] != 0; i++) {
        cout << "->P" << path[i] ;
    }
    
	//���path��Ϊ�´δ��밲ȫ������׼��
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
    cout << "����Ҫ������Դ�Ľ��̺ţ�";
    cin >> n;
    cout << "�����������ĸ���Դ����";
    for (i = 0; i < RNum; i++)
        cin >> Request[i];
    for (i = 0; i < RNum; i++) {
        if (Request[i] > Need[n][i]) {
            cout << "Error���������Դ�����ڽ����������Դ����\n";
            return 1;
        }
        if (Request[i] > Available[i]) {
            cout << "������Դ������δ�������Դ����ϵͳ���㹻��Դ������P" << n << "�����ȴ�...\n";
            return 1;
        }
    }
	//����δ���䡢�ѷ���ͻ������Դ��
    for (i = 0; i < RNum; i++) {
        Available[i] -= Request[i];
        Allocation[n-1][i] += Request[i];
        Need[n-1][i] -= Request[i];
    }
    if (Safe()) {
        cout << "���ڰ�ȫ���У�ϵͳ���ڰ�ȫ״̬��ͬ���������\n";
		outPath();
        print();
    }
	//�������ڰ�ȫ���У���ԭδ���䡢�ѷ���ͻ������Դ��
    else {
        for (i = 0; i < RNum; i++) {
            Available[i] += Request[i];
            Allocation[n-1][i] -= Request[i];
            Need[n-1][i] += Request[i];
        }
        cout << "�����ڰ�ȫ���У�ϵͳ���ڲ���ȫ״̬���ܾ�����\n";
    }
    return 0;
}




int main(){
	cout<<"----------���м��㷨----------\n";
    cout << "�����������";
    cin >> PNum;
    cout << "������Դ���ࣺ";
    cin >> RNum;
    input(PNum, RNum);	//��ȡ����
    if (Safe()) {
        cout << "���ڰ�ȫ���У�ϵͳ���ڰ�ȫ״̬��\n";
        outPath();
		cout<<endl;
        print();
    }
    else {
        cout << "�����ڰ�ȫ���У�ϵͳ���ڲ���ȫ״̬��\n";
        return 0;
    }
    cout << endl;
    while (true) {
        requestP();
       
        string s;
        cout << "�Ƿ��ٴ�������䣿������yes��no��\n";
        while (true) {
            cin >> s;
            if (s == "yes" || s == "no")
                break;
            else {
                cout << "�밴Ҫ���������룺\n";
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
