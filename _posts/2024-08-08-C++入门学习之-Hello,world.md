---
layout:     post
title:      "C++入门学习之——打印Hello,world"
subtitle:   " \"C++入门训练\""
date:       2024-08-08 14:12:58
author:     "QnGhonu"
header-img: "img/post-bg-2024.jpg"
catalog: true
tags:
    - Knowledge
---

# C++入门题之 "Hello,World!"
### By QnGhonu from <https://www.luogu.com.cn/blog/QnGhonu>.
----------------
每学习一门新语言之后，我们最常做的事情就是打印 "Hello,World!" ，这是一道非常简单的题，在这篇博客中，我将介绍给大家两种解决办法。

## 方法一：
对于C++的输出，可以借助 **流(stream)** 的形式进行**输入**与**输出**。这时，我们应该引入 **iostream** 头文件来使用流。代码如下：
```cpp
#include<iostream>
```
接下来定义**主函数**，主函数是一个程序的**入口**，每个C++程序都从这里开始运行。
```cpp
int main() {
	// 程序从这儿开始执行哦
   
   
	return 0; // 每条语句后都应该使用';'，当前返回值为零，程序结束。
}
```
我们可以使用 **'std::cout'** 向流中输出内容，使用 **'std::endl'** 刷新窗口并**换行**。则打印输出 "Hello,World!" 的代码语句应该这样写：
```cpp
	std::cout << "Hello,World!" << std::endl; // 别忘记"std::"和";"哟
```
### 最终代码：
```cpp
#include <iostream>

int main() {
	
    std::cout << "Hello,World!" << std::endl;
    
    return 0;
    
}
```

## 方法二:
除了使用 **流(stream)** 以外，我们还可以使用C++中的标准输入和输出，使用 **C++标准库** ，使用方式如下：
```cpp
#include<cstdio>
```
接下来还是定义**主函数**，我们的C++程序都从这里开始运行。
```cpp
int main() {
	// 程序从这儿开始执行哦
   
   
	return 0;
}
```
标准库中有输入和输出的 **函数** ，如何使用标准输出呢？C++中的函数可不是数学里的函数。
我们可以使用 `printf();' 来打印字符串到屏幕上。使用方式如下：
```cpp
	printf("Hello,World!"); // 也可以输出别的，""里的内容改下就行
```
### 最终代码：
```cpp
#include <cstdio>

int main() {
	
    printf("Hello,World!\n"); // "\n"是字符串换行的方法
    
    return 0;
    
}
```