/*
* （1）教学计划编制
* ①问题描述
* 学历进修需要学生在一定的时间内完成一定的课程学习，每一门课有一定的
* 学分，修满学分，可获取相应的学历。因为有些课程内容是另一些课程的学习基
* 础，所以课程学习之间存有一定的先后次序。如：某学历的计算机专业需要学习
* 的课程及课程之间的关系如表 1 所示
* 
* 课程进修关系图 课程编号 课程名称 学分
* C1 程序设计基础 2
* C2 离散数学 3
* C3 数据结构 4
* C4 汇编语言 3
* C5 程序设计与分析 2
* C6 计算机原理 3
* C7 编译原理 4
* C8 操作系统 4
* C9 高等数学 7
* C10 线性代数 5
* C11 普通物理 2
* C12 数值分析 3
* C13 软件工程 3
* C14 数据库原理 
* 本设计的主要任务是根据需要完成的课程的先修关系、每学期开设的课程总
* 数及总的学习时间，制定出教学计划。需事先的基本功能如下。
* -  课程进修目录的读入。
* -  课程进修目录的编辑，如课程增加、删除、信息修改等。
* -  满足一定条件的教学计划的输出。
* ②设计要求
* -  设学期总数不超过 8，课程总数不超过 5，设计一份课程进修单，包括：
* 学期总数、一学期的学分上限、每门课的课程编号、学分和直接先修课
* 程的课程号。
* -  实现上述基本功能。
* -  按各学期中的学习负担尽量均匀地制定教学计划。
* -  按尽可能短的时间完成学习，制定教学计划。
* -  如果无解，报告适当信息。
* （2）修道士野人问题
* ①问题描述
* 河的左岸有 N 个野人和 N 个修道士以及一条小船，修道士们想用这条小船
* 把所有的人都运到河的右岸，但又受到以下限制：
* -  修道士和野人都会划船，但船一次只能载 C 人。
* -  在任何岸边，为了防止野人侵犯修道士，野人数不能超过修道士数，否
* 则修道士将会被野人吃掉。
* 假定野人愿意服从任何一种过河的安排，本设计的主要任务是规划出一种确
* 保修道士安全的过河方案。
* ②设计要求
* -  设计表示野人、修道士、船的位置信息等数据的逻辑结构和存储结构。
* -  从键盘输入修道士与野人的人数 N 和船可容纳的人数 C。
* -  设计检测某一时刻两岸修道士是否安全的算法。
* -  输出安全过河的详细路径。
* -  界面友好，操作简单。
* -  设计做够多的测试用例。
* （3）食物送递服务
* ①问题描述
* 有一个小村，被水围困，村中有 n（n≤30）个住户，现在要给他们送去食
* 物。因每户的储备不一样，能够自救的时间也不同，若超过自救时间段，该住户
* 的人就会被饿死。根据住户地理上的分布和各家能够自救的时间，设计算法求用
* 最短时间把食物送到的方案。
* ②设计要求
* -  设计住户的抽象模型和存储结构。
* -  程序中包含测试数据。另外提供交互方式输入数据。
* -  设计用最短时间把食物送到的算法。
* -  设计结果输出格式，尽量做到易懂
* （4）校园导游
* ①问题描述
* 校园占地几千亩，生活设施分布较散；校园内景色优美，景点甚多。在校园
* 内移动，因时间、交通工具和用户兴趣等原因，需要选择线路。本设计的主要任
* 25
* 务是为在哈尔滨工程大学校区内生活、购物、参观的人们提供行走线路查询、选
* 择、景点介绍的帮助。需实现的基本功能如下：
* -  景点信息的查询。
* -  邻接景点信息的查询。
* -  给出到某个景点的最佳路线。
* -  给出到所有景点的最佳路线。
* -  修改景点信息。
* ②设计要求
* -  设计校园游览图，景点不少于 6 个。
* -  设计图的存储结构。
* -  文件读入或键盘输入图的顶点信息和边信息，在内存中创建图。
* -  实现上述基本功能。
* -  设计足够多的测试用例。
* （5）中国邮路问题
* ①问题描述
* 一个邮递员从邮局选好邮件去投递，然后回到邮局。当然他必须经过他所管
* 辖的每条街至少一次。请为他设计一条投递路线，使其所行的路程尽可能短。
* ②设计要求
* -  设计邮递员的辖区，并将其抽象成图结构进行表示，建立其存储结构
* （注：数据输入可以键盘输入和文件输入两种方式）。
* -  按照输入邮局所在位置，为邮递员设计一条最佳投递路线，要能考虑到
* 辖区一般情况。
* 
*/


#include <stdio.h>
#include <iostream>
using namespace std;
#define MAX 100
//状态
struct Rec
{
	int left_c;		//左岸修道士
	int right_c;	//右岸修道士
	int left_y;		//左岸野人
	int right_y;	//右岸野人
	int boat_location;	//靠岸情况
};
struct rec_Cal
{
	int first;  //记录修道士有几个人在船上
    int second;  //记录野人有几个人在船上
};
Rec arr[MAX];
int index=0;		//下标
int numpass=0;		//成功的路径数量
int start_c,start_y, boat_member_max;//初始化
int cnt;

struct rec_Cal cal[MAX];

//计算当最大载船量为boat_member_max的所有乘船情况
void Cal()
{
	int st = 0;
	for(int i = 0; i <= boat_member_max; ++i)
	{
		if(i != 0)
			st = 0;
		else 
			st = 1;
		for(int j = st; j <= boat_member_max-i; ++j)
		{
			cnt++;
			cal[cnt].first = i, cal[cnt].second = j;
		}
	}
}

//检查是否安全
bool check(Rec t)
{
	//是否重复操作
	for(int i = 0; i < index; i++)
	{
		if((t.left_c == arr[i].left_c && t.left_y == arr[i].left_y) 
			&& (t.boat_location == arr[i].boat_location))
		{
			return false;
		}
	}
	//人数小于0 出错
	if(t.left_c < 0 || t.left_y < 0 || t.right_c < 0 || t.right_y < 0  )
	{
		return false;
	}
	
	/*
	修道士是否被吃
	1、左岸：在修道士人数 不等于0 的情况下，修道士人数 < 野人人数
	2、右岸：在修道士人数 不等于0 的情况下，修道士人数 < 野人人数
	*/
	if((t.left_c != 0 && t.left_c < t.left_y) || 
		(t.right_c < t.right_y && t.right_c != 0) )
	{
		return false;
	}
	return true;
}
int handle(Rec t)
{
	//是否达到目标状态
	if(	t.right_c == start_c && t.right_y == start_y)
	{
		numpass++;
		cout<<endl<<"找到第"<<numpass<<"条路径!"<<endl;
		printf("左岸传教士数\t左岸野人数\t右岸传教士数\t右岸野人数\t船值靠岸\n");
		for(int i = 0; i <= index; i++)
		{
			printf("%4d\t\t",arr[i].left_c);
			printf("%4d\t\t",arr[i].left_y);
			printf("%4d\t\t",arr[i].right_c);
			printf("%4d\t\t",arr[i].right_y);
			if(arr[i].boat_location == 1)
				printf("left");
			else 
				printf("right");
			cout<<endl;
		}
		//找到多条路径的关键一
		return 0;
	}
	if(!check(t))  //查看是否满足条件
		return 0;
	for(int i = 1; i <= cnt; ++i)
	{
		//定义一个临时节点
		struct Rec ttt;
		ttt.left_c = t.left_c - cal[i].first * t.boat_location;
		ttt.left_y = t.left_y - cal[i].second * t.boat_location;
		ttt.right_c = t.right_c + cal[i].first * t.boat_location;
		ttt.right_y = t.right_y + cal[i].second * t.boat_location;
		ttt.boat_location = ( -1 * t.boat_location);
		arr[++index] = ttt;
		handle(arr[index]);			//递归调入点
		--index;
	}
	//找到多条路径的关键二
	return 0;
}

//输入
void CIN()
{
	cout<<"输入修道士人数"<<endl;
	cin>>start_c;
	start_y = start_c;
	cout<<"输入最大船载量"<<endl;
	cin>>boat_member_max;
	arr[index].left_c = start_c;		//初始状态全部在左岸、目的状态全部在右岸
	arr[index].left_y = start_y;
	arr[index].right_c = 0;
	arr[index].right_y = 0;
	arr[index].boat_location = 1;		//初始状态船在左岸
}

int main()
{
	CIN();
	Cal();
	handle(arr[index]);
	cout<<"已找到"<<numpass<<"条过河路径!"<<endl;
	return 0;
}