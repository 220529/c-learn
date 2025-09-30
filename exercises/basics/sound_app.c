// 声音控制小应用 - 显示真实状态并切换
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <initguid.h>

// 定义COM接口GUID
DEFINE_GUID(CLSID_MMDeviceEnumerator_Local, 0xBCDE0395, 0xE52F, 0x467C, 0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E);
DEFINE_GUID(IID_IMMDeviceEnumerator_Local, 0xA95664D2, 0x9614, 0x4F35, 0xA7, 0x46, 0xDE, 0x8D, 0xB6, 0x36, 0x17, 0xE6);
DEFINE_GUID(IID_IAudioEndpointVolume_Local, 0x5CDF2C82, 0x841E, 0x4546, 0x97, 0x22, 0x0C, 0xF7, 0x40, 0x78, 0x22, 0x9A);

#define ID_BUTTON 1

HWND hButton;

// 获取当前静音状态：TRUE=静音, FALSE=开启
BOOL isMuted() {
    BOOL muted = FALSE;
    CoInitialize(NULL);
    
    IMMDeviceEnumerator *enumerator = NULL;
    IMMDevice *device = NULL;
    IAudioEndpointVolume *volume = NULL;
    
    // 创建设备枚举器
    if (CoCreateInstance(&CLSID_MMDeviceEnumerator_Local, NULL, CLSCTX_ALL,
                        &IID_IMMDeviceEnumerator_Local, (void**)&enumerator) == S_OK) {
        // 获取默认音频设备
        if (enumerator->lpVtbl->GetDefaultAudioEndpoint(enumerator, eRender, eConsole, &device) == S_OK) {
            // 激活音量控制接口
            if (device->lpVtbl->Activate(device, &IID_IAudioEndpointVolume_Local,
                                        CLSCTX_ALL, NULL, (void**)&volume) == S_OK) {
                // 获取静音状态
                volume->lpVtbl->GetMute(volume, &muted);
                volume->lpVtbl->Release(volume);
            }
            device->lpVtbl->Release(device);
        }
        enumerator->lpVtbl->Release(enumerator);
    }
    
    CoUninitialize();
    return muted;
}

// 更新按钮文字
void updateButton() {
    if (isMuted()) {
        SetWindowText(hButton, "已静音\n(点击开启)");
    } else {
        SetWindowText(hButton, "声音开启\n(点击静音)");
    }
}

// 窗口消息处理
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            hButton = CreateWindow("BUTTON", "检测中...", 
                                  WS_VISIBLE | WS_CHILD | BS_MULTILINE | BS_CENTER,
                                  15, 15, 130, 50, hwnd, (HMENU)ID_BUTTON, NULL, NULL);
            // 延迟100ms后更新状态
            SetTimer(hwnd, 1, 100, NULL);
            break;
            
        case WM_TIMER:
            KillTimer(hwnd, 1);
            updateButton();  // 初始化显示真实状态
            break;
            
        case WM_COMMAND:
            if (LOWORD(wp) == ID_BUTTON) {
                // 切换静音
                keybd_event(VK_VOLUME_MUTE, 0, 0, 0);
                keybd_event(VK_VOLUME_MUTE, 0, KEYEVENTF_KEYUP, 0);
                Sleep(50);  // 等待系统响应
                updateButton();  // 更新显示
            }
            break;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

// 程序入口
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmd, int show) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "Sound";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);
    
    HWND hwnd = CreateWindow("Sound", "声音控制",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT, 180, 130,
        NULL, NULL, hInst, NULL);
    
    ShowWindow(hwnd, show);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
    }
    return 0;
}