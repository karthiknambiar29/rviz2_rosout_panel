#pragma once

#include <rviz_common/panel.hpp>

#include <rclcpp/rclcpp.hpp>
#include <rcl_interfaces/msg/log.hpp>

#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>

namespace rviz2_rosout_panel
{

class RosoutPanel : public rviz_common::Panel
{
  Q_OBJECT

public:
  RosoutPanel(QWidget * parent = nullptr);

  void onInitialize() override;

private Q_SLOTS:
  void addChip();

private:
  void logCallback(const rcl_interfaces::msg::Log::SharedPtr msg);

  rclcpp::Node::SharedPtr node_;
  rclcpp::Subscription<rcl_interfaces::msg::Log>::SharedPtr sub_;

  QTextEdit * text_edit_;
  QLineEdit * input_edit_;

  QWidget * chip_container_;
  QHBoxLayout * chip_layout_;

  std::vector<QString> filters_;
};

} // namespace
