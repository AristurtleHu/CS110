#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 42;
    char *normal = malloc(135);
    char *leak = malloc(246);
    leak[0] = 'q'; // Avoid unused variable warning
    printf("%d\n", a);
    free(normal);
    return 0;
}