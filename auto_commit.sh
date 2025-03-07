#!/bin/bash

# 检查是否在Git仓库中
if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
    echo "错误：当前目录不是一个Git仓库。"
    exit 1
fi

# 添加所有更改
git add -A

# 读取提交信息
read -p "请输入提交消息: " commit_message
git commit -m "$commit_message"

# 关闭dae服务
echo "正在关闭dae服务..."
if ! sudo systemctl stop dae; then
    echo "错误：无法停止dae服务"
    exit 1
fi

# 推送更改并捕获状态
push_success=true
if ! git push; then
    echo "警告：git push失败"
    push_success=false
fi

# 启动dae服务
echo "正在启动dae服务..."
if ! sudo systemctl start dae; then
    echo "错误：无法启动dae服务"
    exit 1
fi

# 最终状态报告
if [ "$push_success" = true ]; then
    echo "✅ 所有操作已完成！"
else
    echo "⚠️ 推送失败，但已恢复dae服务"
    exit 1
fi
