#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

static void xml_fzs_title(FILE* fp){
    char buf[128] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    fputs(buf, fp);
}
static void xml_fzs_root(FILE* fp, int bgn){
    char buf[16] = "";        
    if(bgn == 1)
        sprintf(buf, "%s\n", "<root>");  
    else
        sprintf(buf, "%s\n", "</root>"); 
    fputs(buf, fp);
}
static void xml_ora_type(FILE* fp, int file_type){
    char buf[64] = "";
    sprintf(buf, "\t<ora_type>%d</ora_type>\n", file_type);
    fputs(buf, fp);
    
}
static void xml_ora_xtlb(FILE* fp, int sys_type){
    char buf[64] = "";
    sprintf(buf, "\t<ora_xtlb>%d</ora_xtlb>\n", sys_type);
    fputs(buf, fp);
}
static void xml_ora_transaction(FILE* fp, int sessionid, int serial, int bgn){
    char buf[128] = "";
    if(bgn == 1)
        sprintf(buf, "\t<ora_transaction sessionid=\"%d\" serial=\"%d\">\n", sessionid, serial);
    else
        sprintf(buf, "\t</ora_transaction>\n");
    fputs(buf, fp);
}
static void xml_ora_user(FILE* fp, const char* user){
    char buf[256] = "";
    sprintf(buf, "\t\t<ora_user>%s</ora_user>\n", user);
    fputs(buf, fp);
}
static void xml_ora_client(FILE* fp, const char* client){
    char buf[256] = "";
    sprintf(buf, "\t\t<ora_client>%s</ora_client>\n", client);
    fputs(buf, fp);
}
static void xml_ora_time(FILE* fp, const char* time){
    char buf[128] = "";
    sprintf(buf, "\t\t<ora_time>%s</ora_time>\n", time);
    fputs(buf, fp);
}
static void xml_ora_program(FILE* fp, const char* prosess_name){
    char buf[256] = "";
    sprintf(buf, "\t\t<ora_program>%s</ora_program>\n", prosess_name);
    fputs(buf, fp);
}
static void xml_ora_datalist(FILE* fp, int bgn){
    char buf[32] = "";
    if(bgn == 1)
        sprintf(buf, "\t\t<ora_datalist>\n");
    else
        sprintf(buf, "\t\t</ora_datalist>\n");
    fputs(buf, fp);
}
static void xml_ora_recode(FILE* fp, int recnum, int bgn){
    char buf[64] = "";
    if(bgn == 1)
        sprintf(buf, "\t\t\t<ora_record recnum=\"%d\">\n", recnum);
    else
        sprintf(buf, "\t\t\t</ora_record>\n");
    fputs(buf, fp);
}
static void xml_ora_schema(FILE* fp, const char* schema){
    char buf[256] = "";
    sprintf(buf, "\t\t\t\t<ora_schema>%s</ora_schema>\n", schema);
    fputs(buf, fp);
}
static void xml_tab_name(FILE* fp, const char* tab_name){
    char buf[256] = "";
    sprintf(buf, "\t\t\t\t<tab_name>%s</tab_name>\n", tab_name);
    fputs(buf, fp);
}
static void xml_tab_action(FILE* fp, const char* tab_action){
    char buf[64] = "";
    sprintf(buf, "\t\t\t\t<tab_action>%s</tab_action>\n", tab_action);
    fputs(buf, fp);
}

static void irqdrp2xml(){
    FILE *fp = fopen("filename", "a+");
    xml_fzs_title(fp);
    xml_fzs_root(fp, 1);
    xml_ora_type(fp, 2);
    xml_ora_xtlb(fp, 10);
    xml_ora_transaction(fp, 21, 4457, 1);
    xml_ora_user(fp, "test_admin");
    xml_ora_client(fp, "machine123");
    xml_ora_time(fp, "2017-11-09 09:20:17");
    xml_ora_program(fp, "plsqldev");
    xml_ora_datalist(fp, 1);
    xml_ora_recode(fp, 1, 1);
    xml_ora_schema(fp, "redosync");
    xml_tab_name(fp, "employee");
    xml_tab_action(fp, "insert");
	xml_ora_recode(fp, 0, 0);
    xml_ora_datalist(fp, 0);
    xml_ora_transaction(fp, 0, 0, 0);
    xml_fzs_root(fp, 0);
    fclose(fp);

}


int main(){
	irqdrp2xml();
}
