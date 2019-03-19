#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#include "config.h"
#include "bytes_value_conv.h"
#include "ora_opt.h"
#include "mem_to_file.h"
#include "fzs_mem.h"
#include "scn_time.h"

char time_buf[30] = {0};
char opstr_buf[16] = {0};

void op_to_str(unsigned char* op_code, char* opstr)
{
    if (*op_code == OP_FCREATE)
        sprintf(opstr, "FCREATE");
    else if (*op_code == OP_FDEL)
        sprintf(opstr, "FDEL");
    else if (*op_code == OP_FWRITE)
        sprintf(opstr, "FWRITE");
    else if (*op_code == OP_FTRUNCATE)
        sprintf(opstr, "FTRUNCATE");
    else if (*op_code == OP_FRENAME)
        sprintf(opstr, "FRENAME");
    else if (*op_code == OP_DIRCREATE)
        sprintf(opstr, "DIRCREATE");
    else if (*op_code == OP_DIRDEL)
        sprintf(opstr, "DIRDEL");
    else if (*op_code == OP_DIRRENAME)
        sprintf(opstr, "DIRRENAME");
    else if (*op_code == OP_FCHMOD)
        sprintf(opstr, "FCHMOD");
    else if (*op_code == OP_FCHOWN)
        sprintf(opstr, "FCHOWN");
    else if (*op_code == OP_SYMLINK)
        sprintf(opstr, "SYMLINK");
    else
        sprintf(opstr," ");
}



/*******************
 * cdp info to xml
 ******************/
int main(int argc, char* argv[])
{
	int num = 1;
	int rc = -1;
	int tgt_id = 1;
	FILE* fp = NULL;
	int queue_id = 0;
	int fzs_del_no = -1;
	int fzs_end_no = -1;
	int tmp_fzs_no = -1;

	char* pbuf = NULL;
	char* pbuf_end = NULL;

	char file_path[128] = "";
	char xml_path[64] = "";
	char file_context[4096] = "";

	struct stat fst;
	int file_len = -1;

	int fd = -1;
	char* buffer = NULL;
	char strbuffer[32] = {0};

	FZS *pfzs;
	int sum_size = 0;

	sprintf(file_path, "./fzs_tgt/%d/del_%d_%d", tgt_id, tgt_id, queue_id);
	fp = fopen(file_path, "rb");
	if(fp != NULL)
	{
		fread(file_path, sizeof(file_path), 1, fp);
		if(strlen(file_path) > 0)
			fzs_del_no = atoi(file_path);
	}else{
		fzs_del_no = 0;
	}
	fclose(fp);fp = NULL;

	sprintf(file_path, "./fzs_tgt/%d/conf_%d", tgt_id, tgt_id);
	fp = fopen(file_path, "rb");
	if(fp != NULL)
	{
		fread(file_path, sizeof(file_path), 1, fp);
		if(strlen(file_path) > 0)
			fzs_end_no = atoi(file_path);
	}else{
		fzs_end_no = 0;
	}
	fclose(fp);fp = NULL;

	sprintf(xml_path, "./fzs_tgt/%d/operation.xml", tgt_id);

	if(file_exist(xml_path)){
		rc = 0;
		fp = fopen(xml_path, "r");
		fgets(file_context, sizeof(file_context), fp);
		fgets(file_context, sizeof(file_context), fp);
		sprintf(strbuffer, "%d.%d.fzs", fzs_del_no, queue_id);
		if(!strstr(file_context, strbuffer)){
			rc = 1;
		}
		fgets(file_context, sizeof(file_context), fp);
		fclose(fp);
		sprintf(strbuffer, "%d.%d.fzs", fzs_end_no, queue_id);
#if 0
		if(rc == 0 && !strstr(file_context, strbuffer)){
		}else 
#endif
		if(rc == 0 && strstr(file_context, strbuffer)){
			printf("dont have to anailysis\n");
			return 0;
		}
	}

	fp = fopen(xml_path, "w+");
	fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
//	fprintf(fp, "    <start: %d.%d.fzs - end: %d.%d.fzs>\n", fzs_del_no, queue_id, fzs_end_no, queue_id);
	fprintf(fp, "<val fzs_del_no=\"%d.%d.fzs\"></val>\n", fzs_del_no, queue_id);
	fprintf(fp, "<val fzs_end_no=\"%d.%d.fzs\"></val>\n", fzs_end_no, queue_id);
	fprintf(fp, "<operations>\n");

	while(fzs_del_no <= fzs_end_no)
	{
		sprintf(file_path, "./fzs_tgt/%d/%d/%d.%d.fzs", tgt_id, fzs_del_no / FILE_NUM_EACH_DIR, fzs_del_no, queue_id);
		if(stat(file_path, &fst) < 0){
			fzs_del_no++;
			continue;
		}
		file_len = fst.st_size;

		fd = open(file_path, O_RDONLY, 0600);
		if(fd < 0)
		{
			fzs_del_no++;
			continue;
		}

		buffer = (char*)malloc(file_len+10);
		memset(buffer, '\0', file_len+10);

		read(fd, buffer, file_len);
		close(fd);

		pfzs = (FZS*)FZS_MALLOC(sizeof(FZS));
		
		for(pbuf = buffer, pbuf_end = buffer+file_len; pbuf < pbuf_end; )
		{
			memset(pfzs, 0x0, sizeof(FZS));
			rc = buf2fzs(pfzs, pbuf);

			sum_size += pfzs->nil.length + 4;

			switch(pfzs->nil.op_code)
			{
				case OP_FCREATE:
				case OP_FDEL:
				case OP_DIRCREATE:
				case OP_DIRDEL:
					numtime2str(pfzs->fcreate.mtime, time_buf);
					op_to_str(pfzs->fcreate.op_code, opstr_buf);
					fprintf(fp, "    <opt num=\"%d\" op_time=\"%s\" op_code=\"%s\" op_file=\"%s\" fzsfile=\"%s\"></opt>\n",
                                           num, time_buf, opstr_buf, pfzs->fcreate.filename, file_path );
					num++;
					break;
				case OP_FWRITE:
					numtime2str(pfzs->fwrite.mtime, time_buf);
					op_to_str(pfzs->fwrite.op_code, opstr_buf);
					fprintf(fp, "    <opt num=\"%d\" op_time=\"%s\" op_code=\"%s\" op_file=\"%s\" fzsfile=\"%s\"></opt>\n", 
                                           num, time_buf, opstr_buf, pfzs->fwrite.filename, file_path);
					num++;
					break;
				case OP_FTRUNCATE:
					numtime2str(pfzs->filetruncate.mtime, time_buf);
					op_to_str(pfzs->filetruncate.op_code, opstr_buf);
					fprintf(fp, "    <opt num=\"%d\" op_time=\"%s\" op_code=\"%s\" op_file=\"%s\" fzsfile=\"%s\"></opt>\n", 
                                           num, time_buf, opstr_buf, pfzs->filetruncate.filename,file_path );
					num++;
					break;
				case OP_FRENAME:
				case OP_DIRRENAME:
					numtime2str(pfzs->frename.mtime, time_buf);
					op_to_str(pfzs->frename.op_code, opstr_buf);
					fprintf(fp, "    <opt num=\"%d\" op_time=\"%s\" op_code=\"%s\" op_file=\"%s\" fzsfile=\"%s\"></opt>\n", 
                                           num, time_buf, opstr_buf, pfzs->frename.filename ,file_path);
					num++;
					break;
				case OP_FCHMOD:
					numtime2str(pfzs->fchmod.mtime, time_buf);
					op_to_str(pfzs->fchmod.op_code, opstr_buf);
					fprintf(fp, "    <opt num=\"%d\" op_time=\"%s\" op_code=\"%s\" op_file=\"%s\" fzsfile=\"%s\"></opt>\n", 
                                           num, time_buf, opstr_buf, pfzs->fchmod.filename, file_path);
					num++;
					break;
				case OP_FCHOWN:
					numtime2str(pfzs->fchown.mtime, time_buf);
					op_to_str(pfzs->fchown.op_code, opstr_buf);
					fprintf(fp, "    <opt num=\"%d\" op_time=\"%s\" op_code=\"%s\" op_file=\"%s\" fzsfile=\"%s\"></opt>\n", 
                                           num, time_buf, opstr_buf, pfzs->fchown.filename, file_path );
					num++;
					break;
				case OP_SYMLINK:
					numtime2str(pfzs->sym_link.mtime, time_buf);
					op_to_str(pfzs->sym_link.op_code, opstr_buf);
					fprintf(fp, "    <opt num=\"%d\" op_time=\"%s\" op_code=\"%s\" op_file=\"%s\" fzsfile=\"%s\"></opt>\n", 
                                           num, time_buf, opstr_buf, pfzs->sym_link.symlinkname , file_path);
					num++;
					break;
				default:
					break;

			}
			pbuf += (pfzs->nil.length + 4);
		}

		FZS_FREE(pfzs);
		
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}

		fzs_del_no++;
	}
	
	fprintf(fp,"</operations>\n");
	fclose(fp);

	return 0;
	

}

