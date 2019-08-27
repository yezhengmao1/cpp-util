#include <alogrithm>
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
void SelectSort(std::vector<T> arr) {
    int len = arr.size();
    if(len <= 1)
        return;
    for(int i = 0; i < len - 1; ++i) {
        int min = 0x7FFFFFFF;
        for(int j = i; j < len; ++j) {
            arr[j] < min ? min = arr[j] : ;
        }
        std::swap<arr[i],min>;
    }
}
