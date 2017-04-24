//
//  kmeans.cpp
//  kmeansTest
//
//  Created by Apple on 2017/4/20.
//  Copyright © 2017年 Apple. All rights reserved.
//

#include "kmeans.hpp"


int main(void){
    int n,m,k;
    fin>>n>>m>>k;
    kmeans a(n,m,k);
    for( int i=0; i<n; i++)
        a.in(i);
    a.train();
    a.out();
}
