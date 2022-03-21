#include "SeqList_realize.h"
int main()
{
    int m;
    cout<<"请输入顺序表的长度"<<endl;
    cin>>m;
    SeqList l(m);
    int i;
    cout << "1.创建一个顺序表\n2.输出顺序表\n3.通过下标获取元素\n4.查找要查询的元素的下标\n5.通过下标插入元素\n6.通过下标删除一个元素\n7.获取顺序表的长度\n8.删除所有元素\n9.判断顺序表是否为空\n10.判断顺序表是否满\n11.根据数据删除节点\n0.退出" << endl;
    do
    {
        cout << "请选择一个操作: ";
        cin >> i;
        switch (i)
        {
        case 1:
            int n;
            cout << "请输入顺序表的元素个数: ";
            cin >> n;
            l.CreateSeqList(n);
            break;
        case 2:
            l.Show();
            break;
        case 3:
            int i;
            cout << "请输入将要获取元素的下标: ";
            cin >> i;
            l.SearchByIndex(i);
            break;
        case 4:
            int data;
            cout << "请输入将要查找元素的值: ";
            cin >> data;
            l.SearchByItem(data);
            break;
        case 5:
            int index;
            int insertData;
            cout << "请输入要插入的数据的位置: ";
            cin >> index;
            cout << "请输入要插入的数据: ";
            cin >> insertData;
            l.InsertSeqList(insertData, index);
            break;
        case 6:
            int deleteIndex;
            cout << "请输入要删除的数据的下标: ";
            cin >> deleteIndex;
            l.DeleteByIndex(deleteIndex);
            break;
        case 7:
            cout << l.GetLength() << endl;
            break;
        case 8:
            l.DeleteAll();
            cout<<"全部删除成功！"<<endl;
            break;
        case 9:
            if (l.isEmpty() == 1)
            {
                cout << "顺序表为空" << endl;
            }
            else
            {
                cout << "顺序表不为空" << endl;
            }
            break;
        case 10:
            if (l.isFull() == 1)
            {
                cout << "顺序表满" << endl;
            }
            else
            {
                cout << "顺序表不满" << endl;
            }
            break;
        case 11:
            int data1;
            cout << "请输入要删除的数据: ";
            cin >> data1;
            l.DeleteByItem(data1);
            break;
       default:
            break;
        }
    } while (i != 0);
    system("pause");
    return 0;
}