#include <stdio.h>

int is_str_utf8(const char* str)
{
  unsigned int nBytes = 0;
  unsigned char chr = *str;
  int bAllAscii = 1;
  unsigned int i = 0;
  for (i = 0; str[i] != '\0'; ++i){
    chr = *(str + i);
    if (nBytes == 0 && (chr & 0x80) != 0){
      bAllAscii = 0;
    }
    if (nBytes == 0) {
      if (chr >= 0x80) {
        if (chr >= 0xFC && chr <= 0xFD){
          nBytes = 6;
        }
        else if (chr >= 0xF8){
          nBytes = 5;
        }
        else if (chr >= 0xF0){
          nBytes = 4;
        }
        else if (chr >= 0xE0){
          nBytes = 3;
        }
        else if (chr >= 0xC0){
          nBytes = 2;
        }
        else{
          return 0;
        }
        nBytes--;
      }
    }
    else{
      if ((chr & 0xC0) != 0x80){
        return 0;
      }
      nBytes--;
    }
  }
  if (nBytes != 0) {
    return 0;
  }
  if (bAllAscii){
    return 1;
  }
  return 1;
}

int is_str_gbk(const char* str)
{
  unsigned int nBytes = 0;
  unsigned char chr = *str;
  int bAllAscii = 1;
  unsigned int i = -1;
  for (i = 0; str[i] != '\0'; ++i){
    chr = *(str + i);
    if ((chr & 0x80) != 0 && nBytes == 0){
      bAllAscii = 0;
    }
    if (nBytes == 0) {
      if (chr >= 0x80) {
        if (chr >= 0x81 && chr <= 0xFE){
          nBytes = +2;
        }
        else{
          return 0;
        }
        nBytes--;
      }
    }
    else{
      if (chr < 0x40 || chr>0xFE){
        return 0;
      }
      nBytes--;
    }
  }
  if (nBytes != 0) {
    return 0;
  }
  if (bAllAscii){
    return 1;
  }
  return 1;
}

void main(){
	char utfstr[32] = "12345687654fghgfds";
	char gdkstr[32] = "你好我是机器人呢";

	if(is_str_utf8(utfstr)){
		printf("utfstr is utf8\n");
	}
	if(is_str_utf8(gdkstr)){
		printf("gdkstr is utf8\n");
	}
	if(is_str_gbk(utfstr)){
		printf("utfstr is gbk\n");
	}
	if(is_str_gbk(gdkstr)){
		printf("gdkstr is gbk\n");
	}
}
