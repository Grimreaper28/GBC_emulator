#include<stdio.h>
#include<stdlib.h>
#include"memmap.h"

memMap createMemMap()
{
	int i;
	memMap new;
	new.inBIOS = 0;  // must be cahnged to 1 after BIOS loading is implemented
	new.BIOS = (memBlock*) malloc ( 0xFF * sizeof(memBlock));
	new.mainMap = (memBlock*) malloc ( 0xFFFF * sizeof(memBlock));
	if ( !new.BIOS || !new.mainMap)
	{
		printf("creation error\n");
		return;
	}
	for ( i=0 ; i<0xFF ; i++)
		new.BIOS[i].loc = i;
	for ( i=0 ; i<0xFFFF ; i++)
		new.mainMap[i].loc = i;
	return new;
}

void writeb ( int addr , memMap map , char data)
{
	map.mainMap[addr].data = data;
}

char readb ( int addr , memMap map )
{
	if ( map.inBIOS )
	{
		if ( addr < 0x100 )
			return map.BIOS[addr].data;
		else if ( addr == 0x100 )
		{
			map.inBIOS = 0;
			return map.mainMap[addr].data;
		}
	}
	else
		return map.mainMap[addr].data;
}
