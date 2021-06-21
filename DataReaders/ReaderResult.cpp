#include "ReaderResult.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>

ReaderResult::ReaderResult() : bResult(true)
{
    strcpy(this->szErrMsg, "");
}

ReaderResult::ReaderResult(bool result, const char *errmsg, ...) : bResult(true)
{
    va_list ap;

    va_start(ap, errmsg);
    vsprintf(this->szErrMsg, errmsg, ap);
    va_end(ap);
}

ReaderResult::~ReaderResult()
{
}

ReaderResult::operator bool(void)
{
    return this->bResult;
}

ReaderResult::operator const char *(void)
{
    return this->szErrMsg;
}

void ReaderResult::operator=(ReaderResult r)
{
    this->bResult = r.bResult;
    strcpy(this->szErrMsg, r.szErrMsg);
}

const char *ReaderResult::ErrMsg()
{
    return this->szErrMsg;
}
