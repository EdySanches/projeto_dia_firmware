#ifndef _SPIFFSHANDLER_H
#define _SPIFFSHANDLER_H

#define PATH_SSIDNAMEFILE "/spiffs/ssidname.txt"
#define PATH_PASSWORDFILE "/spiffs/password.txt"

#define PATH_DNSFILE "/spiffs/dns.txt"

#define PATH_CALIBS "/spiffs/calibs2.txt"
#define PATH_REF "/spiffs/reffile21.txt"

#define PATH_ID "/spiffs/bal_id.txt"

#define PATH_INDEX "/spiffs/PersonalBOVIndex2.bin"


#define PATH_DATA "/spiffs/PersonalBOV2.bin"

#define PATH_POINTERS "/spiffs/PersonalBovFlags.bin"
#define PATH_POINTERS_BACKUP "/spiffs/PersonalBovFlagsbackup.bin"

char isThisSPIFFSFileCreated(char * PATH);
char CreateSPIFFSFile(char * PATH, int initialSize, char initialContent[initialSize]);
char CreateSPIFFSBlankFile(char * PATH, int initialSize);
char ReadDataSPIFFSFile(char * PATH, int pointer,int dataSize, char data[dataSize]);
char WriteDataSPIFFSFile(char * PATH, int pointer, int dataSize, char data[dataSize], char checkData);

void RemoveSPIFFSFile(char * PATH);
void InitSPIFFS(void);

#endif
