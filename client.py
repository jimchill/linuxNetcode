import socket
import time

HOST = '#.#.#.#'  #指服务端IP地址
PORT = 8001  #端口号
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST,PORT))  #注意，在客户端是连接connect，而在服务端是bind
time.sleep(2)
sock.send(b'1')  #发送信息
print(sock.recv(1024).decode()) #打印接收消息，并且译码
sock.close() #关闭连接
