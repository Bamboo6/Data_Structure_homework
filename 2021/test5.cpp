//
// Created by Tou on 2021/12/22.
//

#include <iostream>

using namespace std;

void Merge(int a[],int low,int mid,int high) //
{
    int *tmp=new int[high-low+1];//辅助数组用来合并
    int i=low,j=mid+1,k=0;
    while(i<=mid&&j<=high)
    {
        if(a[i]<a[j])
            tmp[k++]=a[i++];
        if(a[j]<a[i])
            tmp[k++]=a[j++];
    }
    while(i<=mid)
        tmp[k++]=a[i++];
    while(j<=high)
        tmp[k++]=a[j++];
    for(k=0,i=low;i<=high;k++,i++)
        a[i]=tmp[k];
    delete [] tmp;
}

/*
若子表个数为奇数，则最后一个子表无须和其他子表归并（即本趟轮空）；
若子表个数为偶数，则需要注意到最后一个子表的区间上界是n-1
*/
void MergePass(int a[],int len,int n)
{
    int i;
    for(i=0;i+2*len-1<n;i=i+2*len)
        Merge(a,i,i+len-1,i+2*len-1);

    //当只剩下2个表的时候，归并这两个子表
    if(i+len-1<n)
        Merge(a,i,i+len-1,n-1);
}


void MergeSort(int a[],int n)
{
    for(int len=1;len<n;len=2*len)
        MergePass(a,len,n);
}

int main()
{
    int a[]={2,5,1,7,10,6,9,4,3,8};

    cout<<"排序前:";
    for(int i=0;i<10;i++)
        cout<<a[i]<<" ";
    cout<<endl;

    MergeSort(a,10);

    cout<<"排序后:";
    for(int i=0;i<10;i++)
        cout<<a[i]<<" ";
    cout<<endl;

    return 0;
}
