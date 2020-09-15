//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>

#include <msgpack.h>

#include <Eigen/Core>

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server…" << std::endl;
    socket.connect ("tcp://localhost:5555");

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != 1; request_nbr++) {
        zmq::message_t request (5);
        memcpy (request.data (), "Hello", 5);
        std::cout << "Sending Hello " << request_nbr << "…" << std::endl;
        socket.send (request, zmq::send_flags::none);

        //  Get the reply.
        zmq::message_t reply;
        auto ret = socket.recv (reply);
        if (ret) {
            std::cout << "Received data " << reply.size() << std::endl;
            /* deserializes it. */
            msgpack_unpacked msg;
            msgpack_unpacked_init(&msg);
            msgpack_unpack_return ret = msgpack_unpack_next(&msg, reinterpret_cast<const char*>(reply.data()), reply.size(), NULL);

            /* prints the deserialized object. */
            msgpack_object obj = msg.data;
            std::cout << "size of array: " << obj.via.array.size << std::endl;
            std::cout << "bin size: " << obj.via.array.ptr->via.bin.size << std::endl;
            Eigen::MatrixXd m = Eigen::Map<const Eigen::MatrixXd>(reinterpret_cast<const double*>(obj.via.array.ptr->via.bin.ptr), 10240, 10240);
            std::cout << "trace: " << m.trace() << std::endl;
            //msgpack_object_print(stdout, obj);  /*=> ["Hello", "MessagePack"] */
        } else {
            std::cout << "Failed to get data." << std::endl;
        }
    }
    return 0;
}
