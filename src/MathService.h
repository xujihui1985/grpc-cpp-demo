//
// Created by Sean on 2019-08-11.
//

#ifndef GRPC_HELLO_MATHSERVICE_H
#define GRPC_HELLO_MATHSERVICE_H


#include <grpcpp/grpcpp.h>
#include "mathtest.grpc.pb.h"

using mathtest::MathTest;
using mathtest::MathRequest;
using mathtest::MathReply;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class MathService final : public MathTest::Service {
public:
    Status sendRequest(ServerContext *context,
                       const MathRequest *request,
                       MathReply *reply) override {
        int a = request->a();
        int b = request->b();
        reply->set_result(a * 100);
        return Status::OK;
    };
};


#endif //GRPC_HELLO_MATHSERVICE_H
