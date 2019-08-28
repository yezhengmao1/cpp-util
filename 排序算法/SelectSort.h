#ifndef SELECTSORT_H_
#define SELECTSORT_H_
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
