#include "hello.hpp"
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/utils/daemon_run.hpp>
#include <userver/engine/async.hpp>
#include <userver/utils/uuid4.hpp>
#include <userver/utils/scope_guard.hpp>
//-------------------------------------------------------------------------------------------------------------

namespace Websocket {

void WebsocketsHandler::BroadcastMessage(std::string_view message){
    std::lock_guard<std::mutex> lock(connections_mutex);
    for(auto* connection : connections){
        try{
            connection->Send(server::websocket::Message{std::string{message}});
        } catch(const std::exception& ex){
            LOG_WARNING() << "error send message! - " << ex.what();
        }
        
    }
}
//-------------------------------------------------------------------------------------------------------------
void WebsocketsHandler::Handle(
    userver::server::websocket::WebSocketConnection& chat,
    userver::server::request::RequestContext&) const {
    
    // add new users
    {
        std::lock_guard<std::mutex> lock(connections_mutex);
        connections.insert(&chat);
    }

    //erase user if disconnetc
    //Deleting the connection when exiting the scope (RAII)
    auto connection_guard = userver::utils::ScopeGuard([&chat, this] {
        std::lock_guard<std::mutex> lock(connections_mutex);
        connections.erase(&chat);
        LOG_INFO() << "Connection removed from pool!";
    });
   
    // message for incoming messages
    userver::server::websocket::Message message; 

    // пока не будет запрошена отмена задачи
    while (!engine::current_task::ShouldCancel()) {
        chat.Recv(message);               // throws on closed/dropped connection
        if (message.close_status) break;  // explicit close if any
        if (message.is_text) BroadcastMessage(message.data);

        //chat.Send(std::move(message));    // throws on closed/dropped connection
    }
    if (message.close_status) chat.Close(*message.close_status);  // send messafe about closing confiramtion
}
//-------------------------------------------------------------------------------------------------------------
}  // namespace samples::websocket

