# RViz2 Rosout Panel Plugin

A custom RViz2 panel plugin for viewing and filtering ROS2 log messages (rosout) in real-time.

## Overview

This plugin provides an interactive panel for RViz2 that displays log messages from the `/rosout` topic with filtering capabilities. It allows you to monitor logs from specific nodes by adding multiple filters through a clean, chip-based interface.

## Features

- **Real-time Log Viewing**: Subscribes to `/rosout` topic and displays log messages as they arrive
- **Color-Coded Messages**: Log levels are color-coded for easy identification:
  - 🔴 **Red**: Error messages
  - 🟠 **Orange**: Warning messages
  - ⚫ **Black**: Info messages
  - ⚪ **Gray**: Debug messages
- **Multi-Node Filtering**: Add multiple node name filters to view logs from specific nodes
- **Interactive Filter Chips**: Easy-to-use chip interface for adding and removing filters
- **Case-Insensitive Matching**: Filters work with partial, case-insensitive node name matching

## Dependencies

- ROS2 (Foxy or later)
- RViz2
- Qt5 Widgets
- rclcpp
- rcl_interfaces
- rviz_common
- pluginlib

## Building

1. Clone this repository into your ROS2 workspace:
```bash
cd ~/ros2_ws/src
git clone https://github.com/karthiknambiar29/rviz2_rosout_panel.git rviz2_plugin_rosout
```

2. Build the package:
```bash
cd ~/ros2_ws
colcon build --packages-select rviz2_rosout_panel
```

3. Source your workspace:
```bash
source ~/ros2_ws/install/setup.bash
```

## Usage

1. Launch RViz2:
```bash
rviz2
```

2. Add the Rosout Panel:
   - Click on "Panels" menu → "Add New Panel"
   - Select "RosoutPanel" under "rviz2_rosout_panel"
   - The panel will appear in your RViz2 window

3. Filter logs by node name:
   - Type a node name (or partial name) in the input field
   - Press Enter to add a filter chip
   - Click the × on any chip to remove that filter
   - Leave empty to see all logs

## How It Works

The panel subscribes to the `/rosout` topic which aggregates log messages from all ROS2 nodes. When filters are active, only messages from nodes matching any of the filter strings are displayed. If no filters are set, all log messages are shown.

## Package Structure

```
rviz2_rosout_panel/
├── CMakeLists.txt
├── package.xml
├── plugin_description.xml
├── include/
│   └── rviz2_rosout_panel/
│       └── rosout_panel.hpp
└── src/
    └── rosout_panel.cpp
```

## License

TODO: Add license information

## Maintainer

moonlab (karthik23@iiserb.ac.in)

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests.
