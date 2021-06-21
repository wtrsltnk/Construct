#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#define MAX_TOKEN_SIZE 1024

#define TOKEN_EOF -1
#define TOKEN_READY 0
#define TOKEN_ERROR 1

#define IS_QUOTED_TOKEN(ptr) (ptr == '"')
#define IS_COMMENT_TOKEN(ptr) (ptr == '#' || ptr == ';')
#define IS_SPACE_TOKEN(ptr) (ptr <= 32)
#define IS_NEWLINE_TOKEN(ptr) (ptr == '\n')

class Tokenizer
{
protected:
	char* data;
	int datasize;
	
	char* ptr;
	char* end;
	
	int line;
	
	bool ready;
	
	int SkipSpaces();
	int TokenError(char* err);
	
public:
	Tokenizer();
	virtual ~Tokenizer();

	void Setup(char* filename);
	void Setup(char* data, int datasize);
	int GetToken(char* token[], int maxtokensize = MAX_TOKEN_SIZE);
};

#endif /*TOKENIZER_H_*/
