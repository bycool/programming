#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dbus/dbus.h>

DBusConnection*    conn;
DBusMessage*       msg;
DBusMessageIter    args;
DBusError          err;

void dbus_daemon_recv(void* data){
	int err = -1;

	dbus_error_init(&err);

	conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
	
}

int mdbus_init(){
	int ret = 0;
	char* recvmsg = NULL;

	dbus_error_init(&err);

	conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
	if(conn == NULL){
		ret = -1;
		goto err;
	}

	ret = dbus_bus_request_name(conn, "mydbus.daemon.conn", DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
	if(ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER){
		ret = -1;
		goto err;
	}

err:
	if(dbus_error_is_set(&err)){
		fprintf(stderr, "Connection Error [%s]\n", err.message);
		dbus_error_free(&err);
	}
}

int init_process(){
		
}

int exit_process(){

}

int main(void){

}
