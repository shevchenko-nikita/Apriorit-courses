#include <iostream>
#include <string>

#include <boost/asio.hpp>

#include "fileHandle.h"

namespace basio = boost::asio;

using basio::ip::tcp;

void sendFile(tcp::socket& socket, char* path) {
    try {
        HANDLE file = getFileHandle(path, OPEN_EXISTING);

        std::string file_name(path);
        DWORD file_size = GetFileSize(file, NULL);

        basio::write(socket, basio::buffer(file_name));
//        basio::write(socket, basio::buffer(std::to_string(file_size)));

        while (true) {
            DWORD bytesRead = 0;
            char buffer[1024];
            if (!ReadFile(file, buffer, sizeof(buffer), &bytesRead, NULL) || bytesRead == 0)
                break;
            basio::write(socket, basio::buffer(buffer, bytesRead));
        }
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        exit(1);
    }

}

int main(int argc, char* argv[]) {


    try {
        if(argc < 2) {
            std::cerr << "Not enough arguments" << std::endl;
            exit(1);
        }

        basio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("localhost", "12345");

        tcp::socket socket(io_context);
        basio::connect(socket, endpoints);

        sendFile(socket, argv[1]);
        std::cout << fileReceiveStatus() << std::endl;
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        exit(1);
    }
}