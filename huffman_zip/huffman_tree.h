#include <string>
#include <iostream>
#include <limits.h>
#include <fstream>
using namespace std;

//临时结点
typedef struct
{
    unsigned char UnsignedChar; //以8比特为单位的无符号字符,方便统计字符种类、交换字符种类位置
    unsigned long weight;       //每一类(二进制编码区分)字符出现的频度,即权值
} TmpNode;
// Huffman结点
typedef struct
{
    unsigned char UnsignedChar; //以8比特为单位的无符号字符,方便统计字符种类、交换字符种类位置
    unsigned long weight;       //每一类(二进制编码区分)字符出现的频度,即权值
    char *code;                 //字符对应的Huffman编码
    int parent, lchild, rchild; //定义双亲结点、左右孩子结点
} HufNode, *HufTree;

//选择最小的和第二小的两个结点建立Huffman树调用
void Select(HufNode *HufTree, unsigned int n, int *s1, int *s2)
{
    //找最小的
    unsigned int i;
    unsigned long min = ULONG_MAX; // unsigned long int的最大值
    for (i = 0; i < n; ++i)
    {
        if (HufTree[i].parent == 0 && HufTree[i].weight < min)
        {
            min = HufTree[i].weight;
            *s1 = i;
        }
        HufTree[*s1].parent = 1; //标记此结点已经被选中
    }
    min = ULONG_MAX;
    for (i = 0; i < n; ++i)
    {
        if (HufTree[i].parent == 0 && HufTree[i].weight < min)
        {
            min = HufTree[i].weight;
            *s2 = i;
        }
    }
}

//建立Huffman树
void CreateTree(HufNode *HufTree, unsigned int CharKinds, unsigned int NodeNum)
{
    unsigned int i;
    int s1, s2;
    for (i = CharKinds; i < NodeNum; ++i)
    {
        Select(HufTree, i, &s1, &s2); //选择最小与第二小的两个结点
        HufTree[s1].parent = HufTree[s2].parent = i;
        HufTree[i].lchild = s1;
        HufTree[i].rchild = s2;
        HufTree[i].weight = HufTree[s1].weight + HufTree[s2].weight;
    }
}

//生成Huffman编码
void HufCode(HufNode *HufTree, unsigned CharKinds)
{
    unsigned int i;
    int cur, next, index;
    char *CodeTmp = new char[256 * sizeof(char)]; //暂存编码,最多256个叶子,长度不超过255
    CodeTmp[255] = '\0';
    for (i = 0; i < CharKinds; ++i)
    {
        index = 255;
        //从根开始反向遍历叶子求编码
        for (cur = i, next = HufTree[i].parent; next != 0; cur = next, next = HufTree[next].parent)
        {
            if (HufTree[next].lchild == cur)
                CodeTmp[--index] = '0'; //左'0'
            else
                CodeTmp[--index] = '1'; //右'0'
        }
        HufTree[i].code = new char[(256 - index) * sizeof(char)]; //为第i个字符编码动态分配空间
        strcpy(HufTree[i].code, &CodeTmp[index]);                 //正向保存编码到结点相应数组中
    }
    free(CodeTmp); //释放临时空间
}

//压缩函数
int Compress(char *InputFileName, char *OutputFileName)
{
    unsigned int i, j;
    unsigned int CharKinds;    //字符种类
    unsigned char CharTmp;     //暂存8bit字符
    unsigned long FIleLen = 0; //读入txt文件中的字符总长度
    fstream IFile, OFile;
    TmpNode NodeTmp; //定义临时结点
    unsigned int NodeNum;
    HufTree HufTree;
    char CodeBuf[256] = "\0"; //设置缓冲区
    unsigned int CodeLen;
    TmpNode *TmpNodes = new TmpNode[256 * sizeof(TmpNode)]; //动态分配空间
    //初始化暂存结点.一个unsigned char有八位,每位是0或者1,所以一共有2^8共计256种字符.所以我们用i来表示相应的字符种类
    for (i = 0; i < 256; ++i)
    {
        TmpNodes[i].weight = 0;
        TmpNodes[i].UnsignedChar = (unsigned char)i; //把数组的下标变成unsigned char形式的种类储存
    }
    IFile.open(InputFileName, ios::binary | ios::in);
    if (!IFile.is_open())
    {
        return -1;
    }
    CharTmp = IFile.get(); //从流中读取一个字符并保存
    while (CharTmp != EOF)
    {
        ++TmpNodes[CharTmp].weight; //统计下标对应字符的权重,利用随机读取加快统计速度
        ++FIleLen;                  //每读一个字符,文件字符总长度+1
        CharTmp = IFile.get();
    }
    IFile.close(); //关闭IFile
    //按照频度排序,从大到小
    for (i = 0; i < 255; ++i)
    {
        for (j = i + 1; j < 256; ++j)
        {
            if (TmpNodes[i].weight < TmpNodes[j].weight)
            {
                NodeTmp = TmpNodes[i];
                TmpNodes[i] = TmpNodes[j];
                TmpNodes[j] = NodeTmp;
            }
        }
    }
    //统计实际的字符种类,排除零
    for (i = 0; i < 256; ++i)
        if (TmpNodes[i].weight == 0)
            break; //此时的i就是CharKinds
    CharKinds = i;

    if (CharKinds == 1)
    {
        OFile.open(OutputFileName, ios::out | ios::binary); //打开outputfile
        OFile.put((char)CharKinds);
        OFile.put((char)TmpNodes[0].UnsignedChar);
        OFile.put((char)TmpNodes[0].weight);
        free(TmpNodes);
        OFile.close();
    }
    else
    {
        NodeNum = 2 * CharKinds - 1;
        HufTree = new HufNode[NodeNum * sizeof(HufNode)];
        //初始化
        for (i = 0; i < CharKinds; ++i)
        {
            //将暂存结点的字符和品读拷贝到树结点
            HufTree[i].UnsignedChar = TmpNodes[i].UnsignedChar;
            HufTree[i].weight = TmpNodes[i].weight;
            HufTree[i].parent = 0;
        }
        free(TmpNodes); //释放字符频度暂存空间
        //初始化后到NodeNum-CharKinds个结点
        for (; i < NodeNum; ++i)
        {
            HufTree[i].parent = 0;
        }
        CreateTree(HufTree, CharKinds, NodeNum); //创建Huffman树
        HufCode(HufTree, CharKinds);             //生成Huffman编码
        //写入字符和相应的权重,供解压时重建Huffman树
        OFile.open(OutputFileName, ios::binary | ios::out); //打开OutputFileName文件
        OFile.put((char)CharKinds);
        for (i = 0; i < CharKinds; ++i)
        {
            OFile.put((char)HufTree[i].UnsignedChar); //写入字符信息
            OFile.put((char)HufTree[i].weight);       //写入字符权重
        }
        OFile.put((char)FIleLen); //写入文件长度
        IFile.open(InputFileName, ios::binary | ios::in);
        CharTmp = IFile.get();
        while (IFile.get() != EOF)
        {
            //匹配字符对应编码
            for (i = 0; i < CharKinds; ++i)
            {
                if (CharTmp == HufTree[i].UnsignedChar)
                    strcat(CodeBuf, HufTree[i].code);
            }
            while (strlen(CodeBuf) >= 8)
            {
                CharTmp = '\0';
                for (i = 0; i < 8; ++i)
                {
                    CharTmp <<= 1; //将CharTmp左移一位
                    if (CodeBuf[i] == '1')
                        CharTmp |= 1; //编码为1时通过或运算添加到最低位
                }
                CharTmp = IFile.get();
                strcpy(CodeBuf, CodeBuf + 8); //编码缓存去掉已经处理的八位
            }
            CharTmp = IFile.get();
        }
        //处理长度不足8bits的编码
        CodeLen = strlen(CodeBuf);
        if (CodeLen > 0)
        {
            CharTmp = '\0';
            for (i = 0; i < CodeLen; ++i)
            {
                CharTmp <<= 1;
                if (CodeBuf[i] == '1')
                    CharTmp |= 1;
            }
            CharTmp <<= 8 - CodeLen; //将编码字段从尾部移动到字节的高位并且+0补齐
            CharTmp = IFile.get();
        }
        //关闭文件
        IFile.close();
        OFile.close();
        //释放内存
        for (i = 0; i < CharKinds; ++i)
        {
            free(HufTree[i].code);
        }
        free(HufTree);
    }
    return 0;
}

//解压函数
int Extract(char *InputFileName, char *OutputFileName)
{
    unsigned int i;
    unsigned long FileLen;
    unsigned long WritenLen = 0; //控制写入文件的长度
    fstream IFile, OFile;
    unsigned int CharKinds;
    unsigned int NodeNum;
    HufTree HufTree;
    unsigned char CodeTmp;
    unsigned int root; //保留根结点索引,匹配编码时使用
    IFile.open(InputFileName, ios::in | ios::binary);
    if (!IFile.is_open())
    {
        return -1;
    }
    //读取压缩文件前端字符和编码,用于重建Huffman树
    CharKinds = IFile.get(); //读取字符种类数
    if (CharKinds == 1)      //如果只有一种字符种类
    {
        CodeTmp = IFile.get(); //读取唯一的字符
        FileLen = IFile.get(); //读取文件长度
        OFile.open(OutputFileName, ios::binary | ios::out);
        while (FileLen--)
        {
            OFile.put((char)CodeTmp);
        }
        IFile.close();
        OFile.close();
    }
    else
    {
        NodeNum = 2 * CharKinds - 1; //根据字符种类计算重建Huffman树的结点数
        HufTree = new HufNode[NodeNum * sizeof(HufNode)];
        //读取字符对应权重存入Huffman树结点
        for (i = 0; i < CharKinds; ++i)
        {
            HufTree[i].UnsignedChar = IFile.get();
            HufTree[i].weight = IFile.get();
            HufTree[i].parent = 0;
        }
        //初始化NodeNum-CharKinds个结点的parent
        for (; i < NodeNum; ++i)
        {
            HufTree[i].parent = 0;
        }
        CreateTree(HufTree, CharKinds, NodeNum); //重建Huffman树
        FileLen = IFile.get();
        OFile.open(OutputFileName, ios::binary | ios::out);
        root = NodeNum - 1;
        while (true)
        {
            CodeTmp = IFile.get();
            for (i = 0; i < 8; ++i)
            {
                //从根向下直至叶子结点正向匹配编码对应字符
                if (CodeTmp & 128)
                {
                    root = HufTree[root].rchild;
                }
                else
                    root = HufTree[root].lchild;
                if (root < CharKinds)
                {
                    OFile.put((char)HufTree[root].UnsignedChar);
                    ++WritenLen;
                    if (WritenLen == FileLen)
                        break;
                    root = NodeNum - 1;
                }
                CodeTmp <<= 1;
            }
            if (WritenLen == FileLen)
                break;
        }
        IFile.close();
        OFile.close();
        free(HufTree);
    }
    return 0;
}
