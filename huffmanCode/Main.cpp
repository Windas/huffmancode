
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
int length;//需要编码的字符个数
int painum;//需要建堆的元素个数-1
extern string str;//要压缩的文件名
HuffNode ** leafNodeSet;//作为存储叶节点的集合
void main()
{
    /* LeafNode * f = new LeafNode(2,'z');
	HuffNode* arr[] = {f,new LeafNode(7,'k'),new LeafNode(24,'m'),new LeafNode(32,'c'),new LeafNode(37,'u'),
						new LeafNode(42,'d'),new LeafNode(42,'l'),new LeafNode(120,'e')};//建立叶节点
*/
	

	
	while(1)
	{

	    cout<<"**************************"<<endl;
		cout<<"请输入编号选择压缩或解压 *"<<endl;
		cout<<"1.压缩                   *"<<endl;
		cout<<"2.解压                   *"<<endl;
		cout<<"3.退出                   *"<<endl;
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
						cout<<"请选择压缩的原文件类型   *"<<endl;
						cout<<"1.文本文件               *"<<endl;
						cout<<"2.图片或音频文件或exe文件*"<<endl;
						cout<<"3.退出                   *"<<endl;
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
							leafNodeSet = (HuffNode **)malloc(length*sizeof(HuffNode*));//用于存储叶节点的集合
							encode(root,strval);
							To01String();
							compress();
							cout<<"压缩成功！"<<endl;
							system("pause");
							return;
						
						}
					case 2:
						{
							calcount_exe();
							HuffNode* root= buildHuff();
							leafNodeSet = (HuffNode **)malloc(length*sizeof(HuffNode*));//用于存储叶节点的集合
							string str = "";
							encode(root,str);
							To01String_exe();
							compress();
							cout<<"压缩成功！"<<endl;
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
					cout<<"压缩成功！"<<endl;
					system("pause");
					return;*/
				}
			case 2:
				{
						while(1)
						{	
								cout<<"**************************"<<endl;
								cout<<"请选择解压后的文件类型   *"<<endl;
								cout<<"1.文本文件               *"<<endl;
								cout<<"2.图片或音频文件或exe文件*"<<endl;
								cout<<"3.退出                   *"<<endl;
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
										cout<<"请输入要解压的文件名(须加后缀,且文件名不存在空格)"<<endl;
										cin>>str;
										if(str.length() > 4 &&str.substr(str.length()-4,str.length()) == ".pyr")
										{
											cout<<"正在解压，请稍后......"<<endl;
											readCompressFile();
											decompress();
											system("pause");
											return; 
										}
										else
										{
											cout<<"该文件非压缩文件\n";
											system("pause");
											return; 
										}
										
									
									}
								case 2:
									{
										cout<<"请输入要解压的文件名(须加后缀,且文件名不存在空格)"<<endl;
										cin>>str;
										if(str.length() > 4 &&str.substr(str.length()-4,str.length()) == ".pyr")
										{
											cout<<"正在解压，请稍后......"<<endl;
											readCompressFile();
											decompress_exe();
											system("pause");
											return; 
										}
										else
										{
											cout<<"该文件非压缩文件\n";
											system("pause");
											return; 
										}
										
									}
								case 3:
									exit(1);
								}
							}
					}
					
				/*	cout<<"请输入要解压的文件名(须加后缀)"<<endl;
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
					cout<<"输入错误";
					system("cls");
					break;
				}

		}
		
		
	}
	
}