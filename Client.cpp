// Client-side
// using C++ boost::asio 
#include <iostream>
#include <boost/asio.hpp> 
#include <string> 
#include <boost/lexical_cast.hpp>

#define _WIN32_WINNT 0x0601

using namespace std; 
using namespace boost::asio; 
using namespace boost::asio::ip;

    string getData(tcp::socket& socket) 
    { 
        boost::asio::streambuf buf; 
        read_until(socket, buf, "\n"); 
        string data = buffer_cast<const char*>(buf.data()); 
        return data; 
    } 

    void sendData(tcp::socket& socket, const string& message) 
    { 
        write(socket, 
            buffer(message + "\n")); 
    }
    
    u_long randomnumber()
    {
    const uint32_t max_rand = 100000000;
    u_long x1 = 1000000, x2 = 100000000, x;

    x = x1 + ( x2 - x1) * (rand() % max_rand) / max_rand;
    return x;
   }

    int main(int argc, char* argv[]) 
    { 
        io_service io_service; 
        // socket creation 
        ip::tcp::socket client_socket(io_service); 

        client_socket.connect(tcp::endpoint( 
                    address::from_string("127.0.0.1"), 
                    1234)); 
                    
        string u_name, reply, response;         
        

        // Infinite loop
        while (true) { 
            
            // Sending random number to Server
             sendData(client_socket, boost::lexical_cast<string>(randomnumber()));

            // Fetching response 
            response = getData(client_socket); 

            // Popping last character "\n" 
            response.pop_back();
            
            sleep(0.5);

            // Validating if the connection has to be closed 
            if (response == "exit") { 
                cout << "Connection terminated" << endl; 
                break; 
            } 
            cout << "Server: " << response << endl; 

            if (reply == "exit") 
                break; 
        } 
        return 0; 
    }


