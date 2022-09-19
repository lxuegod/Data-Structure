/*
* 考试日程安排与成绩统计
* ①问题描述
* -  现要安排考试的考表（即考试日程表），假设共有 10 个班的学生，要
* 安排 10 门必修课程的考试，必修课程是以班级来确定的，每个班各有 3
* 门必修课，因此各班的考试科目是不相同的；安排考表的原则是：相同
* 课程采用统一的试卷，因此同一门课程的考试必须在相同时间进行，同
* 一个班所修的科目必须安排在不同的时间进行考试，以避免考试时间的
* 冲突。并要求全部考试的日程尽可能短。
* -  要求对考试结果做统计和排序。假设分别以编号 0,1,2,3,4,5,6,7,8,9 代表
* 10 门要考试的课程，以 B1，B2，B3，B4，B5，B6，B7，B8，B9，B10代
* 表 10 个班，每个人的信息包括学号、姓名、班级、各门考试课程成绩、
* 三门课程总成绩，每个班的学生人数自行设定。要求设计一个简单的考
* 28
* 试成绩的查询统计系统实现以下功能：
*  显示学生考试情况
* -按考试总分从高到底输出全体学生的信息。
* -按照从 B1到 B10的班级顺序，分班级按照考试总分从高到底的顺序
* 输出各班学生的信息。
* -输出指定班的学生考试成绩信息。
*  统计学生考试成绩
* -按总成绩统计出 90 分以上、80~89 分、70~79 分、60~69 分、60 分
* 以下各分数段的人数，并按总分从高到低分段输出。
* -根据指定的某们课程的成绩，统计出上述各分数段的人数，并按分
* 数从高到低分段输出。
* -统计并输出指定班级中总成绩或某一门课成绩的各分数段人数和
* 每个人具体的信息。
*  查找学生成绩
* -查找总分或某一门课程成绩的指定分数段的人数及学生的详细信
* 息。
* -查找指定班级中总分或某一门课程成绩属于某分数段的学生详细
* 信息。
* -查找指定学生（例如给定学号）的具体信息，包括：姓名、班级、
* 各科分数、总分数等
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#define M 300
#define N 1000
using namespace std;
class Sort
{
public:
    vector<int> Random();      //生成随机数
    void InsertSort(vector<int>& v);    //直接插入算法
    void QuickSort(vector<int>& v, int low, int high);      //快速排序算法
    void SelectionSort(vector<int>& v);     //选择排序算法

};

vector<int> Sort::Random()
{   vector<int> v;
    srand(int(time(0)));
    for(int i = 0; i < M; i++) {
        v.push_back(rand()%N);
    }
    cout<<"排序前："<<endl;
    vector<int>::iterator it;
    for(it = v.begin(); it != v.end(); it++) {
        cout<<*it<<"  ";
    }
    cout<<endl;
    return v;
}

//直接插入算法
void Sort::InsertSort(vector<int>& v)
{
    int len = v.size();
	for (int i = 1; i < len; ++i) {
		int temp = v[i];   //temp为待插入的值，监视哨
        for(int j = i - 1; j >= 0; --j)
        {//从后一个开始比较，找到比temp大的值
            if(v[j] > temp)
            {
                v[j + 1] = v[j];
                v[j] = temp;
            }
            else
                break;
        }
	}
    cout<<"直接插入排序："<<endl;
    for(int i = 0;i < len;++i) {
        cout<<v[i]<<"  ";
    }
    cout<<endl;
}

//快速排序算法
void Sort::QuickSort(vector<int>& v, int low, int high) {
    if(low = high) {//结束标志
        cout<<"快速排序："<<endl;
        for(int i = 0;i < v.size();++i) {
            cout<<v[i]<<"  ";
        }
        cout<<endl;
        return;
    }
        
    int first = low;
    int last = high;
    int key = v[first];

    while(first < last){
        //将比第一个小的移到前面
        while(first < last && v[last] >= key){
            last--;
        }
        if(first < last){
            v[first++] = v[last];
        }
        //将比第一个大的移到后面
        while(first < last && v[last] <= key){
            first++;
        }
        if(first < last){
            v[last--] = v[first];
        }
    }
    //基准置位
    v[first] = key;
    //前半递归
    QuickSort(v, low, first-1);
    //后半递归
    QuickSort(v, first + 1, high);
    
    
}

//选择排序算法
void Sort::SelectionSort(vector<int>& v) {
	int min, len = v.size();
	for (int i = 0; i < len - 1; ++i) {
		min = i;
		for (int j = i + 1; j < len; ++j) {
			if (v[j] < v[min]) {    // 标记最小的
				min = j;
			}
		}
		if (i != min)  // 交换到前面
			swap(v[i], v[min]);
	}
    cout<<"选择排序："<<endl;
    for(int i = 0;i < len;++i) {
        cout<<v[i]<<"  ";
    }
    cout<<endl;
}

int main(){
    vector<int> v;
    Sort* s = new Sort;
    v = s->Random();
    s->InsertSort(v);
    s->QuickSort(v, 0, M);
    s->SelectionSort(v);
    return 0;
}