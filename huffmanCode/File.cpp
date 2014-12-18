#include "File.h"
#include "Main.h"
extern int bytearr[256];
extern int length;//需要编码的字符个数
extern int painum;//需要建堆的元素个数-1
string str;//要压缩的文件名
extern HuffNode * rootNode;//保存形成的树的根节点
string code = "";//储存文件编码后的01字符串
string byteCode = "";//储存01字符串转换的字节字符串
int add0 = 0;//文件最后补上0的个数
int pagesizecount = 0;//作为文本长度计数器，计算读取的文本
string page = "";//表示解码后的文本
int pagesize=0;//存储传入时记录的原文本长度,作为校验文本是否丢失的标准
/*--------------------------------
读取文件并统计次数
-------------------------------*/
void calcount()
{
	cout<<"请输入要压缩的文件名(须加后缀,且文件名不存在空格)"<<endl;
	cin>>str;

	memset(bytearr,0,sizeof(bytearr));
	FILE *fp = fopen(str.c_str(),"rb");
	if(fp ==NULL)
	{
		cout<<"文件打开失败"<<endl;
		system("pause");
		exit(1);
	}
	int val;
	cout<<"正在压缩，请稍后......"<<endl;
	val = fgetc(fp);
	while(!feof(fp))
	{
		bytearr[val]++;//将记录数目的值加1
		val = fgetc(fp);
		//fread(&val,1,1,fp);//每次从文件中读取1个字节
	}
	fclose(fp);
	
}
/*--------------------------------
制成编码表
-------------------------------*/
infor* codeTable()
{
	infor * informa = (infor *)malloc(length*sizeof(infor));
	int j = 0;//用于informa的计数器
	for(int i = 0;i < 256;++i)
	{
		if(bytearr[i] != 0)
		{
			informa[j].ch = i;
			informa[j].number = bytearr[i];
			++j;
		}
	}
	return informa;
}
/*--------------------------------
读取文件内容，将其转化为01字符串
-------------------------------*/
void To01String()
{
	FILE *fp = fopen(str.c_str(),"rb");
	if(fp ==NULL)
	{
		cout<<"文件打开失败"<<endl;
		system("pause");
		exit(1);
	}
	int val;
	//fread(&val,1,1,fp);
	val = fgetc(fp);
	while(!feof(fp))
	{
		findCode(val,rootNode);
		val = fgetc(fp);
		//fread(&val,1,1,fp);
	}
	fclose(fp);
}
/*--------------------------------
将01字符串转化为编码完的字节字符串
-------------------------------*/
void StringToCode()
{
	int block = code.length()/8;
	add0 = 8-(code.length()-block*8);
	string stri = "0";
	for(int i = 0;i < add0;++i)
	{
		code+=stri;
	}
	string string8;
	
	unsigned char sum = 0;
	char* ch;
string st = code.substr(code.length()-add0);//除去补上的0
	for(i = 0;i < code.length();i+=8)
	{
		string8 = code.substr(i,8);//每次取8位
		ch = (char*)string8.c_str();
		sum = 0;
		for(int j = 128;j >= 1;j/=2)
		{
			sum += ((*ch)-48)*j;//计算该一个字节对应的字符
			++ch;
		}
		//string val(&sum,1);//将char转为string
		byteCode+=sum;
	}
}

/*--------------------------------
输出压缩文件
-------------------------------*/
void compress()
{
	//codeTable();
	
	
	StringToCode();
	string strval = str+".pyr";
	FILE *fp = fopen(strval.c_str(),"wb");
	char * content = (char*)byteCode.c_str();
	fwrite(&length,sizeof(int),1,fp);//传入需要编码的字符个数
	fwrite(codeTable(),sizeof(infor)*length,1,fp);//传入编码表

	fwrite(&add0,sizeof(int),1,fp);//传入需要补0的个数
	fwrite(&pagesizecount,sizeof(int),1,fp);//传入未编码前文本的总字节数
	for(int i = 0;i < byteCode.length();++i)
	{
		fwrite(content,1,1,fp);//传入文本内容
		++content;
	}
	fclose(fp);
	

}
/*--------------------------------
将文本信息读出并转化为01编码,并构建好哈夫曼树
-------------------------------*/
void readCompressFile()
{
	memset(bytearr,0,sizeof(bytearr));
	FILE *fp = fopen(str.c_str(),"rb");
	if(fp ==NULL)
	{
		cout<<"文件打开失败"<<endl;
		system("pause");
		exit(1);
	}
	char val;

	fread(&length,sizeof(int),1,fp);
	infor * informa = (infor *)malloc(length*sizeof(infor));
	fread(informa,sizeof(infor)*length,1,fp);

	fread(&add0,sizeof(int),1,fp);
	fread(&pagesize,sizeof(int),1,fp);
	fread(&val,1,1,fp);
	while(!feof(fp))
	{
		
			string strval(&val,1);//将val转为string
			byteCode+=strval;
			fread(&val,1,1,fp);//每次从文件中读取1个字节
	
		
	}
	fclose(fp);
	unsigned char * ch = (unsigned char*)byteCode.c_str();
	for(int i = 0;i < byteCode.length();++i)
	{
		for(int pos = 128;pos >= 1;pos/=2)//将一个字节的每一位取出来变成字符串
		{
			if((*ch)/pos == 0)
			{
				code+="0";
			}
			else
			{
				code+="1";
				(*ch) -= pos;
			}
		}
		++ch;
	}

	for(i= 0;i < length;++i)
	{
		bytearr[informa->ch] = informa->number;
		++informa;
	}
	rootNode = buildHuff();

}
/*--------------------------------
将01编码变成字符,并输出到文件中
-------------------------------*/
void decompress()
{
//	string val = code.substr(code.length() - add0);
	code = code.substr(0,code.length() - add0);
	char *chpos= (char *)code.c_str();
	str = str.substr(0,str.length()-4);
	str = str.insert(0,"decompress_");
	FILE *fp = fopen(str.c_str(),"w");
	int countnum = 0;
	if(code.length() !=0)
	{
		while(countnum < code.length())//防止越界
		{
			findBytecode(rootNode,&chpos,&countnum,fp);
		}
	}
	else
	{
		for(int i = 0;i < pagesize;++i)
		{
			string strval(&(rootNode->element),1);
			
			if(rootNode->element != '\r')//文本格式输出会自动识别\n
			{
				fputc(rootNode->element,fp);
				
			}
				page+=strval;
			}
		
	}
	
	if(page.length() == pagesize)//判断文件是否损坏
	{
		
		//fputs(page.c_str(),fp);
		cout<<"解压成功！"<<endl;
		fclose(fp);
	}
	else
	{
		cout<<"文件损坏！"<<endl;
		fclose(fp);
	}
	
}
/*--------------------------------
遍历树找到与之对应的字符
-------------------------------*/
void findBytecode(HuffNode *root,char** ch,int* countnum,FILE *fp)//传入的参数为每次递归的根节点，解析的01字符，作为01字符长度的计数器，防止越界
{
	
		if(!(root->isLeaf()))//递归到内部节点
		{
			if(**ch == '0')
			{
				
				findBytecode(root->left,&(++(*ch)),&(++(*countnum)),fp);//复杂是因为防止栈溢出
				
			}
			else
			{
				findBytecode(root->right,&(++(*ch)),&(++(*countnum)),fp);
				
			}
			
		}
		else//递归到叶节点
		{
			string strval(&(root->element),1);
			
				if(root->element != '\r')//文本格式输出会自动识别\n
				{
					fputc(root->element,fp);
					
				}
				page+=strval;

			
			
			//fflush(fp);
		
			
		}
		//findBytecode(rootNode,ch,countnum,fp);
	
	
	return;
}
/*--------------------------------
非文本
-------------------------------*/
/*--------------------------------
读取非文本文件并统计次数
-------------------------------*/
void calcount_exe()
{
	cout<<"请输入要压缩的文件名(须加后缀,且文件名不存在空格)"<<endl;
	cin>>str;
	memset(bytearr,0,sizeof(bytearr));
	FILE *fp = fopen(str.c_str(),"rb");
	if(fp ==NULL)
	{
		cout<<"文件打开失败"<<endl;
		system("pause");
		exit(1);
	}
	unsigned char val;
	cout<<"正在压缩，请稍后......"<<endl;
	fread(&val,1,1,fp);//每次从文件中读取1个字节
	while(!feof(fp))
	{
		bytearr[val]++;//将记录数目的值加1
		fread(&val,1,1,fp);//每次从文件中读取1个字节
	}
	fclose(fp);
	
}
/*--------------------------------
读取非文本文件内容，将其转化为01字符串
-------------------------------*/
void To01String_exe()
{
	FILE *fp = fopen(str.c_str(),"rb");
	if(fp ==NULL)
	{
		cout<<"文件打开失败"<<endl;
		system("pause");
		exit(1);
	}
	unsigned char val;
	fread(&val,1,1,fp);
	while(!feof(fp))
	{
		findCode(val,rootNode);
		fread(&val,1,1,fp);
	}
	fclose(fp);
}
/*--------------------------------
遍历树找到与之对应的字节，输出非文本文件
-------------------------------*/
void findBytecode_exe(HuffNode *root,char** ch,int* countnum,FILE *fp)//传入的参数为每次递归的根节点，解析的01字符，作为01字符长度的计数器，防止越界
{
	
		if(!(root->isLeaf()))//递归到内部节点
		{
			if(**ch == '0')
			{
				
				findBytecode_exe(root->left,&(++(*ch)),&(++(*countnum)),fp);//复杂是因为防止栈溢出
				
			}
			else
			{
				findBytecode_exe(root->right,&(++(*ch)),&(++(*countnum)),fp);
				
			}
			
		}
		else//递归到叶节点
		{
			string strval(&(root->element),1);
			fwrite(&root->element,1,1,fp);
			page+=strval;

			
			
			//fflush(fp);
		
			
		}
		//findBytecode(rootNode,ch,countnum,fp);
	
	
	return;
}
/*--------------------------------
将01编码变成字节，非文本,并输出到文件中
-------------------------------*/
void decompress_exe()
{
//	string val = code.substr(code.length() - add0);
	code = code.substr(0,code.length() - add0);
	char *chpos= (char *)code.c_str();
	str = str.substr(0,str.length()-4);
	str = str.insert(0,"decompress_");
	FILE *fp = fopen(str.c_str(),"wb");
	int countnum = 0;
	if(code.length() !=0)
	{
		while(countnum < code.length())//防止越界
		{
			findBytecode_exe(rootNode,&chpos,&countnum,fp);
		}
	}
	else
	{
		for(int i = 0;i < pagesize;++i)
		{
			string strval(&(rootNode->element),1);
			
			fwrite(&rootNode->element,1,1,fp);
			page+=strval;
		}
		
	}
	
	if(page.length() == pagesize)//判断文件是否损坏
	{
		
		//fputs(page.c_str(),fp);
		cout<<"解压成功！"<<endl;
		fclose(fp);
	}
	else
	{
		cout<<"文件损坏！"<<endl;
		fclose(fp);
	}
	
}