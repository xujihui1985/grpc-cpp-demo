cmake_minimum_required(VERSION 3.5.1)

project(grpc-hello C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf REQUIRED)

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

find_package(GRPC REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
set(_GRPC_GRPCPP_REFLECTION gRPC::grpc++_reflection)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
message(STATUS "Using gRPC ${gRPC_VERSION}")

get_filename_component(hw_proto ${CMAKE_CURRENT_SOURCE_DIR}/protos/mathtest.proto ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/mathtest.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/mathtest.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/mathtest.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/mathtest.grpc.pb.h")

add_custom_command(
        OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
        DEPENDS "${hw_proto}")

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

foreach(_target
        client server)
    add_executable(${_target} "${CMAKE_CURRENT_LIST_DIR}/src/${_target}.cc"
            ${hw_proto_srcs}
            ${hw_grpc_srcs}
            "${CMAKE_CURRENT_LIST_DIR/src/MathServce.h}"
            "${CMAKE_CURRENT_LIST_DIR/src/MathServce.cpp}"
            )
    target_link_libraries(${_target}
#            ${_GRPC_GRPCPP_UNSECURE}
            ${_GRPC_GRPCPP_REFLECTION}
            ${_PROTOBUF_LIBPROTOBUF})
endforeach()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

