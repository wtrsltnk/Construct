#ifndef SPRFILE_H_
#define SPRFILE_H_

class SPRFile
{
public:
	SPRFile();
	virtual ~SPRFile();

	bool LoadSPR(char *sprname);
};

#endif /*SPRFILE_H_*/
