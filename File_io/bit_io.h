#include <fstream>
#include <iostream>
#include<sstream>
#include<string>
#include<bitset>
#include<locale>
#include<codecvt>
using namespace std;
void bitout(const char *filename, string str)
{
    ofstream output(filename,ios::ate);
    output.imbue(std::locale(output.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::little_endian>));
    int length = str.length();
    for (int i = 0; i < length; i++)
    {
        output<<str[i];
        if (i % 8 == 7)
            output << ' ';
        if ((i + 1) % (8 * 10) == 0)
            output << endl;
    }
    output.close();
    cout<<"写入成功!"<<endl;
} //输入文件名、字符串
string readfile(const char *filename)//读取文件的utf-8数值并返回一个储存了那个数值的字符串
{
    ifstream input(filename,ios::binary);
    ostringstream buf;
    char ch;
    cin.unsetf(ios::skipws);
    while (buf&&input.get(ch))
    {
        buf.put(ch);
    }
    input.close();
    return buf.str();
}
string bitin(const char *filename)//文件名,保存二进制码的string
{
    string bit_str;
    string str = readfile(filename);
    int length = str.length();
    for (int i = 0; i < length; i++)
    {
        bit_str.append(bitset<8>(str[i]).to_string());//由于文件是用utf-8编码的所以这里的二进制数字也是utf-8,每一个字符串保存在bit_str末尾
    }
    return bit_str;
}
void display(string bit_str,int n)//字符串整齐打印,依次输入字符串与每行的组数
{
    int length=bit_str.length();
    for(int i=0;i<length;i++)
    {
        cout<<bit_str[i];
        if(i%8==7) cout<<' ';
        if((i+1)%(8*n)==0) cout<<endl;
    }
}