//UC_Dir.cpp

#include <string.h>

#include "UC_UtilsV2.h"
#include "stdio.h"
#include "myClass.h"

char *getDir()
{
	//return "c:\\GameProg4Uni\\GameKit\\"; // home
	//return "c:\\GptAss2\\Data\\"; // Uni
	return  MYDIR;
}

char *getFileName(char *fname)
{
static char temp[255];
strcpy(temp,getDir());
strcat(temp,fname);
return temp;
}

char *getTexFName(int i)
{
static char temp[255];
sprintf(temp,"%sT%03d.bmp",getDir(),i);
return temp;
}

char *getSurFName(int i)
{
static char temp[255];
sprintf(temp,"%sS%03d.bmp",getDir(),i);
return temp;
}

// end