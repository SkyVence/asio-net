#include <asio.hpp>
#include <iostream>

using asio::ip::tcp;

int main() {
	try {
		asio::io_context io;
		tcp::resolver	 resolver(io);
		tcp::socket		 socket(io);

		auto endpoints = resolver.resolve("127.0.0.1", "8080");
		asio::connect(socket, endpoints);

		std::string msg = "Hello from client!";
		asio::write(socket, asio::buffer(msg));

		std::array<char, 1024> buf;
		size_t				   len = socket.read_some(asio::buffer(buf));

		std::cout << "Reply: " << std::string(buf.data(), len) << "\n";
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
}
