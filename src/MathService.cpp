//
// Created by Sean on 2019-08-11.
//

#include "MathService.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using mathtest::MathTest;
using mathtest::MathRequest;
using mathtest::MathReply;

Status MathService::sendRequest(ServerContext *context, const MathRequest *request,
                                MathReply *response){

}

