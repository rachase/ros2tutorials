//https://docs.ros.org/en/foxy/Tutorials/Single-Package-Define-And-Use-Interface.html
#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "third/msg/address_book.hpp"
#include "third/msg/nested_msg.hpp"

using namespace std::chrono_literals;

class AddressBookPublisher : public rclcpp::Node
{
public:
  AddressBookPublisher()
  : Node("address_book_publisher")
  {
    address_book_publisher_ =
      this->create_publisher<third::msg::AddressBook>("address_book", 10);

    auto publish_msg = [this]() -> void {
        auto message = third::msg::AddressBook();

        message.first_name = "John";
        message.last_name = "Doe";
        message.age = 30;
        message.gender = message.MALE;
        message.address = "unknown";

        std::cout << "Publishing Contact\nFirst:" << message.first_name <<
          "  Last:" << message.last_name << std::endl;

        this->address_book_publisher_->publish(message);
      };
    timer_ = this->create_wall_timer(1s, publish_msg);
  }

private:
  rclcpp::Publisher<third::msg::AddressBook>::SharedPtr address_book_publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto Anestedmsg = third::msg::NestedMsg();

  Anestedmsg.anint = 23;
  
  rclcpp::spin(std::make_shared<AddressBookPublisher>());
  rclcpp::shutdown();

  return 0;
}
