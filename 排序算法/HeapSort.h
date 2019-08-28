#ifndef HEAPSORT_H_
#define HEAPSORT_H_
#include <vector>
#include <algorithm>
/*
 * File:            HeapSort.h
 * Description:     堆排序
 * Author:          Pipapa
 * Email:           yezhengmaolove@gmail.com
 * Date:            2019-08-25 23:31:34
 * License:         GPL
 * */

/*
 * Function:        BuildHeap
 * Description:     建堆
 * Input:       
 *     arr          待建堆容器
 *     root         建堆父节点
 *     l            容器左端点，闭区间
 *     r            容器右端点，开区间
 * Return:    
 *     None
 * Note:      
 *     左儿子为 root*2+1
 *     右儿子为 root*2+2
 *     父节点为 (i+1)/2-1
 * Sample: 
 *     BuildHeap(arr, 0, arr.size() - 1);   
 * */
template<typename T>
void BuildHeap(std::vector<T> &arr, int root, int l, int r) {
    int son = (root-l)*2+1+l;
    while(son <= r) {
        if(son + 1 <= r && arr[son] < arr[son+1]) son++;
        if(arr[root] >= arr[son]) return;
        std::swap(arr[son], arr[root]);
        root = son;
        son = (root-l)*2+1+l;
    }
}

/*
 * Function:        HeapSort
 * Description:     堆排序
 * Input:     
 *     arr          排序容器
 *     l            排序左端点，闭区间
 *     r            排序右端点，闭区间
 * Return:    
 *     None
 * Note:      
 *     节点i的左儿子为2*i+1，右儿子为2*i+2
 *     构建大根堆，即满足对于任意i，arr[i] >= arr[2*i+1] && arr[i] >= arr[2*i+2]
 *     构建小根堆，即满足对于任意i，arr[i] <= arr[2*i+1] && arr[i] <= arr[2*i+2]
 *     初始化堆过程：从最后一个父节点开始构建堆
 *     最后一个父节点为：(r-l+1)/2-1
 *     在区间[L,R]中x的子节点为：l+(x-l)*2+1
 * Sample:    
 *     HeapSort(arr, 0, arr.size() - 1)
 * */
template<typename T>
void HeapSort(std::vector<T> &arr, int l, int r) {
    for(int i = l+(r-l+1)/2-1; i >= l; --i) {
        BuildHeap(arr, i, l, r);
    }
    while(r > l) {
        std::swap(arr[l], arr[r]);
        BuildHeap(arr, l, l, --r);
    }
}
#endif
