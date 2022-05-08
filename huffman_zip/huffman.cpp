#include "huffman_tree.h"
int main()
{
    while (true)
    {
        int opt, flag = 0;
        char InputFileName[256], OutputFileName[256]; //保存输入与输出的文件名
    p:
        cout << "请输入选项:\n 1:压缩\n 2:解压缩\n 3:退出\n";
        cin >> opt;
        if (opt == 3)
            break;
        else if (opt != 1 && opt != 2 && opt != 3)
        {
            cout << "输入错误,请重新输入" << endl;
            goto p;
        }
        else
        {
            cout << "请输入文件名:";
            fflush(stdin); //清空标准输入流,以防gets()被干扰读取文件名
            gets(InputFileName);
            cout << "请输入需要输出的文件名:";
            fflush(stdin);
            gets(OutputFileName);
        }
        switch (opt)
        {
        case 1:
            flag = Compress(InputFileName, OutputFileName); //压缩,返回值用于判断文件是否存在
            if (flag == -1)
                cout << "源文件不存在!\n";
            else
            {
                cout << "压缩中(^_-)−☆\n";
                cout << "操作成功!\n";
            }
            break;

        case 2:
            flag = Extract(InputFileName, OutputFileName);
            if (flag == -1)
                cout << "源文件不存在!\n";
            else
            {
                cout << "解压中(^з^)-☆\n";
                cout << "解压成功!\n";
            }
            break;
        }
    }
    return 0;
}