/*Joao Paquete n89477*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gridsolver.h"

int main() {
    int i, N, M, v1, v2;

    scanf("%d", &N);
    scanf("%d", &M);
    for( i = 0; i++; i<M ) {
        scanf("%d %d", &v1, &v2);
        save_edge( v1, v2 );
    }
    
}

void save_edge( int v1, int v2) {
    //TODO: everything
}