/*
.so文件生成：
g++ -fPIC -shared -o libmathlib52.so mathlib52.cpp
*/
#ifndef _MATHLIB_H
#define _MATHLIB_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define __stdcall

extern "C" 
{
int brinv(double *a,int n);//实矩阵求逆的全选主元高斯约当法
/* 返回值：
      0: delta=0，有3个实根，其中y_2和y_3是重根
      1: delta>0 && delta2>=0||delta<0，有3个相异实根
      2: delta>0 && delta2<0，1实2虚  
*/
int Cardano(double a,double b,double c,double d,double *y);//计算实系数一元三次方程ax^3+bx^2+cx+d=0的3个复根
int poly3(double *mtx3,double *abcd);//计算三阶方阵的特征多项式,返回值0表示是对称矩阵，1表示不是对称矩阵
int chhqr(double *a,int n,double *u,double *v,double eps,int jt);//求赫申伯格矩阵全部特征值的QR方法
int dqrrt(double a[],int n,double xr[],double xi[],double eps,int jt);//求实系数代数方程全部根的QR方法
};

#endif