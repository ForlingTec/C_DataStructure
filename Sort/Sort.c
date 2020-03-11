#include <stdio.h>
#include <stdlib.h>

/*
	实现常见排序
	--zjp
	marc07@qq.com
*/

#define MAXSIZE	10
typedef struct
{
	int r[MAXSIZE + 1];	//用于存储要排序的数组，r[0]用作哨兵或临时变量
	int length;			//用于记录顺序表的长度
}SqList;

typedef enum
{
	FALSE = 0,
	TRUE
}Status;

//交换数组前后两个元素
void Swap(SqList *L, int i, int j)
{
	int temp = L->r[i];
	L->r[i] = L->r[j];
	L->r[j] = temp;
}

//打印排序结果
void Print_Result(SqList *L)
{
	printf("sort result: \n");
	for (int i = 1; i <= L->length; i++)
	{
		printf("%d ", L->r[i]);
	}
	printf("\n");
}

/****************************************1、冒泡排序**************************************************/
//冒泡排序算法1--初级冒泡排序
void BubbleSort_1(void)
{
	int i, j;
	SqList L = { { 9999, 9, 1, 5, 8, 3, 7, 2, 4, 6, 10 }, MAXSIZE };//首元素保留使用，不参与排序运算

	for (i = 1; i <= L.length; i++)
	{
		for (j = i + 1; j <= L.length; j++)
		{
			if (L.r[i] > L.r[j])	//升序
			{
				Swap(&L, i, j);
			}
		}
	}

	Print_Result(&L);//打印排序结果
}

//冒泡排序算法2--正宗冒泡排序
void BubbleSort_2(void)
{
	int i, j;
	SqList L = { { 9999, 9, 1, 5, 8, 3, 7, 2, 4, 6, 10 }, MAXSIZE };//首元素保留使用，不参与排序运算

	for (i = 1; i < L.length; i++)
	{
		for (j = L.length - 1; j >= i; j--)
		{
			if (L.r[j] > L.r[j + 1])//冒泡升序
			{
				Swap(&L, j, j+1);
			}
		}
	}

	Print_Result(&L);//打印排序结果
}

//冒泡排序算法2--冒泡优化
//可避免在大部分元素已有序的情况下进行无意义的循环判断
void BubbleSort_2_Improve(void)
{
	int i, j;
	Status flag = TRUE;//添加标记处理
	SqList L = { { 9999, 2, 1, 3, 4, 5, 6, 7, 8, 9, 10 }, MAXSIZE };//首元素保留使用，不参与排序运算
	//注意，上面元素已大部分有序
	for (i = 1; i < L.length && flag; i++)//加入flag
	{
		flag = FALSE;//默认FALSE
		for (j = L.length - 1; j >= i; j--)
		{
			if (L.r[j] > L.r[j+1])
			{
				Swap(&L, j, j+1);
				flag = TRUE; //修改标记，用于指示需要进行下一次循环判断，否则排序完成。
			}
		}
	}

	Print_Result(&L);//打印排序结果
}

/****************************************2、选择排序**************************************************/
void SelectSort(void)
{
	int i, j, min;
	SqList L = { { 9999, 9, 1, 5, 8, 3, 7, 2, 4, 6, 10 }, MAXSIZE };//首元素保留使用，不参与排序运算

	for (i = 1; i < L.length; i++)
	{
		min = i;
		for (j = i + 1; j <= L.length; j++)
		{
			if (L.r[min] > L.r[j])
			{
				min = j;
			}
		}
		if (min != i)
		{
			Swap(&L, i, min);
		}
	}

	Print_Result(&L);//打印排序结果
}

/****************************************3、直接插入排序**************************************************/
void InsertSort(void)
{
	int i, j;
	SqList L = { { 0, 5, 1, 4, 6, 2 }, 5 };//首元素作哨兵，不参与排序运算

	for (i = 2; i <= L.length; i++)
	{
		if (L.r[i] < L.r[i - 1])
		{
			L.r[0] = L.r[i];//哨兵元素，即此处记录为待操作元素
			for (j = i - 1; L.r[j] > L.r[0]; j--)
			{
				L.r[j + 1] = L.r[j];//元素往后移动，腾出位置
			}
			L.r[j + 1] = L.r[0];//找到了合适位置，插入哨兵元素
		}
	}

	Print_Result(&L);//打印排序结果
}

/****************************************4、希尔排序**************************************************/
void ShellSort(void)
{
	int i, j;
	SqList L = { { 0, 9, 1, 5, 8, 3, 7, 2, 4, 6, 10 }, MAXSIZE };//首元素作哨兵，不参与排序运算
	int increment = L.length;
	do
	{
		increment = increment / 3 + 1; //此处自定义增量序列
		for (i = increment + 1; i < L.length; i++)
		{
			if (L.r[i] < L.r[i - increment])
			{
				L.r[0] = L.r[i];
				for (j = i - increment; j > 0 && L.r[j] > L.r[0]; j -= increment)
				{
					L.r[j + increment] = L.r[j];
				}
				L.r[j + increment] = L.r[0];
			}//此处实质为直接插入排序，只不过增量变为increment，而不是1
		}
		printf("对增量为 %d 的序列进行希尔排序\n", increment);
		Print_Result(&L);//打印希尔排序中间过程结果
	} while (increment > 1);//根据增量序列，进行多次直接插入排序
	printf("最终希尔排序结果：\n");
	Print_Result(&L);//打印最终排序结果
}

/****************************************5、堆排序**************************************************/
/* 堆排序过程（以大顶堆为例）
（1）构建一个完全二叉树大顶堆，取出堆顶数字（也就是最大值）；
（2）将剩下的数字重新构建一个大顶堆，再取出堆顶数字（也就是剩下值当中的最大值）；
（3）重复以上过程，直到取完堆中数字，最终得到一个从大到小排列的序列
*/
//构建完全二叉树大顶堆
void HeapAddjust(SqList *L, int s, int m)
{
	int temp, j;
	temp = L->r[s];
	for (j = 2 * s; j <= m; j *= 2)//孩子节点下标以2倍跃进，
	{
		if (j < m && L->r[j] < L->r[j + 1])
		{
			++j;	//沿关键字较大的孩子结点
		}
		if (temp >= L->r[j])
		{
			break;
		}
		L->r[s] = L->r[j];//调换
		s = j; //记录调换位置
	}
	L->r[s] = temp;	//插入
}
//堆排序算法
void HeapSort()
{
	int i;
	SqList L = { { 0, 9, 1, 5, 8, 3, 7, 2, 4, 6, 10 }, MAXSIZE };
	//1、构建大顶堆，从下标为n/2的节点开始
	for (i = L.length / 2; i > 0; i--)
	{
		HeapAddjust(&L, i, L.length);
	}
	//2、获取从大到小的堆顶数字，重新构建大顶堆，最后获取结果序列
	for (i = L.length; i > 1; i--)
	{
		Swap(&L, 1, i);//将堆顶记录和当前未经排序的子序列的最后一个记录交换
		HeapAddjust(&L, 1, i - 1);//将L.r[1...i -1]重新构建为大顶堆，从堆顶开始
	}

	Print_Result(&L);//打印最终排序结果
}

void test_Sort(void)
{
	//1、冒泡排序
	//BubbleSort_1();
	//BubbleSort_2();
	//BubbleSort_2_Improve();

	//2、选择排序
	//SelectSort();

	//3、直接插入排序
	//InsertSort();

	//4、希尔排序
	//ShellSort();

	//5、堆排序
	HeapSort();
}

