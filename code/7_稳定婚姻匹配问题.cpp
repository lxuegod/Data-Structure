#include<iostream>
#define M 10
using namespace std;

struct people 
{
	int score[M][2];
	int couple = 0;   //无配偶 
};


class Stable
{
public:
    void Heap(int i,int j,int n);   //建堆
    void maxHeap();                 //堆顶                
    void adjust(int i);             //调整堆
    void Choice();                  //进行匹配 
    void Out();                     //输出

    int n;  //人数 
    people boy[M], girl[M];
};

//建堆
void Stable::Heap(int i,int j,int n) 
{
	if(2*j<=n&&boy[i].score[2*j][1]>boy[i].score[j][1]) {
		int temp1=boy[i].score[j][0];
		int temp2=boy[i].score[j][1];
		boy[i].score[j][0] = boy[i].score[2*j][0];
		boy[i].score[j][1] = boy[i].score[2*j][1];
		boy[i].score[2*j][0] = temp1;
		boy[i].score[2*j][1] = temp2;
		Heap(i,2*j,n);
	}
	if(2*j<=n&&boy[i].score[2*j+1][1]>boy[i].score[j][1]) {
		int temp1=boy[i].score[j][0];
		int temp2=boy[i].score[j][1];
		boy[i].score[j][0] = boy[i].score[2*j+1][0];
		boy[i].score[j][1] = boy[i].score[2*j+1][1];
		boy[i].score[2*j+1][0] = temp1;
		boy[i].score[2*j+1][1] = temp2;
		Heap(i,2*j+1,n);
	}
	if(2*j<=n&&boy[i].score[2*j][1]>boy[i].score[j][1]) {
		int temp1=boy[i].score[j][0];
		int temp2=boy[i].score[j][1];
		boy[i].score[j][0] = boy[i].score[2*j][0];
		boy[i].score[j][1] = boy[i].score[2*j][1];
		boy[i].score[2*j][0] = temp1;
		boy[i].score[2*j][1] = temp2;
		Heap(i,2*j,n);
	}
	if(2*j<=n&&boy[i].score[2*j+1][1]>boy[i].score[j][1]) {
		int temp1=boy[i].score[j][0];
		int temp2=boy[i].score[j][1];
		boy[i].score[j][0] = boy[i].score[2*j+1][0];
		boy[i].score[j][1] = boy[i].score[2*j+1][1];
		boy[i].score[2*j+1][0] = temp1;
		boy[i].score[2*j+1][1] = temp2;
		Heap(i,2*j+1,n);
	}
}

//堆顶
void Stable::maxHeap() 
{
	for(int i = 1 ; i <= n ; ++i)
		for(int j = n ; j > 0 ; --j)
			Heap(i,j,n);
}

//调整堆
void Stable::adjust(int i) 
{
	boy[i].score[1][0]= boy[i].score[n][0];
	boy[i].score[1][1]= boy[i].score[n][1];
	boy[i].score[n][0] = 0;
	boy[i].score[n][1] = 0;
	Heap(i,1,n);
}

//进行匹配
void Stable::Choice() 
{
	while(1) {
		int flag = 0;
		for(int i = 1 ; i <= n ; ++i) {
			if(boy[i].couple == 0 && boy[i].score[1][0] != 0) {
				if(girl[boy[i].score[1][0]].couple==0) {
					girl[boy[i].score[1][0]].couple=i;
					boy[i].couple = boy[i].score[1][0];
					adjust(i);
				} 
				else {
					if(girl[boy[i].score[1][0]].score[girl[boy[i].score[1][0]].couple][1]< girl[boy[i].score[1][0]].score[i][1]) {
						boy[girl[boy[i].score[1][0]].couple].couple = 0;
						girl[boy[i].score[1][0]].couple = i;
						boy[i].couple = boy[i].score[1][0];
						adjust(i);
					}
					else{
						adjust(i);
					}
				}
				flag = 1;	
			}
		}
		if(!flag) break;
	}
}

//输出
void Stable::Out() 
{
	cout<<"男女生人数:";
	cin>>n;  //人数
	cout<<endl; 
	for(int i = 1 ; i <= n ; ++i) {   //输入男
		cout<<"第"<<i<<"个男生对"<<n<<"个女生的评价分别是："<<endl; 
		for(int j = 1 ; j <= n ; ++j) {
			boy[i].score[j][0] = j;
			cin>>boy[i].score[j][1];
		}
	}
	cout<<endl;
	for(int i = 1 ; i <= n ; ++i) {  //输入女
		cout<<"第"<<i<<"个女生对"<<n<<"个男生的评价分别是："<<endl; 
		for(int j = 1 ; j <= n ; ++j) {
			girl[i].score[j][0] = j;
			cin>>girl[i].score[j][1];
		}
	}
	maxHeap();
	Choice();
	cout<<endl<<"匹配结果为:"<<endl;
	for(int i = 1 ; i <= n ; ++i) {
		cout<<"男生:"<<i<<" 配对女生:"<<boy[i].couple<<endl;
	}
}

int main() {
    Stable* s = new Stable;
    s->Out();
    system("pause");
    return 0;
}