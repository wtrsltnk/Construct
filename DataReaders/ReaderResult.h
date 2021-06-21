#ifndef READERRESULT_H_
#define READERRESULT_H_

class ReaderResult
{
protected:
	bool bResult;
	char szErrMsg[256];
	
public:
	ReaderResult();
	ReaderResult(bool result, const char* errmsg = 0, ...);
	virtual ~ReaderResult();

	operator bool (void);
	operator const char* (void);
    void operator = (ReaderResult r);
    
    const char* ErrMsg();
};

#endif /*READERRESULT_H_*/
