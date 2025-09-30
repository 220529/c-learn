#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        // 根据参数决定操作
        if (strcmp(argv[1], "on") == 0) {
            printf("*** 声音已开启 ***\n");
        } else if (strcmp(argv[1], "off") == 0) {
            printf("*** 声音已关闭 ***\n");
        } else {
            printf("用法: sound_toggle [on/off]\n");
            return 1;
        }
    } else {
        printf("*** 声音已切换 ***\n");
    }
    
    // 模拟按下静音键
    keybd_event(VK_VOLUME_MUTE, 0, 0, 0);
    keybd_event(VK_VOLUME_MUTE, 0, KEYEVENTF_KEYUP, 0);
    
    return 0;
}
