/**
 * @file main.cpp
 * @author YangJinxi (you@domain.com)
 * @brief 计算任意两个日期之间的总天数，考虑大小月，闰年，并检验输入日期是否存在以及先后顺序是否合理
 * @version 0.1
 * @date 2023-08-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>

using namespace std;

int IsLeapYear(int year);
int DaysInMonth(int year, int month);
int ConvertToDays(struct Date release, struct Date current);
int DateCorrectnessCheck(struct Date release, struct Date current);


/**
 * @brief 日期结构体
 * 
 */
typedef struct Date
{
    int year;
    int month;
    int day;
} Date;

// 发布日期
Date release_date = 
{
    .year = 0, 
    .month = 0, 
    .day = 0
};
//当前日期
Date current_date = 
{
    .year = 0, 
    .month = 0, 
    .day = 0
};

int main()
{
    cout << "########################################" << endl;
    cout << "### Input release date:  ";

    // 输入固件发布日期
    cin >> release_date.year >> release_date.month >> release_date.day;

    cout << "### Input current date:  ";
    // 输入当前日期
    cin >> current_date.year >> current_date.month >> current_date.day;
    
    // 数据合法性校验
    if (DateCorrectnessCheck(release_date, current_date) == 1)
    {
        cout << endl << "### Release date: " << release_date.year << "/" << release_date.month << "/" << release_date.day << "/" << endl; 
        cout << "### Current date: " << current_date.year << "/" << current_date.month << "/" << current_date.day << "/" << endl; 

        int total = ConvertToDays(release_date, current_date); // 计算总天数

        cout << endl << "### Total Difference: " << total << endl;
        if (total >= 30) // 判断是否超过30天
        {
            cout << "### Sorry, you must update your firmware" << endl; // 超过三十天提示
            // UpdateFirmwareAuto();
        }
    }
    else
    {
        cout << "Check correctness of INPUT DATE" << endl;
    }

    cout << "########################################" << endl;

}

/**
 * @brief 判断是否是闰年
 * 
 * @param year 
 * @return int 
 */
int IsLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) // 闰年判断条件
    {
        return 1;
    }

    return 0;
}

/**
 * @brief 判断当前月份天数
 * 
 * @param year 
 * @param month 
 * @return int 
 */
int DaysInMonth(int year, int month)
{
    int daysList[] = {0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 默认非闰年
    
    if (month == 2) // 判断当年二月的天数
    {
        if (IsLeapYear(year) == 1) // 是闰年
        {
            // cout << "run!!!" << endl;
            return 29; // 闰年2月有29天
        }
        else // 不是润年
        {
            return 28;
        }
    }

    return daysList[month];
}

/**
 * @brief 计算两个日期相距的总天数
 * 
 * @param release 
 * @param current 
 * @return int 
 */
int ConvertToDays(struct Date release, struct Date current)
{   
    int totalDays = 0; // 总天数，返回值

    if (release.year != current.year) // 两个日期不属于同一年
    {
        // 计算首年
        for (int i = release.month; i <= 12; i++)
        {
            totalDays += DaysInMonth(release.year, i);
        }
        totalDays -= release.day; // 减去起始月份已经过去的天数

        // 计算尾年
        for (int i = 1; i < current.month; i++) // 遍历到当前日期的上一个月
        {
            totalDays += DaysInMonth(current.year, i);
        }

        totalDays += current.day; // 加上当前月份已经过去的天数

        for (int i = ++release.year; i < current.year;i ++) // 如果发布日和当前日期中间有若干年
        {
            if (IsLeapYear(i) == 1)
            {
                totalDays += 366; //闰年 +366
            }
            else
            {
                totalDays += 365;

            }
        }

    }
    else
    {
        //同一年
        for (int i = release.month; i < current.month; i++) 
        {
            totalDays += DaysInMonth(release.year, i);
        }

        totalDays = totalDays + current.day - release.day;
    }

    return totalDays;
}

/**
 * @brief 数据合法性校验，检查日期是否存在，检查两日期先后顺序是否合理
 * 
 * @param release 
 * @param current 
 * @return int 
 */
int DateCorrectnessCheck(struct Date release, struct Date current)
{
    // 时间前后合理性检验
    if (release.year > current.year) //发布年份晚于当前年份
    {
        cout << "Input wrong a" << endl;
        return -1;
    }
    if (release.year == current.year && release.month > current.month) //同一年，发布月份晚于当前月份
    {
        cout << "Input wrong b" << endl;
        return -1;
    }
    if (release.year == current.year && release.month == current.month && release.day > current.day) //同一年，发布日期晚于当前日期
    {
        cout << "Input wrong c" << endl;
        return -1;
    }

    //月份数据合理性建检验
    //只取 1~12 之间的数字
    if (release.month <= 12 && release.month > 0)
    {
        //当月天数合理性检验
        //不得超过当月最大天数
        if (release.day > DaysInMonth(release.year, release.month))
        {
            cout << "Input wrong e" << endl;
            return -1;
        }
        
    }
    else
    {
        cout << "Input wrong d" << endl;
        return -1;
    }

    //月份数据合理性建检验
    if (current.month <= 12 && current.month > 0)
    {
        //当月天数合理性检验
        if (current.day > DaysInMonth(current.year, current.month))
        {
            cout << "Input wrong g" << endl;
            return -1;
        }
        
    }
    else
    {
        cout << "Input wrong f" << endl;
        return -1;
    }

    return 1;

}