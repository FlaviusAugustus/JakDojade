cmake_minimum_required(VERSION 3.25)
project(JakDojade)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FETCHCONTENT_DECLARE(

        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip

)

FETCHCONTENT_MAKEAVAILABLE(googletest)

add_executable(JakDojade main.cpp String/String.cpp String/String.h List/List.h List/List.tpp List/Node.h List/Node.tpp GraphConstructor.cpp GraphConstructor.h Vector/Vector.h Graph/Graph.cpp Graph/Graph.h Graph/graphNode.h Graph/Connection.h Graph/Point.h HashMap/HashMap.h HashMap/HashNode.h PriorityQueueDijkstra/PriorityQueueDijkstra.cpp PriorityQueueDijkstra/PriorityQueueDijkstra.h PriorityQueueDijkstra/DijkstraNode.h)
add_executable(Test test/test.cpp String/String.h String/String.cpp PriorityQueueDijkstra/PriorityQueueDijkstra.h PriorityQueueDijkstra/ GraphConstructor.cpp)

target_link_libraries(Test gtest gtest_main)
