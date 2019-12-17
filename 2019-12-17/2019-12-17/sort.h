#pragma once
#include <stdio.h>
//��������
void InsertSort(int *a, int n)
{
	//��������
	//5  2  4  6  1  3
	for (int i = 0; i < n - 1;i++)
		//��������������βǰһ��ֵ��
		//���˳�򲻶ԣ�������˳����ȷ�����޸ġ�
	{
		//a[end+1] ����a[0]---a[end]��������
		int end = i;
		int temp = a[end + 1];
		//���������ֵ
		while (end >= 0)
		{
			if (temp < a[end])
			{
				a[end + 1] = a[end];
				--end;
			}
			else
			{
				//����Ҫ�����ֵ����������ֵ
				//����û�б��������ʱ������ѭ��
				break;
			}
		}
		a[end + 1] = temp;
	}
}

void Swap(int* p1,int* p2)
{
	int x = *p1;
	*p1 = *p2;
	*p2 = x;
}

//ѡ������
void SelectSort(int* a, int n)
{
	//7 4 5 9 8 2 1
	int begin = 0;
	int end = n - 1;
	int min_index, max_index;
	while (begin <= end)
	{
		//��С�����͵�һ�������н�����
		//������ֺ����һ�����н����������Ǹ���
		min_index = max_index = begin;
		for (int i = begin + 1; i <= end; ++i)
		{
			if (a[i] < a[min_index])
			{
				min_index = i;
			}
			if (a[i]>a[max_index])
			{
				max_index = i;
			}
		}
		Swap(&a[begin], &a[min_index]);

		//��Ҫע�����׳�bug�ĵط�
		//����:����� 9 5 7 8 6 1 3 4 2 �����
		//�Ӹ��������
		if (max_index == begin)
			//�����ֵmax�ڿ�ʼλ��ʱ���ͻᱻ��Сֵ�Ȼ��ߣ�
			//��ʱ��Ҫ����maxֵ���±꣬max_index = min_index;
		{
			max_index = min_index;
		}
		Swap(&a[end], &a[max_index]);

		++begin;
		--end;
	}
}

void AdjustDown(int* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
		//�����Ӵ��ڵ���nʱ���Ͳ�������
	{
		if (child + 1 < n &&a[child + 1] > a[child])
			//����Һ��Ӵ���  ��  �Һ��Ӵ�������
		{
			++child;
		}
		//��ʱchildָ����Ǻ����д���Ǹ�

		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//����
void HeapSort(int*a, int n)
{
	//�����
	//2^20=100��2^19=50��2^17=12.5��  ����10������16��17֮��
	//ʹ�ö�����10�������ֻ��Ҫ16��17�Σ���10���֮��Ĳ��ͱȽϴ���
	for (int i = (n - 2) / 2; i >= 0; --i)
		//�ӵ�����һ������ڵ㿪ʼ����
	{
		AdjustDown(a, n, i);
	}
	//ѡ������
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		--end;
	}
}

//ð������
void BubbleSort(int* a, int n)
{
	//��������
	int end = n;
	while (end > 0)
	{
		for (int i = 1; i < end; ++i)
		{
			//��ͷ��ʼǰ���������������бȽϣ�
			//��������ֵ����ǰ���ֵ�����н�������������
			if (a[i - 1]>a[i])
			{
				Swap(&a[i - 1], &a[i]);
			}
		}
		--end;
		//�ȽϽ�����ֵһֱ�ڱ�
	}
}

//��һ
//���ϻ���С����ݹ���п���˼��
//49 38 65 97 76 13 27 49
//���ұ�ֵΪkey���ȶ���ߣ������key���ȶ��ұ�
//���ұ�ֵΪkey�����ֵͣ��ͣ�ڱ�key�ġ�ֵ������û�����⣻����֮����ͣ��С��ֵ�ϣ�����������
//�ȶ��Ǳ߾��������ֵ�����������

//��һ������49   38  27 13  49  97  65  76
//�ڶ�������49   38  27 13  49  65  76  97
int PartSort1(int *a, int left, int right)
{
	int key = a[right];
	int keyindex = right;
	while (left < right)
	{
		//left�ұ�key���ֵ��right�ұ�keyС��ֵ
		while (left<right && a[left] <= key)
		{
			++left;
		}

		while (left<right && a[right] >= key)
		{
			--right;
		}
		if (left < right)
		{
			Swap(&a[left], &a[right]);
			++left;//left�Ҵ�
			--right;//right��С
		}
	}
	Swap(&a[left], &a[keyindex]);
	return left;
}
  
//�������ڿӷ�
int PartSort2(int *a, int left, int right)
{
	int key = a[right];
	while (left < right)
	{
		//����Ҵ󣬷ŵ��ұߵĿ�
		while (left < right && a[left] <= key)
		{
			++left;
		}
		a[right] = a[left];
		//�ұ���С���ŵ���ߵĿ�
		while (left < right && a[right] >= key)
		{
			--right;
		}
		a[left] = a[right];
	}
	a[left] = key;
	return left;
}

//����:����ȡ�з�
int GetMidIndex(int* a, int left, int right)
{
	int mid = left + (right - left) / 2;
	if (a[left] < a[mid])
	{
		if (a[mid] < a[right])
			return mid;
		else if (a[left]>a[right])
			return left;
		else
			return right;
	}
	else //a[left] > a[mid]
	{
		if (a[mid] > a[right])
			return mid;
		else if (a[left] < a[right])
			return left;
		else
			return right;
	}
}

int PartSort3(int *a, int left, int right)
{
	int mid = GetMidIndex(a, left, right);
	Swap(&a[mid], &a[right]);
	int key = a[right];
	while (left < right)
	{
		//����Ҵ󣬷ŵ��ұߵĿ�
		while (left < right && a[left] <= key)
		{
			++left;
		}
		a[right] = a[left];
		//�ұ���С���ŵ���ߵĿ�
		while (left < right && a[right] >= key)
		{
			--right;
		}
		a[left] = a[right];
	}
	a[left] = key;
	return left;
}

//���ŵ���ʱ�临�Ӷȣ�O��N��
//���ŵ�ʱ�临�Ӷȣ�N*logn
//���㷽����N���ڵ㣬�������߶�(�ݹ����)Ϊlog n.
void QuickSort(int*a, int left,int right)
{
	if (left >= right)
	{
		return;
	}
	if (right - left+1 > 10)
	{
		//����10��ʱ��ѡ�񣬵ݹ�������
		int keyindex = PartSort3(a, left, right);
		//[left, keyindex-1] key [keyindex+1, right]
		QuickSort(a, left, keyindex - 1);
		QuickSort(a, keyindex + 1, right);
	}
	else
	{
		//�Ż�׼��С���䲻�õݹ鷽����⣬ѡ�ò��뷽�����Ч��
		InsertSort(a+left,right-left+1);
	}
}

void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void TestInsertSort()
{
	int a[] = {2,5,1,8,6,9,3,4,7};
	InsertSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}

void TestSelectSort()
{
	int a[] = { 9,5,7,8,6,1,3,4,2};
	SelectSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}

void TestHeapSort()
{
	int a[] = { 9, 5, 7, 8, 6, 1, 3, 4, 2 };
	HeapSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}

void TestQuickSort()
{
	int a[] = { 9, 5, 7, 8, 6, 1, 3, 4, 2 };
	QuickSort(a, 0, sizeof(a) / sizeof(int)-1);
	PrintArray(a, sizeof(a) / sizeof(int));
}