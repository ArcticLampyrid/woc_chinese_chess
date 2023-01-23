# SAST2023 - C++ 组寒假大作战项目：在线象棋客户端
## 版权声明
仓库所包含的原始模板代码归属南邮校科协所有，如需使用请联系南邮校科协取得授权。  
对于本人所编写的代码部分，保留所有权利，但授予南邮校科协可无条件自由使用。  

## 免责声明
本项目以原样提供，不作任何形式（明示或暗示）的保证，包括但不限于对适销性、特定用途适用性和非侵权性的保证。在任何情况下，如合同诉讼、侵权诉讼或其他诉讼中，作者或版权持有人均不承担因本项目或本项目的使用、交易或其他行为而产生的、引起的或因其它任何原因与之相关的任何责任（包括但不限于索赔、损害等）。

## 试题要求
### 一、编写要求
使用 C++ 和 Qt6 框架在所给项目的基础上编写一个能实现象棋操作功能的客户端，并对服务器响应。

**如非特殊要求，请不要修改代码的组织结构，尽量仅在所给代码的基础上插入和添加代码。**

### 二、项目任务要求
#### （1）基本任务
1. 重写 `class Piece` 派生类中的 `bool isBasicMove(int x, int y)` 函数实现对派生类棋子基本走法的限制约束。
2. 重写 `class Piece` 派生类中的 `isValidMove (int x, int y)` 函数实现对派生类棋子走法是否可行的判断。
3. 在1、2的基础上，重写 `class Piece` 派生类中 `getBasicMoves()` 函数，实现获得该子所有可能走法的功能。
4. 为 `class board` 实现 `find` 函数。其中，`side` 筛选棋子颜色，`-1` 不筛选；`x` 筛选棋子横坐标，`-1` 不筛选；`y` 筛选棋子纵坐标，`-1` 不筛选。
5. 用 lambda 表达式为每一个 `class Piece` 的派生类实现一个工厂函数。
6. 实现 `class Piece` 中 `bool noThreat(int x, int y)` 判断走棋后是否处于将军状态。
7. 正确虚析构和使用 `std::shared_ptr`、`std::weak_ptr` 使得吃子自动析构。
8. 合理配置信号槽使得网络、数据、界面三者解耦，并使得UI正确响应。
9. 使用 Qt 网络库根据 API 正确处理 GET 请求的响应。

#### （2）进阶任务（选做）
1. 学习和使用 qss 装点界面。
2. 优化算法逻辑。
3. 当遇到网络原因，引导用户重新开始。
4. 根据 API 实现聊天功能。
5. 根据 API 实现认输功能。

### 三、API
#### Request
方法：`GET`  
格式：`application/x-www-form-urlencoded`  
项目代码中已包含所有发包部分，略。简单来说是长轮询机制。
#### Response
格式：`application/json`  
字段表：
| 字段名     | 类型     | 描述                           | 取值                                                            |
| ---------- | -------- | ------------------------------ | --------------------------------------------------------------- |
| Type       | `string` | （必填）响应类型（不区分大小写） | `"signup"` `"login"` `"find"` `"message"` `"move"` `"continue"` |
| Sucess     | `bool`   | （必填）请求是否成功           | `true`/`false`                                                  |  |
| ErrMessage | `string` | （Success==false）失败信息     |                                                                 |
| Message    | `string` | （Type=="message"）聊天信息    |                                                                 |
| Opp        | `string` | （Type=="find"）匹配的用户     |                                                                 |
| Side       | `bool`   | （Type=="find"）红/黑方        | `true`/`false`                                                  |
| X1         | `int`    | （Type=="move"）起始点x        | 1~9                                                             |
| Y1         | `int`    | （Type=="move"）起始点y        | 1~12                                                            |
| X2         | `int`    | （Type=="move"）目标点x        | 1~9                                                             |
| Y2         | `int`    | （Type=="move"）目标点y        | 1~12                                                            |

HTTP-STATUS-CODE：200为服务器正确接收并处理响应，201表示一次轮询结束。
