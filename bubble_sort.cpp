/**
 * ����:ð������
 * @param a:����
 * @param n:����Ĵ�С
 * �߽�����:
 * 1) �ж������Ƿ�������
 * �㷨˼·:
 * 1)��ѭ�� for ��Ҫ n ������ n ��ð��
 * 2)��ѭ��ÿ��ð�ݵıȽϴ�����ÿð�ݱȽϴ����� -1
 * 3)ð���Ż�
 */
var flag = false;
const bubblesort = (a) = >
{
    if (a.length < 1) return;
    for (let i = 0; i < a.length; i++){
		 for (let j = 0; j < a.length - 1 - i; j++){
			if (a[j] >= a[j + 1])
			{
				 let temp = a[j];
				 a[j] = a[j + 1];
				 a[j + 1] = temp;
				 flag = true;
			}
		}
	if (!flag)
	{
		 break;
	}
 }
}