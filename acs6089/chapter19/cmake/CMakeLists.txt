# CMake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.11)

# 프로젝트 정보
project(
  ModooCode
  VERSION 0.1
  DESCRIPTION "예제 프로젝트"

  # 어떤 언어로 프로젝트가 만들어 졌지는 명시
  LANGUAGES CXX)

# 확인할 디렉토리 추가
add_subdirectory(lib)

add_executable (program main.cc foo.cc)

target_include_directories(program PUBLIC ${CMAKE_SOURCE_DIR}/includes)

# program 에 shape 를 링크
target_link_libraries(program shape)

# FetchContene 모듈을 불러온다
include(FetchContent)

# 어디서 데이터를 불러올지 선언한다.
FetchContent_Declare(
  Fmt
  GIT_REPOSITORY "https://github.com/fmtlib/fmt"
  GIT_TAG "7.1.3"
)
# fmt 라이브러리를 사용하는 것을 활성화한다.
FetchContent_MakeAvailable(Fmt)