#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int CalCrc(int crc, const char *buf, int len)
{
    unsigned int byte;
    unsigned char k;
    unsigned short ACC,TOPBIT;
    unsigned short remainder = crc;
    TOPBIT = 0x8000; // 1000 0000 0000 0000
    for (byte = 0; byte < len; ++byte)
    {
        ACC = buf[byte];
        remainder ^= (ACC <<8);
        for (k = 8; k > 0; --k)
        {
            if (remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^0x8005;  // 1000 0000 0000 0101
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }
    remainder=remainder^0x0000;
    return remainder;
}

int main(int argc, char* argv[])
{
    char buffer[220] = "abcdefghihklmnopqrstiiabcdefghihklmnopqrstiiabcdefghihklmnopqrstiiabcdefghihklmnopqrstiiabcdefghihklmnopqrstiiabcdefghihklmnopqrstiiabcdefghihklmnopqrstiiabcdefghihklmnopqrstiiabcdefghihklmnopqrstiiabcdefghihklmnopqrsa";
    int crc = CalCrc(0, buffer, 218);//计算得到的16位CRC校验码

	printf("crc: %d\n", crc);

    buffer[21] = (char)crc;//取校验码的低八位
    buffer[20] = (char)(crc >> 8);//取校验码的高八位
//接收方在接收到buffer中的数据时，代入CalCrc进行计算，若result的值为0，则说明数据传输过程无误
    int result = CalCrc(0, buffer, 220);

	printf("result: %d\n", result);

    return 0;
}
