#include <iostream>
#include <string>
#include <filesystem>

#include <boost/asio.hpp>

#include "fileHandle.h"


namespace basio = boost::asio;
namespace ip = boost::asio::ip;

using basio::ip::tcp;

int main(int argc, char* argv[]) {

    try {
        if(argc < 1) {
            std::cerr << "Not enough arguments" << std::endl;
            exit(1);
        }

        basio::io_context io_context;
        ip::tcp::acceptor acceptor(io_context, ip::tcp::endpoint(ip::tcp::v4(), 12345));

        while(true) {
            ip::tcp::socket socket(io_context);
            acceptor.accept(socket);

            char file_name_buffer[1024];
            size_t file_name_length = socket.read_some(basio::buffer(file_name_buffer));

            std::string file_path(file_name_buffer, file_name_length);
            auto file_name = std::filesystem::path(file_path).filename().string();
            std::cout << "Received file: " << file_name << std::endl;

            auto file = getFileHandle(file_name.c_str(), CREATE_ALWAYS);

            size_t total_received_bytes = 0;

            while(true) {
                char buffer[1024];

                try {
                    size_t received_bytes = socket.read_some(basio::buffer(buffer));
                    if (received_bytes == 0) {
                        std::cout << "empty response" << std::endl;
                        break;
                    }

                    total_received_bytes += received_bytes;

                    DWORD bytesWritten;
                    WriteFile(file, buffer, received_bytes, &bytesWritten, NULL);
                    if (bytesWritten != received_bytes) {
                        std::cerr << "Error writing to file" << std::endl;
                        break;
                    }
                    else {
                        basio::write(socket, basio::buffer(std::to_string(total_received_bytes)));
                    }
                }
                catch(std::exception& ex) {
                    std::cerr << ex.what() << std::endl;
                    break;
                }
            }

            CloseHandle(file);
        }


    }
    catch(const std::exception& ex) {
        std::cout << "exception :" << ex.what() << std::endl;
        exit(1);
    }

}