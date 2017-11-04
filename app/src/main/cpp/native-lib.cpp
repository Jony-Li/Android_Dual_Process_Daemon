#include <jni.h>
#include <string>
#include "native_lib.h"

int m_child;
const char *userId;
//定义一个文件
const char *PATH = "/data/data/com.jony.rswh.android_dual_process_daemon/my.socket";

void child_do_work(){
    LOGE("child_do_work");
    //建立socket  服务端
    if(child_create_channel()){
        child_listen_msg();
    }
}

/**
 * 服务端读取信息
 * 读取客户端信息
 */
void child_listen_msg() {
    LOGE("child_listen_msg");
    fd_set rfds;
    struct timeval timeout = {3,0};//3s 超时
    while (1){// 阻塞式函数 不会一直执行死循环
        //清空客户端内容
        FD_ZERO(&rfds);
        //重新设置客户端内容  &rfds 取地址
        FD_SET(m_child,&rfds);
        //m_child+1 一般是文件数 + 1
        int r = select(m_child+1,&rfds,NULL,NULL,&timeout);
        LOGE("读取消息前 %d ",r);
        if (r > 0){
            //设置缓冲区大小
            char pkg[256] = {0};
            //保证所读到的信息是指定APK客户端的信息
            if(FD_ISSET(m_child,&rfds)){
                //阻塞式函数 read
                int result = read(m_child,pkg, sizeof(pkg));
                LOGE("userId %s ",userId);
                //开启服务  adb shell am start -a android.intent.action.CALL -d tel:112
                //Linux 可以通过发送命令启动Action
                //使用am命令启动服务  360 卸载问卷调查也是采用类似的方式实现
                execlp("am","am","startservice","--user",userId,
                       "com.jony.rswh.android_dual_process_daemon/com.jony.rswh.android_dual_process_daemon.ProcessService",
                       (char*)NULL);
                break;
            }
        }
    }
}

/**
 * 创建服务端的socket
 */
int child_create_channel() {
    LOGE("child_create_channel");
    //C语言中可以理解int皆对象  句柄
    //IP 端口号 文件
    int listenfd=socket(AF_LOCAL,SOCK_STREAM,0);
    unlink(PATH);//清除之前创建的连接
    // addr --> 内存区域
    struct sockaddr_un addr;
    //清空内存
    memset(&addr,0, sizeof(sockaddr_un));
    addr.sun_family = AF_LOCAL;

    int connfd=0;
    //做内存拷贝
    strcpy(addr.sun_path,PATH);
    if (bind(listenfd,(const sockaddr * )&addr, sizeof(sockaddr_un)) < 0){
        LOGE("绑定错误……");
        return 0;
    }
    listen(listenfd,5);//最大监听5个客户端
    //保证宿主进程连接成功 百度全家桶应用
    while (1){
        // 返回值 客户端地址  阻塞式函数
        connfd = accept(listenfd,NULL,NULL);
        if((connfd = accept(listenfd,NULL,NULL)) < 0){
            if (errno == EINTR){
                continue;
            } else{
                LOGE("读取错误……");
                return 0;
            }
        }
        m_child = connfd;



        LOGE("apk 父进程连接上了 %d ",m_child);
        break;
    }
    return 1;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jony_rswh_android_1dual_1process_1daemon_WatchDog_connectMonitor(JNIEnv *env,
                                                                          jobject /* this */) {
    //该方法运行在客户端进程 APK进程
    int socked;
    // addr -->内存区域
    struct sockaddr_un addr;
    while (1){
        LOGE("客户端 父进程开始连接……");
        socked = socket(AF_LOCAL,SOCK_STREAM,0);
        if (socked < 0){
            LOGE("连接失败……");
            return;
        }
        //清空内存
        memset(&addr,0, sizeof(sockaddr));
        addr.sun_family = AF_LOCAL;
        strcpy(addr.sun_path,PATH);
        if(connect(socked, (const sockaddr *) &addr, sizeof(sockaddr_un)) < 0){
            LOGE("连接失败……");
            close(socked);
            sleep(1);//休眠1s，再次尝试连接，直到连接成功
            continue;
        }
        LOGE("连接成功……");
        break;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jony_rswh_android_1dual_1process_1daemon_WatchDog_createWatchDog(JNIEnv *env,
                                                                          jobject instance,
                                                                          jstring userId_) {
    userId = env->GetStringUTFChars(userId_, 0);
    LOGE("userId %s ",userId);
    //开启双进程
    pid_t pid=fork();

    LOGE("pid %d ",pid);

    if (pid<0){//代表进程fork失败

    } else if(pid == 0){//子进程 守护进程
        child_do_work();
    }else if(pid > 0){//代表父进程
        //child_do_work();

    }
    env->ReleaseStringUTFChars(userId_, userId);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jony_rswh_android_1dual_1process_1daemon_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject instance) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
