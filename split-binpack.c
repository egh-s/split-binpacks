#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long k1,k2,k3,k4,k5;
FILE *fps,*fpd;
char fns[256],fnd[256],fno[256],w[256];
int x,count;
int nr=0;
int limit = 1000000;	// binpack size one million
char *q;
int total=0;

int main(int argc, char *argv[]) {

        if (argc==2)	// binpack size
         { strcpy(w,argv[1]); limit=atoi(w); }

again:	printf("Enter Binpack File Name : "); gets(fns);
	q=strstr(fns,".binpack"); if (q) q[0]=0;
	strcpy(fnd,fns);
	strcat(fns,".binpack");
	fps=fopen(fns,"rb");
	if (fps==0) { printf("\nFile %s not present, try again",fns); goto again; }

loop:   nr++;
        sprintf(fno,"%s-%d.binpack",fnd,nr);
        fpd=fopen(fno,"wb");
        count=0;

read:   x=fread(&k1,8,1,fps); if (x<1) { fclose(fps); goto done; }
	  fread(&k2,8,1,fps);
	  fread(&k3,8,1,fps);
	  fread(&k4,8,1,fps);
	  fread(&k5,8,1,fps);

          fwrite(&k1,8,1,fpd);
          fwrite(&k2,8,1,fpd);
          fwrite(&k3,8,1,fpd);
          fwrite(&k4,8,1,fpd);
          fwrite(&k5,8,1,fpd);
        total++;
        count++; if (count < limit) goto read;

        fclose(fpd);
        printf("Created %s size: %d total: %d\n",fno,limit,total);

        goto loop;

done:   printf("\n\nDone... counted %d binpacks ",total);

        fclose(fps);
        fclose(fpd);

        gets(w);

	return 0;
}
