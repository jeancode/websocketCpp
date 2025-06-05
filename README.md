# Cliente WebSocket en C++ con WebSocket++ y ASIO (sin TLS)

Este proyecto implementa un cliente WebSocket simple usando la biblioteca [WebSocket++](https://github.com/zaphoyd/websocketpp) y ASIO como backend, sin usar Boost ni TLS.

## Características

- Conexión a un servidor WebSocket.
- Envío automático de un mensaje al conectar.
- Recepción e impresión de mensajes desde el servidor.
- Manejo de errores de conexión y cierre de la conexión.

## Requisitos

- C++11 o superior
- [WebSocket++](https://github.com/zaphoyd/websocketpp)
- [ASIO](https://think-async.com/Asio/) (puede usarse como standalone)

## Compilación

Asegúrate de tener WebSocket++ y ASIO en tu sistema. Luego compila con:

