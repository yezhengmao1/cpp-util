#include <vector>
#include <algorithm>
/*
 * File:            InsertSort.h
 * Description:     插入排序 
 * Author:          Pipapa
 * Email:           yezhengmaolove@gmail.com
 * Date:            2019-08-27 15:29:50
 * License:         GPL
 * */

/*
 * Function:        InsertSort        
 * Description:     插入排序     
 * Input:     
 *      arr         排序容器
 * Return:    
 *      None
 * Note:
 *      排序容器size <= 1 直接返回
 *      排序容器size > 1,从 i = 1位置向后开始遍历每个元素
 *      对于每个位置元素，从当前位置j  = i向前比较相邻元素
 *          arr[j] 与 arr[j - 1]
 *      如果arr[j] < arr[j - 1] 交换二者的值
 * Sample:  
 *      InsertSort<int>(arr);  
 * */
template<typename T>
void InsertSort(std::vector<T> &arr) {
    int len = arr.size();
    if(len <= 1)
        return;
    for(int i = 1; i < len; ++i) 
        for(int j = i; j > 0; --j) 
            if(arr[j] < arr[j - 1])
                std::swap(arr[j],arr[j - 1]);
}
