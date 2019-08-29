#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_
#include <vector>
#include <algorithm>
/*
 * File:            BubbleSort.h
 * Description:     冒泡排序
 * Author:          Pipapa
 * Email:           yezhengmaolove@gmail.com
 * Date:            2019-08-29 09:27:49
 * License:         GPL
 * */

/*
 * Function:        BubbleSort
 * Description:     冒泡排序
 * Input:     
 *     arr          待排序容器
 *     l            容器左端点，闭区间
 *     r            容器右端点，闭区间
 * Return:    
 *     None
 * Note:      
 *     从r位置的元素开始，将最小的元素交换到l位置
 *     之后l++，即可保证arr[l..l`)元素为有序元素
 * Sample:    
 *     BubbleSort(arr, 0, arr.size() - 1);
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
