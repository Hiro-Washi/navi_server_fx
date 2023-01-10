#include <memory> // smart pointer
#include <chrono> // process time measure
//#include <move_base_msgs/MoveBase/Action
#include <iostream>
//#include <list>
#include <vector>
#include <algorithm> // for std::find
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp" //------------
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/string.hpp"
//#include "geometry_msgs/msg/pose_stamped.hpp"
#include "nav2_msgs/action/navigate_to_pose.hpp"
#include "rclcpp/time.hpp" //-------------------------
#include <gen2_navigation2/action/nav2_location_ac.hpp> //!!!

using namespace std::chrono_literals;
using std::placeholders::_1; //----------------
using std::placeholders::_2;//_1,_2,_Nは、bind()で使用するプレースホルダーオブジェクト
// std::bind 式の引数として使用すると、プレースホルダーオブジェクトは生成された関数オブジェクトに格納され、その関数オブジェクトが非バインド引数で呼び出されると、各プレースホルダー _N は対応するN番目の非バインド引数に置き換えらる

//----------

//-----------

enum NaviState {
  SUCCEEDED,
  ACTIVE,
  ABORTED,
  REJECTED,
  CANCELED,
  STUCKED
}

struct Pose{
  double x;
  double y;
  double z;
  double theta
}


class Navi2LocationAcServer : public rclcpp::Node
{
private:
  std::string location_name;  //!!!
  std::vector<std::string> location_list;
  std::vector<double> coord_list;
  // Alias
  using Nav2Pose = nav2_msgs::action::NavigateToPose;
  using Nav2PoseCGH = rclcpp_action::ClientGoalHandle<Nav2Pose>;
  using NavLocAc = gen2_navigation2::action::Navi2LocationAc; //!!
  // ActionClient
  rclcpp_action::Client<Nav2Pose>::SharedPtr n2p_client;
  // ServiceServer
  rclcpp::Service<NavLocAc>::SharedPtr navi2_srv;
  // clear costmap
  //rclcpp::Service<nav2_msgs::srv::ClearCostmapAroundRobot>::SharedPtr clear_around_srv_;
  // Publisher
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr current_location_pub;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr head_pub;
  

public:
  // Attaching 'explicit' to constructer, you can protect from  type changes.
  explicit Navi2LocationAcServer(): Node("navi2_location_acserver")
  {
    // AtionClient. lib::func<type>();
    this->n2p_client =
      rclcpp_action::create_client<Nav2Pose>(this, "navigate_to_pose");
    // ActionServer
    rclcpp_action::create_server<NavLocAc>("/navi2_location_server", 
      std::bind( &Navi2LocationAcServer::searchLocationName, this, _1, _2 ) //!!!
    );
    // PUB
    this->latest_location_pub =
      this->create_publisher<std_msgs::msg::String>("/current_location", 1);
    auto head_pub = 
      this->create_publisher<std_msgs::msg::Float64>("/servo/head", 1);
    // ROS2 PARAM
    location_name = "NULL";
    std::string current_location_name = "";
    this->declare_parameter("location_list"); // declare
    rclcpp::Parameter location_list_param("location_list", <std::vector<std::string>>({}));
    this->get_parameter("location_list", location_list_param); //get
    location_list = location_list_param.as_string_array(); // declare type

    //!!! coord_list 
    //this->declare_parameter("location_list/" + location_name);
    //rclcpp::Parameter
    //coord_list = 


    //std::vector<std::vector<double>>

    //YAML::Node location_list = YAML::LoadFile("yumeko_location_list.yaml");
    //if (location_list[msg.location_name]) {
    //  location_name = msg.location_name
    //  this->
    //}
  }

  bool searchLocationName(const std::shared_ptr<NavLoc> &request,
                          const std::shared_ptr<NavLoc> &response);
  void sendGoalPose(const std::vector<double> coord_list);
  void naviResponseCB(std::shared_future<Nav2PoseCGH::SharedPtr> future);
  void naviFeedbackCB(Nav2PoseCGH::SharedPtr,
                      const std::shared_ptr<const Nav2Pose::Feedback> feedback);
  void naviResultCB(const Nav2PoseCGH::WrappedResult &result);
};
