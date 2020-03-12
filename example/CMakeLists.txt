cmake_minimum_required(VERSION 3.13)

project(jsonSettings LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADER_FILES
	../src/settings.h
	)

set(jsonSettings_SRCS
    main.cpp
    ../src/settings.cpp
    ${HEADER_FILES}
    )

add_executable(jsonSettings ${jsonSettings_SRCS})
target_include_directories(jsonSettings PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(jsonSettings PRIVATE Threads::Threads)

find_package(PkgConfig REQUIRED)

pkg_check_modules(JSONPP REQUIRED libjsonpp-0.1)
target_link_libraries(jsonSettings PUBLIC ${JSONPP_LIBRARIES})
target_link_options(jsonSettings PUBLIC ${JSONPP_LDFLAGS})

install(TARGETS jsonSettings
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/usr/bin)

