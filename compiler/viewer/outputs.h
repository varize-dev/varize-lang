/*
 * outputs.h
 *
 *  Created on: Sep 28, 2019
 *      Author: #void-skeleton
 */

#ifndef COMPILER_VIEWER_OUTPUTS_H_
#define COMPILER_VIEWER_OUTPUTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *VALID_MAGIC = "varl";
int writeValidation(FILE* stream, int magic)
{
	if (magic != *((int *) VALID_MAGIC))
	{
		fprintf(stream, "\nInvalid magic number: %x\n", magic);
		return 1;
	}
	fprintf(stream, "\nValid Varize byte code: \n\n");
	return 0;
}

void writeVersion(FILE *stream, unsigned long long version)
{
	char* arr = malloc(9);
	int i;
	unsigned long long *ver = malloc(8);
	(*ver) = version;
	// fprintf(stream, "%I64x\n", *ver);
	for (i = 0; i < 8; i ++, (*ver) >>= 8)
	{
		// printf("%I64x\n", *ver);
		// printf("%I64x\n", *ver & 255);
		(*(arr + i)) = ((*ver) & 255);
		// printf("%x\n", arr[i]);
	}
	free(ver);
	*(arr + 8) = 0;
	fprintf(stream, "Version: %s\n", &(arr[0]));
}

short storedDeclLength;
void writeDeclHeader(FILE* stream, short declLength)
{
	fprintf(stream, "\nSegment .decl: \nLength: %x\n", declLength);
	storedDeclLength = declLength;
}


char *writeDeclInfo(FILE* stream, short num, char *data)
{
	char type = data[0];
	char *stype;
	switch (type)
	{
	case 'i':
		stype = "integer";
		break;
	case 'f':
		stype = "function";
		break;
	}
	fprintf(stream, "#%d %s: %s\n", num, stype, data + 1);
	int len = strlen(data + 1);
	return data + len + 2; // to the next .decl info
}

char *writeDeclSegment(FILE *stream, short current, char *data)
{
	if (current == storedDeclLength) return data;
	char *new = writeDeclInfo(stream, current, data);
	return writeDeclSegment(stream, current + 1, new); // recursion
}

short storedImplLength;
void writeImplHeader(FILE* stream, short implLength)
{
	fprintf(stream, "\nSegment .impl: \nLength: %d\n", implLength);
	storedImplLength = implLength;
}

char *INSTRUCTION_MAPPING[] =
	{"nop", "pop", "loadl", "storel", "loadg", "storeg", "local_function", "add", "sub", "mul",
	"div", "and", "or", "xor", "not", "mod", "call", "push", "jump", "cmpl", "cmpg", "cmple",
	"cmpge", "cmpeq", "cmpneq"};
char INSTRUCTION_LENGTH[] =
	{1, 1, 3, 3, 3, 3, 3, 1,
	 1, 1, 1, 1, 1, 1, 1, 1,
	 1, 5, 5, 1, 1, 1, 1, 1,
	 1};
 char *writeImplInfo(FILE *stream, short num, char *data)
{
	// printf("called\n");
	int len = 0;
	len += 1;
	// printf("%x", data[0]);
	if ('i' == data[0])
	{
		fprintf(stream, "#%d: integer %d\n", num, *((int *) (data + 1)));
		len += 4;
	}
	if ('f' == data[0])
	{
		fprintf(stream, "#%d: function\n", num);
		int i;
		short locals, params;
		int instructions;
		char *start = data + 1;
		locals = *((short *) start);
		start += 2;
		len += 2;
		params = *((short *) start);
		start += 2;
		len += 2;
		instructions = *((int *) start);
		start += 4;
		len += 4;
		fprintf(stream, "%d locals, %d parameters, %d instructions\n", locals, params, instructions);
		int off = 0;
		for (i = 0; i < instructions; i ++)
		{
			char instruction = *start;
			start += 1;
			int l = INSTRUCTION_LENGTH[instruction];
			len += l;
			off += l;
			int val;
			switch (l)
			{
			case 3:
				val = *((short *) start);
				break;
			case 5:
				val = *((int *) start);
				break;
			default:
				break;
			}
			if (l == 1) fprintf(stream, "Offset %x: %s\n", off, INSTRUCTION_MAPPING[instruction]);
			else fprintf(stream, "Offset %x: %s %x\n", off, INSTRUCTION_MAPPING[instruction], val);
			start += (l - 1);
		}
	}
	return data + len;
}

void writeImplSegment(FILE *stream, short current, char *data)
{
	if (current == storedImplLength) return;
	char *new = writeImplInfo(stream, current, data);
	writeImplSegment(stream, current + 1, new);
}

void writeViewResult(FILE *infp, FILE *stream)
{
	/* bam! dead
	fseek(infp, 0, SEEK_END);
	int size = ftell(infp);
	rewind(infp);
	char *buff = malloc(size);
	const int start = buff;
	fread(buff, 1, size, infp);
	int magic;
	char *version;
	fread(&magic, 1, 5, infp);
	fread(version, 1, 5, infp);
	writeValidation(stream, magic);
	writeVersion(stream, version);
	buff += 12;
	short declLen, implLen;
	fread(&declLen, 1, 3, infp);
	writeDeclHeader(stream, declLen);
	buff += 2;
	buff = writeDeclSegment(stream, 0, buff);
	fread(&implLen, 1, 3, infp);
	fseek(infp, (int) buff - (int) start, SEEK_SET);
	fread(&implLen, 1, 3, infp);
	buff += 2;
	writeImplHeader(stream, implLen);
	writeImplSegment(stream, 0, buff);
	*/
	// read the file
	fseek(infp, 0, SEEK_END);
	const long size = ftell(infp);
	char* buff = malloc(size + 1);
	rewind(infp);
	fread(buff, 1, size, infp);
	buff[size] = 0;
	// printf(buff);
	// extract the header
	int magic = *((int *) buff);
	if (writeValidation(stream, magic)) return;
	buff += 4;
	unsigned long long version = *((unsigned long long *) buff);
	// printf("%I64x\n", version);
	writeVersion(stream, version);
	buff += 8;
	short declLen, implLen;
	declLen = *((short *) buff);
	buff += 2;
	writeDeclHeader(stream, declLen);
	buff = writeDeclSegment(stream, 0, buff);
	implLen = *((short *) buff);
	buff += 2;
	writeImplHeader(stream, implLen);
	writeImplSegment(stream, 0, buff);
}

#endif /* COMPILER_VIEWER_OUTPUTS_H_ */
