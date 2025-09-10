@echo off
set PROTOC="C:\Program Files (x86)\grpc\bin\protoc.exe"
set PLUGIN="C:\Program Files (x86)\grpc\bin\grpc_cpp_plugin.exe"

mkdir generated 2>nul

%PROTOC% -I=protos --cpp_out=generated --grpc_out=generated --plugin=protoc-gen-grpc=%PLUGIN% protos\message.proto

pause
