#include "json.hpp"

using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
using namespace std;

// json序列化示例1
string func1() {
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing now?";
    cout << js << endl;

    string sendbuf = js.dump();                 // dump方法将json对象序列化为json字符串
    // cout << sendbuf << endl;
    // cout << sendbuf.c_str() << endl;            // c_str()再将string转为c风格串
    return sendbuf;
}

// json序列化示例2
void func2() {
    json js;
    // 添加数组
    js["id"] = {1, 2, 3, 4, 5};
    // 添加key-value
    js["name"] = "zhang san";
    // 添加对象
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu shuo"] = "hello china";
    // 上面等同于下面这句一次性添加数组对象
    js["msg"] = {{"zhang san", "hello world"}, {"liu shuo", "hello china"}};
    cout << js << endl;
}

// json序列化示例3
string func3() {
    json js;

    // 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;

    // 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});
    js["path"] = m;

    // cout << js << endl;
    string sendbuf = js.dump();
    // cout << sendbuf << endl;
    return sendbuf;
}

int main() {
    // func1();
    // func2();
    // func3();

    string recvbuf = func1();

    // 数据的反序列化 json字符串反序列化为json对象（看作JSON容器 方便访问）
    json jsbuf = json::parse(recvbuf);
    cout << jsbuf["msg_type"] << endl;
    cout << jsbuf["from"] << endl;
    cout << jsbuf["to"] << endl;
    cout << jsbuf["msg"] << endl;

    string recvbuf3 = func3();
    json jsbuf3 = json::parse(recvbuf3);
    vector<int> vec = jsbuf3["list"];
    for(auto x : vec)
        cout << x << " ";
    cout << endl;

    return 0;
}
