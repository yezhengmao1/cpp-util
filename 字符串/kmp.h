#ifndef KMP_H_
#define KMP_H_
#include <string>
/*
 * File:            kmp.h
 * Description:     字符串Knuth-Morris-Pratt查找算法
 * Author:          Pipapa
 * Email:           yezhengmaolove@gmail.com
 * Date:            2019-08-26 23:19:50
 * License:         GPL
 * */

/*
 * Function:        KMP
 * Description:     字符串匹配算法 - KMP
 * Input:     
 *     src          查找字符串
 *     pattern      匹配字符串
 * Return:    
 *     int          返回第一次匹配到位置，找不到情况返回-1
 * Note:      
 *     当，str[l..r] == pattern[0..q]
 *     str[r+1] != pattern[r+1]时，失去匹配
 *     根据next数组使 str[l`..r] == pattern[0..q`]
 * Sample:    
 *     std::vector<int> ans = KMP("AAAAAA", "A");
 * */

int KMP(std::string &str, std::string &pattern) {
    int len = pattern.length();
    if(len <= 0) return 0;
    // 计算next数组
    int *next = new int[len+2];
    next[0] = next[1] = 0;
    int q = 0;
    for(int i = 1; pattern[i] != '\0'; ++i) {
        while(q > 0 && pattern[q] != pattern[i]) q = next[q];
        if(pattern[q] == pattern[i]) q++;
        next[i+1] = q;
    }
    // 匹配字符串
    q = 0;
    for(int i = 0; str[i] != '\0'; ++i) {
        while(q > 0 && str[i] != pattern[q]) q = next[q];
        if(str[i] == pattern[q]) q++;
        if(q == len) return i - len + 1;
    }
    return -1;
}
#endif
