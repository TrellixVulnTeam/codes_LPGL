#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <iostream>
#include <stdexcept>
#include <sstream>

#include "../gen-cpp/Calculator.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace tutorial;
using namespace shared;

class CalculatorHandler : public CalculatorIf {
 public:
  CalculatorHandler() {}

  void ping() {
    printf("ping()\n");
  }

  int32_t add(const int32_t n1, const int32_t n2) {
    printf("add(%d,%d)\n", n1, n2);
    return n1 + n2;
  }

  int32_t calculate(const int32_t logid, const Work &work) {
    printf("calculate(%d,{%d,%d,%d})\n", logid, work.op, work.num1, work.num2);
    int32_t val;

    switch (work.op) {
    case Operation::ADD:
      val = work.num1 + work.num2;
      break;
    case Operation::SUBTRACT:
      val = work.num1 - work.num2;
      break;
    case Operation::MULTIPLY:
      val = work.num1 * work.num2;
      break;
    case Operation::DIVIDE:
      if (work.num2 == 0) {
        InvalidOperation io;
        io.what = work.op;
        io.why = "Cannot divide by 0";
        throw io;
      }
      val = work.num1 / work.num2;
      break;
    default:
      InvalidOperation io;
      io.what = work.op;
      io.why = "Invalid Operation";
      throw io;
    }

    SharedStruct ss;
    ss.key = logid;
    char buffer[12];
    snprintf(buffer, sizeof(buffer), "%d", val);
    ss.value = buffer;

    log[logid] = ss;

    return val;
  }

  void getStruct(SharedStruct &ret, const int32_t logid) {
    printf("getStruct(%d)\n", logid);
    ret = log[logid];
  }

  void zip() {
    printf("zip()\n");
  }

protected:
  map<int32_t, SharedStruct> log;

};

int main(int argc, char **argv) {

  boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
  boost::shared_ptr<CalculatorHandler> handler(new CalculatorHandler());
  boost::shared_ptr<TProcessor> processor(new CalculatorProcessor(handler));
  boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(9090));
  boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());

  TSimpleServer server(processor,
                       serverTransport,
                       transportFactory,
                       protocolFactory);


  /**
   * Or you could do one of these

  boost::shared_ptr<ThreadManager> threadManager =
    ThreadManager::newSimpleThreadManager(workerCount);
  boost::shared_ptr<PosixThreadFactory> threadFactory =
    boost::shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();
  TThreadPoolServer server(processor,
                           serverTransport,
                           transportFactory,
                           protocolFactory,
                           threadManager);

  TThreadedServer server(processor,
                         serverTransport,
                         transportFactory,
                         protocolFactory);

  */

  printf("Starting the server...\n");
  server.serve();
  printf("done.\n");
  return 0;
}
