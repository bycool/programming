#include <dbus/dbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void Usage(){
	printf("Usage: mydbus [recv | send]\n");
}

void sender(char* msgval){
	DBusConnection* conn;
	DBusMessage* msg;
	DBusMessageIter args;
	DBusError err;

	int ret = -1;

	fprintf(stdout, "msgval: %s\n", msgval);

	dbus_uint32_t serial = 0;

	dbus_error_init(&err);

	conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
	if(dbus_error_is_set(&err)){
		fprintf(stderr, "Connection err[%s]\n", err.message);
		dbus_error_free(&err);
	}

	if(conn == NULL)
		exit(1);

	ret = dbus_bus_request_name(conn, "mydbus.send.conn", DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
	if(dbus_error_is_set(&err)){
		fprintf(stderr, "Name err[%s]\n", err.message);
		dbus_error_free(&err);
	}
	if ( DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret )
        exit(1);

	msg = dbus_message_new_signal(	"/mydbus/send/msg",
									"mydbus.sender.msg",
									"send"
									);
	if(msg == NULL)
		exit(1);

	

	dbus_message_iter_init_append(msg, &args);
	if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &msgval)){
		fprintf(stderr, "Out of Memery\n");
		exit(1);
	}
	
	if (!dbus_connection_send(conn, msg, &serial)){
		fprintf(stderr, "Out Of Memory!");
		exit(1);
	}

	dbus_connection_flush(conn);
	dbus_message_unref(msg);
}

void recver(){
	DBusConnection* conn;
	DBusMessage* msg;
	DBusMessageIter args;
	DBusError err;

	int ret = -1;
	char* recvmsg = NULL;

	dbus_error_init(&err);

	conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
	if (dbus_error_is_set(&err)) {
		fprintf(stderr,"Connection Error [%s]\n",err.message);
		dbus_error_free(&err);
	}
	if(NULL == conn)
		exit(1);

	ret = dbus_bus_request_name(conn, "mydbus.recver.conn",DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
	if(dbus_error_is_set(&err)){
        fprintf(stderr,"Name error [%s]\n",err.message);
        dbus_error_free(&err);
    }
    if(ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)
        exit(1);

    dbus_bus_add_match(conn, "type='signal',interface='mydbus.sender.msg'",&err);
    dbus_connection_flush(conn);
    if(dbus_error_is_set(&err)){
        fprintf(stderr,"Match Error [%s]\n",err.message);
        exit(1);
    }

    while(1){

        dbus_connection_read_write(conn, 0);
        msg = dbus_connection_pop_message(conn);

        if(msg == NULL){
            sleep(1);
            continue;
        }

        if(dbus_message_is_signal(msg,"mydbus.sender.msg","send")){
            if (!dbus_message_iter_init(msg, &args))
                fprintf(stderr,"Message has no parameters\n");
            else if (DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&args))
                fprintf(stderr,"Argument is not string\n");
            else
                dbus_message_iter_get_basic(&args, &recvmsg);

            printf("Got signal with value %s\n", recvmsg);
        }

        dbus_message_unref(msg);
    }


}

void main(int argc, char** argv){
	if(argc < 2){
		Usage();
		return ;
	}

	if(argc >= 2 && argv[1] != NULL){
		if( strcmp(argv[1], "send") == 0){
			printf("send\n");
			sender(argv[2]);
		}else if( strcmp(argv[1], "recv") == 0){
			printf("recv\n");
			recver();
		}else
			printf("err parm\n");
	}
}
