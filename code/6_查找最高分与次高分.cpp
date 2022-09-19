#include <iostream>
#include <cstdlib>
#include <ctime>
#define M 512
#define N 1000
using namespace std;
struct player
{
    int id;  //标号
    int grade;  //分数
};

class Search
{
public:
    void RandomNum();   //生成随机分数
    void SequentialSearch();  //顺序查找
    void TournamentSearch();  //锦标赛查找
    void HeapSort();        //堆排序查找
    void Adjust(int *pos, int n, int m);  //调整双亲
private:
    player p[M];
};

//生成随机分数
void Search::RandomNum()
{
    srand((int)time(0));   //以系统时间为种子
    for(int i = 0; i < M; i++) {
        this->p[i].id = i+1;
        this->p[i].grade = rand()%N;
    }
    for(int i = 0; i < M; i++) {
         cout<<"第"<<this->p[i].id<<"个参与者,得分为"<<p[i].grade<<endl;
    }
}

//顺序查找
void Search::SequentialSearch()
{
    int max = -1;
    int max_2 = -1;
    int j, k, num = 0;
    for(int i = 0; i < M; i++) {
        if(p[i].grade > max) {
            j = i;   //为第一个最大的位置
            max = p[i].grade;
        }  
    }
    for(int i = 0; i < M; i++) {
        if(p[i].grade < max && p[i].grade > max_2){//p[i].grade < max && 
            max_2 = p[i].grade;
            k = i;   //为最后一个次高的位置
        }
    }
    cout<<"顺序法排序："<<endl;
    cout<<"最高分为"<<p[j].grade<<"是第"<<p[j].id<<"个参与者"<<endl;
    cout<<"次高分为"<<p[k].grade<<"是第"<<p[k].id<<"个参与者"<<endl;
    cout<<endl<<endl<<endl;
}

 //锦标赛查找
void Search::TournamentSearch()
{
    player cp[M/2];                //新分配空间
	int flag = M / 2;                   //一轮过后获胜者的人数
	int leftchild, rightchild;
	for (int i = 0; i < flag; i++) {//第一轮
		leftchild = i * 2;              //左孩子的编号是父节点*2；
		rightchild = leftchild + 1;     //右孩子编号是父节点*2+1
		//if判断，决出两个子节点中的最大值
		if (p[leftchild].grade >= p[rightchild].grade) {
            cp[i].grade = p[leftchild].grade;
            cp[i].id = leftchild + 1;
		} else {
            cp[i].grade = p[rightchild].grade;
            cp[i].id = rightchild + 1;
		}
	}
	while (flag != 1) {
		flag /= 2;
		for (int i = 0; i < flag; i++) {
			leftchild = i * 2;
			rightchild = leftchild + 1;
            if (cp[leftchild].grade >= cp[rightchild].grade) {
				cp[i].grade = cp[leftchild].grade;
				cp[i].id = cp[leftchild].id;
			} else {
				cp[i].grade = cp[rightchild].grade;
				cp[i].id = cp[rightchild].id;
			}
		}
	}
    int max = p[cp[0].id-1].grade;
    int j = 0;
    while(1) {
        if(max != p[cp[j].id-1].grade)
            break;
        j++;
    }
    cout<<"锦标赛排序："<<endl;
    cout<<"最高分为"<<p[cp[0].id-1].grade<<"是第"<<cp[0].id<<"个参与者"<<endl;
    cout<<"次高分为"<<p[cp[j].id-1].grade<<"是第"<<cp[j].id<<"个参与者"<<endl;
    cout<<endl<<endl<<endl;
}

void Search::Adjust(int *pos, int n, int m)
{
    int adj = pos[n];       //adj是当前需调整的双亲，
	for (int i = 2 * n; i <= m; i *= 2) {//i是子树的下标
		if (i < m && p[pos[i]].grade < p[pos[i + 1]].grade)
			++i;        //比较左子树和右子树    子树中的较大者的编号赋给i;
		if (p[adj].grade > p[pos[i]].grade)
			break;      //比较双亲与孩子中的较大值
		pos[n] = pos[i];
		n = i;
	}
	pos[n] = adj;
}

void Search::HeapSort()
{
    int pos[M];  //位置数组
	for (int i = 0; i < M; i++){
        pos[i] = i ;
    }
	for (int i = (M-1) / 2; i > 0; i--) {
		Adjust(pos, i, M-1);
	}
    cout<<"堆排序："<<endl;
    cout<<"最高分为"<<p[pos[1]].grade<<"是第"<<pos[1]+1<<"个参与者"<<endl;
    cout<<"次高分为"<<p[pos[2]].grade<<"是第"<<pos[2]+1<<"个参与者"<<endl;
}

int main(){
    Search *s = new Search;
    s->RandomNum();
    s->SequentialSearch();
    s->TournamentSearch();
    s->HeapSort();
    return 0;
}