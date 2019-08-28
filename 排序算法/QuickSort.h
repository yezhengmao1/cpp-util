#ifndef QUICKSORT_H_
#define QUICKSORT_H_
#include <vector>
#include <algorithm>
/*
 * File:            QuickSort.h
 * Description:     快速排序
 * Author:          Pipapa
 * Email:           yezhengmaolove@gmail.com
 * Date:            2019-08-25 13:24
 * License:         GPL
 * */

/*
 * Function:        QuickSort
 * Description:     快速排序
 * Input:
 *     arr          排序容器
 *     l            容器左端点，闭区间
 *     r            容器右端点，闭区间
 * Return:
 *     None
 * Note:
 *     将arr[l] 作为哨兵点 target = l
 *     维护哨兵点位置target而非哨兵值，节省复制构造函数消耗
 *     每次与arr[target]比较，并维护以下条件:
 *         arr[l..toSwap) < arr[target]
 *     最终达成:
 *         arr[l..target-1] < arr[target] < arr[target+1...r]
 * Sample:
 *         QuickSrot<int>(arr, 0, arr.size() - 1);
 * */
template<typename T>
void QuickSort(std::vector<T> &arr, int l, int r) {
    if(l >= r) return;
    int toSwap = l;
    int target = l;
    for(int i = l + 1; i <= r; ++i) {
        if(arr[i] < arr[target]) {
            std::swap(arr[i], arr[toSwap]);
            if(toSwap == target) {
                target = i;
            }
            toSwap++;
        }
    }
    std::swap(arr[toSwap], arr[target]);
    target = toSwap;
    QuickSort(arr, l, target - 1);
    QuickSort(arr, target + 1, r);
}
#endif
