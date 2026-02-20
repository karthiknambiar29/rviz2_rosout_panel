#include "rviz2_rosout_panel/rosout_panel.hpp"

#include <rviz_common/display_context.hpp>
#include <rviz_common/ros_integration/ros_node_abstraction_iface.hpp>

#include <pluginlib/class_list_macros.hpp>

#include <algorithm>

namespace rviz2_rosout_panel
{

RosoutPanel::RosoutPanel(QWidget * parent)
: rviz_common::Panel(parent)
{
  text_edit_ = new QTextEdit;
  text_edit_->setReadOnly(true);

  input_edit_ = new QLineEdit;
  input_edit_->setPlaceholderText("Type node name + Enter...");
  connect(input_edit_, &QLineEdit::returnPressed,
          this, &RosoutPanel::addChip);

  chip_container_ = new QWidget;
  chip_layout_ = new QHBoxLayout(chip_container_);
  chip_layout_->setAlignment(Qt::AlignLeft);

  auto * scroll = new QScrollArea;
  scroll->setWidgetResizable(true);
  scroll->setWidget(chip_container_);
  scroll->setFixedHeight(50);

  auto * layout = new QVBoxLayout;
  layout->addWidget(input_edit_);
  layout->addWidget(scroll);
  layout->addWidget(text_edit_);

  setLayout(layout);
}

void RosoutPanel::onInitialize()
{
  auto ros_node_abstraction =
    getDisplayContext()->getRosNodeAbstraction().lock();

  node_ = ros_node_abstraction->get_raw_node();

  sub_ = node_->create_subscription<rcl_interfaces::msg::Log>(
    "/rosout",
    rclcpp::QoS(100),
    std::bind(&RosoutPanel::logCallback, this, std::placeholders::_1));
}

void RosoutPanel::addChip()
{
  QString text = input_edit_->text().trimmed();
  if (text.isEmpty()) return;

  filters_.push_back(text);

  auto * chip = new QPushButton(text + "  ✕");

  connect(chip, &QPushButton::clicked, this, [this, chip, text]() {
    filters_.erase(
      std::remove(filters_.begin(), filters_.end(), text),
      filters_.end());
    delete chip;
  });

  chip_layout_->addWidget(chip);
  input_edit_->clear();
}

void RosoutPanel::logCallback(
  const rcl_interfaces::msg::Log::SharedPtr msg)
{
  QString node = QString::fromStdString(msg->name);

  // Multi-filter logic
  if (!filters_.empty()) {
    bool match = false;
    for (auto & f : filters_) {
      if (node.contains(f, Qt::CaseInsensitive)) {
        match = true;
        break;
      }
    }
    if (!match) return;
  }

  QString color = "black";
  if (msg->level == rcl_interfaces::msg::Log::WARN) color = "orange";
  if (msg->level >= rcl_interfaces::msg::Log::ERROR) color = "red";
  if (msg->level == rcl_interfaces::msg::Log::DEBUG) color = "gray";

  QString line = QString("<font color='%1'>[%2] %3</font>")
    .arg(color)
    .arg(node)
    .arg(QString::fromStdString(msg->msg));

  text_edit_->append(line);
}

} // namespace

PLUGINLIB_EXPORT_CLASS(
  rviz2_rosout_panel::RosoutPanel,
  rviz_common::Panel)
