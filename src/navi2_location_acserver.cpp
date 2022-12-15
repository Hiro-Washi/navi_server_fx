// 受け取ったロケーション座標をナビゲーションゴールとして送るアクションサーバー

// ClassName funcName memverFuncName local_variable
// member_variable CONSTANT_NUMBER constNumber
// アンチ・ハンガリアン記法(class名にClass・文字列なら先頭にsとか)

// Objective：
// 　・Nothing move_base_msgs | But: 
// 　・Modularized
// 　・Update costmap to suitable for dynamic env
// 　・Add telerance or distance for compromise mode
// 　・Visual or odometry info integration

//class NaviLocationServer2 : public rclcpp::Node
//  ~
//  bool searchLocationName(self, req)      req/res yaml sendGoal(loc) NaviLocationResponse
//  
//  bool sendGoal()
 
#include <memory> // smart pointer
#include <chrono> // process time measure
#include <list>
//#include <move_base_msgs/MoveBase/Action

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"
#include "nav2_msgs/action/navigate_to_pose.hpp"
#include "rclcpp/time.hpp"

#include "mimi_navi2/srv/navi2_location.hpp" 
//#include "mimi_navi2/action/navi2_location.hpp" //------------------!!!

using namespace std::chrono_literals;
using std::placeholders::_1; //----------------
using std::placeholders::_2; //_1,_2,_Nは、bind()で使用するプレースホルダーオブジェクト
// std::bind 式の引数として使用すると、プレースホルダーオブジェクトは生成された関数オブジェクトに格納され、その関数オブジェクトが非バインド引数で呼び出されると、各プレースホルダー _N は対応するN番目の非バインド引数に置き換えらる

// 
class Navi2LocationAcServer : public rclcpp::Node
{
// local変数の宣言 Service,メンバ変数などの型を宣言
pravate:
  std::list<std::string> location_dict;
  std::string location_name;

  // Instance of necessary types
  using Navi2Pose = nav2_msgs::action::NavigateToPose;
  using Navi2Location = mimi_navi2::action::NavigateToPose;
  using Navi2PoseCGH = rclcpp_action::ClientGoalHandle<Navi2Pose>;
  //ACTION
  rclcpp_action::Client<Navi2Pose>::SharedPtr n2p_client;
  // SERVICE    // !!!!
  rclcpp::Service<Navi2Location>::SharedPtr navi2_srv;
  // clear costmap
  //rclcpp::Service<nav2_msgs::srv::ClearCostmapAroundRobot>::SharedPtr clear_around_service_;

  // PUBLISHER
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr current_location_pub;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr head_pub;

  void init();
  bool searchLocationName(const std::shared_ptr<Navi2Location> request,
                          const std::shared_ptr<Navi2Location> result
  );
  void sendGoal();// !!!!
  void naviFeedbackCB(){}
  void naviResultCB(){}

public:
  Navi2LocationAcServer() : Node("navi2_location_acserver")//{
    // 初めに実行する場所? }

  // Constructerにexplicit修飾子をつけ、暗黙的な型変換を防止できる
  explicit Navi2LocationAcServer(): Node("navi2_location_acserver")
  {
    // ACTION  Generate ac client (lib::func<type>())
    this->n2p_client =
      rclcpp_action::create_client<Navi2Pose>(this,"navi2pose_client");
  }

  void init(){
    // ACTION
    // SERVICE
    auto navi2_srv = this->create_service<happymimi_navigation
    // PUB
    auto current_location_pub = this->create_publisher<std::msg::String>("/current_location", 1)
    auto head_pub = this->create_publisher<std::msg::Float64>("/servo/head", 1)
    // location_list

  }

  bool searchLocationName(const std::shared_ptr<happymimi_msgs2::srv::NaviLocation> request,
                            const std::shared_ptr<happymimi_msgs2::srv::NaviLocation> result
    ){
      if (request.location_name )
    };



  //!!! サーバーモジュール化,server type, request 
  void sendGoal(location_list) { //-------------------
    //wait action server
    while (!this->n2p_client->wait_for_action_server()) {
      RCLCPP_INFO(get_logger(), "waiting for the action server...");
      rclcpp::sleep_for(1000ms)
    }
    
    // set goal_pose
    auto goal = Navi2Pose::Goal();
    goal.pose.header.stamp = this->now();
    goal.pose.header.frame_id = "map"; //-------------
    goal.pose.pose.position.x = location_list[0]
    goal.pose.pose.position.y = location_list[1]
    goal.pose.pose.orientation.x = location_list[2]
    goal.pose.pose.orientation.w = location_list[3]
 
    //clear costmap
    //RCLCPP_INFO(get_logger(), "clearing cost map...");
    // rclcpp::wa---------------
    //

    // Feedback
    auto goal_options = rclcpp_action::Client<Navi2Pose>::SendGoalOptions();
    goal_options.feedback_callback = std::bind(&Navi2LocationAcServer::naviFeedbackCB,
                                               this, _1, _2);
    goal_options.result_callback = std::bind(&Navi2LocationAcServer::naviResultCB,
                                             this, 1_);
    n2p_client->async_send_goal(goal, goal_options); // send the goal to server
  }
  // !!!!
  void naviFeedbackCB(Navi2PoseCGH::SharedPtr,
                      const std::shared_ptr<const Navi2Pose::Feedback feedback){
    
  }

  void naviResultCB(const Navi2PoseCGH::WrappedResult &result){
    switch (result.code){
      RCLCPP_INFO(get.logger(), "Navigation Success"
    }
  }
  
    // モジュール時に任意のlocationへのNavi2を実行する用関数
    //void execute(){
      // ノードの初期化
      //rclcpp::init(
      // NaviLocationServer2のインスタンス化
      // 例外処理で実行

}


// モジュール化のためできるだけMain関数は短く
int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  NaviLocationAcServer2 nlas2; // generate node, local_v
  
  nlas2.init(); // pub/sub client local_v 

  rclcpp::rate::Rate loop_rate(33);
  while (rclcpp::ok()) {


    rclcpp::spin_some(navi2_location_acserver);
    loop_rate.sleep();
  }

  rclcpp::shutdown(); // ノードの停止。これを呼ぶとspinから抜ける。

  return 0;
}
