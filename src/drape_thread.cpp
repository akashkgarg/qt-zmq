#include "drape_thread.h"
#include <iostream>
#include <chrono>
#include <QDebug>

#include <zmq.hpp>

#include <msgpack.h>

#include <Eigen/Core>

//------------------------------------------------------------------------------

DrapeThread::DrapeThread() :
    QThread(NULL)
{
    qDebug() << "Created drape thread";
}

//------------------------------------------------------------------------------

DrapeThread::~DrapeThread()
{
    // Here we wait until the thread has finished executing the run() method.
    wait();

    qDebug() << "Finished drape thread!";
}

//------------------------------------------------------------------------------

void
DrapeThread::run()
{
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    // Step indefinitely.
    while (1) {
        zmq::message_t request;

        //  Wait for next request from client
        std::cout << "Waiting for request from client..." << std::endl;
        auto ret = socket.recv (request);
        std::cout << (ret.has_value() ? ret.value() : 0) << std::endl;
        std::cout << "Received Hello" << std::endl;

        msgpack_sbuffer* buffer = msgpack_sbuffer_new();
        msgpack_packer* pk = msgpack_packer_new(buffer, msgpack_sbuffer_write);

        Eigen::MatrixXd m = Eigen::MatrixXd::Random(10240, 10240);

        msgpack_pack_array(pk, 1);
        msgpack_pack_bin_with_body(pk, m.data(), m.size()*sizeof(double));

        std::cout << "sending trace: " << m.trace() << std::endl;

        //  Send reply back to client
        zmq::message_t reply (buffer->size);
        memcpy (reply.data (), buffer->data, buffer->size);
        socket.send (reply, zmq::send_flags::none);

        /* cleaning */
        msgpack_sbuffer_free(buffer);
        msgpack_packer_free(pk);
    }
}
