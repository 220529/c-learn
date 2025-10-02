#!/bin/bash
# 贪吃蛇 Mac App 打包脚本

APP_NAME="SnakeGame"
DISPLAY_NAME="🐍 贪吃蛇"

echo "📦 打包贪吃蛇游戏..."

# 编译
echo "🔨 编译..."
mkdir -p build
gcc -Wall -Wextra -std=c99 -g exercises/basics/snake.c -o build/snake $(sdl2-config --cflags --libs)
if [ $? -ne 0 ]; then
    echo "❌ 编译失败！"
    exit 1
fi

# 创建打包目录
echo "📁 创建 App..."
mkdir -p di
rm -rf dist/${APP_NAME}.app
mkdir -p dist/${APP_NAME}.app/Contents/MacOS

# 复制可执行文件
cp build/snake dist/${APP_NAME}.app/Contents/MacOS/${APP_NAME}
chmod +x dist/${APP_NAME}.app/Contents/MacOS/${APP_NAME}

# 创建 Info.plist
cat > dist/${APP_NAME}.app/Contents/Info.plist << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleExecutable</key>
    <string>${APP_NAME}</string>
    <key>CFBundleIdentifier</key>
    <string>com.example.${APP_NAME}</string>
    <key>CFBundleName</key>
    <string>${DISPLAY_NAME}</string>
    <key>CFBundleVersion</key>
    <string>1.0</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>NSHighResolutionCapable</key>
    <true/>
</dict>
</plist>
EOF

# 创建 DMG
echo "💿 生成 DMG..."
rm -f dist/${APP_NAME}.dmg
hdiutil create -volname "$DISPLAY_NAME" -srcfolder dist/${APP_NAME}.app -ov -format UDZO dist/${APP_NAME}.dmg > /dev/null

echo "✅ 完成！"
echo ""
echo "📦 打包产物："
ls -lh dist/
echo ""
echo "双击 dist/${APP_NAME}.dmg 安装使用"
