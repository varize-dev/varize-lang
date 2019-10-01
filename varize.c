/*
 * varize.c
 *
 *  Created on: Sep 29, 2019
 *      Author: #void-skeleton
 */

#include <string.h>
#include "compiler/viewer/viewer.h"

int main(int argc, char *argv[])
{
	char *exec = argv[1];
	if (strcmp(exec, "-view") == 0)
	{
		view(argv[2]);
	}
	return 0;
}
