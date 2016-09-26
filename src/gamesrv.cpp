#include "gamesrv.hpp"

#include <iostream>
#include <cstdlib>

#include "db.hpp"
#include "websocketsrv.hpp"
#include "macros.hpp"

// static initialization
bool GameSrv::is_initialized= false;
bool GameSrv::is_running= false;
std::queue<Msg> GameSrv::msgQueue;
std::thread GameSrv::ws_thread;

//******************************************************************************

void GameSrv::start()
{
    if(!is_initialized)
        init();

    run();
}

void GameSrv::stop() {}

void GameSrv::init()
{
    std::cout << "Hexawars game server\n"
              << "build:  " << BUILD << std::endl << "author: Paweł \"ptaszkie\" Ptaszkiewicz\n\n";

    std::cout << "-- DB connection initialization\n";
    DB::init();

    std::cout << "-- WebSocket server initialization\n";
    if(!WebSocketSrv::init())
        exit(-1);

    is_initialized= true;
}

void GameSrv::run()
{
    // std::cout << "Przykladowe pobranie danych\n";
    // auto con= DB::getConnection();
    // con->findPlayer("57c1f103271934151a3a6041");

    std::cout << "Starting WebSocket thread\n";
    ws_thread= std::thread(WebSocketSrv::run);

    std::cout << "Starting processing loop\n\n";
    
    std::cout << "Logs:\n";
    
    while(is_running) {
        // TODO: petla przetwarzajaca wiadomosci

        if(!msgQueue.empty()) {
            m_msgQueue.lock();

            auto m = msgQueue.front();
            msgQueue.pop();

            m_msgQueue.unlock();
            
            m.process();
            
        }
    }

    ws_thread.join();
}

void GameSrv::addMsg(Msg m)
{
    std::lock_guard<std::mutex> lock(m_msgQueue);
    msgQueue.push(m);
}

/********************************************************************
void gamesrv::start()
{
    (...)

    if(!ws_server::init())
    {
        cout << "Wystąpił problem z inicjalizacją serwera WebSocket.\n";
        exit(-1);
    };

    // start websocket serwera
    //ws_server::run();
    //ws_server::stop();


    DB::clear();
}

*********************************************************************/

#ifdef zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz

#include "gamesrv.h"

void gamesrv::start()
{
    cout << "SERWER GRY HEXAWARS\n"
         << "wersja: 0.01\n"
         << "autor: Paweł Ptaszkiewicz (Quave)\n\n";

    DB::init();

    if(!ws_server::init()) {
        cout << "Wystąpił problem z inicjalizacją serwera WebSocket.\n";
        exit(-1);
    };

    // start websocket serwera
    // ws_server::run();
    // ws_server::stop();

    DB::clear();
}

#endif
