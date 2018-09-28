#include<stdio.h>
unsigned int CRC32_table[256] = {0};
void init_CRC32_table()
{
  int i = 0;
  for (i = 0; i != 256; i++)
  {
    unsigned int CRC = i;
	unsigned int j = 0;
    for (j = 0; j != 8; j++)
    {
      if (CRC & 1)
        CRC = (CRC >> 1) ^ 0xEDB88320;
      else
        CRC >>= 1;
    }
    CRC32_table[i] = CRC;
  }
}
unsigned int GetCRC32(unsigned char* buf, unsigned int len)
{
  unsigned int CRC32_data = 0xFFFFFFFF;
  unsigned int i = 0;
  for (i = 0; i != len; ++i)
  {
    unsigned int t = (CRC32_data ^ buf[i]) & 0xFF;
    CRC32_data = ((CRC32_data >> 8) & 0xFFFFFF) ^ CRC32_table[t];
  }
  return ~CRC32_data;
}

int main()
{
    unsigned char i[8] = "abcdefgh";
    init_CRC32_table();
    printf("BUFFER i's CRC32: 0x%x\n", GetCRC32(i,8));
    printf("CRC32 TABLE:\n");
	int ii = 0;
    for(ii=0;ii<256;ii++)
    {
         printf("0x%8x\t",CRC32_table[ii]);
         if((ii+1)%8 == 0)
             printf("\n");
    }
} 
