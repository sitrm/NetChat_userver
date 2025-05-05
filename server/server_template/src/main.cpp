#include "hello.hpp"
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/utils/daemon_run.hpp>



// [Websocket service sample - main]
int main(int argc, char* argv[]) {
    const auto component_list =
        userver::components::MinimalServerComponentList().Append<Websocket::WebsocketsHandler>();
        
    return userver::utils::DaemonMain(argc, argv, component_list);
}
// [Websocket service sample - main]