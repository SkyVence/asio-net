#include "asio.hpp"
#include "server.hpp"

#include <iostream>

using asio::ip::tcp;

Server::Server(std::string Ip, int Port) {
	try {
		asio::io_context io;
		tcp::acceptor	 acceptor(io, tcp::endpoint(tcp::v4(), Port));

		while (true) {
			tcp::socket socket(io);
			acceptor.accept(socket);

			std::array<char, 1024> buf;
			asio::error_code	   ec;
			size_t				   len = socket.read_some(asio::buffer(buf), ec);

			if (!ec) {
				std::cout << "Received: " << std::string(buf.data(), len) << "\n";
				asio::write(socket, asio::buffer(buf, len));
			}
		}

	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
}
Server::~Server() {}
