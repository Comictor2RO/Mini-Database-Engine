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

// Handles communication with a connected client
void NetworkServer::handleClient(tcp::socket socket)
{
    auto sharedSocket = std::make_shared<tcp::socket>(std::move(socket));
    auto buffer = std::make_shared<asio::streambuf>();

    asio::async_read_until(*sharedSocket, *buffer, "\n", [this, sharedSocket, buffer](asio::error_code ec, std::size_t bytes_transferred) {
        if (!ec && bytes_transferred > 0) {

            std::istream is(buffer.get());
            std::string message;
            std::getline(is, message);

            executeCommand(message);
        }
        else {
            std::cerr << "Error reading from client: " << ec.message() << std::endl;
        }
    });
}


