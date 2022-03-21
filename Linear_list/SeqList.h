#include <iostream>
using namespace std;
class SeqList
{
public:
    SeqList();                              //初始化顺序表
    SeqList(int n);                         //初始化顺序表
    ~SeqList();                             //删除顺序表
    int SearchByIndex(int i);               //顺序表按索引查找
    void SearchByItem(int item);             //顺序表按内容查找
    void CreateSeqList(int n);              //创建顺序表
    void InsertSeqList(int NewItem, int i); //在第i处插入值NewItem
    void DeleteByIndex(int i);              //按索引删除第i+1个元素
    void DeleteByItem(int item);            //按内容删除元素
    void Show();                            //输出顺序表
    bool isEmpty();//判断是否为空表
    bool isFull();//判断是否为满表
    int GetLength();//
    void DeleteAll();//全部删除
private:
    int *base;  //存储数组的指针
    int length; //数组长度
};

