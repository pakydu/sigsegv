#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int test()
{return 0;}

int add1(int num)
{
    int ret = 0x00;
    int *pTemp = NULL;
    *pTemp = 0x01;
    ret = num + *pTemp;

    return ret;
}

int add(int num)
{
    int ret = 0x00;

    ret = add1(num);

    return ret;
}

