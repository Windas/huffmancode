#include "File.h"
#include "Main.h"
extern int bytearr[256];
extern int length;//��Ҫ������ַ�����
extern int painum;//��Ҫ���ѵ�Ԫ�ظ���-1
string str;//Ҫѹ�����ļ���
extern HuffNode * rootNode;//�����γɵ����ĸ��ڵ�
string code = "";//�����ļ�������01�ַ���
string byteCode = "";//����01�ַ���ת�����ֽ��ַ���
int add0 = 0;//�ļ������0�ĸ���
int pagesizecount = 0;//��Ϊ�ı����ȼ������������ȡ���ı�
string page = "";//��ʾ�������ı�
int pagesize=0;//�洢����ʱ��¼��ԭ�ı�����,��ΪУ���ı��Ƿ�ʧ�ı�׼
/*--------------------------------
��ȡ�ļ���ͳ�ƴ���
-------------------------------*/
void calcount()
{
	cout<<"������Ҫѹ�����ļ���(��Ӻ�׺,���ļ��������ڿո�)"<<endl;
	cin>>str;

	memset(bytearr,0,sizeof(bytearr));
	FILE *fp = fopen(str.c_str(),"rb");
	if(fp ==NULL)
	{
		cout<<"�ļ���ʧ��"<<endl;
		system("pause");
		exit(1);
	}
	int val;
	cout<<"����ѹ�������Ժ�......"<<endl;
	val = fgetc(fp);
	while(!feof(fp))
	{
		bytearr[val]++;//����¼��Ŀ��ֵ��1
		val = fgetc(fp);
		//fread(&val,1,1,fp);//ÿ�δ��ļ��ж�ȡ1���ֽ�
	}
	fclose(fp);
	
}
/*--------------------------------
�Ƴɱ����
-------------------------------*/
infor* codeTable()
{
	infor * informa = (infor *)malloc(length*sizeof(infor));
	int j = 0;//����informa�ļ�����
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
��ȡ�ļ����ݣ�����ת��Ϊ01�ַ���
-------------------------------*/
void To01String()
{
	FILE *fp = fopen(str.c_str(),"rb");
	if(fp ==NULL)
	{
		cout<<"�ļ���ʧ��"<<endl;
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
��01�ַ���ת��Ϊ��������ֽ��ַ���
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
string st = code.substr(code.length()-add0);//��ȥ���ϵ�0
	for(i = 0;i < code.length();i+=8)
	{
		string8 = code.substr(i,8);//ÿ��ȡ8λ
		ch = (char*)string8.c_str();
		sum = 0;
		for(int j = 128;j >= 1;j/=2)
		{
			sum += ((*ch)-48)*j;//�����һ���ֽڶ�Ӧ���ַ�
			++ch;
		}
		//string val(&sum,1);//��charתΪstring
		byteCode+=sum;
	}
}

/*--------------------------------
���ѹ���ļ�
-------------------------------*/
void compress()
{
	//codeTable();
	
	
	StringToCode();
	string strval = str+".pyr";
	FILE *fp = fopen(strval.c_str(),"wb");
	char * content = (char*)byteCode.c_str();
	fwrite(&length,sizeof(int),1,fp);//������Ҫ������ַ�����
	fwrite(codeTable(),sizeof(infor)*length,1,fp);//��������

	fwrite(&add0,sizeof(int),1,fp);//������Ҫ��0�ĸ���
	fwrite(&pagesizecount,sizeof(int),1,fp);//����δ����ǰ�ı������ֽ���
	for(int i = 0;i < byteCode.length();++i)
	{
		fwrite(content,1,1,fp);//�����ı�����
		++content;
	}
	fclose(fp);
	

}
/*--------------------------------
���ı���Ϣ������ת��Ϊ01����,�������ù�������
-------------------------------*/
void readCompressFile()
{
	memset(bytearr,0,sizeof(bytearr));
	FILE *fp = fopen(str.c_str(),"rb");
	if(fp ==NULL)
	{
		cout<<"�ļ���ʧ��"<<endl;
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
		
			string strval(&val,1);//��valתΪstring
			byteCode+=strval;
			fread(&val,1,1,fp);//ÿ�δ��ļ��ж�ȡ1���ֽ�
	
		
	}
	fclose(fp);
	unsigned char * ch = (unsigned char*)byteCode.c_str();
	for(int i = 0;i < byteCode.length();++i)
	{
		for(int pos = 128;pos >= 1;pos/=2)//��һ���ֽڵ�ÿһλȡ��������ַ���
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
��01�������ַ�,��������ļ���
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
		while(countnum < code.length())//��ֹԽ��
		{
			findBytecode(rootNode,&chpos,&countnum,fp);
		}
	}
	else
	{
		for(int i = 0;i < pagesize;++i)
		{
			string strval(&(rootNode->element),1);
			
			if(rootNode->element != '\r')//�ı���ʽ������Զ�ʶ��\n
			{
				fputc(rootNode->element,fp);
				
			}
				page+=strval;
			}
		
	}
	
	if(page.length() == pagesize)//�ж��ļ��Ƿ���
	{
		
		//fputs(page.c_str(),fp);
		cout<<"��ѹ�ɹ���"<<endl;
		fclose(fp);
	}
	else
	{
		cout<<"�ļ��𻵣�"<<endl;
		fclose(fp);
	}
	
}
/*--------------------------------
�������ҵ���֮��Ӧ���ַ�
-------------------------------*/
void findBytecode(HuffNode *root,char** ch,int* countnum,FILE *fp)//����Ĳ���Ϊÿ�εݹ�ĸ��ڵ㣬������01�ַ�����Ϊ01�ַ����ȵļ���������ֹԽ��
{
	
		if(!(root->isLeaf()))//�ݹ鵽�ڲ��ڵ�
		{
			if(**ch == '0')
			{
				
				findBytecode(root->left,&(++(*ch)),&(++(*countnum)),fp);//��������Ϊ��ֹջ���
				
			}
			else
			{
				findBytecode(root->right,&(++(*ch)),&(++(*countnum)),fp);
				
			}
			
		}
		else//�ݹ鵽Ҷ�ڵ�
		{
			string strval(&(root->element),1);
			
				if(root->element != '\r')//�ı���ʽ������Զ�ʶ��\n
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
���ı�
-------------------------------*/
/*--------------------------------
��ȡ���ı��ļ���ͳ�ƴ���
-------------------------------*/
void calcount_exe()
{
	cout<<"������Ҫѹ�����ļ���(��Ӻ�׺,���ļ��������ڿո�)"<<endl;
	cin>>str;
	memset(bytearr,0,sizeof(bytearr));
	FILE *fp = fopen(str.c_str(),"rb");
	if(fp ==NULL)
	{
		cout<<"�ļ���ʧ��"<<endl;
		system("pause");
		exit(1);
	}
	unsigned char val;
	cout<<"����ѹ�������Ժ�......"<<endl;
	fread(&val,1,1,fp);//ÿ�δ��ļ��ж�ȡ1���ֽ�
	while(!feof(fp))
	{
		bytearr[val]++;//����¼��Ŀ��ֵ��1
		fread(&val,1,1,fp);//ÿ�δ��ļ��ж�ȡ1���ֽ�
	}
	fclose(fp);
	
}
/*--------------------------------
��ȡ���ı��ļ����ݣ�����ת��Ϊ01�ַ���
-------------------------------*/
void To01String_exe()
{
	FILE *fp = fopen(str.c_str(),"rb");
	if(fp ==NULL)
	{
		cout<<"�ļ���ʧ��"<<endl;
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
�������ҵ���֮��Ӧ���ֽڣ�������ı��ļ�
-------------------------------*/
void findBytecode_exe(HuffNode *root,char** ch,int* countnum,FILE *fp)//����Ĳ���Ϊÿ�εݹ�ĸ��ڵ㣬������01�ַ�����Ϊ01�ַ����ȵļ���������ֹԽ��
{
	
		if(!(root->isLeaf()))//�ݹ鵽�ڲ��ڵ�
		{
			if(**ch == '0')
			{
				
				findBytecode_exe(root->left,&(++(*ch)),&(++(*countnum)),fp);//��������Ϊ��ֹջ���
				
			}
			else
			{
				findBytecode_exe(root->right,&(++(*ch)),&(++(*countnum)),fp);
				
			}
			
		}
		else//�ݹ鵽Ҷ�ڵ�
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
��01�������ֽڣ����ı�,��������ļ���
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
		while(countnum < code.length())//��ֹԽ��
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
	
	if(page.length() == pagesize)//�ж��ļ��Ƿ���
	{
		
		//fputs(page.c_str(),fp);
		cout<<"��ѹ�ɹ���"<<endl;
		fclose(fp);
	}
	else
	{
		cout<<"�ļ��𻵣�"<<endl;
		fclose(fp);
	}
	
}