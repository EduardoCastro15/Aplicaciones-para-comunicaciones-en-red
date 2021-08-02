#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    struct timeval start, end;
    long mtime = 0, seconds, useconds;

    gettimeofday(&start, NULL);
    while (mtime<200) {
        gettimeofday(&end, NULL);
        seconds = end.tv_sec -start.tv_sec;    
        useconds = end.tv_usec -start.tv_usec;    
        mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
        printf(" %li ", mtime);
        if(mtime>=200){mtime=0;gettimeofday(&start, NULL);}
    }

    // printf("Elapsed time: %ld milliseconds\n", mtime);

    return 0;
}