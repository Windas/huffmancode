
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <stdio.h>
#include "Main.h"
//#include <algorithm>
//#include <function>
using namespace std;
int bytearr[256];
int length;//��Ҫ������ַ�����
int painum;//��Ҫ���ѵ�Ԫ�ظ���-1
extern string str;//Ҫѹ�����ļ���
HuffNode ** leafNodeSet;//��Ϊ�洢Ҷ�ڵ�ļ���
void main()
{
    /* LeafNode * f = new LeafNode(2,'z');
	HuffNode* arr[] = {f,new LeafNode(7,'k'),new LeafNode(24,'m'),new LeafNode(32,'c'),new LeafNode(37,'u'),
						new LeafNode(42,'d'),new LeafNode(42,'l'),new LeafNode(120,'e')};//����Ҷ�ڵ�
*/
	

	
	while(1)
	{

	    cout<<"**************************"<<endl;
		cout<<"��������ѡ��ѹ�����ѹ *"<<endl;
		cout<<"1.ѹ��                   *"<<endl;
		cout<<"2.��ѹ                   *"<<endl;
		cout<<"3.�˳�                   *"<<endl;
		cout<<"**************************"<<endl;
		int ch;
		while(!(cin>>ch))
		{
			cin.clear();
			cin.sync();
			break;
		}
		switch(ch)
		{
			case 1:
				{
					while(1)
					{
						cout<<"**************************"<<endl;
						cout<<"��ѡ��ѹ����ԭ�ļ�����   *"<<endl;
						cout<<"1.�ı��ļ�               *"<<endl;
						cout<<"2.ͼƬ����Ƶ�ļ���exe�ļ�*"<<endl;
						cout<<"3.�˳�                   *"<<endl;
						cout<<"**************************"<<endl;
						int ch;
						while(!(cin>>ch))
						{
							cin.clear();
							cin.sync();
							break;
						}	
				
					switch (ch)
					{
					case 1:
						{
							calcount();
							HuffNode* root= buildHuff();
							string strval = "";
							leafNodeSet = (HuffNode **)malloc(length*sizeof(HuffNode*));//���ڴ洢Ҷ�ڵ�ļ���
							encode(root,strval);
							To01String();
							compress();
							cout<<"ѹ���ɹ���"<<endl;
							system("pause");
							return;
						
						}
					case 2:
						{
							calcount_exe();
							HuffNode* root= buildHuff();
							leafNodeSet = (HuffNode **)malloc(length*sizeof(HuffNode*));//���ڴ洢Ҷ�ڵ�ļ���
							string str = "";
							encode(root,str);
							To01String_exe();
							compress();
							cout<<"ѹ���ɹ���"<<endl;
							system("pause");
							return;
						}
					case 3:
						exit(1);
					}
			
				/*	calcount();
					HuffNode* root= buildHuff();
					string str = "";
					encode(root,str);
					To01String();
					compress();
					cout<<"ѹ���ɹ���"<<endl;
					system("pause");
					return;*/
				}
			case 2:
				{
						while(1)
						{	
								cout<<"**************************"<<endl;
								cout<<"��ѡ���ѹ����ļ�����   *"<<endl;
								cout<<"1.�ı��ļ�               *"<<endl;
								cout<<"2.ͼƬ����Ƶ�ļ���exe�ļ�*"<<endl;
								cout<<"3.�˳�                   *"<<endl;
								cout<<"**************************"<<endl;
								int ch;
								while(!(cin>>ch))
								{
									cin.clear();
									cin.sync();
									break;
								}	
							
								switch (ch)
								{
								case 1:
									{
										cout<<"������Ҫ��ѹ���ļ���(��Ӻ�׺,���ļ��������ڿո�)"<<endl;
										cin>>str;
										if(str.length() > 4 &&str.substr(str.length()-4,str.length()) == ".pyr")
										{
											cout<<"���ڽ�ѹ�����Ժ�......"<<endl;
											readCompressFile();
											decompress();
											system("pause");
											return; 
										}
										else
										{
											cout<<"���ļ���ѹ���ļ�\n";
											system("pause");
											return; 
										}
										
									
									}
								case 2:
									{
										cout<<"������Ҫ��ѹ���ļ���(��Ӻ�׺,���ļ��������ڿո�)"<<endl;
										cin>>str;
										if(str.length() > 4 &&str.substr(str.length()-4,str.length()) == ".pyr")
										{
											cout<<"���ڽ�ѹ�����Ժ�......"<<endl;
											readCompressFile();
											decompress_exe();
											system("pause");
											return; 
										}
										else
										{
											cout<<"���ļ���ѹ���ļ�\n";
											system("pause");
											return; 
										}
										
									}
								case 3:
									exit(1);
								}
							}
					}
					
				/*	cout<<"������Ҫ��ѹ���ļ���(��Ӻ�׺)"<<endl;
					cin>>str;
					readCompressFile();
					decompress();
					system("pause");
					return; 
				*/}
			case 3:
				{
					return;
				}
			default:
				{
					cout<<"�������";
					system("cls");
					break;
				}

		}
		
		
	}
	
}