from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    node_params = [{
        'slave_num': LaunchConfiguration('slave_num'),
        'cycle_time_ms': LaunchConfiguration('cycle_time_ms'),
        'publish_motor_states': LaunchConfiguration('publish_motor_states'),
        'temperature_limit_deg': LaunchConfiguration('temperature_limit_deg'),
    }]
    # 需在 root 下先 source install/setup.bash 再 ros2 launch，节点会继承环境；勿用 prefix 传 env，易触发 File name too long
    return LaunchDescription([
        DeclareLaunchArgument('slave_num', default_value='3', description='Number of EtherCAT slaves'),
        DeclareLaunchArgument('cycle_time_ms', default_value='1', description='Cycle time in ms'),
        DeclareLaunchArgument('publish_motor_states', default_value='true', description='Publish motor states'),
        DeclareLaunchArgument('temperature_limit_deg', default_value='80', description='Temperature protection threshold (°C), enter zero-current mode when exceeded'),
        Node(
            package='ethercat_motor_node',
            executable='ethercat_motor_node',
            name='ethercat_motor_node',
            output='screen',
            parameters=node_params,
        ),
    ])
