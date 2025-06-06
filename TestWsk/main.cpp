#define ASIO_STANDALONE
#define _WEBSOCKETPP_NO_BOOST_CONFIG_
#define _WEBSOCKETPP_NO_BOOST_RANDOM_
#define _WEBSOCKETPP_CPP11_STL_

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <iostream>
#include <string>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class ws_client {
public:
    ws_client() {
        // Inicializar ASIO
        c.init_asio();

        // Registrar handlers
        c.set_open_handler([this](websocketpp::connection_hdl hdl) {
            std::cout << "Conectado al servidor\n";
            this->hdl = hdl;

            websocketpp::lib::error_code ec;
            c.send(hdl, "¡Hola desde websocketpp!", websocketpp::frame::opcode::binary, ec);
            if (ec) {
                std::cerr << "Error al enviar mensaje: " << ec.message() << std::endl;
            }
            });

        c.set_message_handler([](websocketpp::connection_hdl, client::message_ptr msg) {
            std::cout << "Mensaje recibido: " << msg->get_payload() << std::endl;
            });

        c.set_fail_handler([this](websocketpp::connection_hdl hdl) {
            client::connection_ptr con = c.get_con_from_hdl(hdl);
            std::cerr << "Fallo en la conexión: " << con->get_ec().message() << std::endl;
            });

        c.set_close_handler([](websocketpp::connection_hdl) {
            std::cout << "Conexión cerrada por el servidor o el cliente\n";
            });
    }

    void start(const std::string& uri) {
        websocketpp::lib::error_code ec;
        client::connection_ptr con = c.get_connection(uri, ec);
        if (ec) {
            std::cerr << "Error al conectar: " << ec.message() << std::endl;
            return;
        }

        c.connect(con);

        try {
            c.run(); // Bloquea hasta que termine la conexión
        }
        catch (const std::exception& e) {
            std::cerr << "Excepción en run(): " << e.what() << std::endl;
        }
        catch (...) {
            std::cerr << "Excepción desconocida en run()\n";
        }
    }

private:
    client c;
    websocketpp::connection_hdl hdl;
};

int main() {
    try {
        ws_client cliente;
        cliente.start("ws://localhost:9002");
    }
    catch (const std::exception& e) {
        std::cerr << "Excepción en main: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Excepción desconocida en main\n";
    }
    return 0;
}
