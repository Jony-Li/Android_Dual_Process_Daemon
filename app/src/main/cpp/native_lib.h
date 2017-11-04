//
// Created by Administrator on 2017/10/29 0029.
//

#ifndef ANDROID_DUAL_PROCESS_DAEMON_NATIVE_LIB_H
#define ANDROID_DUAL_PROCESS_DAEMON_NATIVE_LIB_H

#include <sys/select.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>
#include <android/log.h>
#include <sys/types.h>
#include <sys/un.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/signal.h>
void child_do_work();
int child_create_channel();
void child_listen_msg();

#define LOG_TAG "ANDROID_DAEMON"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif //ANDROID_DUAL_PROCESS_DAEMON_NATIVE_LIB_H