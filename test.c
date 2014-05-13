#include <stdlib.h>
#include <stdio.h>


typedef struct {
	char **a;
} se;


static void call(se e) {
	printf("e.a = %p (from call)\n", (void *)e.a);
	*e.a = "bar";
}


int main(int argc, char *argv[]) {
	char *a[1];
	printf("a = %p\n", (void *)a);
	a[0] = "foo";
	se e = {a};
	printf("e.a = %p (from main)\n", (void *)e.a);
	call(e);
	puts(a[0]);
	
	char *s = "foo";
	char *p = s;
	s = "bar";
	puts(s);
	puts(p);
	
	char S[80] = "foo";
	char *P = S;
	S = "bar";
	puts(S);
	puts(P);
	
	return 0;
}
