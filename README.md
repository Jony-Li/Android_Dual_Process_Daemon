# Android_Dual_Process_Daemon
# Android双进程守护设计方案
  * Java层实现双进程守护——容易被系统杀死；
  * 轮询方式——消耗系统性能，容易被系统杀死；
  * 类似百度全家桶模式应用之间相互启动——手机厂商优化Framework APP的进程启动方式，导致守护进程不能正常启动；
  * NDK socket通信——目前Android最有效的方式（手机厂商修改Linux内核成本较高）；
  * 加入手机厂商的白名单——非技术方式

# Android NDK双进程守护设计思路
![image](https://github.com/Jony-Li/Android_Dual_Process_Daemon/blob/master/linux-socket.jpg)


# 效果展示
![image](https://github.com/Jony-Li/Android_Dual_Process_Daemon/blob/master/Android_Dual_Process_Daemon.gif)