/*
* （1）表达式求值问题
* 问题描述
* 表达式是数据运算的基本形式。人们的书写习惯是中缀式，如：
* 11+22*(7-4)/3。中缀式的计算按运算符的优先级及括号优先的原则，相同级别从
* 左到右进行计算。表达式还有后缀式（如：22 7 4 - * 3 / 11 +）和前缀式（如：+
* 11 / * 22 – 7 4 3）。后缀表达式和前缀表达式中没有括号，给计算带来方便。如
* 后缀式计算时按运算符出现的先后进行计算。本设计的主要任务是进行表达式形
* 式的转换及不同形式的表达式计算。
* ②基本要求
* -  从文件或键盘读入中缀表达式。
* -  设计操作数为多位整数，操作符为加、减、乘、除、求模的中缀表达式
* 求值算法。
* -  设计将中缀表达式转换为后缀表达式的算法。
* -  设计将中缀表达式转换为前缀表达式的算法。
* -  设计后缀表达式求值算法。
* -  设计前缀表达式求值算法。
* -  输出各种形式的表达式。
* （2）任务调度
* ①问题描述
* 多用户多任务操作系统中，多个任务同时共享计算机系统资源。为了使多个
* 任务均能够顺利执行，操作系统要按一定的原则对它们进行调度，使它们按一定
* 的次序进行。设只有一个 CPU，现有多个任务，它们需要 CPU 服务的时间已知。
* 在下列假设下，按平均等待时间最短为原则，设计算法求出任务的执行顺序。
* -  忽略任务提交的时间差，即认为各任务同时提交。
* -  各任务不同时提交。
* ②基本要求
* -  为任务列表设计数据结构和存储结构。
* -  任务输入，至少包括任务编号及所需 CPU 的服务时间，任务数不得少
* 于 5 个。
* -  如果按提交顺序执行，求出每个任务的开始执行时间、终止时间、等待
* 时间和所有任务的平均等待时间。
* -  按平均等待时间最短，设计任务调度算法，输出任务的执行序列；求出
* 每个任务的开始执行时间、终止时间、等待时间和所有任务的平均等待
* 时间；并把结果与上一时间对比。
* ③思考
* -  最短作业优先，存在“长任务饥饿”的问题，即如果动态地不断加入作
* 业，只要提交作业所需要的 CPU 服务时间比较短，则先提交的长任务
* 将一直得不到服务，如何解决该问题？

*/

#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10;
int n;
double sum = 0;
struct task
{
    int startTime;  //开始时间
    int continuedTime;  //持续时间
    int waitTime;  //当前时刻多长时间可能被处理  等待时间
    int idx;  //序号
}t[N];

class Dispatch
{
public:
    void Work(int top, int tmp);
    void Out();
};

//比较a, b 的开始时间
bool CompareStartTime(task a, task b)
{
    return a.startTime < b.startTime;
}

//比较持续时间和等待时间
bool CompareWaitTime(task a, task b)
{
    if(a.waitTime + a.continuedTime == b.waitTime + b.continuedTime) {
        return a.waitTime < b.waitTime;
    }
    return a.waitTime + a.continuedTime < b.waitTime + b.continuedTime; 
}

void Dispatch::Work(int top, int tmp)
{
    if(top == n+1) {
        return;
    }
    sort(t + top, t + n + 1, CompareWaitTime);
    tmp = max(tmp, t[top].startTime);
    cout<<"第 "<<top<<" 个处理的任务序号是 "<<t[top].idx<<endl;
    cout<<"开始时间 "<<tmp<<endl;
    cout<<"等待时间 "<<tmp<<endl;
    sum += tmp;
    tmp += t[top].continuedTime;
    cout<<"结束时间 "<<tmp<<endl;
    cout<<endl;
    for(int i = top + 1; i <= n; i++) {
        t[i].waitTime = max(0, t[i].startTime - tmp);
    }
    Work(top + 1, tmp);
}

void Dispatch::Out()
{
    cout<<"选择问题情形"<<endl;
    cout<<"1.同时提交"<<endl;
    cout<<"2.不同时提交"<<endl;
    int m;
    cin>>m;
    if(m < 1 || m > 2) {
        cout<<"错误！"<<endl;
        Out();
    }else {
        cout<<"输入要处理的任务个数"<<endl;
        cin>>n;
        sum = 0;
        if(m == 1) {
            for(int i = 1; i <= n; i++) {
                cout<<"第 "<<i<<" 个任务的处理时间"<<endl;
                cin>>t[i].continuedTime;
                t[i].startTime = 0;
                t[i].waitTime = 0;
                t[i].idx = i;
            }
            Work(1, 0);
            cout<<"平均等待时间"<<sum/n<<endl;
        }else {
            cout<<"请选择执行方式"<<endl;
            cout<<"1.按提交顺序"<<endl;
            cout<<"2.按平均等待时间最短"<<endl;
            int orr;
            cin>>orr;
            for(int i = 0; i <= n; i++) {
                cout<<"输入第 "<<i<<" 个任务的开始执行时间和处理时间"<<endl;
                cin>>t[i].startTime>>t[i].continuedTime;
                t[i].waitTime = t[i].startTime;
                t[i].idx = i;
            }
            if(orr == 1) {
                int tmp = 0;
                sort(t + 1, t + n + 1, CompareStartTime);
                for(int i = 1; i <= n; i++) {
                    tmp = max(tmp, t[i].startTime);
                    sum += tmp;
                    cout<<"第 "<<i<<" 个被任务处理的任务编号是 "<<t[i].idx<<endl;
                    cout<<"开始时间"<<tmp<<endl;
                    cout<<"等待时间 "<<tmp<<endl;
                    tmp += t[i].continuedTime;
                    cout<<"结束时间 "<<tmp<<endl;
                    cout<<endl;
                }
                cout<<"平均等待时间 "<<sum/n<<endl;
            }else {
                int tmp = 0;
                sort(t + 1, t + n+ 1, CompareStartTime);
                for(int i = 1; i <= n; i++) {
                    tmp = max(tmp, t[i].startTime);
                    sum += tmp;
                    tmp += t[i].continuedTime;
                    cout<<endl;
                }
                double pre = sum/n;
                sum = 0;
                Work(1, 0);
                cout<<"平均等待时间 "<<sum/n<<endl;
                cout<<"和按顺序处理，节省时间是 "<<pre-sum/n<<endl;
            }
        }
    }
}

int main() {
    Dispatch * dis = new Dispatch;
    dis->Out(); 
    return 0;
}