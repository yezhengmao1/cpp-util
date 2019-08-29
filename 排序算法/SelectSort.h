#ifndef SELECTSORT_H_
#define SELECTSORT_H_
#include <vector>
#include <algorithm>
/*
 * File:            SelectSort.h
 * Description:     选择排序
 * Author:          Pipapa
 * Email:           yezhengmaolove@gmail.com
 * Date:            2019-08-29 09:33:24
 * License:         GPL
 * */

/*
 * Function:        SelectSort
 * Description:     选择排序
 * Input:     
 *     arr          待排序容器
 *     l            容器左端点，闭区间
 *     r            容器右端点，开区间
 * Return:    
 *     None
 * Note:      
 *     保证arr[l..k)已经是有序数组，且arr[l..k) < arr[k..r]
 *     从arr[k..r]中选择最小数min，令arr[k] = min，即可保证arr[l..k`) < arr[k`..r]
 * Sample:    
 *     SelectSort(arr, 0, arr.size() - 1);
 * */
template<typename T>
void SelectSort(std::vector<T> &arr, int l, int r) {
    for(int i = l; i < r; ++i) {
        int min = i;
        for(int j = i + 1; j <= r; ++j) {
            if(arr[j] < arr[min]) min = j;
        }
        std::swap(arr[i], arr[min]);
    }
}

#endif
