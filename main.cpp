// main.cpp
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <iostream>
#include "cuda_hello.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

 

class SumServer {
public:
    SumServer(utility::string_t url) : listener_(url) {
        listener_.support(methods::GET, std::bind(&SumServer::handle_get, this, std::placeholders::_1));
    }

    void handle_get(http_request request) {
         // Sample arrays for summation
           std::vector<int> array1 = {1, 6, 7, 8, 5};
           std::vector<int> array2 = {5, 4, 3, 2, 1};

           // Perform array summation on the GPU (CUDA)
           std::vector<int> gpuResult(array1.size());
           arraySumCUDA(array1, array2, gpuResult);

            // // Print the result on the host side
            // std::cout << "Result from CUDA: ";
            //    for (const auto& value : gpuResult) {
            //      std::cout << value << " ";
            // }
            // std::cout << std::endl;

           // Create a JSON array and add elements from the vector
            json::value gpuResultJsonArray;

            for (size_t i = 0; i < gpuResult.size(); ++i) {
                gpuResultJsonArray[i] = json::value::number(gpuResult[i]);
            }

           // Respond to the GET request with the results
           json::value response;
           response[U("GPU_Result")] = gpuResultJsonArray;
           request.reply(status_codes::OK, response);
    }

    pplx::task<void> open() { return listener_.open(); }
    pplx::task<void> close() { return listener_.close(); }

private:
    http_listener listener_;
};

int main() {
    utility::string_t url = U("http://localhost:8080");
    SumServer server(url);

    try {
        // Start the server
        server.open().wait();

        std::cout << L"Server listening at " << url << std::endl;

        // Keep the application running
        std::wstring line;
        std::getline(std::wcin, line);
    } catch (const std::exception& e) {
        std::wcerr << e.what() << std::endl;
    }

    // Close the server before exiting
    server.close().wait();

    return 0;
}
