#pragma once

#include <userver/utest/using_namespace_userver.hpp>
#include <userver/server/websocket/websocket_handler.hpp>
#include <userver/server/websocket/server.hpp>
//-------------------------------------------------------------------------------------------------------------
#include <unordered_set>
#include <mutex>
//-------------------------------------------------------------------------------------------------------------
namespace Websocket {

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

private:
	static inline std::unordered_set<server::websocket::WebSocketConnection*> connections;
	static inline std::mutex connections_mutex;
};
/// [Websocket service sample - component]

}    // namespace samples::websocket