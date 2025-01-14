#include  <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "../gen-cpp/Calculator.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace tutorial;
using namespace shared;

int main(int argc, char** argv) {
  boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  CalculatorClient client(protocol);

  try {
    transport->open();

    client.ping();
    printf("ping()\n");

    int32_t sum = client.add(1,1);
    printf("1+1=%d\n", sum);

    Work work;
    work.op = Operation::DIVIDE;
    work.num1 = 1;
    work.num2 = 0;

    try {
      client.calculate(1, work);
      printf("Whoa? We can divide by zero!\n");
    } catch (InvalidOperation &io) {
      printf("InvalidOperation: %s\n", io.why.c_str());
    }

    work.op = Operation::SUBTRACT;
    work.num1 = 15;
    work.num2 = 10;
    int32_t diff = client.calculate(1, work);
    printf("15-10=%d\n", diff);

    // Note that C++ uses return by reference for complex types to avoid
    // costly copy construction
    SharedStruct ss;
    client.getStruct(ss, 1);
    printf("Check log: %s\n", ss.value.c_str());

    transport->close();
  } catch (TException &tx) {
    printf("ERROR: %s\n", tx.what());
  }

}
