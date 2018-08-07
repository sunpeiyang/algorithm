/*
 *实现排序算法
 *
 * */
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MAXSIZE 20
#if 0
typedef struct
{
    int key;
    string otherInfo;
}RedType;

typedef struct
{
    RedType r[MAXSIZE + 1];
    int length;
}SqList;
#endif 
void printList(vector<int>& L)
{
    for (int i = 0; i < L.size(); i++)
    {
        cout << L[i] << "\t";
    }
    cout << endl;
}


/*
 插入排序
 数组第一个元素为哨兵， 监测对比用， 不作为真实数据。
 每个数跟他前面的数 依次向前比。
 */
void InsertSort(vector<int> &L)
{
    for (int i = 2; i < L.size(); i++)
    {
        if (L[i] < L[i - 1])
        {
            L[0] = L[i];

            int j = i - 1;
            while (L[0] < L[j] && j)
            {
                L[j + 1] = L[j];
                j--;
            }
            j++;
            L[j] = L[0];
            L[0] = 0;
        }
    }

}

/*
 希尔排序  插入排序的变种
    先将整个待排记录序列分割成若干个子序列分别进行直接插入排序，
    待整个序列中的记录基本有序是， 在对全体记录进行移植直接插入排序
 */
typedef  vector<int> vi;
void ShellInsert(vi& L, int delta)
{
    for (int i = delta + 1; i <= L.size() - 1; ++i)
    {
        if (L[i] < L[i - delta])
        {
            L[0] = L[i];
            int j = i;
            while (L[0] < L[j - delta] && j - delta > 0)
            {
                L[j] = L[j - delta];
                j -= delta;
            }
            //j += delta;
            L[j] = L[0];
            L[0] = 0;
        }
    }
    return ;
}

void ShellSort(vi& L, int delta[], int t)
{
    for (int k = 0; k < t; ++k)
    {
        ShellInsert(L, delta[k]);
    }
}

/*
 冒泡排序
 */
void BubbleSort(vi& L)
{
    int l = (int)(L.size());
    for (int i = 0; i < l - 1; i++)
    {
        for (int j = i + 1; j < l; j++)
        {
            if (L[i] > L[j])
            {
                int tmp = L[i];
                L[i] = L[j];
                L[j] = tmp;
            }
        }
    }
    return ;
}

/*
 快速排序 冒泡的变种
    快速排序是对冒泡排序的一种改进， 它的基本思想是，通过一趟排序将待排记录分割成两部分，
    其中一部分记录的关键字比另一部分记录的关键字小， 则可分别对这两部分记录进行排序，以达到整个序列有序。
    
    排序一次分成两部分的过程称为一次快速排序
 */
int Partition(vi& L, int low, int high)
{
    int privot = L[low];
    
    while (low < high)
    {
        while (low < high && L[high] >= privot)
            --high;
        L[low] = L[high]; //swap(L[low], L[high])
        while (low < high && L[low] <= privot)
            ++low;
        L[high] = L[low];//swap(L[low], L[high])
    }
    L[low] = privot;
    return low;
}
void QuickSort(vi& L, int low, int high)
{
    if (low < high)
    {
        int privotloc = Partition(L, low, high);
        QuickSort(L, low, privotloc - 1);
        QuickSort(L, privotloc + 1, high);

    }
}
/*
    选择排序
    每次选出一个最小值
 */
void SelectSort(vi& L)
{
    for (int i = 0; i < (int)(L.size()) - 1; i++)
    {
        int min = L[i];
        int minIndex = i;
        for (int j = i + 1; j < (int)(L.size()); j++)
        {
            if (L[j] < min)
            {
                min = L[j];
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            int t = L[i];
            L[i] = min;
            L[minIndex] = t;
        }
    }
}

/*
    堆排序 选择排序变种
        堆是具有以下性质的完全二叉树：每个结点的值都大于或等于其左右孩子结点的值，称为大顶堆；或者每个结点的值都小于或等于其左右孩子结点的值，称为小顶堆。
    堆排序的基本思想是：将待排序序列构造成一个大顶堆，此时，整个序列的最大值就是堆顶的根节点。将其与末尾元素进行交换，此时末尾就为最大值。然后将剩余n-1个元素重新构造成一个堆，这样会得到n个元素的次小值。如此反复执行，便能得到一个有序序列了
        建堆，筛选
 */
void swap(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
    return;
}
//对于长度为length的数组，对位置i处进行调整，确保i的左右节点都比i小
void HeapAdjuct(vi& L, int i, int length)
{
    int temp = L[i];
    //对i位置的节点的 子节点为 i*2+1, i*2+2
    for (int k = i * 2 + 1; k < length; k = k * 2 + 1)
    {
        if (k + 1 < length && L[k] < L[k + 1])//右子节点大于左子节点，k++ 指向右子节点
        {
            k++;
        }
        if (L[k] > temp)
        {
            L[i] = L[k];
            i = k;
        }
        else
            break;
    }
    L[i] = temp;
    return;
}
void HeapSort(vi& L)
{
    int length = (int)L.size();
    for (int i = length / 2; i >= 0; --i)//从一半除往前调，即可筛选出一个大顶堆
    {
        HeapAdjuct(L, i, length);
        printList(L);
    }
    cout << "大顶堆: "; printList(L);

    for (int i = length - 1; i > 0; --i)
    {
        swap(L[i], L[0]); //将堆顶元素移动 堆的最后，堆的长度-1
   //     printList(L);
        HeapAdjuct(L, 0, i);//重新调整堆顶的位置
    }
}

/*
 归并排序
    归并的含义是将两个或两个以上的有序表组成一个新的有序表
    两两一合 类似一倒置的完全二叉树
 
 */
void Merge(vi& L, vi& T, int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = low;
    
    while (i <= mid) {
        T[i] = L[i];
        ++i;
    }
    i = low;
    while (i <= mid && j <= high)
    {
        if(T[i] <= L[j])
        {
            L[k++] = T[i++];
        }
        else
        {
            L[k++] = L[j++];
        }

    }
    while(i <= mid)
    {
        L[k++] = T[i++]; //将剩余的help[i...mid]复制到list中
    }

}
void MSort(vi& L, vi& T, int low, int high)
{
    if (low < high)
    {
        int mid = (high + low) / 2;
        MSort(L, T, low, mid);
        MSort(L, T, mid + 1, high);
        Merge(L, T, low, mid, high);
    }
}

void MergeSort(vi& L)
{
    int length = (int)L.size();
    vi T(length);
    MSort(L, T, 0, length - 1);
}

int main()
{
    int a[] = {0, 9, 8, 7, 6,1,2,3,4};
    vector<int> L(a, a + 9);
    printList(L);
    //直接插入排序
    //InsertSort(L);
    
    //希尔排序
    //int delta[] = {3,2,1};
    //ShellSort(L, delta, 3);
    
    //冒泡排序
    //BubbleSort(L);
    
    //快速排序
    //QuickSort(L, 0, (int)(L.size()) - 1);
    
    //选择排序
    //SelectSort(L);
    
    //堆排序
    //HeapSort(L);
    
    //归并排序
    MergeSort(L);
    
    printList(L);
    return 0;
}
