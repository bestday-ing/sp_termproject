#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
	char *arr[2];

	arr[0]="./sender";
	arr[1]=0;

	execvp(arr[0],arr);
}
