#ifndef _memmap
#define _memmap

typedef struct memBlock
{
	int loc;
	char data;
} memBlock;

typedef struct memMap
{
	int inBIOS;
	memBlock* BIOS;
	memBlock* mainMap;
} memMap;

memMap createMemMap ();
char readb (int addr , memMap map);
void writeb (int addr , memMap map , char data);

#endif
