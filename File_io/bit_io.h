#include <fstream>
#include <iostream>

void bitin(const char *name, unsigned char **str)
{
    std::ifstream f(name, std::ios::binary); //以二进制方式流式读取文件
    int index = 0;                           //设置索引起点
    f.seekg(0, f.end);                       //把指针指向文件结尾
    int length = f.tellg();                  //获取文件长度
    for (int i = 0; i < length; i++)
    {
        f.seekg(i, std::ios::beg); //指针指向第i+1个位置
        unsigned char c = (unsigned char)f.get();
        //将得到的字节存入 buffer 中
        unsigned char *buf = new unsigned char[9 * sizeof(unsigned char)];
        for (int i = 7; i >= 0; i--)
        {
            buf[7 - i] = (c & (1 << i) ? '1' : '0'); //按位计算再判断
        }
        buf[8] = '\0';
        // 将 bufffer 写入 str 中去
        str[index++] = buf;
        delete[] buf;
    }
    f.close();
} //输入文件名、数组

void bitout(const char *name, unsigned char **str)
{
    std::ofstream f(name, std::ios::binary | std::ios::ate);
    int i = f.tellp();
    while (*str)
    {
        unsigned int buf = 0;
        for (int i = 0; i < 8; i++)
        {
            // 根据str中得到的每个字节，保存到 buffer 中，进而写入文件中
            buf |= (*(*str + i) - '0') << (7 - i);
        }
        f.seekp(i, f.beg);
        f.write((const char *)buf, sizeof(unsigned int));
        i--;
        str = str + 1;
    }
} //输入文件名、数组

// 调控输出，每八个换行
void show(unsigned char **str)
{
    int index = 0;
    while (str)
    {
        if (*str == NULL)
            break;
        else
        {
            printf("%s ", *str);
            if (++index % 8 == 0)
                std::cout << '\n';
        }
        str++;
    }
    std::cout << "\n";
}