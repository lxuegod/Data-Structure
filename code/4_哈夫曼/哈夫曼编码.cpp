/*
* 文件压缩
* 22
* ①基本要求
* 哈夫曼编码是一种常用的数据压缩技术，对数据文件进行哈夫曼编码可大大
* 缩短文件的传输长度，提高信道利用率及传输效率。要求采用哈夫曼编码原理，
* 统计文本文件中字符出现的词频，以词频作为权值，对文件进行哈夫曼编码以达
* 到压缩文件的目的，再用哈夫曼编码进行译码解压缩。
* -  统计待压缩的文本文件中各字符的词频，以词频为权值建立哈夫曼树，
* 并将该哈夫曼树保存到文件 HufTree.dat 中。
* -  根据哈夫曼树（保存在 HufTree.dat 中）对每个字符进行哈夫曼编码，并
* 将字符编码保存到 HufCode.txt 文件中。
* -  压缩：根据哈夫曼编码，将源文件进行编码得到压缩文件 CodeFile.dat。
* -  解压：将 CodeFile.dat 文件利用哈夫曼树译码解压，恢复为源文件。
* ②选做要求
* -  实现 Burrows-Wheeler 压缩算法。
* -  比较 Burrows-Wheeler 压缩算法与单纯的哈夫曼编码压缩算法的压缩效
* 率。
* 针对不同长度的文件，统计 Burrows-Wheeler 压缩算法的执行时间。

*/

#include <iostream>
#include <map>
#include <fstream>
#include <bits/stdc++.h>
#define Max 255
using namespace std;
//树节点结构体
struct TreeNode{
    int weight;  //权值
    char word;   //字符
    string huffmancode;  //哈夫曼编码
    struct TreeNode* lChild;   //左孩子
    struct TreeNode* rChild;   //右孩子
};

int M = 0;  //记录一共有多少关键字
TreeNode *w_node[Max];

class HuffMan
{
public:
    map<char, int> Hash(string str);  //统计字符出现的频率
    void HuffManTree(map<char, int> map_char);  //构造huffmantree
    string ReadFile(const char* fileName);  //读文件，获取字符串
    void Out();     //测试输出函数
    void OutFile(string str, const char* fileName); //新建HufCode的文件
    void Compress(string str);  //压缩 , map<char, int> map_char

    TreeNode* CreateHuffmanTree(int w[],char s[]); //创建哈夫曼树
    void encode(TreeNode *node,string code); //递归编码
    //int getWPL(TreeNode *node,int depth);  //WPL

};

class cmp
{
    public:
    bool operator()(const TreeNode *n1,const TreeNode *n2)const{
        return n1->weight > n2->weight;
    }
};

//创建哈夫曼树
TreeNode* HuffMan::CreateHuffmanTree(int w[],char s[]) {
    //优先队列  让权值最大的在前面
    priority_queue<TreeNode*,vector<TreeNode*>,cmp > q;
    for(int i = 0;i < M; i++){
        TreeNode* node = new TreeNode;
        node->lChild = node->rChild = NULL;
        node->weight = w[i];
        node->word = s[i];
        q.push(node);
        w_node[i] = node;  //记录下原本的点
    }
    
    while (q.size()>1) { //队列长度大于1
        TreeNode *parent = new TreeNode;
        parent->lChild = q.top();
        q.pop();
        parent->rChild = q.top();
        q.pop();
        parent->weight = parent->lChild->weight + parent->rChild->weight;
        q.push(parent);
    }
    return q.top();
}

//递归编码
void HuffMan::encode(TreeNode *node, string code) {
    if(node == NULL) return;
    node->huffmancode = code;
    encode(node->lChild,code+'0');  //左孩子为加  0
    encode(node->rChild,code+'1');  //右孩子加  1 
}


// //WPL
// int HuffMan::getWPL(TreeNode *node,int depth) {
//     if(node->lChild == NULL&&node->rChild==NULL) {
//         return node->weight*depth;
//     }
//     return getWPL(node->lChild,depth+1)+getWPL(node->rChild,depth+1);
// }


//统计字符出现的频率
map<char, int> HuffMan::Hash(string str)
{
    map<char, int> map_char;  //map存储字符和出现的次数
    map<char, int>::iterator it;
    int i;
    int len = str.length();
    for(i = 0; i < len; i++) {
        it = map_char.find(str[i]);
        if(it != map_char.end()) { //找到出现过的字符 value值加一
            map_char[str[i]]++;
        }else { //插入新的字符
            map_char.insert(pair<char, int>(str[i], 1));
            M++;
        }
    }
    return map_char;

    // for (it = map_char.begin(); it != map_char.end(); ++it) {
    //     cout << it->first<< " " << it->second<< endl;
    // }
}

//读文件，获取字符串
string HuffMan::ReadFile(const char* fileName)
{
    string str;
    string line; //每行的字符串
    fstream infile;  //输入流
    infile.open(fileName, ios::in);  //只读打开  ./1.txt
    while(getline(infile, line)) { //按行读取
        str += line + '\n';
    } 
    infile.close();
    return str;
}

//构造huffmantree
void HuffMan::HuffManTree(map<char, int> map_char)
{
    string str = "";
    map<char, int>::iterator it;
    char s[Max];
    int weight[Max];
    int i;
    for(it = map_char.begin(), i = 0; it != map_char.end(); ++it, i++) {
        s[i] = it->first;
        weight[i] = it->second;
    }

    map<char, string> mapCode;
    TreeNode *root = CreateHuffmanTree(weight,s);
    encode(root,"");
    for(int i = 0; i < M; i++){
        //cout<<w_node[i]->word<<":"<<w_node[i]->huffmancode<<"   ";
        //获得哈夫曼树的编码转为字符串类型
        string s(1, w_node[i]->word);
        str += s + ":" + w_node[i]->huffmancode + "\n"; //加上'\n'是为了记录 换行
        mapCode.insert(pair<char, string>(w_node[i]->word, w_node[i]->huffmancode));
        
    }
    OutFile(str, "HufTree.txt");
    map<char, string>::iterator iter;
    for(iter = mapCode.begin(); iter != mapCode.end(); iter++) {
         cout<<iter->first<<":"<<iter->second<<endl;
    }
    string file_str = ReadFile("./2.txt");//ReadFile("./2.txt");
    string compress_str = "";
    int len = file_str.length();
    for(int i = 0; i < len; i++) {
        iter = mapCode.find(file_str[i]);
        if(iter != mapCode.end()) {
            compress_str += iter->second + " ";
        }
    }
    // cout<<compress_str<<endl;
    //OutFile(compress_str, "CodeFile.txt");  //CodeFile.txt
    //cout<<str;
    // cout<<endl;
    // cout<<"平均查找长度:"<<getWPL(root,0)<<endl;
    //测试两个数组
    // for(int j = 0; j < i; j++) {
    //     cout<<s[j]<<":"<<weight[j]<<"  ";
    // }
    Compress(compress_str);
    
}

//新建HufCode的文件
void HuffMan::OutFile(string str, const char* fileName)
{
    ofstream outFile;
    outFile.open(fileName);
    outFile<<str;
    outFile.close();
}

 //进行压缩
void HuffMan::Compress(string str) //, map<char, int> map_char
{
    FILE* fOut = fopen("CodeFile.dat", "wb");//2进制写入文件
    int Hufflength = 0;//压缩长度
    int num = 0;
    unsigned char saveChar = 0;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        //用来保存二进制文件，因为char类型是1个字节，所以每8位储存一次 ,而且用unsigned无符号型，避免符号位干扰
        saveChar = ((str[i]) | saveChar);//让saveChar和编码中的每一位进行或操作
        num++;
        if (num == 8)
        {
            fwrite(&saveChar, sizeof(char), 1, fOut);//每8位写入一次文件
            Hufflength++;
            saveChar = 0;//重新置0
            num = 0;
        }
        else {
            saveChar = saveChar << 1; //每做完一步，左移一位
        }
    }
    //最后不到8位，移到最左端
    if (num != 8)
    {
        saveChar = saveChar << (7 - num);//移到最左端
        fwrite(&saveChar, sizeof(char), 1, fOut);
        Hufflength++;
    }
    fclose(fOut);
}

//测试输出函数
void HuffMan::Out()
{
    string str;
    const char* fileName;
    fileName = "./2.txt";//"./2.txt";
    str = ReadFile(fileName);
    
    //测试字符串str
    //cout<<str<<endl;
    // cin>>str;

    map<char, int> map_char= Hash(str);
    //测试map是否正确
    string strWeight = "";
    map<char, int>::iterator it;
    for (it = map_char.begin(); it != map_char.end(); ++it) {
        cout << it->first<< ":" << it->second<<"  ";  //<< endl
        string s(1, it->first);
        stringstream ss;
        ss << it->second;
        strWeight += s + ":" + ss.str() + "\n";
    }
    //cout<<endl;
    OutFile(strWeight, "HufTree.dat");

    HuffManTree(map_char);
}

int main() {
    HuffMan * huf = new HuffMan;
    huf->Out();
}