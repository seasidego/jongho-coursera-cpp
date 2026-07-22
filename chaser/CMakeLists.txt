project(chaser) # _exe를 빼고 깔끔하게 작성

# 프로젝트 이름(quick_sort) 그대로 실행 파일이 생성됩니다.
# 현재 디렉토리와 chaser 폴더 안의 모든 .cpp 파일을 자동으로 찾아서 SRC_FILES 변수에 저장
file(GLOB_RECURSE SRC_FILES "*.cpp")

# 자동으로 찾아낸 모든 파일로 실행 파일 생성
add_executable(chaser ${SRC_FILES})

# 1. Google Test 패키지 찾기
find_package(GTest REQUIRED)

# 2. 헤더 파일 경로 포함하기
include_directories(${GTEST_INCLUDE_DIRS})

# 3. chaser 타겟에 gtest 라이브러리 링크하기
# (기존 add_executable(chaser ...) 정의 아래에 추가하세요)
target_link_libraries(chaser PRIVATE GTest::gtest GTest::gtest_main)
