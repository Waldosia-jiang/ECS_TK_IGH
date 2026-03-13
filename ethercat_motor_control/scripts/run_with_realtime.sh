#!/bin/bash
# EtherCAT 电机控制节点启动脚本（带实时优先级，使用 sudo 在 root 下运行）

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PKG_DIR="$(dirname "$SCRIPT_DIR")"

if [ -f /opt/ros/humble/setup.bash ]; then
    source /opt/ros/humble/setup.bash
fi
if [ -f "$PKG_DIR/install/setup.bash" ]; then
    source "$PKG_DIR/install/setup.bash"
fi

INSTALL_LIB="$PKG_DIR/install/ethercat_motor_node/lib"
EXEC_PATH="$INSTALL_LIB/ethercat_motor_node/ethercat_motor_node"
if [ ! -f "$EXEC_PATH" ]; then
    PREFIX=$(ros2 pkg prefix ethercat_motor_node 2>/dev/null)
    if [ -n "$PREFIX" ]; then
        INSTALL_LIB="$PREFIX/lib"
        EXEC_PATH="$INSTALL_LIB/ethercat_motor_node/ethercat_motor_node"
    fi
fi
if [ -f "$EXEC_PATH" ]; then
    INSTALL_LIB="$(cd "$(dirname "$(dirname "$EXEC_PATH")")" && pwd)"
fi
export LD_LIBRARY_PATH="${INSTALL_LIB}${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"

if [ -f "$EXEC_PATH" ]; then
    sudo -E env \
        PATH="$PATH" \
        "LD_LIBRARY_PATH=${LD_LIBRARY_PATH}" \
        PYTHONPATH="${PYTHONPATH:-}" \
        ROS_DOMAIN_ID="${ROS_DOMAIN_ID:-0}" \
        AMENT_PREFIX_PATH="${AMENT_PREFIX_PATH:-}" \
        COLCON_PREFIX_PATH="${COLCON_PREFIX_PATH:-}" \
        "$EXEC_PATH" "$@"
else
    echo "Error: Cannot find ethercat_motor_node at $EXEC_PATH"
    echo "Please build first: colcon build --packages-select ethercat_motor_node"
    exit 1
fi
