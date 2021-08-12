cmake_minimum_required(VERSION 3.16)
project(GtkTemplate C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(${GTK3_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS} ${GTKMM_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(gtk-template src/main.cpp)

target_link_options(gtk-template PRIVATE -rdynamic)
target_link_libraries(
  gtk-template PRIVATE 
  ${GTK3_LIBRARIES} 
  ${GTKMM_LIBRARIES}         
  ${CMAKE_THREAD_LIBS_INIT}
  )
