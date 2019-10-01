#include <stdio.h>
#include <string.h>
#include "judge_system.h"
#include "compiler/viewer/viewer.h"
int main(int argc,char *argv[])
{
	if(argc==1)
	{
		fprintf(stderr,"varize: no input file!\n");
		return 1;
	}
	if(strcmp(argv[1],"view")==0)
	{
		if(argc!=3)
		{
			fprintf(stderr,"varize: bad usage!\n");
			fprintf(stderr,"varize: view receive only one input!\n");
			return 1;
		}
		view(argv[2]);
	}
	return 0;
}
