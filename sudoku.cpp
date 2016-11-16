#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
typedef int strType[9];
typedef strType sudoku[9];
bool boolChange;
sudoku numbers;
int myindex;
int countNumbers;
void getCoord (int *i, int *k, int hvb)
{
    int a, b;
    switch (hvb)
    {
    case 1:
        a=*k;
        *k=*i;
        *i=a;
        break;
    case 2:
        a=*i;
        b=*k;
        *i=(a/3) *3 + (b/3);
        *k=(a%3) *3 + (b%3);
        break;
    default:
        break;
    }
}
bool getPermission(int num,int i,int k,int hvb)
{
    getCoord(&i,&k,hvb);
    if(numbers[i][k]==(num&(1<<15)))
    {
        return(true);
    }
    else
    {
        if(((numbers[i][k]&(1<<15))==0)&&((numbers[i][k]&(1<<num))==0))
        {
            return(true);
        }
        else
        {
            return(false);
        }
    }
}
int getNum(int i,int k,int hvb)
{
    getCoord(&i,&k,hvb);
    return(numbers[i][k]);
}
bool getPermission2(int num,int i,int k,int hvb)
{
    int a=getNum(i,k,hvb);
    if(!(a&(1<<15)))
    {
        return(!(a&(1<<num)));
    }
    else
    {
        return(false);
    }
}
void setPermission (int num, int i, int k, int hvb)
{
    getCoord (&i, &k, hvb);
    if((numbers[i][k]&(1<<15))==0)
    {
        if(getPermission(num,i,k,0))
        {
            numbers[i][k]=numbers[i][k]|(1<<num);
            boolChange=true;
        }
    }
    else if(numbers[i][k]==(num|(1<<15)))
    {
        printf("Error\n");
        exit(1);
    }
}
void setNum(int num,int i,int k,int hvb)
{
    int l;
    getCoord(&i,&k,hvb);
    int blockNumK,blockNumI;
    blockNumK=(i%3)*3+(k%3);
    blockNumI=(i/3)*3+(k/3);
    for(l=0; l<9; l++)
    {
        if(k!=l)
        {
            setPermission(num,i,l,0);
        }
        if(i!=l)
        {
            setPermission(num,l,k,0);
        }
        if(l!=blockNumK)
        {
            setPermission(num,blockNumI,l,2);
        }
    }
    if(getPermission(num,i,k,0))
    {
        if(numbers[i][k]!=(num|(1<<15)))
        {
            boolChange=true;
            countNumbers++;
            numbers[i][k]=(num|(1<<15));
        }
    }
    else
    {
        printf("Error\n");
        exit(1);
    }
}
void tree(void)
{
    strType str;
    int num,noZeroNum[8],trees[8],i,k,n,a,b,countTrees,count=0,countBits,allBits,hvb;
    bool boolResult;
    for(hvb=0; hvb<3; hvb++)
    {
        for(i=0; i<9; i++)
        {
            for(k=0; k<9; k++)
            {
                for(n=0; n<9; n++)
                {
                    num=getNum(i,k,hvb);
                    if((num&(1<<15)==0)&&(getPermission(n,i,k,hvb)))
                    {
                        str[n]=str[n]|(1<<k);
                    }
                    else
                    {
                        str[n]=str[n]&((1<<9)-1-(1<<k));
                    }
                }
            }
            for(k=0; k<9; k++)
            {
                if((str[k])&&(((1<<9)-1)!=0))
                {
                    noZeroNum[count++]=k;
                }
            }
            if(count!=0)
            {
                countTrees=1;
                trees[0]=0;
                while(countTrees!=0)
                {
                    allBits=0;
                    countBits=0;
                    for(k=0; k<countTrees; k++)
                    {
                        allBits=allBits|str[noZeroNum[trees[k]]];
                    }
                    for(k=0; k<9; k++)
                    {
                        if((allBits&(1<<k))!=0)
                        {
                            countBits++;
                        }
                    }
                    if(countBits==countTrees)
                    {
                        a=0;
                        b=0;
                        for(k=0; k<count; k++)
                        {
                            if(noZeroNum[k]==noZeroNum[trees[a]])
                            {
                                noZeroNum[b]=noZeroNum[k];
                                b++;
                            }
                            else
                            {
                                k--;
                                a++;
                            }
                        }
                        count=b;
                        for(k=0; k<count; k++)
                        {
                            for(n=0; n<9; n++)
                            {
                                if((allBits&(1<<n))!=0)
                                {
                                    setPermission(noZeroNum[k],i,n,hvb);
                                }
                            }
                        }
                        trees[0]=0;
                        countTrees=1;
                    }
                    else
                    {
                        boolResult=true;
                        while(boolResult)
                        {
                            if(trees[countTrees-1]<(count-2))
                            {
                                trees[countTrees-1]++;
                                boolResult=false;
                            }
                            else
                            {
                                countTrees--;
                            }
                            if(countTrees==0)
                            {
                                boolResult=false;
                            }
                        }
                    }
                }
            }
        }
    }
}
void zeroNum()
{
    int i,k;
    for(i=0; i<9; i++)
    {
        for(k=0; k<9; k++)
        {
            numbers[i][k]=0;
        }
    }
}
void start()
{
    char i,k,l,num,mycount,hvb,countBlockStr,countStlb,numBlockStr,numStlb,lastI,lastK,firstStr,firstStlb;
    boolChange=true;
    while(boolChange)
    {
        while(boolChange)
        {
            printf("start %d\n",myindex);
	    myindex++;
            boolChange=false;
            for(hvb=0; hvb<3; hvb++)
            {
                for(i=0; i<9; i++)
                {
                    for(num=0; num<9; num++)
                    {
                        mycount=0;
                        countBlockStr=0;
                        countStlb=0;
                        for(k=0; k<9; k++)
                        {
                            if(getNum(i,k,hvb)==((1<<9)-1-(1<<num)))
                            {
                                setNum(num,i,k,hvb);
                                k=8;
				mycount=0;
                            }
                            if(getPermission2(num,i,k,hvb))
                            {
                                mycount++;
                                lastI=i;
                                lastK=k;
                                if(countBlockStr==0)
                                {
                                    numBlockStr=k/3;
                                    countBlockStr++;
                                }
                                else if(numBlockStr!=(k/3))
                                {
                                    countBlockStr++;
                                }
                                if(countStlb==0)
                                {
                                    numStlb=k%3;
                                    countStlb++;
                                }
                                else if(numStlb!=(k%3))
                                {
                                    countStlb++;
                                }
                            }
                        }
                        if(mycount==1)
                        {
                            setNum(num,lastI,lastK,hvb);
                            mycount=0;
                        }
                        else if(mycount!=0)
                        {
                            if(countBlockStr==1)
                            {
                                firstStr=(i/3)*3;
                                for(k=0; k<3; k++)
                                {
                                    if(k!=(i%3))
                                    {
                                        for(l=0; l<3; l++)
                                        {
                                            setPermission(num,firstStr+k,l+numBlockStr*3,hvb);
                                        }
                                    }
                                }
                            }
                            if(hvb==2)
                            {
                                if(countStlb==1)
                                {
                                    firstStlb=i%3;
                                    for(k=0; k<3; k++)
                                    {
                                        if(k!=(i/3))
                                        {
                                            for(l=0; l<3; l++)
                                            {
                                                setPermission(num,k*3+firstStlb,numStlb+l*3,hvb);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if(countNumbers<81)
        {
            printf("tree\n");
        }
    }
}
void ioNum(bool thread)
{
    char i,k;
    for(i=0; i<9; i++)
    {
        if(thread)
        {
            for(k=0; k<9; k++)
            {
                if(!(numbers[i][k]&(1<<15)))
                {
                    printf("%d",0);
                }
                else
                {
                    printf("%d",numbers[i][k]-(1<<15)+1);
                }
                if((k%3)==2)
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
        else
        {
            char a[10];
            cin>>a;
            if(strlen(a)!=9)
            {
                printf("Error\n");
                i--;
            }
            else
            {
                for(k=0; k<9; k++)
                {
                    if(a[k]!=48)
                    {
                        setNum(a[k]-49,i,k,0);
                    }
                }
            }
        }
        if((i%3)==2)
        {
            printf("\n");
        }
    }
}
int main()
{
    zeroNum();
    ioNum(false);
    start();
    printf("\n");
    ioNum(true);
}
