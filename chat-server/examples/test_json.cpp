/**
 * @file   : test_json.cpp
 * @author : wangdong (wangdong1328@163.com)
 * @brief  :
 * @version: 0.1
 * @date   : 2025-04-16
 *
 * @copyright Copyright (c) 2025
 *
 * **********************************************************
 * @Attention   :
 * @修改日志:
 * <table>
 * <tr><th>Date         <th>Version   <th>Author    <th>Description
 * <tr><td>2025-04-16   <td>0.1       <td>wangdong  <td>创建初始版本
 * </table>
 *
 */
#include <jsoncpp/json/json.h>

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::string str = R"({"姓名":"小明", "年龄":18, "成绩":[76.5, 55, 88]})";
    Json::Value root;
    Json::CharReaderBuilder crb;
    std::unique_ptr<Json::CharReader> cr(crb.newCharReader());
    std::string err;
    cr->parse(str.c_str(), str.c_str() + str.size(), &root, &err);

    std::cout << root["姓名"].asString() << std::endl;
    std::cout << root["年龄"].asInt() << std::endl;
    int sz = root["成绩"].size();
    for (int i = 0; i < sz; i++)
    {
        std::cout << root["成绩"][i].asFloat() << std::endl;
    }

    for (auto it = root["成绩"].begin(); it != root["成绩"].end(); it++)
    {
        std::cout << it->asFloat() << std::endl;
    }

    return 0;
}