# Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

if(NOT ((MSVC OR MSVC_IDE) AND EPROSIMA_INSTALLER))
    include(${PROJECT_SOURCE_DIR}/cmake/dev/gtest.cmake)
    check_gtest()

    if(GTEST_FOUND)
        find_package(Threads REQUIRED)

        if(WIN32)
            add_definitions(-D_WIN32_WINNT=0x0601)
        endif()

        set(NETWORKFACTORYTESTS_SOURCE 
            NetworkFactoryTests.cpp 
            mock/MockTransport.cpp
            ${PROJECT_SOURCE_DIR}/src/cpp/rtps/network/NetworkFactory.cpp
            ${PROJECT_SOURCE_DIR}/src/cpp/rtps/network/ReceiverResource.cpp
            ${PROJECT_SOURCE_DIR}/src/cpp/rtps/network/SenderResource.cpp)

        include_directories(mock/)

        add_executable(NetworkFactoryTests ${NETWORKFACTORYTESTS_SOURCE})
        add_gtest(NetworkFactoryTests ${NETWORKFACTORYTESTS_SOURCE})
        target_compile_definitions(NetworkFactoryTests PRIVATE FASTRTPS_NO_LIB)
        target_include_directories(NetworkFactoryTests PRIVATE ${Boost_INCLUDE_DIR} ${GTEST_INCLUDE_DIRS}
            ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME})
        target_link_libraries(NetworkFactoryTests ${GTEST_LIBRARIES} ${Boost_LIBRARIES} ${MOCKS} ${CMAKE_THREAD_LIBS_INIT})
        target_link_libraries(NetworkFactoryTests fastrtps fastcdr) # Later so mocks have precedence
    endif()
endif()
