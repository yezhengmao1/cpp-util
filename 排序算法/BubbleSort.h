#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_
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
void BubbleSort(std::vector<T> &arr, int l, int r) {
    for(int i = l; i < r; ++i) {
        for(int j = r; j > i; --j) {
            if(arr[j] < arr[j-1]) std::swap(arr[j], arr[j-1]);
        }
    }
}
#endif
