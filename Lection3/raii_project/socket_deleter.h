#pragma once

#include <memory>
#include <windows.h>

void deleteSocket(SOCKET* socket) {
    closesocket(*socket);
}

auto socketDeleter = [](SOCKET* socket) {
    closesocket(*socket);
};

class Functor {
public:
    void operator()(SOCKET* socket) {
        closesocket(*socket);
    }
};

void testSocketDeleters() {
    // using lambda "socket_deleter"
    std::unique_ptr<SOCKET, decltype(socketDeleter)> socket_example1(new SOCKET, socketDeleter);

    //using function pointer "delete_socket"
    std::unique_ptr<SOCKET, void(*)(SOCKET*)> socket_example2(new SOCKET, deleteSocket);

    //using function
    std::unique_ptr<SOCKET, Functor> socket_example3(new SOCKET);
}