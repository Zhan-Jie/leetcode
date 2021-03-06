### 问题描述 ###

给定的非负整数使用字符串*num*来表示 , 从这个整数中移除*k*个数，要求输出的数字最小.

**条件**

- 字符串*num*的长度小于10002并且大于等于*k*.
- 字符串*num*不以数字0开头.

**解题要求**

- 在输出的数字不能以0开头。如果数字前面以0开头，应该去掉开头的0；
- 如果输出字符串是空的，则以“0”代替；

### 解题方法 ###

字符串`num`去掉`k`个数字后，剩下的数字个数设为`n`。为了使得剩下的n个数字组成的数最小，可以依次从字符串`num`中挑选出n个数，从左到右组成这个最小的n位数。由于最小n位数的高位先被挑选出来，所以每次都尝试从`num`中挑选最小的数。

下图表示挑选的过程。`total`表示字符串`num`的长度，`number`字符串表示被挑选出的最小n位数。

![remove k digits](https://raw.githubusercontent.com/Zhan-Jie/images/master/remove-k-digits.PNG)

假设现在已经有i位数被挑选出来，`num`字符串中的`j-1`位置是上一个被挑选出的数字（那么`number[i-1]=num[j-1]`）。那么挑选出下一个数字，只需要从`j`位置开始从后查找出最小的字符，并赋值给`number[i]`就可以。挑选过程中，如果发现`j`位置右边的字符数和`i`位置右边的字符数一样多，就没有必要再往后查了，这时候直接将`j`位置开始的字符序列复制到`i`位置及之后。所以从`j`位置开始查询时，右边应该有一个边界，可以求出这个边界的位置是`k+i`。

所以查找的位置范围可以得出是`[j, k+i]`。
