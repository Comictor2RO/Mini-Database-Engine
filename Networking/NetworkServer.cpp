#include "NetworkServer.hpp"

NetworkServer::NetworkServer(size_t port, Engine &engine)
    : port(port), engine(engine), acceptor(io_context)
{};

// Opens the server on the specified port
void NetworkServer::openServer()
{
    acceptor.open(tcp::v4());
    acceptor.bind(tcp::endpoint(tcp::v4(), port));
    acceptor.listen();
    std::cout << "Server started at 127.0.0.1:" << port << std::endl;
}

// Accepts incoming connections and handles them async
void NetworkServer::acceptConnections()
{
    acceptor.async_accept(io_context, [this](asio::error_code ec, tcp::socket socket) {
        if (!ec) {
            handleClient(std::move(socket));
            std::cout << "Client connected" << std::endl;
        }
        else {
            std::cerr << "Error accepting connection: " << ec.message() << std::endl;
        }

        acceptConnections();
    });
}
