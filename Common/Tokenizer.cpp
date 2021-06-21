#include "Tokenizer.h"
#include "../Common/cmdlib.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

void Tokenizer::Setup(char* filename)
{
	if (filename != 0)
	{
		char* data = 0;
		int datasize = 0;
		
		datasize = LoadFile(filename, (void**)&data);
		this->Setup(data, datasize);
	}
}

void Tokenizer::Setup(char* data, int datasize)
{
	if (datasize > 0)
	{
		if (this->data != 0)
		{
			free(this->data);
		}
		
		this->data = (char*)malloc(sizeof(char) * datasize);
		memcpy(this->data, data, datasize);
		this->datasize = datasize;
		
		this->ptr = this->data;
		this->end = this->data + this->datasize;
		this->line = 1;

		this->ready = true;
	}
}

int Tokenizer::GetToken(char* token[], int maxtokensize)
{
	char* result = *token;
	int res = 0;
	
	if (token != 0 && this->ready)
	{
		// Check for end of script
		if (this->ptr >= this->end)
			return TOKEN_EOF;
		
		// Skip all space characters
		if ((res = this->SkipSpaces()) != TOKEN_READY)
			return res;
		
		// What kind of token is it?
		if (IS_COMMENT_TOKEN(*this->ptr))
		{
			// Comment line
			while (*this->ptr != '\n')
			{
				this->ptr++;
				if (this->ptr >= this->end)
					return TOKEN_EOF;
				
				this->line++;
			}
			return GetToken(token, maxtokensize);
		}
		else if (IS_QUOTED_TOKEN(*this->ptr))
		{
			// Quoted token
			this->ptr++;
			while (!IS_QUOTED_TOKEN(*this->ptr))
			{
				if (this->ptr >= this->end)
					break;
				
				if (maxtokensize <= 0)
					return this->TokenError("max token size reached");
				
				*result++ = *this->ptr++;
				*result = 0;
				maxtokensize--;
			}
			this->ptr++;
			return TOKEN_READY;
		}
		else
		{
			// Regular token
			while (!IS_SPACE_TOKEN(*this->ptr) && !IS_COMMENT_TOKEN(*this->ptr))
			{
				if (this->ptr >= this->end)
					break;
				
				if (maxtokensize <= 0)
					return this->TokenError("max token size reached");
				
				*result++ = *this->ptr++;
				*result = 0;
				maxtokensize--;
			}
			return TOKEN_READY;
		}
	}
	else
	{
		return this->TokenError("token is NULL or tokenizer not ready");
	}
	return TOKEN_ERROR;
}

int Tokenizer::SkipSpaces()
{
	while (IS_SPACE_TOKEN(*this->ptr))
	{
		if (this->ptr >= this->end)
			return TOKEN_EOF;
		
		if (IS_NEWLINE_TOKEN(*this->ptr))
			this->line++;

		this->ptr++;
	}
	return TOKEN_READY;
}

int Tokenizer::TokenError(char* err)
{
	printf("*** ERROR *** on line %d : %s\n", this->line, err);
	
	return TOKEN_ERROR;
}

Tokenizer::Tokenizer()
{
	this->data = 0;
	this->datasize = 0;
	this->ptr = 0;
	this->end = 0;
	this->line = 1;
	this->ready = false;
}

Tokenizer::~Tokenizer()
{
	if (this->data != 0)
	{
		free(this->data);
	}
	this->data = 0;
	this->datasize = 0;
	this->ptr = 0;
	this->end = 0;
	this->line = 1;
	this->ready = false;
}
