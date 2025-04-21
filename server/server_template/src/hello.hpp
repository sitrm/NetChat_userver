#pragma once

#include <userver/utest/using_namespace_userver.hpp>
#include <userver/server/websocket/websocket_handler.hpp>

namespace samples::websocket {

/// [Websocket service sample - component]
class WebsocketsHandler final : public server::websocket::WebsocketHandlerBase {
public:
    // `kName` is used as the component name in static config
    static constexpr std::string_view kName = "websocket-handler";

    // Component is valid after construction and is able to accept requests
    using WebsocketHandlerBase::WebsocketHandlerBase;

    void Handle(userver::server::websocket::WebSocketConnection& chat,
                userver::server::request::RequestContext&) const override;
};
/// [Websocket service sample - component]

}    // namespace samples::websocket