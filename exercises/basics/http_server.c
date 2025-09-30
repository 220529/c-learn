// 简单的 HTTP 服务器 - 监听 8080 端口，返回 HTML 页面
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")  // 链接 Winsock 库

#define PORT 8080
#define BUFFER_SIZE 4096

// HTTP 响应模板
const char* HTTP_RESPONSE = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html; charset=utf-8\r\n"
    "Connection: close\r\n"
    "\r\n"
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "<meta charset='UTF-8'>"
    "<title>C 语言 HTTP 服务器</title>"
    "<style>"
    "body { font-family: Arial; max-width: 800px; margin: 50px auto; padding: 20px; background: #f0f0f0; }"
    "h1 { color: #333; }"
    ".info { background: white; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }"
    "code { background: #e0e0e0; padding: 2px 6px; border-radius: 3px; }"
    "</style>"
    "</head>"
    "<body>"
    "<div class='info'>"
    "<h1>🎉 你的 C 语言 HTTP 服务器运行成功！</h1>"
    "<p>✅ 这个页面由 <code>http_server.c</code> 生成</p>"
    "<p>📍 服务器地址: <code>http://localhost:8080</code></p>"
    "<p>🔧 端口: <code>8080</code></p>"
    "<p>💡 这是一个用纯 C 语言写的 Web 服务器</p>"
    "<hr>"
    "<p><strong>技术栈:</strong></p>"
    "<ul>"
    "<li>语言: C</li>"
    "<li>Socket: Winsock2</li>"
    "<li>协议: HTTP/1.1</li>"
    "</ul>"
    "</div>"
    "</body>"
    "</html>";

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    
    printf("===================================\n");
    printf("  C 语言 HTTP 服务器\n");
    printf("===================================\n\n");
    
    // 1. 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("❌ Winsock 初始化失败! 错误码: %d\n", WSAGetLastError());
        return 1;
    }
    printf("✅ Winsock 初始化成功\n");
    
    // 2. 创建 Socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("❌ Socket 创建失败! 错误码: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("✅ Socket 创建成功\n");
    
    // 3. 配置服务器地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // 监听所有网卡
    server_addr.sin_port = htons(PORT);         // 端口 8080
    
    // 4. 绑定端口
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("❌ 端口绑定失败! 错误码: %d\n", WSAGetLastError());
        printf("💡 提示: 端口 %d 可能被占用，请关闭占用该端口的程序\n", PORT);
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    printf("✅ 端口 %d 绑定成功\n", PORT);
    
    // 5. 开始监听
    if (listen(server_socket, 5) == SOCKET_ERROR) {
        printf("❌ 监听失败! 错误码: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    
    printf("\n🚀 服务器启动成功!\n");
    printf("📡 监听地址: http://localhost:%d\n", PORT);
    printf("💡 在浏览器中打开上面的地址访问\n");
    printf("⏹️  按 Ctrl+C 停止服务器\n");
    printf("\n等待连接...\n\n");
    
    // 6. 主循环：接受连接并处理请求
    while (1) {
        // 接受客户端连接
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket == INVALID_SOCKET) {
            printf("❌ 接受连接失败! 错误码: %d\n", WSAGetLastError());
            continue;
        }
        
        // 接收 HTTP 请求
        int recv_size = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (recv_size > 0) {
            buffer[recv_size] = '\0';
            
            // 解析请求首行（GET /xxx HTTP/1.1）
            char method[16], path[256], protocol[16];
            sscanf(buffer, "%s %s %s", method, path, protocol);
            
            printf("📥 [%s] %s %s\n", 
                   inet_ntoa(client_addr.sin_addr), method, path);
            
            // 发送 HTTP 响应
            send(client_socket, HTTP_RESPONSE, strlen(HTTP_RESPONSE), 0);
        }
        
        // 关闭连接
        closesocket(client_socket);
    }
    
    // 7. 清理（实际上这段代码不会执行，因为上面是无限循环）
    closesocket(server_socket);
    WSACleanup();
    
    return 0;
}
