#include "SeqList.h"
const int MAXSIZE = 300;
int ERROR;

//初始化顺序表
SeqList ::SeqList()
{
    base = new int[MAXSIZE];
}
SeqList::SeqList(int n)
{
    base = new int[n];
}
//销毁顺序表
SeqList ::~SeqList()
{
    delete[] base; //删除数组地址的指针
}
//顺序表按索引查找返回内容
int SeqList::SearchByIndex(int i)
{
    if ((i > MAXSIZE) || (i < 0) || isEmpty())
    {
        ERROR = -1;
        return (-1); //查找出错返回
    }
    else
    {
        return base[i]; //返回指定位置的元素值
    }
}
//顺序表按内容查找输出索引
void SeqList::SearchByItem(int item)
{
    if (isEmpty())
        cout << "查找失败，这是空表" << endl;
    int i;
    bool find=0;
    for (i = 0; i < length; i++)
    {
        if (base[i] == item)
        {
            find = 1;
            cout << "第" << i + 1 << "个元素是" << item << endl;
        }
    }
    if (find)
        cout << "查找成功" << endl;
    else
        cout << "查找失败，表中无此元素" << endl;
}
//创建顺序表
void SeqList ::CreateSeqList(int n)
{
    if (n < 0)
    {
        cout << "输入节点个数有误！" << endl;
        exit(EXIT_FAILURE);
    }
    else
    { 
        int i;
        for (i = 0; i < n; i++)
        {
            cout << "请输入第" << i + 1 << "个节点元素:";
            cin >> base[i];
        }
        length = n;
    }
}
//顺序表的插入
void SeqList::InsertSeqList(int NewItem, int i)
{
    int j;

    if ((i > MAXSIZE + 1) || (i < 0) || isFull())
    {
        ERROR = -2; //插入出错返回
        cout << "插入出错";
    }
    else
    {
        for (j = length; j >= i; j--) //从后往前移
        {
            base[j + 1] = base[j];
        }
        base[i] = NewItem;   //插入新元素
        length = length + 1; //表长加一
    }
}
//判断顺序表是否为空
bool SeqList ::isEmpty()
{
    if (length == 0) //如果顺序表的长度为0，则表为空
        return true;
    return false; //长度不为0，表不为空
}
//判断顺序表是否满
bool SeqList ::isFull()
{
    if (length == MAXSIZE) //当长度为定义的最大长度，则顺序表满
        return true;
    return false; //否则不满
}
//获取顺序表的长度
int SeqList::GetLength()
{
    return length; //返回顺序表的长度
}
//根据下标删除一个节点
void SeqList ::DeleteByIndex(int i)
{
    int j;
    if (i < 0 || i > length) //输入的位置不合法报异常
        cout << "删除失败，索引不在顺序表范围中" << endl;
    else
    {
        for (j = i; j <= length - 1; j++)
        {                          //循环到要删除节点的位置
            base[j] = base[j+1]; //该位置后的元素全体向前移一个位置
        }
        length-=1; //更改顺序表长度
    }
}
//按值删除元素
void SeqList ::DeleteByItem(int item)
{
    int L=length;
    for(int i =0; i<L+1;i++)
    {
        if(base[i]==item)
        {
          for(int j =i;j<L+1;j++)  
          {
              base[j]=base[j+1];
              length-=1;
          }
        }
    }
}
//删除所有元素
void SeqList ::DeleteAll()
{
    for (int i = length; i > 0; i--) //从最后一个元素开始删除，长度减一
    {
        base[i] = base[i - 1]; //元素向前移位
        length--;              //长度减一
    }
}
//顺序表显示
void SeqList::Show()
{
    int i;

    cout << "The list : ";
    for (i = 0; i <length; i++)
    {
        cout << base[i] << " "; //逐个显示数据元素
    }
    cout << endl; //换行
}