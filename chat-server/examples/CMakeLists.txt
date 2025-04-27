
add_executable(test_json test_json.cpp)
target_link_libraries(test_json PRIVATE jsoncpp)


add_executable(test_muduo test_muduo.cpp)
target_link_libraries(test_muduo muduo_net muduo_base pthread)