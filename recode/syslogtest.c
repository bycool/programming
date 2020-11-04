#include <syslog.h> 

int main(int argc, char **argv) 
{ 
    syslog(LOG_ERR|LOG_USER,"test - %m/n"); 
    openlog("1.log", LOG_CONS | LOG_PID, 0); 
    syslog(LOG_ERR,"This is a syslog test message generated by program '%s'/n",argv[0]); 
    closelog(); 
    return 0; 
}