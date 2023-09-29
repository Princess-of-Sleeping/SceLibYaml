cmake_minimum_required(VERSION 3.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(SceLibYaml)
include("${VITASDK}/share/vita.cmake" REQUIRED)
include(ExternalProject)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O2 -fno-inline -fno-builtin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")

enable_language(C ASM)

ExternalProject_add(libyaml_download
  URL http://pyyaml.org/download/libyaml/yaml-0.2.2.tar.gz
  URL_HASH SHA256=4a9100ab61047fd9bd395bcef3ce5403365cafd55c1e0d0299cde14958e47be9
  DOWNLOAD_DIR ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

set(libyaml_src
  libyaml_download-prefix/src/libyaml_download/src/api.c
  libyaml_download-prefix/src/libyaml_download/src/dumper.c
  libyaml_download-prefix/src/libyaml_download/src/emitter.c
  libyaml_download-prefix/src/libyaml_download/src/loader.c
  libyaml_download-prefix/src/libyaml_download/src/parser.c
  libyaml_download-prefix/src/libyaml_download/src/reader.c
  libyaml_download-prefix/src/libyaml_download/src/scanner.c
  libyaml_download-prefix/src/libyaml_download/src/writer.c
)

add_custom_command(
  OUTPUT ${libyaml_src}
  DEPENDS ${libyaml_download}
)

include_directories(
  libyaml_download-prefix/src/libyaml_download/include
)

add_executable(${PROJECT_NAME}
  src/main.c
  ${libyaml_src}
)

target_link_libraries(${PROJECT_NAME}
  SceLibc_stub
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_FLAGS "-nostdlib"
  COMPILE_FLAGS "-D__PSP2_USER__ -DNDEBUG -DYAML_VERSION_STRING='\"0.2.2\"' -DYAML_VERSION_MAJOR='0' -DYAML_VERSION_MINOR='2' -DYAML_VERSION_PATCH='2'"
)

vita_create_self(libSceYaml.suprx ${PROJECT_NAME}
  CONFIG exports.yml
  STRIPPED
  REL_OPTIMIZE
)

vita_create_stubs(${PROJECT_NAME}_stub ${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/exports.yml KERNEL)

install(FILES build/${PROJECT_NAME}_stub/libSceLibYaml_stub.a
  DESTINATION lib
)
