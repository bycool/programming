dbus总结:
dbus是一种ipc，进程间通信方式。主要通过dbus daemon进程来帮助进程间的通信。
1.接收信号：
    1.1.初始化error
        dbus_error_init(&err); //初始化DBusError结构体实例
    1.2.连接上bus daemon并检查err                             （我得先跟邮局联系）
        dbus_bus_get(DBUS_BUS_SESSION,&err);
        dbus_error_is_set(&err);
    1.3.为连接上bus daemon的connection命名                     （告诉邮局我的联系方式）
        dbus_bus_request_name(conn,"mydbus.signal.receive",DBUS_NAME_FLAG_REPLACE_EXISTING,&err);
    1.4.添加规则                                               （告诉邮局我在等一个邮寄到mydbus.signal.Type地方的快递）
        dbus_bus_add_match(conn, "type='signal',interface='mydbus.signal.Type'",&err);
    1.5.循环监听conn连接发来的信号                                 （我时常翻阅邮局里收到的快递）
        dbus_connection_read_write(conn, 0);
        msg = dbus_connection_pop_message(conn);
        dbus_message_is_signal(msg,"mydbus.signal.Type","Test")；（看看有没有发送到mydbus.signal.Type的Test的邮件）
        dbus_message_iter_get_basic(&args, &sigvalue);           （有，我就取出快递里的东西）
        
2.发送信号：
    2.1初始化error
        dbus_error_init(&err);
    2.2连接上bus daemon并检查err                              （先和邮局取得联系)
        dbus_bus_get(DBUS_BUS_SESSION,&err);
    2.3为连接上bus daemon的connection命名                      （告诉邮局我的联系方式）
        dbus_bus_request_name(conn,"mydbus.sigal.source", DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
    2.4创建信号                                               （在邮局下个订单，邮寄给“mydbus.signal.Type”的“Test”）
        msg = dbus_message_new_signal("/mydbus/signal/Object","mydbus.signal.Type","Test");
    2.5添加参数                                               （往订单的袋子里放好要邮寄的东西）          
    dbus_message_iter_init_append(msg, &args);
    dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &sigvalue)
    2.6发送信号                                               （把订单发出去）
    dbus_connection_send(conn, msg, &serial)

        


