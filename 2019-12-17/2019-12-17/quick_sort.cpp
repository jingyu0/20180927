#include<stdlib.h>
#include <stdio.h>

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

void QuickSort(int*a, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	if (right - left + 1 > 10)
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
		InsertSort(a + left, right - left + 1);
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

void TestQuickSort()
{
	int a[] = { 9, 5, 7, 8, 6, 1, 3, 4, 2 };
	QuickSort(a, 0, sizeof(a) / sizeof(int)-1);
	PrintArray(a, sizeof(a) / sizeof(int));
}

int main()
{
	TestQuickSort();
	system("pause");
	return 0;
}