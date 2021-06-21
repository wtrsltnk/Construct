#include "Utility.h"

#include <windows.h>

#include <io.h> // For access().
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  // For stat().
#include <sys/types.h> // For stat().

//************************************************
// Utility
//************************************************

char *Utility::GetFileName(const char *src)
{
    static char result[MAX_RESULT] = {0};
    int len = strlen(src);
    bool haspath = false;

    for (int i = len; i >= 0; i--)
    {
        if (src[i] == '\\' || src[i] == '/')
        {
            haspath = true;
            i++;
            int j = 0;
            for (j = 0; (j + i) < len; j++)
            {
                result[j] = src[i + j];
            }
            result[j] = '\0';
            break;
        }
    }
    if (!haspath)
    {
        strcpy(result, src);
    }
    return result;
}

char *Utility::GetFilePath(const char *src)
{
    static char result[MAX_RESULT] = {0};
    int len = strlen(src);
    int j = 0;

    for (int i = len; i >= 0; i--)
    {
        if (src[i] == '\\' || src[i] == '/')
        {
            for (j = 0; j < i; j++)
            {
                result[j] = src[j];
            }
            break;
        }
    }
    result[j] = '\0';
    return result;
}

char *Utility::GetBaseFileName(const char *src)
{
    static char result[MAX_RESULT] = {0};
    int len = strlen(src);
    bool haspath = false;
    int j = 0;

    for (int i = len; i >= 0; i--)
    {
        if (src[i] == '\\' || src[i] == '/')
        {
            haspath = true;
            i++;
            for (j = 0; (j + i) < len; j++)
            {
                if (src[i + j] == '.') break;

                result[j] = src[i + j];
            }
            result[j] = '\0';
            break;
        }
    }
    if (!haspath)
    {
        for (j = 0; j < len; j++)
        {
            if (src[j] == '.') break;

            result[j] = src[j];
        }
        result[j] = '\0';
    }
    return result;
}

char *Utility::GetExtension(const char *src)
{
    static char result[MAX_RESULT] = {0};
    int len = strlen(src);
    int j = 0;

    for (int i = len; i >= 0; i--)
    {
        if (src[i] == '.')
        {
            for (j = 0; (j + i) < len; j++)
            {
                result[j] = src[i + j];
            }
            break;
        }
    }
    result[j] = '\0';
    return result;
}

Utility::Utility()
{
}

Utility::~Utility()
{
}

//************************************************
// Utility::Result
//************************************************

Utility::Result::operator bool(void)
{
    return this->bResult;
}

Utility::Result::operator int(void)
{
    return this->nErrCode;
}

Utility::Result::operator const char *(void)
{
    return this->szErrMsg;
}

void Utility::Result::operator=(Utility::Result r)
{
    this->bResult = r.bResult;
    strcpy(this->szErrMsg, r.szErrMsg);
}

const char *Utility::Result::ErrMsg()
{
    return this->szErrMsg;
}

Utility::Result::Result() : bResult(true), nErrCode(0)
{
    strcpy(this->szErrMsg, "");
}

Utility::Result::Result(bool result, const char *errmsg, ...) : bResult(true), nErrCode(0)
{
    va_list ap;

    va_start(ap, errmsg);
    vsprintf(this->szErrMsg, errmsg, ap);
    va_end(ap);
}

Utility::Result::Result(bool result, int errcode, const char *errmsg, ...) : bResult(true), nErrCode(errcode)
{
    va_list ap;

    va_start(ap, errmsg);
    vsprintf(this->szErrMsg, errmsg, ap);
    va_end(ap);
}

Utility::Result::~Result()
{
}

//************************************************
// Utility::DataBlock
//************************************************

char *Utility::DataBlock::Ptr()
{
    return this->pData;
}

int Utility::DataBlock::Size()
{
    return this->nSize;
}

Utility::DataBlock *Utility::DataBlock::Read(FILE *file, int size, int offset)
{
    Utility::DataBlock *result = new Utility::DataBlock();

    if (size >= 0)
    {
        result->pData = (char *)malloc(size);
        if (offset != -1)
        {
            ::fseek(file, offset, SEEK_SET);
        }
        result->nSize = ::fread(result->pData, 1, size, file);
    }
    else
    {
        ::fseek(file, 0, SEEK_END);
        result->nSize = (int)::ftell(file);
        ::fseek(file, 0, SEEK_SET);

        result->pData = (char *)malloc(result->nSize);
        result->nSize = ::fread(result->pData, 1, size, file);
    }

    if (result->nSize == 0)
    {
        delete result;
        result = 0;
    }

    return result;
}

Utility::DataBlock *Utility::DataBlock::Create(char *data, int size)
{
    Utility::DataBlock *result = new Utility::DataBlock();

    result->pData = (char *)malloc(size);
    result->nSize = size;
    memcpy(result->pData, data, result->nSize);

    return result;
}

int Utility::DataBlock::Write(FILE *file, int offset)
{
    if (file != 0)
    {
        if (offset >= 0)
        {
            ::fseek(file, offset, SEEK_SET);
        }
        return (int)::fwrite(this->pData, 1, this->nSize, file);
    }
    return 0;
}

Utility::DataBlock::DataBlock()
{
    this->pData = 0;
    this->nSize = 0;
}

Utility::DataBlock::~DataBlock()
{
    if (this->pData != 0)
    {
        free(this->pData);
    }
    this->pData = 0;
    this->nSize = 0;
}

//************************************************
// Utility::File
//************************************************

bool Utility::File::Exists(const char *filename)
{
    FILE *file = ::fopen(filename, "rb");

    if (file != 0)
    {
        ::fclose(file);
        return true;
    }
    return false;
}

Utility::File *Utility::File::Open(const char *filename, bool forwriting)
{
    Utility::File *result = new Utility::File(filename);

    if (result != 0)
    {
        result->bWritable = forwriting;
        if (forwriting)
        {
            result->hFile = ::fopen(filename, "wb");
        }
        else
        {
            result->hFile = ::fopen(filename, "rb");
        }

        if (result->hFile == 0)
        {
            delete result;
        }

        ::fseek(result->hFile, 0, SEEK_END);
        result->nSize = (int)::ftell(result->hFile);
        ::fseek(result->hFile, 0, SEEK_SET);
    }

    return result;
}

Utility::File *Utility::File::Create(const char *filename)
{
    Utility::File *result = new Utility::File(filename);

    if (result != 0)
    {
        result->bWritable = true;
        result->hFile = ::fopen(filename, "wb");

        if (result->hFile == 0)
        {
            delete result;
        }

        ::fseek(result->hFile, 0, SEEK_END);
        result->nSize = (int)::ftell(result->hFile);
        ::fseek(result->hFile, 0, SEEK_SET);
    }

    return result;
}

Utility::Result Utility::File::ReadData(DataBlock **result, int size, int offset)
{
    if (!this->bWritable)
    {
        (*result) = DataBlock::Read(this->hFile, size, offset);
    }
    return Utility::Result(false, "You can\'t read from this file object");
}

Utility::Result Utility::File::ReadAll(DataBlock **result)
{
    if (!this->bWritable)
    {
        (*result) = DataBlock::Read(this->hFile);
    }
    return Utility::Result(false, "You can\'t read from this file object");
}

Utility::Result Utility::File::WriteData(DataBlock *data, int offset)
{
    if (this->bWritable)
    {
        if (data->Write(this->hFile, offset) == data->Size())
        {
            return Result();
        }
        else
        {
            return Result(false, "Wrong number of bytes written to file");
        }
    }
    return Utility::Result(false, "You can\'t write to this file object");
}

int Utility::File::Size()
{
    return this->nSize;
}

bool Utility::File::IsWritable()
{
    return this->bWritable;
}

const char *Utility::File::GetFileName()
{
    return this->szFilename;
}

Utility::File::File(const char *filename)
{
    this->hFile = 0;
    this->szFilename = new char[strlen(filename) + 1];
    strcpy(this->szFilename, filename);
}

Utility::File::~File()
{
    delete[] this->szFilename;
    this->szFilename = 0;

    if (this->hFile != 0)
    {
        ::fclose(this->hFile);
        this->hFile = 0;
    }
}

//************************************************
// Utility::Directory
//************************************************

bool Utility::Directory::Exists(const char *path)
{
    if (access(path, 0) == 0)
    {
        struct stat status;

        stat(path, &status);

        return (status.st_mode & S_IFDIR);
    }

    return false;
}

Utility::Directory *Utility::Directory::Open(const char *path)
{
    if (Utility::Directory::Exists(path))
    {
        return new Utility::Directory(path);
    }
    return 0;
}

Utility::Directory *Utility::Directory::Make(const char *path)
{
    Directory *result = new Directory(path);

    CreateDirectory(path, NULL);

    return result;
}

Utility::Directory *Utility::Directory::GetSubDir(const char *name)
{
    char str[256] = {0};

    sprintf(str, "%s%s", this->szPath, name);

    if (access(str, 0) == 0)
    {
        return new Directory(str);
    }
    return 0;
}

Utility::File *Utility::Directory::GetFile(const char *filename, bool forwriting)
{
    char str[256] = {0};

    sprintf(str, "%s%s", this->szPath, filename);

    if (access(str, 0) == 0)
    {
        return Utility::File::Open(filename, forwriting);
    }
    return 0;
}

Utility::File *Utility::Directory::MakeFile(const char *filename)
{
    char str[256] = {0};

    sprintf(str, "%s%s", this->szPath, filename);

    if (access(str, 0) == 0)
    {
        return Utility::File::Create(filename);
    }
    return 0;
}

const char *Utility::Directory::GetPath()
{
    return this->szPath;
}

bool Utility::Directory::Exists()
{
    return Utility::Directory::Exists(this->szPath);
}

Utility::Directory::Directory(const char *path)
{
    int size = strlen(path);

    if (path[size - 1] != '\\' && path[size - 1] != '/')
    {
        this->szPath = new char[strlen(path) + 2];
        sprintf(this->szPath, "%s\\", path);
    }
    else
    {
        this->szPath = new char[strlen(path) + 1];
        strcpy(this->szPath, path);
    }
}

Utility::Directory::~Directory()
{
    delete[] this->szPath;
}

//************************************************
// Utility::Drive
//************************************************

Utility::Drive *Utility::Drive::Open(char letter)
{
    return new Drive(letter);
}

Utility::Directory *Utility::Drive::GetSubDir(const char *name)
{
    char str[256] = {0};

    sprintf(str, "%s%s", this->szDrive, name);

    return Utility::Directory::Open(str);
}

Utility::File *Utility::Drive::GetFile(const char *filename, bool forwriting)
{
    char str[256] = {0};

    sprintf(str, "%s%s", this->szDrive, filename);

    return Utility::File::Open(str, forwriting);
}

Utility::File *Utility::Drive::MakeFile(const char *filename)
{
    char str[256] = {0};

    sprintf(str, "%s%s", this->szDrive, filename);

    return Utility::File::Create(str);
}

const char *Utility::Drive::GetDrive()
{
    return this->szDrive;
}

Utility::Drive::Drive(char letter)
{
    if ((letter < 'A' && letter > 'Z') ||
        (letter < 'a' && letter > 'z'))
    {
        letter = 'c';
    }
    if (letter < 'a')
    {
        letter -= ('a' - 'A');
    }
    this->szDrive[0] = letter;
    this->szDrive[1] = ':';
    this->szDrive[2] = '\\';
}

Utility::Drive::~Drive()
{
}
