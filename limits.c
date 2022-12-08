#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>


int getrlimit(int resource, struct rlimit *rlim);   //man getrlimit

int main() {
    struct rlimit stack_size;
    struct rlimit nu_processes;
    struct rlimit nu_file;

    getrlimit(RLIMIT_STACK,&stack_size);
    getrlimit(RLIMIT_NPROC,&nu_processes);
    getrlimit(RLIMIT_NOFILE,&nu_file);

    printf("Maximum Stack Size: %ld\n",stack_size.rlim_cur);   // "rlim_cur" for the soft limit
    printf("Maximum Number of Processes: %ld\n", nu_processes.rlim_cur);
    printf("Maximum Number of File Descriptors: %ld\n", nu_file.rlim_cur);
    return 0;
}
