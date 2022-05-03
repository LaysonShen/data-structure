#include "bit_io.h"
int main()
{
    string bit_str;//创建用于保存二进制字符串的string
    const char *readfile="test1.txt";//输入文件名
    const char *writefile="test2.txt";
    cout<<"以下是读取文件并且当作二进制保存的、整齐打印功能:"<<endl;
    bit_str=bitin(readfile);//储存生成的二进制数字字符串
    display(bit_str,10);//调用整齐打印函数
    cout<<'\n'<<"接下来实现把字符串保存到另一个文件当中的功能:"<<endl;
    bitout(writefile,bit_str);
    return 0;
}