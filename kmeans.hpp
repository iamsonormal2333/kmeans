//
//  kmeans.hpp
//  kmeansTest
//
//  Created by Apple on 2017/4/20.
//  Copyright © 2017年 Apple. All rights reserved.
//

#ifndef kmeans_hpp
#define kmeans_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

std::ifstream fin("kmeans.in");
std::ofstream fout("kmeans.out");

//实际上实现的是kmeans++算法
using std::vector;

class kmeans {
public:
    int n,m,k;
    vector< vector< float>> s;
    vector< vector< float>> res;
    kmeans(int n1,int m1,int k1) : n(n1),m(m1),k(k1){
        ;
    }
    void train();
    void out();
    void in(int i);
    //s为特征集，n为点个数，m为特征个数，k为聚类个数
private:
    static const int maxn = 50;
    static const int maxfloat = 2000000000.0;
    float dis[maxn];
    int belongs[maxn];
    void buildCenter();
    bool updateCenter();
    float distance(float p,float q);
};

void kmeans::in(int i) {
    for( int j=0; j<n; j++)
        fin>>s[i][j];
}

void kmeans::out() {
    for( int i=0; i<k; i++) {
        for( int j=0; j<m; j++)
            fout<<res[i][j]<<" ";
        fout<<std::endl;
    }
}

void kmeans::buildCenter() {
    int newCenter = rand()%n;
    int i = k, j, p, q = 0;
    float sum, newPlace;
    while(i--) {
        for( j=0; j<m; j++)
            res[q][j] = s[newCenter][j];
        q++;
        sum = 0;
        for( j=0; j<n; j++) {
            dis[j] = 0;
            for( p=0; p<m; p++)
                dis[j] += distance(s[j][p],s[newCenter][p]);
            dis[j] = sqrtf(dis[j]);
            sum += dis[j];
        }
        j = 0;
        newPlace = rand()%((int)sum);
        while(newPlace>0)
            newPlace -= dis[j++];
        newCenter = j-1;
    }
}

bool kmeans::updateCenter() {
    int i, j, q;
    float min,preRes;
    int p;
    bool flag = true;
    for( i=0; i<n; i++) {
        min = maxfloat;
        for( j=0; j<k; j++) {
            preRes = 0.0;
            for( q=0; q<m; q++)
                preRes += distance(res[j][q], s[i][q]);
            if(preRes < min) {
                min = preRes;
                p = j;
            }
        }
        if(j!=belongs[i]) {
            belongs[i] = j;
            flag = false;
        }
    }
    return flag;
}

void kmeans::train() {
    vector< vector< float>> center(k,vector< float>(m));
    int centerNum[k];
    buildCenter();
    while(updateCenter()) {
        for( int i=0; i<k; i++)
            centerNum[i] = 0;
        for( int i=0; i<k; i++)
            for( int j=0; j<m; j++)
                center[i][j] = 0.0;
        for( int i=0; i<n; i++) {
            for( int j=0; j<m; j++)
                center[belongs[i]][j] += s[i][j];
            centerNum[belongs[i]]++;
        }
        for( int i=0; i<k; i++)
            for( int j=0; j<m; j++)
                res[i][j] = center[i][j]/centerNum[i];
    }
}

float kmeans::distance(float p,float q) {
    return fabsf(p*p-q*q);
}




#endif /* kmeans_hpp */
