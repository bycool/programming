
#include <dbus/dbus.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <dbus/dbus-glib.h>  
#include <stdbool.h>  
#include <pthread.h>

static DBusConnection *connect;  

static gpointer mainloop(gpointer user_data);  
static void send_singal(DBusConnection *dbconn,char *buf);  
static DBusHandlerResult filter_session_message (DBusConnection *connection,DBusMessage *message,void  *user_data);  
  
int main(int argc ,char **argv)  
{  
    DBusError dberr;  
    DBusConnection *dbconn;  
    DBusMessage *msg;  
    pthread_t tid;  
  
    dbus_error_init (&dberr);  
    pthread_create(&tid,NULL,mainloop,NULL);  
    connect = dbconn = dbus_bus_get (DBUS_BUS_SESSION, &dberr);  
    dbus_bus_request_name (dbconn, "com.wq.test",DBUS_NAME_FLAG_REPLACE_EXISTING, &dberr);  
  
  
    if (dbus_error_is_set (&dberr)){  
        printf ("getting session bus failed: %s\n", dberr.message);  
        dbus_error_free (&dberr);  
        return -1;  
    }  
  
    while(1){   
        dbus_connection_read_write (dbconn,0);  
        msg = dbus_connection_pop_message (dbconn);  
  
        if(msg == NULL){  
            usleep(1000);  
            continue;  
        }   
  
        filter_session_message (dbconn,msg,NULL);  
        dbus_message_unref(msg);   
    }  
  
    return 1;  
}  
  
static gpointer mainloop(gpointer user_data)  
{  
    char input[256];  
	printf("enter 's' to test singal:");  
  
    while(1){  
        if(fgets(input, sizeof(input), stdin)){          
            if(input[0] == 's'){  
                printf("please enter a string:\n");  
                char send[256];  
                scanf("%s", send);  
                send_singal(connect,send);  
            }  
        }  
    }  
}  
  
  
static void send_singal(DBusConnection *dbconn,char *buf)  
{  
    DBusMessage *dbmsg;  
    dbmsg = dbus_message_new_signal ("/com/wq/test","com.wq.test","TESTSINGAL");  
  
    if (!dbmsg){  
        printf ("Could not create a new signal\n");  
        return;  
    }  
  
    if (!dbus_message_append_args ( dbmsg, DBUS_TYPE_STRING, &buf, DBUS_TYPE_INVALID)){  
        printf("Out Of Memory!\n");  
        return;  
    }  
  
    if (!dbus_connection_send (dbconn, dbmsg, NULL)){  
        printf("Out Of Memory!\n");  
        return;  
    }  
    dbus_connection_flush(dbconn);  
}  
  
  
static DBusHandlerResult filter_session_message (DBusConnection *connection,DBusMessage *message,void  *user_data)  
{  
    int a = 0;  
    int b = 0;  
    int c = 0;  
  
    if (dbus_message_is_method_call (message,"com.wq.test","METHODTEST")){  
        dbus_message_get_args(message, NULL, DBUS_TYPE_INT32, &a, DBUS_TYPE_INT32,&b,DBUS_TYPE_INVALID);  
        printf("service get tow number: %d %d\n",a,b);  
        c = a + b;  
        DBusMessage *reply;  
        reply = dbus_message_new_method_return (message);  
        dbus_message_append_args (reply, DBUS_TYPE_INT32,&c, DBUS_TYPE_INVALID);  
        dbus_connection_send (connection, reply, NULL);  
        dbus_message_unref (reply);  
        return DBUS_HANDLER_RESULT_HANDLED;  
    }  
  
    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;  
} 
