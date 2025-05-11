#pragma once

#include <userver/utest/using_namespace_userver.hpp>
#include <userver/server/websocket/websocket_handler.hpp>
#include <userver/server/websocket/server.hpp>
//-------------------------------------------------------------------------------------------------------------
#include <userver/utils/uuid4.hpp>
#include <userver/engine/io/socket.hpp>
//-------------------------------------------------------------------------------------------------------------
#include <chrono>
#include <unordered_set>
#include <mutex>
//-------------------------------------------------------------------------------------------------------------
namespace Websocket {

struct ClientInfo{
    std::string id;
    std::string ip_address;
    server::websocket::WebSocketConnection* connection;
    std::chrono::system_clock::time_point connected_at;
};


/// [Websocket service sample - component]
class WebsocketsHandler final : public server::websocket::WebsocketHandlerBase {
public:
    // `kName` is used as the component name in static config
    static constexpr std::string_view kName = "websocket-handler";

public:
    // Component is valid after construction and is able to accept requests
    using WebsocketHandlerBase::WebsocketHandlerBase;  // наследуем конструктор базового класса 

    void Handle(userver::server::websocket::WebSocketConnection& chat,
                userver::server::request::RequestContext&) const override;
    // chat - объект соединения
    // контекст запроса     
//-------------------------------------------------------------------------------------------------------------
private:
	static void BroadcastMessage(std::string_view message);
  //  static void SendToClient(const std::string& client_id, std::string_view message);
    static std::vector<ClientInfo> GetConnectedClients();

    static ClientInfo CreateClientInfo(userver::server::websocket::WebSocketConnection& chat,
                                        userver::server::request::RequestContext&);
    
private:
    // static inline server::websocket::WebSocketConnection* connections;
	// static inline std::mutex connections_mutex;
    static inline std::unordered_map<std::string, ClientInfo> clients;
    static inline std::mutex clients_mutex;
};
/// [Websocket service sample - component]

}    // namespace samples::websocket