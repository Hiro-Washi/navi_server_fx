// アション通信でナビゲーションのゴールを送るアクションサーバー
// Nothing: move_base_msgs
// 非モジュール
// 型代入： BIG_AND_ANDERSCORE
//
// メモ：
// thisとは具体的に？
// ClassName 
// funcName  memverFuncName 
// local_variable  member_variable
// CONSTANT_NUMBER  
// constNumber
// 
// ㊟アンチ・ハンガリアン記法(class 名に Class・文字列なら先頭に s toka)
#include <memory> // smart pointer
#include <chrono> // process time measure
//#include <move_base_msgs/MoveBase/Action

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp" //------------
#include "nav2_msgs/action/navigate_to_pose.hpp"
#include "rclcpp/time.hpp" //-------------------------

using namespace std::chrono_literals;
using std::placeholders::_1; //----------------
using std::placeholders::_2; //_1,_2,_Nは、bind()で使用するプレースホルダーオブジェクト
// std::bind 式の引数として使用すると、プレースホルダーオブジェクトは生成された関数オブジェクトに格納され、その関数オブジェクトが非バインド引数で呼び出されると、各プレースホルダー _N は対応するN番目の非バインド引数に置き換えらる

// executeでNaviの実行とサーバーを起動
// navi_location2メッセージ受信でexecute実行アクション通信でamclのnaviの
class NaviLocationServer2 : public rclcpp::Node
{
public:
  // Instance of necessary types
  using Navi2Pose = nav2_msgs::action::NavigateToPose;
  using N2P_GOAL_HANDLE= rclcpp_action::ClientGoalHandle<Navi2Pose>;
  rclcpp_action::Client<Navi2Pose>::SharedPtr ac_client;
  
  // Constructerにexplicit修飾子をつけ、暗黙的な型変換を防止できる
  explicit NaviLocationServer2(): Node("navi_location_server_2")
  {
    // Generate ac client (lib::func<type>())
    this->ac_client = rclcpp_action::create_client<NaviToPose>(this,"navi2pose_client");
  }
  
  // type????
  void searchLocationName(

  //!!! サーバーモジュール化,server type, request 
  void sendGoal(location_list) { //-------------------
    //wait action server
    while (!this->ac_client->wait_for_action_server()) {
      RCLCPP_INFO(get_logger(), "waiting for the action server...");
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

void 

	// 実行関数
	void execute(){
	 // ノードの初期化
	//rclcpp::init(
	// NaviLocationServer2のインスタンス化
	 // 例外処理で実行



// モジュール化のためできるだけMain関数は短く
int main(int argc, char* argv[])
{
  rclcpp::init(ク
