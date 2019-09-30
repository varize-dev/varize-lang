/*
 * viewer.h
 *
 *  Created on: Sep 28, 2019
 *      Author: #void-skeleton
 */

#ifndef COMPILER_VIEWER_VIEWER_H_
#define COMPILER_VIEWER_VIEWER_H_

#include <stdio.h>
#include "outputs.h"

void view(const char *fname)
{
	FILE *infp = fopen(fname, "rb");
	FILE *stream = stdout;
	writeViewResult(infp, stream);
	fclose(infp);
}

#endif /* COMPILER_VIEWER_VIEWER_H_ */
