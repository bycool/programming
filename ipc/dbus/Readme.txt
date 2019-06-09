dbus总结:
dbus是一种ipc，进程间通信方式。主要通过dbus daemon进程来帮助进程间的通信。
1.接收信号：
    1.1.初始化error
        dbus_error_init(&err); //初始化DBusError结构体实例
    1.2.连接上bus daemon并检查err 
        dbus_bus_get(DBUS_BUS_SESSION,&err);
        dbus_error_is_set(&err);
    1.3.为连接上bus daemon的connection命名
        dbus_bus_request_name(conn,"mydbus.signal.receive",DBUS_NAME_FLAG_REPLACE_EXISTING,&err);
    1.4.添加规则
        dbus_bus_add_match(conn, "type='signal',interface='mydbus.signal.Type'",&err);
    1.5.循环监听conn连接发来的信号
        dbus_connection_read_write(conn, 0);
        msg = dbus_connection_pop_message(conn);
        dbus_message_is_signal(msg,"mydbus.signal.Type","Test")；
        dbus_message_iter_get_basic(&args, &sigvalue);
        
2.发送信号：
    2.1初始化error
        dbus_error_init(&err);
    2.2连接上bus daemon并检查err
        dbus_bus_get(DBUS_BUS_SESSION,&err);
    2.3为连接上bus daemon的connection命名
        dbus_bus_request_name(conn,"mydbus.sigal.source", DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
    2.4创建信号
        msg = dbus_message_new_signal("/mydbus/signal/Object","mydbus.signal.Type","Test");
    2.5添加参数
    dbus_message_iter_init_append(msg, &args);
    dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &sigvalue)
    2.6发送信号
    dbus_connection_send(conn, msg, &serial)

        


