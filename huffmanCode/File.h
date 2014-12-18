
/*--------------------------------
全局变量
-------------------------------*/
//extern int bytearr[256];//表示每个字节对应的出现次数
#pragma once
void calcount();//读取文件并统计次数
void compress();//输出压缩文件
void To01String();//读取文件内容，将其转化为01字符串
void StringToCode();//将01字符串转化为编码完的字节字符串
void readCompressFile();//将文本信息读出并转化为01编码,并构建好哈夫曼树
void decompress();//将01编码变成字符
void decompress_exe();//将01编码变成字符,非文本
void To01String_exe();//读取文件内容，将其转化为01字符串，非文本
void calcount_exe();//读取文件并统计次数，非文本
/*--------------------------------
 用于写入文件的字符出现个数信息结构体
-------------------------------*/

typedef struct Infor
{
	unsigned char ch;
	int number;
}infor;