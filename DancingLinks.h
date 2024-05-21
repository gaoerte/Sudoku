//
// Created by sanshuifengyu on 2024/5/20.
//

#ifndef SUDOKU_DANCINGLINKS_H
#define SUDOKU_DANCINGLINKS_H

#include <iostream>
#include <array>
#include <random>
#include<cstring>
#include<algorithm>
using namespace std;

array<array<int,9>,9> sudoku;
#define mx 400000//其实不用这么大只要大于729*324即可

struct DLX{
    int n,m,cnt;//矩阵的长，宽，点的数量
    int l[mx],r[mx],u[mx],d[mx],row[mx],col[mx];//每个点的左，右，上下，行，列信息
    int h[mx];//每行的头结点
    int s[mx];//每列的结点数
    int ansk[mx];//ansk[] 装答案（选了哪几行）
    void init(int _n,int _m){
        n=_n,m=_m;
        int i;
        for(i=0;i<=m;i++){
            r[i]=i+1;l[i]=i-1;u[i]=d[i]=i;
        }
        r[m]=0;//m右边是0
        l[0]=m;//0左边是m
        memset(h,-1,sizeof(h));
        memset(s,0,sizeof(s));
        cnt=m+1;//开始时有m个结点（0结点和各列头结点）
    }//初始化，生成每列的头
    void link(int R,int C){
        s[C]++;
        row[cnt]=R;
        col[cnt]=C;
        u[cnt]=C;
        d[cnt]=d[C];
        u[d[C]]=cnt;
        d[C]=cnt;
        if(h[R]<0)h[R]=r[cnt]=l[cnt]=cnt;//该行没有别的点,把第一个加入的点作为该行的行头结点
        else{
            r[cnt]=h[R];
            l[cnt]=l[h[R]];
            r[l[h[R]]]=cnt;
            l[h[R]]=cnt;
        }
        cnt++;
    }//在r行c列插入点
    void remove(int c){
        r[l[c]]=r[c],l[r[c]]=l[c];
        for(int i=d[c];i!=c;i=d[i]){
            for(int j=r[i];j!=i;j=r[j]){
                u[d[j]]=u[j];
                d[u[j]]=d[j];
                s[col[j]]--;
            }
        }
    }//删除c列和c列上有点的行
    void resume(int c){
        for(int i=u[c];i!=c;i=u[i]){
            for(int j=l[i];j!=i;j=l[j]){
                u[d[j]]=j;
                d[u[j]]=j;
                s[col[j]]++;
            }
        }
        r[l[c]]=c;
        l[r[c]]=c;
    }//恢复c列和c列上有点的行
    bool dance(int deep){
        if(r[0]==0){
            int x,y,v;
            for(int i=0;i<deep;i++){
                x=(ansk[i]-1)/9/9;
                y=(ansk[i]-1)/9%9;
                v=(ansk[i])%9;//把行信息转换成对应的点的值
                if(v==0)v=9;//防止9的倍数%9==0
                sudoku[x][y]=v;
            }
            return true;//只要找一组解
        }
        int c=r[0];
        for(int i=r[0];i!=0;i=r[i])if(s[i]<s[c])c=i;//找到点最少的列
        remove(c);
        for(int i=d[c];i!=c;i=d[i]){
            ansk[deep]=row[i];
            for(int j=r[i];j!=i;j=r[j]) remove(col[j]);
            if(dance(deep+1)==1)return true;//只要找一组解
            for(int j=l[i];j!=i;j=l[j]) resume(col[j]);
        }
        resume(c);
        return false;
    }
}dlx;


void SolveByDLXRandom(){
    array<int, 9> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    random_device rd;
    mt19937 g(rd());
    shuffle(numbers.begin(), numbers.end(), g);

    dlx.init(729,324);
    //729:
    //9^4种情况对应9^4行;
    //324:
    //对应数独的规则:每个格子，每行，每列，每个九宫只能填1~9各一次
    //对于第m列：
    //若m在[1,81]表示在(m/9，m%9)填数
    //若m在[81*1,81*2]在第1+（m-81）/9行填1+（m-81）%9
    //若m在[81*2,81*3]在第1+（m-81*2）/9列填1+（m-81*2）%9
    //若m在[81*3,81*4]在第1+（m-81*3）/9宫填1+（m-81*3）%9
    int x;
    int o;
    for(int i=0;i<=8;i++){
        for(int j=0;j<=8;j++){
            x = sudoku[i][j];
            for(auto k:numbers){
                if(x!=k&&x!=0)continue;//已经填好的点就不用考虑了
                o=i*9*9+j*9+k;
                dlx.link(o,i*9+j+1);
                dlx.link(o,i*9+81+k);
                dlx.link(o,j*9+81*2+k);
                dlx.link(o,81*3+(i/3*3+j/3)*9+k);//把点对应成行（集合）
            }
        }
    }
    dlx.dance(0);
}

void CreateASudoku() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib1(1, 9);
    uniform_int_distribution<> distrib2(81 - 60, 81 - 5);
    int x, y;
    SolveByDLXRandom();
    int lim = distrib2(gen);
    cout << "Sudoku with " << lim << " missing values" << endl;
    for (int i = 0; i < lim; ++i) {
        x = distrib1(gen) - 1;
        y = distrib1(gen) - 1;
        if (sudoku[x][y]) {
            sudoku[x][y] = 0;
        }
        else {
            --i;
            continue;
        }
    }
}

void displayBoard() {
    for (int i = 0; i < 9; ++i) {
        if (!(i % 3)) cout << "-----------------------------------" << endl;
        for (int j = 0; j < 9; ++j) {
            if (!(j % 3)) cout << "| ";
            if(sudoku[i][j] == 0) cout << "_" << "  ";
            else cout << sudoku[i][j] << "  ";
        }
        cout << " |" << endl;
    }
    cout << "-----------------------------------" << endl;
    //cout << "b" << endl;
}
#endif //SUDOKU_DANCINGLINKS_H
