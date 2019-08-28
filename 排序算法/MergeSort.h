#ifndef MERGESORT_H_
#define MERGESORT_H_
#include <vector>
#include <algorithm>
/*
 * File:            SelectSort.h
 * Description:     
 * Author:          Pipapa
 * Email:           yezhengmaolove@gmail.com
 * Date:            2019-08-27 15:49:55
 * License:         GPL
 * */

/*
 * Function:        SelectSort
 * Description:     选择排序
 * Input:     
 *      arr         排序容器
 * Return:    
 *      None
 * Note:    
 *      排序容器size <= 1 直接返回
 *      排序容器size > 1,从i = 0位置开始遍历
 *      对于每个位置寻找此位置之后的最小值 min
 *      交换 arr[i] 与 min  
 * Sample:    
 *      SelectSort<int>(arr);
 * */
template<typename T>
void Merge(std::vector<T> &arr, int l, int mid, int r) {
    for(int i = l, j = mid + 1; i <= mid && j <= r; ++i) {
        if(arr[i] > arr[j]) {
            std::swap(arr[i], arr[j]);
            for(int k = j; k < r; ++k) {
                if(arr[k] > arr[k+1]) std::swap(arr[k], arr[k+1]);
            }
        }
    }
}

template<typename T>
void MergeSort(std::vector<T> &arr, int l, int r) {
    if(l < r) {
        int mid = (l + r) / 2;
        MergeSort(arr, l, mid);
        MergeSort(arr, mid  + 1, r);
        Merge(arr, l, mid, r);
    }
}
#endif
