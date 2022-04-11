#include"bit_io.h"

int main()
{
    unsigned char **string = new unsigned char*[256 * sizeof(unsigned char)] ;
    std::cout << "以下是按位读取:" << std::endl;
    bitin("信号与系统-第2章.pdf", string);
    std::cout<<string;
    show(string);
    std::cout<<"接下来是按位输出:"<<std::endl;
    bitout("信号与系统-第3章.txt", string);
    return 0;
}