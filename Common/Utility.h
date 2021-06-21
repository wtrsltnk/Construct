#ifndef UTILITY_H_
#define UTILITY_H_

#define MAX_RESULT 256
#include <stdio.h>

class Utility
{
public:
	Utility();
	virtual ~Utility();

	static char* GetFileName(const char* src);
	static char* GetFilePath(const char* src);
	static char* GetBaseFileName(const char* src);
	static char* GetExtension(const char* src);

	//************************
	// Utility::Result
	//************************
	class Result
	{
	protected:
		bool bResult;
		int nErrCode;
		char szErrMsg[256];
		
	public:
		Result();
		Result(bool result, const char* errmsg = 0, ...);
		Result(bool result, int errcode, const char* errmsg = 0, ...);
		virtual ~Result();

		operator bool (void);
		operator int (void);
		operator const char* (void);
	    void operator = (Result r);
	    
	    const char* ErrMsg();
	};

	//************************
	// Utility::DataBlock
	//************************
	class DataBlock
	{
	protected:
		char* pData;
		int nSize;
		
		DataBlock();
		
	public:
		virtual ~DataBlock();
		
		char* Ptr();
		int Size();
		
	public:
		static DataBlock* Read(FILE* file, int size = -1, int offset = -1);
		static DataBlock* Create(char* data, int size);
		int Write(FILE* file, int offset = -1);
	};

	//************************
	// Utility::File
	//************************
	class File
	{
	protected:
		FILE* hFile;
		char* szFilename;
		int nSize;
		bool bWritable;

		File(const char* filename);
		
	public:
		static bool Exists(const char* filename);
		static File* Open(const char* filename, bool forwriting = false);
		static File* Create(const char* filename);
		
	public:
		virtual ~File();

		Result ReadData(DataBlock** result, int size, int offset = -1);
		Result ReadAll(DataBlock** result);
		Result WriteData(DataBlock* data, int offset = -1);
		
		int Size();
		bool IsWritable();
		
		const char* GetFileName();
		
	};

	//************************
	// Utility::Directory
	//************************
	class Directory
	{
	protected:
		char* szPath;
		
		Directory(const char* path);
		
	public:
		static bool Exists(const char* path);
		static Directory* Open(const char* path);
		static Directory* Make(const char* path);
		
	public:
		virtual ~Directory();
		
		Directory* GetSubDir(const char* name);
		File* GetFile(const char* filename, bool forwriting = false);
		File* MakeFile(const char* filename);
		
		const char* GetPath();
		bool Exists();
		
	};

	//************************
	// Utility::Drive
	//************************
	class Drive
	{
	protected:
		char szDrive[3];
		
		Drive(char letter);
		
	public:
		static Drive* Open(char letter);
		
	public:
		virtual ~Drive();
		
		Directory* GetSubDir(const char* name);
		File* GetFile(const char* filename, bool forwriting = false);
		File* MakeFile(const char* filename);

		const char* GetDrive();
	};
};

#endif /*UTILITY_H_*/
