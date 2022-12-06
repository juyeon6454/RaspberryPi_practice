#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main()
{
		srand((unsigned int)time(NULL));
		printf("random number : %d\n", rand());
		printf("random number : %d\n", rand());
		printf("random number : %d\n", rand());
		printf("random number : %d\n", rand());
		printf("random number : %d\n", rand());
		return 0;
}
