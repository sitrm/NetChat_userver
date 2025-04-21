#include "hello.hpp"
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/utils/daemon_run.hpp>

namespace samples::websocket {

void WebsocketsHandler::Handle(
    userver::server::websocket::WebSocketConnection& chat,
    userver::server::request::RequestContext&) const {
    userver::server::websocket::Message message;
    while (!engine::current_task::ShouldCancel()) {
        chat.Recv(message);               // throws on closed/dropped connection
        if (message.close_status) break;  // explicit close if any
        chat.Send(std::move(message));    // throws on closed/dropped connection
    }
    if (message.close_status) chat.Close(*message.close_status);
}

}  // namespace samples::websocket

