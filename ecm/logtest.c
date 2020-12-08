#include <stdio.h>
#include <math.h>

int blog(int a) {
	if (a>1) return 1+blog(a>>1);
	return 0;
}

int main() {
	int a = 16;
	printf("log(%d)=%d",a,blog(a));
}	
