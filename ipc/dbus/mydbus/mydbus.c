#include <stdio.h>
#include <dbus/dbus.h>
#include <dbus/dbus.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void sendsignal(char* sigvalue){
	DBusMessage* msg;
	DBusMessageIter args;
	DBusConnection* conn;
	DBusError err;
	int ret;

	dbus_uint32_t serial = 0;

	printf( "Sending: signal with value : [%s]\n",sigvalue);

	//1.初始化err结构体
	dbus_error_init(&err);

	//2.连接到DBUS system bus,conn则是当前进程和system bus的连接桥梁
	conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
	if (dbus_error_is_set(&err)) {
		fprintf(stderr, "Connection Error [%s]\n",err.message);
		dbus_error_free(&err);
	}
	if ( NULL == conn )
		exit(1);

	//3.给连接到DBUS system bus的connection注册一个名字
	ret = dbus_bus_request_name(conn, "mydbus.sigal.source", DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
	if ( dbus_error_is_set(&err) ){
		fprintf(stderr,"Name Error [%s]\n",err.message);
		dbus_error_free(&err);
	}
	if ( DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret )
		exit(1);

	//4.创建一个信号
	msg = dbus_message_new_signal("/mydbus/signal/Object",	//信号的对象名
								  "mydbus.signal.Type",		//信号的接口名
								  "Test");					//信号名
	if ( NULL == msg ){
		fprintf(stderr,"Message NULL\n");
		exit(1);
	}

	//5.给信号添加参数
	dbus_message_iter_init_append(msg, &args);
	if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &sigvalue)){
		fprintf(stderr,"Out Of Memory!\n");
		exit(1);
	}

	//6.发送信息
	if (!dbus_connection_send(conn, msg, &serial)){
		fprintf(stderr, "Out Of Memory!");
		exit(1);
	}
	dbus_connection_flush(conn);
	printf("Signal Sent\n");

	dbus_message_unref(msg);
}

void receive(){
	DBusMessage* msg;
	DBusMessageIter args;
	DBusConnection* conn;
	DBusError err;
	int ret;
	char* sigvalue;

	printf("Listening for sigvalue\n");

	//1.initialise the error
	dbus_error_init(&err);

	//2.connect to the bus daemon and check error
	conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
	if (dbus_error_is_set(&err)) {
		fprintf(stderr,"Connection Error [%s]\n",err.message);
		dbus_error_free(&err);
	}
	if(NULL == conn){
		exit(1);
	}

	//3.request our name on the bus,check for errors
	ret = dbus_bus_request_name(conn, "mydbus.signal.receive",DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
	if(dbus_error_is_set(&err)){
		fprintf(stderr,"Name error [%s]\n",err.message);
		dbus_error_free(&err);
	}
	if(ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER){
		exit(1);
	}

	//4.添加规则
	dbus_bus_add_match(conn, "type='signal',interface='mydbus.signal.Type'",&err);
	dbus_connection_flush(conn);
	if(dbus_error_is_set(&err)){
		fprintf(stderr,"Match Error [%s]\n",err.message);
		exit(1);
	}
	printf("Match rule send\n");

	//5.循环监听被发送的信号
	while(true){
		
		dbus_connection_read_write(conn, 0);
		msg = dbus_connection_pop_message(conn);

		if(msg == NULL){
			sleep(1);
			continue;
		}

		if(dbus_message_is_signal(msg,"mydbus.signal.Type","Test")){
			if (!dbus_message_iter_init(msg, &args))
				fprintf(stderr,"Message has no parameters\n");
			else if (DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&args))
				fprintf(stderr,"Argument is not string\n");
			else
				dbus_message_iter_get_basic(&args, &sigvalue);

			printf("Got signal with value %s\n",sigvalue);
		}

		dbus_message_unref(msg);
	}
}

int main(int argc, char** argv){
	if ( 2 > argc ){
		printf("Syntax: mydbus [send|receive|listen|query] [<param>]\n");
		return 1;
	}
	char* param = "no parm";
	if ( 3 >= argc && NULL != argv[2] )
		param = argv[2];
	if ( 0 == strcmp( argv[1],"send" ) )
		sendsignal( param );
	else if ( 0 == strcmp ( argv[1],"receive" ) )
		receive();
	else if ( 0 == strcmp ( argv[1],"query" ) )
	//	query( param );
		printf("query(param)\n");
	else if ( 0 == strcmp ( argv[1],"listen" ) )
	//	listen();
		printf("listen()\n");
	else {
		printf("Syntax: mydbus [send|receive|listen|query] [<param>]\n");
		return 1;
	}
	return 0;
}

