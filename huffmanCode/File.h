
/*--------------------------------
ȫ�ֱ���
-------------------------------*/
//extern int bytearr[256];//��ʾÿ���ֽڶ�Ӧ�ĳ��ִ���
#pragma once
void calcount();//��ȡ�ļ���ͳ�ƴ���
void compress();//���ѹ���ļ�
void To01String();//��ȡ�ļ����ݣ�����ת��Ϊ01�ַ���
void StringToCode();//��01�ַ���ת��Ϊ��������ֽ��ַ���
void readCompressFile();//���ı���Ϣ������ת��Ϊ01����,�������ù�������
void decompress();//��01�������ַ�
void decompress_exe();//��01�������ַ�,���ı�
void To01String_exe();//��ȡ�ļ����ݣ�����ת��Ϊ01�ַ��������ı�
void calcount_exe();//��ȡ�ļ���ͳ�ƴ��������ı�
/*--------------------------------
 ����д���ļ����ַ����ָ�����Ϣ�ṹ��
-------------------------------*/

typedef struct Infor
{
	unsigned char ch;
	int number;
}infor;