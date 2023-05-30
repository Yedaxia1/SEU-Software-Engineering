'''
    Date: 2021/06/19
    Author: 叶宏庭
'''

# 导入必要的库包
import sys
import socket 
import time
import _thread
import os
from PyQt5 import QtCore
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

# 定义组播网络参数
ANY = '0.0.0.0'
SENDERPORT=1501                     # 发送消息所用端口
MCAST_ADDR = '224.168.2.9'          # 组播消息地址
MCAST_ADDR_FILE = '235.2.3.4'       # 组播文件地址
MCAST_PORT_MSG = 1600               # 组播消息端口
MCAST_PORT_FILE = 1700              # 组播文件端口

# 组播聊天工具UI类
class MultiCastGUI(QWidget):
    
    def __init__(self):
        super().__init__()
        
        # 组播成员组
        self.group_mem = []

        # 链接标志位
        self.connect_flag = False

        # 初始化UI界面
        self.initUI()               
    
    # 初始化UI界面
    def initUI(self):      
        # 控制按钮
        btn1 = QPushButton("Send message", self)
        btn1.move(30, 50)

        btn2 = QPushButton("Choose file...", self)
        btn2.move(150, 50)

        btn3 = QPushButton("JOIN", self)
        btn3.resize(80,30)
        btn3.move(300, 50)

        btn4 = QPushButton("QUIT", self)
        btn4.resize(80,30)
        btn4.move(390, 50)

        # 绑定控制函数
        btn1.clicked.connect(self.sendButtonClicked)            
        btn2.clicked.connect(self.choose_file)
        btn3.clicked.connect(self.join_group)
        btn4.clicked.connect(self.quit_group)

        # 信息输入框
        self.le = QLineEdit(self)
        self.le.setPlaceholderText("Enter message...")
        self.le.setGeometry(40,20,250,20)
        self.le.move(50, 22)

        # 信息列表显示
        self.msglist = QListWidget(self)
        self.msglist.itemClicked.connect(self.checkItem_msg)
        self.msglist.setGeometry(40,20,400,150)
        self.msglist.move(30, 100)

        # 组成员列表显示
        self.userlist = QListWidget(self)
        self.userlist.itemClicked.connect(self.checkItem_gml)
        self.userlist.setGeometry(70,20,400,150)
        self.userlist.move(30, 280)
        #self.statusBar()     
        
        self.setGeometry(300, 300, 500, 500)
        self.setWindowTitle('Event sender')
        self.show()
        
    # 初始化网络参数
    def initNetConfig(self):
        # 修改链接标志位
        self.connect_flag = True

        # 配置发送套接字
        self.send_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP) 
        self.send_sock.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
        self.send_sock.bind((ANY,SENDERPORT)) #绑定发送端口到SENDERPORT，即此例的发送端口为1501
        self.send_sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 255) #设置使用多播发送
        self.send_sock.setsockopt(socket.IPPROTO_IP,socket.IP_MULTICAST_LOOP, False) #设置回环地址
        # self.sock.sendto(bytes(s, encoding="utf8"), (MCAST_ADDR,MCAST_PORT) ); #将'hello world'发送到多播地址的指定端口，属于这个多播组的成员都可以收到这个信息

        # 配置消息接收套接字
        self.rece_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP) #创建UDP socket
        self.rece_sock.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1) #允许端口复用 
        self.rece_sock.bind((ANY,MCAST_PORT_MSG)) #绑定监听多播数据包的端口
        self.rece_sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 255) #告诉内核这是一个多播类型的socket
        self.rece_sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_LOOP, False)   #设置回环地址
        status = self.rece_sock.setsockopt(socket.IPPROTO_IP,  #告诉内核把自己加入指定的多播组，组地址由第三个参数指定
            socket.IP_ADD_MEMBERSHIP, 
            socket.inet_aton(MCAST_ADDR) + socket.inet_aton(ANY));
        self.rece_sock.setblocking(0) 

        # 配置文件接收套接字
        self.rece_file_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP) #创建UDP socket
        self.rece_file_sock.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1) #允许端口复用 
        self.rece_file_sock.bind((ANY,MCAST_PORT_FILE)) #绑定监听多播数据包的端口
        self.rece_file_sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 255) #告诉内核这是一个多播类型的socket
        self.rece_file_sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_LOOP, False) #设置回环地址
        status = self.rece_file_sock.setsockopt(socket.IPPROTO_IP,  #告诉内核把自己加入指定的多播组，组地址由第三个参数指定
            socket.IP_ADD_MEMBERSHIP, 
            socket.inet_aton(MCAST_ADDR_FILE) + socket.inet_aton(ANY));
        self.rece_file_sock.setblocking(0) 

        '''
            开启监听线程
            1 user_msg：定时推送组成员信息
            2 rece_msg_thread：监听消息收取
            3 rece_file_thread：监听文件收取
        '''
        self.user_msg = _thread.start_new_thread(self.send_user_msg, ())
        self.rece_msg_thread = _thread.start_new_thread(self.rece_message, ())
        self.rece_file_thread = _thread.start_new_thread(self.rece_file, ())

    # 加入多播组
    def join_group(self):
        if not self.connect_flag:
            self.initNetConfig()
            self.group_mem.append(socket.gethostbyname(socket.gethostname()))
            self.update_group_mem_list()
    
    # 退出多播组
    def quit_group(self):
        if self.connect_flag:
            # 发送退组信息
            self.send_sock.sendto(bytes("ctl_msg" + "#QUIT", encoding="utf8"), (MCAST_ADDR,MCAST_PORT_MSG) );

            # 关闭网络配置
            self.connect_flag = False
            self.send_sock.close()
            self.rece_sock.close()
            self.rece_file_sock.close()
            self.group_mem.clear()
            self.update_group_mem_list()

    
    # 发送按钮控制函数
    def sendButtonClicked(self):
        message_to_send = self.le.text()

        # TODO 发送str
        self.send_sock.sendto(bytes("normal_msg#"+message_to_send, encoding="utf8"), (MCAST_ADDR,MCAST_PORT_MSG) );

        self.shows("You send: " + message_to_send)

        self.le.clear()
        #self.statusBar().showMessage(message_to_send + ' was pressed')

    # 定时发送组成员信息
    def send_user_msg(self):
        while True:
            self.send_sock.sendto(bytes("ctl_msg" + "#update", encoding="utf8"), (MCAST_ADDR,MCAST_PORT_MSG) );
            time.sleep(5)

    # 发送文件
    def sendFile(self, filePath, filename):
        count = 0
        f = open(filePath, 'rb')
        while True:
            if count == 0:
                data = bytes(filename, encoding = "utf8")
                self.send_sock.sendto(data,(MCAST_ADDR_FILE,MCAST_PORT_FILE))
                print(data)
            
            data = f.read(1024)
            if str(data) != "b''":
                self.send_sock.sendto(data,(MCAST_ADDR_FILE,MCAST_PORT_FILE))
                #print(str(count)+'byte')

            else:
                self.send_sock.sendto('end'.encode('utf-8'),(MCAST_ADDR_FILE,MCAST_PORT_FILE))
                break
            #data, server_addr = self.send_sock.recvfrom(1024)
            count+=1

        self.shows(filename + " send successful!")
    
    # 监听消息收取
    def rece_message(self):
        
        while True: 
            if not self.connect_flag:
                break
            try: 
                data, addr = self.rece_sock.recvfrom(1024) 
                #print('hhh')
                data = bytes.decode(data).split("#")
                ctl = data[0]
                if ctl == "ctl_msg":
                    # TODO 组成员更新
                    if data[1] == "update":
                        if addr[0] not in self.group_mem:
                            print(addr)
                            self.group_mem.append(addr[0])
                            self.update_group_mem_list()
                    elif data[1] == "QUIT":
                        if addr[0] in self.group_mem:
                            self.group_mem.remove(addr[0])
                            self.update_group_mem_list()

                else:
                    self.add_items(addr, "".join(data[1:]))
            except socket.error: 
                pass 

    # 监听文件收取
    def rece_file(self):
        while True:
            if not self.connect_flag:
                break
            filename = ''
            count = 0

            while True:
                if not self.connect_flag:
                    break
                try:
                    if count == 0:
                        data,client_addr = self.rece_file_sock.recvfrom(1024)
                        #print('connected from %s:%s'%client_addr)
                        filename = str(data, encoding = "utf-8")
                        print(data)
                        f = open(data, 'wb')
                    data, client_addr = self.rece_file_sock.recvfrom(1024)
                    if str(data) != "b'end'":
                        f.write(data)
                        #print('recieved '+str(count)+' byte')
                    else:
                        break
                    #self.rece_file_sock.sendto('ok'.encode('utf-8'),client_addr)
                    count+=1
                except socket.error: 
                    pass 
            if not self.connect_flag:
                    break
            self.shows('successfullu rece file: '+ filename)
            #print('successfullu rece file: '+filename)
            f.close()
    
    # 更新组成员列表
    def update_group_mem_list(self):
        self.userlist.clear()
        for mem in self.group_mem:
            item = QListWidgetItem(mem)
            self.userlist.addItem(item)

    # 列表点击控制
    def checkItem_msg(self,index):
         QMessageBox.information(self,"MSG_LIST_VIEW","MSG: " + (index.text()))

    # 列表点击控制
    def checkItem_gml(self,index):
         QMessageBox.information(self,"GOURP_MEM_LIST_VIEW","User: " + (index.text()))
    
    # 选择文件
    def choose_file(self):
        get_filename_path, ok = QFileDialog.getOpenFileName(self,
                                    "选取单个文件",
                                   "C:/",
                                    "All Files (*);;Text Files (*.txt)")
        if ok: 
            fi = QFileInfo(get_filename_path)
            file_name = fi.fileName()
            self.get_file_result(str(file_name))
            self.sendFile(get_filename_path, file_name)
    
    # 列表项添加
    def shows(self, msg):
        item = QListWidgetItem(msg)
        self.msglist.addItem(item)

    # 文件收取成功
    def get_file_result(self, path):
        item_text = "File get successful. " + path
        self.shows(item_text)

    # 列表项添加
    def add_items(self, address, data):
        item_text = "Receive msg: '{}', from: {}".format(data,address)
        self.shows(item_text)

# 程序运行
if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = MultiCastGUI()
    sys.exit(app.exec_())