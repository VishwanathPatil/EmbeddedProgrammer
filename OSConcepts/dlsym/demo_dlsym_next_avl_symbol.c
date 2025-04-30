#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

#define MALLOC   malloc
#define CALLOC   calloc
#define REALLOC  realloc
#define FREE     free

#define xstr(s) str(s)
#define str(s) #s

static void* (*real_malloc)(size_t)=NULL;
static void* (*real_calloc)(size_t, size_t)=NULL;
static void* (*real_realloc)(void*, size_t)=NULL;
static void (*real_free)(void *)=NULL;
FILE *info_file;
int my_alloc_count = 0;

//global variable for initial calloc called
char my_var[100000];
int index;

static inline void backtrace_details (void)
{
    void *array[10];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace (array, 10);
    strings = backtrace_symbols (array, size);

    for (i = 0; i < size; i++)
        fprintf (info_file,"%s\n", strings[i]);

    free (strings);
}

static void my_alloc_init(void)
{
    char *filename = getenv("MY_FILENAME");
    info_file = stdout; //fopen(filename, "w");
    if (info_file == NULL)
    {
        fprintf(stderr, "Error in %s: File \"%s\" open failed\n",__func__, filename);
    }

    real_malloc  = dlsym(RTLD_NEXT, xstr(MALLOC));
    real_calloc = dlsym(RTLD_NEXT, xstr(CALLOC));
    real_realloc  = dlsym(RTLD_NEXT, xstr(REALLOC));
    real_free    = dlsym(RTLD_NEXT, xstr(FREE));

    if ((real_malloc == NULL) ||
        (real_calloc == NULL) ||
        (real_free == NULL) ||
        (real_realloc == NULL))
    {
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
    }
}


void* MALLOC(size_t size)
{
    void *p = NULL;
    if(real_malloc==NULL) {
        my_alloc_init();
    }

    my_alloc_count++;

    //fprintf(info_file, "%8d : START\n",my_alloc_count);
    //backtrace_details();
    p = real_malloc(size);
    fprintf(info_file, "%8d: MEM LOG: malloc: size %d, ptr %p\n",
            my_alloc_count,
            size,
            p);
    return p;
}

void* CALLOC(size_t nitems, size_t size)
{
    void *p = NULL;
    if(real_calloc==NULL) {
        //my_alloc_init();
        p = &my_var[index];
        index += nitems*size;
        return p;
    }

    my_alloc_count++;

    //fprintf(info_file, "%8d : START\n",my_alloc_count);
    //backtrace_details();
    p = real_calloc(nitems, size);
    fprintf(info_file, "%8d: MEM LOG: calloc: blocks %d, size %d, ptr %p\n",
            my_alloc_count,
            nitems,
            size,
            p);
    return p;
}

void* REALLOC(void *ptr, size_t size)
{
    void *p = NULL;
    if(real_realloc==NULL) {
        my_alloc_init();
    }

    my_alloc_count++;

    //fprintf(info_file, "%8d : START\n",my_alloc_count);
    //backtrace_details();
    p = real_realloc(ptr, size);
    fprintf(info_file, "%8d: MEM LOG: realloc: mem %p, size %d, ptr %p\n",
            my_alloc_count,
            ptr,
            size,
            p);
    return p;
}

void FREE(void* ptr)
{
    if(real_free==NULL) {
        my_alloc_init();
    }

    my_alloc_count++;

    //fprintf(info_file, "%8d : START\n",my_alloc_count);
    //backtrace_details();
    real_free(ptr);
    fprintf(info_file, "%8d: MEM LOG: free: ptr %p\n",
            my_alloc_count,
            ptr);
}
