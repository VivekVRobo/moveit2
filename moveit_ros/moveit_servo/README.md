# MoveIt Servo

See the [Realtime Arm Servoing Tutorial](https://moveit.picknik.ai/main/doc/examples/realtime_servo/realtime_servo_tutorial.html) for installation instructions, quick-start guide, an overview about `moveit_servo`, and to learn how to set it up on your robot.

## Outgoing command messages

Servo can publish joint commands in either of these ROS 2 message formats:

- `trajectory_msgs/msg/JointTrajectory`
- `std_msgs/msg/Float64MultiArray`

Set the output topic and message type with `command_out_topic` and
`command_out_type` in the Servo parameters. The default output type is
`trajectory_msgs/JointTrajectory`.

### Using `std_msgs/msg/Float64MultiArray`

Use this mode when the downstream controller expects one scalar command per
joint rather than a trajectory message. For example:

```yaml
servo:
  command_out_topic: /joint_group_position_controller/commands
  command_out_type: std_msgs/Float64MultiArray
  publish_joint_positions: true
  publish_joint_velocities: false
```

The published `Float64MultiArray.data` contains one value for each joint in
the active joint state, in the same joint order used by Servo:

| Configuration | `data[i]` contains |
| --- | --- |
| `publish_joint_positions: true` | Joint position for joint `i` |
| `publish_joint_positions: false` and `publish_joint_velocities: true` | Joint velocity for joint `i` |

Servo's current implementation checks positions first. Therefore, if both
`publish_joint_positions` and `publish_joint_velocities` are enabled,
positions are published in the `Float64MultiArray`. If both are disabled,
the array is still sized to the number of joints but its values are not
populated by either command source.

The message is created by
`composeMultiArrayMessage()` in
`moveit_ros/moveit_servo/src/utils/common.cpp`. The function's declaration
and API contract are in
`moveit_ros/moveit_servo/include/moveit_servo/utils/common.hpp`.

### Choosing the correct output type

Use `trajectory_msgs/msg/JointTrajectory` when the controller consumes
trajectory points and timing information. Use
`std_msgs/msg/Float64MultiArray` when the controller interface expects a
plain vector of per-joint position or velocity commands.

The output message type must match the interface exposed by the controller
receiving `command_out_topic`. Changing `command_out_type` does not
reconfigure the downstream controller.

The example above is intentionally limited to the software interface exposed
by MoveIt Servo. Controller-specific topic names, controller activation, and
hardware safety configuration remain the responsibility of the robot
integration.

For the full Servo setup and incoming-command configuration, see the
[Realtime Arm Servoing Tutorial](https://moveit.picknik.ai/main/doc/examples/realtime_servo/realtime_servo_tutorial.html).
