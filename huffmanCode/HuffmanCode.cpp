#include "HuffmanCode.h"
HuffNode * rootNode;//保存形成的树的根节点
extern string code;//储存文件编码后的字符串
extern string byteCode;//储存01字符串转换的字节字符串
extern int pagesizecount;//作为文本长度计数器，计算读取的文本
extern HuffNode ** leafNodeSet;//作为存储叶节点的集合
int nodecount = 0;//作为叶节点集合遍历的计数器
/*--------------------------------
        构建哈夫曼树
-------------------------------*/
HuffNode* buildHuff()
{
	HuffNode* arr[256];
	int i,j;//i作为bytearr的计数器，j作为arr的计数器
	for(i = 0,j = 0;i < 256;++i)//为文本中出现的字符建立叶节点，并放到数组arr中
	{
		if(bytearr[i] != 0)
		{
			arr[j] = new LeafNode(bytearr[i],(char)i);
			++j;
		}
		else
		{
			continue;
		}
		
	}
	length = j;
	painum = length - 1;
	buildHeap(arr);//建立最小堆,每次去除最小的两个树
	HuffNode *root = arr[0];//用于存储根节点
	while(painum != 0)
	{
		HuffNode *fir = removetop(arr);
		HuffNode *sec = removetop(arr);
		root = (new HuffTree(fir,sec))->root;//两个最小的节点合成一个树，并将头结点放入堆中
		add(arr,root);
	}
	rootNode = root;
	return root;
}
//bool operator>(HuffNode a,HuffNode b)
//{
//	return a.weight > b.weight;
//}

/*--------------------------------
        小顶堆
-------------------------------*/

void buildHeap(HuffNode* arr[] )//传入要建堆的数组
{
	for(int i = painum;i > 0;i-=2)
	{
		int root = (i-1)/2;
		int smallest = root;
		if(arr[smallest]->weight > arr[2*root+1]->weight)//父节点和左子节点比
		{
			smallest = 2*root+1;
		}
		if((2*root+2) <= painum)
		{
			if(arr[smallest]->weight > arr[2*root+2]->weight)
			{
				smallest = 2*root+2;
			}
		}
		if(root != smallest)//父节点不是最小的，交换
		{
			HuffNode * val = arr[root];
			arr[root] = arr[smallest];
			arr[smallest] = val;
		}
		
		
		
	}
	
}
	/*--------------------------------
			取出顶端元素
	-------------------------------*/
HuffNode * removetop(HuffNode *arr[])//传入建好堆的数组
{
	HuffNode * val = arr[0];//将top元素和最后一个元素交换
	arr[0] =arr[painum];
	arr[painum] = val;
	--painum;
	buildHeap(arr);
	return arr[painum+1];
	
}
	/*--------------------------------
			添加元素
	-------------------------------*/
void add(HuffNode *arr[],HuffNode * val)//传入建好堆的数组,要添加的元素
{

	++painum;
	arr[painum] = val;
	buildHeap(arr);
}

/*--------------------------------
        对哈夫曼树进行编码
-------------------------------*/
void encode(HuffNode* root,string zocode)//从根节点开始递归，左为0，右为1
{
	if(root->isLeaf())
	{
		root->code = zocode;
		leafNodeSet[nodecount] = root;
		++nodecount;
		return;
	}
	else
	{
		encode(root->left,zocode+"0");
		encode(root->right,zocode+"1");
		return;
	}
}
/*--------------------------------
       查找编码
-------------------------------*/
void findCode(char ch,HuffNode *root)//char表示要查找的字符，code表示编码
{
	for(nodecount = 0;nodecount < length;++nodecount)
	{
		if(leafNodeSet[nodecount]->element == ch)
		{
			code+=leafNodeSet[nodecount]->code;
			//StringToCode();
			++pagesizecount;
			return;
		}
	}
	
}
