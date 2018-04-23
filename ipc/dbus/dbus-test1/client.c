
#include <glib.h>    
#include <dbus/dbus.h>  
#include <stdbool.h>  
#include <unistd.h>  
#include <stdio.h>  
#include <stdlib.h>   
#include <dbus/dbus-glib.h> 
#include <pthread.h>

static DBusConnection *connect;  
  
static gpointer mainloop(gpointer user_data);  
static DBusHandlerResult filter_func (DBusConnection *connection, DBusMessage *message, void *user_data) ;  
static int method_get(DBusConnection *dbconn,int a,int b);  
  
int main(int argc, char **argv)  
{  
    DBusError dberr;  
    DBusConnection *dbconn;  
    DBusMessage *msg;  
    DBusMessageIter args;  
    int ret;  
    pthread_t tid;  
  
    pthread_create(&tid,NULL,mainloop,NULL);  
    dbus_error_init (&dberr);  
    connect = dbconn = dbus_bus_get (DBUS_BUS_SESSION, &dberr);  
  
    if (dbus_error_is_set (&dberr)){  
        printf ("getting session bus failed: %s\n", dberr.message);  
        dbus_error_free (&dberr);  
        return EXIT_FAILURE;  
    }  
  
    if(connect == NULL){  
        printf ("connect bus failed: %s\n", dberr.message);  
        return EXIT_FAILURE;  
    }  
  
    ret = dbus_bus_request_name (dbconn, "com.wq.test.client",DBUS_NAME_FLAG_REPLACE_EXISTING, &dberr);  
  
    if (dbus_error_is_set (&dberr)){  
        printf ("requesting name failed: %s\n", dberr.message);  
        dbus_error_free (&dberr);  
        return EXIT_FAILURE;  
    }  
  
    if(ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER){  
        printf ("request name failed: %s\n", dberr.message);  
        return EXIT_FAILURE;  
    }  
  
    dbus_bus_add_match(dbconn,"type='signal',interface='com.wq.test'",&dberr);  
  
    while(1){   
        dbus_connection_read_write (dbconn,0);  
        msg = dbus_connection_pop_message (dbconn);  
        if(msg == NULL){  
            usleep(1000);  
            continue;  
        }   
  
        filter_func (dbconn,msg,NULL);  
        dbus_message_unref(msg);   
  
    }  
  
    return EXIT_SUCCESS;  
}  
  
  
static int method_get(DBusConnection *dbconn,int a,int b)  
{  
    DBusMessage *msg;  
    DBusMessageIter arg;  
    DBusPendingCall *pending;  
    DBusMessage *reply;  
    int result;  
    DBusError dberr;  
  
    dbus_error_init(&dberr);  
    msg = dbus_message_new_method_call ("com.wq.test", "/com/wq/test","com.wq.test", "METHODTEST");  
  
    if(msg == NULL){  
        printf("Message NULL\n");  
        return;  
    }   
  
    dbus_message_append_args ( msg, DBUS_TYPE_INT32, &a, DBUS_TYPE_INT32, &b, DBUS_TYPE_INVALID);  
    reply = dbus_connection_send_with_reply_and_block (dbconn, msg, -1, &dberr);  
  
    if (!reply){  
        printf("couldn't send message: %s\n", dberr.message);  
    }   
  
    dbus_message_unref (msg);  
  
    if (!dbus_message_get_args (reply, &dberr, DBUS_TYPE_INT32, &result, DBUS_TYPE_INVALID)){  
        return 0;  
    }  
  
    /*dbus_message_iter_init_append(msg, &arg);  
    if(!dbus_message_iter_append_basic (&arg, DBUS_TYPE_INT32,&a)){ 
        printf("client Out of Memory1!\n"); 
        return 0;  
    } 
 
    if(!dbus_message_iter_append_basic (&arg, DBUS_TYPE_INT32,&b)){ 
        printf("client Out of Memory2!\n"); 
        return 0;  
    } 
 
    if(!dbus_connection_send_with_reply (dbconn, msg,&pending, -1)){  
        printf("client Out of Memory3!\n"); 
        return 0; 
    }       
 
    if(pending == NULL){ 
        printf("Pending Call NULL: connection is disconnected \n"); 
        dbus_message_unref(msg); 
        return 0; 
    }  
 
    dbus_connection_flush(dbconn); 
    dbus_message_unref(msg);  
    dbus_pending_call_block (pending);  
    msg = dbus_pending_call_steal_reply (pending);  
 
    if (msg == NULL) { 
        printf("Reply Null\n"); 
        return 0; 
    } 
 
    dbus_pending_call_unref(pending);  
 
    if (!dbus_message_iter_init(msg, &arg))  
        fprintf(stderr, "Message has no arguments!\n"); 
    else if ( dbus_message_iter_get_arg_type (&arg) != DBUS_TYPE_INT32) 
        fprintf(stderr, "Argument is not boolean!\n"); 
    else 
        dbus_message_iter_get_basic (&arg, &result); 
 
    dbus_message_unref(msg); */  
  
    return result;  
}  
  
  
static DBusHandlerResult filter_func (DBusConnection *connection, DBusMessage *message,void *user_data)    
{    
    if (dbus_message_is_signal (message, "com.wq.test", "TESTSINGAL")) {    
        DBusError error;    
        char *s;    
        dbus_error_init (&error);    
  
        if (dbus_message_get_args(message, &error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID)) {    
            printf("client received singal: %s\n", s);    
        }else {    
            printf("client received, but error getting message: %s\n", error.message);    
            dbus_error_free (&error);    
        }    
  
        return DBUS_HANDLER_RESULT_HANDLED;    
    }    
  
    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;    
}    
  
  
  
static gpointer mainloop(gpointer user_data)  
{  
    char input[256];  
    printf("enter 'm' to test method:");  
    while(1){  
        if(fgets(input, sizeof(input), stdin)){          
            if(input[0] == 'm'){  
                printf("please enter two number:\n");  
                int a;  
                int b;  
                scanf("%d %d",&a,&b);  
                int result = method_get(connect,a,b);  
                printf("result : %d\n",result);  
            }  
        }  
    }  
}
