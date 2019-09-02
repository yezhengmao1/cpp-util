#ifndef MANACHAER_H_
#define MANACHAER_H_
#include <vector>
#include <string>
#include <algorithm>
/*
 * File:            Manacher.h
 * Description:     Manacher - 最长回文算法
 * Author:          Pipapa
 * Email:           yezhengmaolove@gmail.com
 * Date:            2019-08-29 14:55:48
 * License:         GPL
 * */

/*
 * Function:        Manacher
 * Description:     Manacher - 最长回文算法
 * Input:     
 *     str          求最长回文字符串
 * Return:    
 *     uint32_t     最长回文长度
 * Note:      
 *     对于第i位置的字符求其所在回文字符串的长度：
 *     假设pos位置的字符所形成的回文字符串最右字符下标为maxRight
 *     对于i位置的字符其关于pos对称的字符为2*pos-i
 *     第i位置初始所在最长回文长度即为min(maxRight-i, dis[2*pos-i])
 * Sample:    
 *     uint32_t size = Manacher("abccba");
 * */
uint32_t Manacher(const std::string& str) {
    const char split = '#';
    int len = str.length();
    if(len == 0) return 0;
    std::string s(2*len+1, '\0');
    std::vector<int> dis(2*len+1, 0);
    len = 0;
    for(int i = 0; str[i]!='\0'; ++i) {
        s[len++] = split; 
        s[len++] = str[i];
    }
    s[len++] = split;
    s[len] = '\0';
    int pos = 0, ret = 1, maxRight = -1;
    for(int i = 0; i < len; ++i) {
        if(maxRight > i) dis[i] = std::min(maxRight-i, dis[2*pos-i]);
        else dis[i] = 1;
        while(i - dis[i] >= 0 && i + dis[i] < len && s[i+dis[i]] == s[i-dis[i]]) dis[i]++;
        if(i + dis[i] > maxRight) {
            maxRight = i + dis[i];
            pos = i;
        }
        ret = std::max(ret, dis[i]-1);
    }
    return ret;
}
#endif
