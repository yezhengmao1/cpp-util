#ifndef INSERTSORT_H_
#define INSERTSORT_H_
#include <vector>
#include <algorithm>
/*
 * File:            InsertSort.h
 * Description:     插入排序
 * Author:          Pipapa
 * Email:           yezhengmaolove@gmail.com
 * Date:            2019-08-27 17:19:04
 * License:         GPL
 * */

/*
 * Function:        InsertSort
 * Description:     插入排序
 * Input:     
 *     arr          待排序容器
 *     l            排序左端点，闭区间
 *     r            排序右端点，闭区间
 * Return:    
 *     None
 * Note:      
 *     假设arr[0..l]是有序数组
 *     将arr[l+1]插入到arr[0..l]中使arr[0..l+1]仍然有序
 * Sample:    
 *     InsertSort(arr, 0, arr.size() - 1);
 * */
template<typename T>
void InsertSort(std::vector<T> &arr, int l, int r) {
    for(int i = 1; i <= r; ++i) {
        for(int j = i - 1; j >= 0 && arr[j] > arr[j+1]; --j) {
            std::swap(arr[j], arr[j+1]);
        }
    }    
}
#endif
