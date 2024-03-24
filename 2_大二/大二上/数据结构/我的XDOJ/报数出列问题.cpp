#include <stdlib.h>
#include <stdio.h>

void swap(int K[], int i, int j)
{
    int temp = K[i];
    K[i] = K[j];
    K[j] = temp;
}
void HeapAdjust(int k[], int p, int n)
{
    int i, temp;
    temp = k[p];
    for (i = 2 * p; i <= n; i *= 2)    //��ȥ�����Һ��ӽ��
    {
        //�ҵ��������ӽ��������
        if (i < n && k[i] < k[i + 1])
            i++;
        //���ڵ�ͺ������Ľ����жϣ���������Ϊ����
        if (temp >= k[i])
            break;
        //�����ڵ����ݱ�Ϊ���ģ���ԭ�������ݻ��Ƿ���temp�У�
        k[p] = k[i];    //���Ǻ��ӽ������ݸ������ǻὫ�������ƣ�Ϊ������ĵ��ṩλ��
        p = i;
    }
    //��������forѭ�����ҵ���p�����У����������ĵ㣬���Ǿͼ������ݵ��õ�p,ע�⣺p��ԭ�������Ѿ������ƶ���
    //��û���ҵ��������൱�ڶ���ֵ����
    //����
    k[p] = temp;
}

//�󶥶�����
void HeapSort(int k[], int n)
{
    int i;
    //���Ƚ���������ת��Ϊ�󶥶�
    for (i = n / 2; i > 0; i--)    //ע����������ȫ���������������Ǵ�һ����ǰ���죬���븸�ڵ�
        HeapAdjust(k, i, n);

    //����󶥶��Ѿ�������ɣ�����������Ҫ����ÿ�ν�����Ԫ�ط������
    //Ȼ��ʣ��Ԫ�����¹���󶥶ѣ������Ԫ�ط���ʣ�����
    for (i = n; i > 1; i--)
    {
        swap(k, 1, i);
        HeapAdjust(k, 1, i - 1);
    }
}


int main()
{
    int i;
    int a[11] = { -1, 5, 2, 6, 0, 3, 9, 1, 7, 4, 8 };
    HeapSort(a, 10);

    for (i = 1; i <= 10; i++)
        printf("%d ", a[i]);

    system("pause");
    return 0;
}
