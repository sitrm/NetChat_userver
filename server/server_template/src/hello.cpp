#include "hello.hpp"
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/utils/daemon_run.hpp>
#include <userver/utils/uuid4.hpp>
#include <userver/utils/scope_guard.hpp>
#include <userver/engine/io/socket.hpp>
#include <userver/engine/async.hpp>
#include <fmt/format.h>
//-------------------------------------------------------------------------------------------------------------

namespace Websocket {

void WebsocketsHandler::BroadcastMessage(std::string_view message){
    std::lock_guard<std::mutex> lock(clients_mutex);
    
    for(const auto& [id, client] : clients){
        try{
            client.connection->Send(server::websocket::Message{std::string{message}});
        } catch (const std::exception& exp){
            LOG_WARNING() << "Failed to send message to client " << id << ":" << exp.what();
        }
    }
}
//-------------------------------------------------------------------------------------------------------------
ClientInfo WebsocketsHandler::CreateClientInfo(
    userver::server::websocket::WebSocketConnection& chat,
    userver::server::request::RequestContext& context) {

    // get ip_address
    std::string ip_address = "unknown";
    try{
        // get ip ?????
        
    } catch (const std::exception& ex){
        LOG_WARNING() << "Failed to get client IP: " << ex.what();
    }

    return ClientInfo{
        userver::utils::generators::GenerateUuid(),
        std::move(ip_address),
        &chat,
        std::chrono::system_clock::now() };
        
}
//-------------------------------------------------------------------------------------------------------------
std::vector<ClientInfo> WebsocketsHandler::GetConnectedClients(){

    std::lock_guard<std::mutex> lock(clients_mutex);
    std::vector<ClientInfo> result;

    for(const auto& [id, client] : clients){
        result.push_back(client);
    }
    return result;
}
//-------------------------------------------------------------------------------------------------------------
void WebsocketsHandler::Handle(
    userver::server::websocket::WebSocketConnection& chat,
    userver::server::request::RequestContext& context) const {
    
    auto client_info = CreateClientInfo(chat, context);
    std::string client_id = client_info.id;

    // add new users
    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        clients.emplace(client_id, client_info);
    }

    LOG_INFO() << fmt::format("New client connected: ID={}, IP={}",
                                client_id, client_info.ip_address);

    chat.Send(server::websocket::Message{
        fmt::format("Welcome! Your ID: {}", client_id)});

    //erase user if disconnetc
    //Deleting the connection when exiting the scope (RAII)
    auto connection_guard = userver::utils::ScopeGuard([this, client_id] {
        std::lock_guard<std::mutex> lock(clients_mutex);
        if(clients.erase(client_id)){
            LOG_INFO() << fmt::format("Client disconnected: ID={}", client_id);
        }
    });
   
    // message for incoming messages
    userver::server::websocket::Message message; 

    // пока не будет запрошена отмена задачи
    while (!engine::current_task::ShouldCancel()) {
        chat.Recv(message);               // throws on closed/dropped connection
        if (message.close_status) break;  // explicit close if any
        if (message.is_text) {
            if (!message.data.empty()){
                LOG_INFO() << fmt::format("Message from client {}: {}", client_id, message.data);
                BroadcastMessage(fmt::format("{}", message.data));
            }
        }
    }

    if (message.close_status) chat.Close(*message.close_status);  // send messafe about closing confiramtion
}
//-------------------------------------------------------------------------------------------------------------
}  // namespace samples::websocket