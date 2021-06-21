#ifndef MDLFILE_H_
#define MDLFILE_H_

class MDLFile
{
public:
	MDLFile();
	virtual ~MDLFile();

	bool LoadMDL(char *mdlname);
};

#endif /*MDLFILE_H_*/
