cmake_minimum_required(VERSION 3.15)
project(MyGRPCApp LANGUAGES CXX)

# C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置 gRPC 安装路径，并添加到 CMAKE_PREFIX_PATH
set(GRPC_INSTALL_DIR "C:/Program Files (x86)/grpc")
list(APPEND CMAKE_PREFIX_PATH "${GRPC_INSTALL_DIR}")

# Boost 设置
# set(BOOST_ROOT "D:/gongzuo/kaifa")
# set(Boost_NO_SYSTEM_PATHS ON)
# find_package(Boost REQUIRED)
# include_directories("${BOOST_ROOT}/include")
# link_directories("${BOOST_ROOT}/lib")

# 从环境变量读取头文件路径
if(DEFINED ENV{CPLUS_INCLUDE_PATH})
  string(REPLACE ":" ";" ENV_INCLUDE_PATH_LIST "$ENV{CPLUS_INCLUDE_PATH}")
  include_directories(${ENV_INCLUDE_PATH_LIST})
endif()

# 处理 LIBRARY_PATH（注意分隔符）
if(DEFINED ENV{LIBRARY_PATH})
  string(REPLACE ":" ";" ENV_LIBRARY_PATH "$ENV{LIBRARY_PATH}")
  link_directories(${ENV_LIBRARY_PATH})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/generated)


# 寻找 Protobuf 和 gRPC
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# Protobuf 生成文件
set(GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/generated")
set(PROTO_SRCS
  "${GENERATED_DIR}/message.pb.cc"
  "${GENERATED_DIR}/message.grpc.pb.cc"
)

# 添加头文件路径
include_directories(
    ${Protobuf_INCLUDE_DIRS}
    # ${Boost_INCLUDE_DIRS}
    # ${gRPC_INCLUDE_DIRS}  # 一般为空，但保持以防万一
)

# 搜索源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src source_file)

# 可执行文件
add_executable(main ${source_file} ${PROTO_SRCS})

# 链接库
target_link_libraries(main
    protobuf::libprotobuf
    protobuf::libprotoc
    gRPC::grpc
    gRPC::grpc++
    boost_filesystem-mgw14-mt-d-x64-1_88
    boost_system-mgw14-mt-d-x64-1_88
    Ws2_32
    Mswsock
    # jsoncpp  # 如果你用的是 jsoncpp 的 target，可写 jsoncpp，否则用 
    libjsoncpp.a
    hiredis
    mariadbcpp
)
