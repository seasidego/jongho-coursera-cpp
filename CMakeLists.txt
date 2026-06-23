# zed
cmake_minimum_required(VERSION 3.10)
project(jongho-coursera-cpp)

# Zed(Clangd) 코드 자동완성을 위해 필수 추가
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 하위 프로젝트 폴더들을 등록
add_subdirectory(helloworld)
add_subdirectory(quick_sort)
add_subdirectory(binary_tree)
add_subdirectory(graph)
add_subdirectory(compression)

# vscode
# cmake_minimum_required(VERSION 3.15)
# project(UIUC_CS_Fundamentals)

# # M1 Mac 및 C++20 표준 강제 설정
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # 테스트 빌드용 폴더 등록
# add_subdirectory(quick_sort)
