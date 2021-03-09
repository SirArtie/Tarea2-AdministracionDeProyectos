#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define T 500

int i,j,k,a[T][T],b[T][T],cP[T][T],cS[T][T],num;

int main(){
    for(i=0;i<T;i++){
        for(j=0;j<T;j++){
            num = rand() % 100;
            a[i][j] = num;
            num = rand() % 100;
            b[i][j] = num;
        }
    }

    int NRA = T, NCB = T, NCA = T;

    multiSerial(NRA, NCB, NCA);
    multiParallel(NRA, NCB, NCA);

    return 0;
}

void multiParallel(int NRA, int NCB, int NCA){
    clock_t startP = clock();
    #pragma omp parallel for private (j,k)
    for (i=0;i<NRA;i++){
        for (j=0;j<NCB;j++)
            for (k=0;k<NCA;k++)
                cP[i][j]+=a[i][k]*b[k][j];
    }
    printf("Tiempo en paralelo: %f segundos\n",((double)clock() - startP) / CLOCKS_PER_SEC);
}

void multiSerial(int NRA, int NCB, int NCA){
    clock_t startN = clock();
    for(i=0;i<NRA;i++){
        for(j=0;j<NCB;j++)
            for(k=0;k<NCA;k++)
                cS[i][j]+=a[i][k]*b[k][j];
    }
    printf("Tiempo en serie: %f segundos\n",((double)clock() - startN) / CLOCKS_PER_SEC);
}
