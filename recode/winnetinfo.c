#include <stdio.h>
#include <Windows.h>
#include <windef.h>

#define PATHLEN 512
#define DATALEN 256

int wingetnetinfo(char* gipaddr, char* gnetmask, char* ggateway, char* gdns){
    int ret = -1;

    TCHAR keypath[PATHLEN] = "SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e972-e325-11ce-bfc1-08002be10318}";
    TCHAR tmppath[PATHLEN] = { 0 };
    HKEY pkey = NULL;
    HKEY ckey = NULL;

    DWORD datatype;
    DWORD datalen = DATALEN;
    TCHAR data[DATALEN] = { 0 };

    DWORD kidx = 0;
    TCHAR tbuf[DATALEN] = { 0 };
    DWORD tlen = DATALEN;

    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, keypath, 0, KEY_READ, &pkey) == ERROR_SUCCESS) {
        while(RegEnumKeyEx(pkey, kidx, tbuf, &tlen, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
            ret = sprintf(tmppath, "%s\\%s\\Ndi\\Interfaces\\", keypath, tbuf); tmppath[ret] = 0;
            if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, tmppath, 0, KEY_READ, &ckey) == ERROR_SUCCESS) {
                memset(data, 0x0, DATALEN); datalen = DATALEN;
                if(RegQueryValueEx(ckey, "LowerRange", NULL, &datatype, data, &datalen) == ERROR_SUCCESS) {
                    if(strcmp(data, "ethernet") == 0) {
                        ret = sprintf(tmppath, "%s\\%s", keypath, tbuf); tmppath[ret] = 0;
                        RegCloseKey(ckey); ckey = NULL;
                        if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, tmppath, 0, KEY_READ, &ckey) == ERROR_SUCCESS) {
                        	memset(data, 0x0, DATALEN); datalen = DATALEN;
                            if(RegQueryValueEx(ckey, "NetCfgInstanceId", NULL, &datatype, data, &datalen) == ERROR_SUCCESS){
								ret = sprintf(tmppath, "SYSTEM\\CurrentControlSet\\services\\Tcpip\\Parameters\\Interfaces\\%s", data);
								tmppath[ret] = 0;
								RegCloseKey(ckey); ckey = NULL;
								
								if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, tmppath, 0, KEY_READ, &ckey) == ERROR_SUCCESS){
									if(RegQueryValueEx(ckey, "EnableDHCP", NULL, &datatype, data, &datalen) == ERROR_SUCCESS) {
											TCHAR ipaddre[32] = {"DhcpIPAddress"};
											TCHAR netmask[32] = {"DhcpSubnetMask"};
											TCHAR gateway[32] = {"DhcpDefaultGateway"};
											TCHAR dnsaddr[32] = {"DhcpNameServer"};
										
											if(*data == 0){
												strcpy(ipaddre, "IPAddress");
												strcpy(netmask, "SubnetMask");
												strcpy(gateway, "DefaultGateway");
												strcpy(dnsaddr, "NameServer");
											}
											
										 	memset(data, 0x0, DATALEN);	
											datalen = DATALEN;										
											if(RegQueryValueEx(ckey, ipaddre, NULL, &datatype, data, &datalen) == ERROR_SUCCESS)
												strcpy(gipaddr, data);
											
											memset(data, 0x0, DATALEN);	
											datalen = DATALEN;
											if(RegQueryValueEx(ckey, netmask, NULL, &datatype, data, &datalen) == ERROR_SUCCESS)
												strcpy(gnetmask, data);
												
											memset(data, 0x0, DATALEN);	
											datalen = DATALEN;
											if(RegQueryValueEx(ckey, gateway, NULL, &datatype, data, &datalen) == ERROR_SUCCESS)										
												strcpy(ggateway, data);
												
											memset(data, 0x0, DATALEN);
											datalen = DATALEN;
											if(RegQueryValueEx(ckey, dnsaddr, NULL, &datatype, data, &datalen) == ERROR_SUCCESS)
												strcpy(gdns, data);
									}
									RegCloseKey(ckey); ckey = NULL;
								}
                            }
                            if(ckey != NULL){
                            	RegCloseKey(ckey);
                            	ckey = NULL;
                            }
                        }
                        break;
                    }
                }
                if(ckey != NULL){
                	RegCloseKey(ckey);
                	ckey = NULL;
                }
            }
            kidx++; tlen = DATALEN;
        }
        RegCloseKey(pkey);
        pkey = NULL;
    }
    if(ckey != NULL){
    	RegCloseKey(ckey); ckey = NULL;
    }
    if(pkey != NULL){
    	RegCloseKey(pkey); pkey = NULL;
    }
    return 0;
}

int main(){
	char ip[32] = { 0 };
	char netmask[32] = { 0 };
	char gateway[32] = { 0 };
	char dns[32] = { 0 };
	wingetnetinfo(ip, netmask, gateway, dns);
	printf("ip     : %s\netmask : %s\ngetway : %s\ndns    : %s\n", ip, netmask, gateway, dns);
}
