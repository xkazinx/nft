# The nft client for a web browser (WebAssembly, Emscripten). Windows builds the
# client from client.vcxproj (build.ps1); this file is the web one, run by
# build_web.ps1 against kazilib's SFML web build (kazilib web/build_deps.ps1):
#   emcmake cmake -S src/client -B <build> -G Ninja -DSFML_DIR=...
# Output: index.html / .js / .wasm / .data (fonts, configs.json, default.txt, the
# cogollo PNGs from build/client) - the folder kazin.dev/projects/nft serves.
cmake_minimum_required(VERSION 3.21)
project(nft_web CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NFT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(NFT_DATA ${NFT_SRC}/../build/client)
set(SFML_STATIC_LIBRARIES ON)
find_package(SFML 3 REQUIRED COMPONENTS Graphics)
include(${NFT_SRC}/dep/kazilib/web/kazilib_web.cmake)

file(GLOB CLIENT_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(nft ${CLIENT_SOURCES})
kazilib_web_target(nft)
# The ImGui panels when kazilib's web build has ImGui (else the client runs without them)
if(COMMAND kazilib_web_imgui)
	kazilib_web_imgui(nft)
	target_compile_definitions(nft PRIVATE NFT_WEB_IMGUI)
	message(STATUS "nft: ImGui on the web")
else()
	message(STATUS "nft: no ImGui on the web (kazilib_web.cmake has no kazilib_web_imgui)")
endif()
target_include_directories(nft PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(nft PRIVATE SFML::Graphics)
target_link_options(nft PRIVATE
	"--preload-file=${NFT_DATA}/arial.ttf@/arial.ttf"
	"--preload-file=${NFT_DATA}/arialbd.ttf@/arialbd.ttf"
	"--preload-file=${NFT_DATA}/arialbi.ttf@/arialbi.ttf"
	"--preload-file=${NFT_DATA}/ariali.ttf@/ariali.ttf"
	"--preload-file=${NFT_DATA}/ariblk.ttf@/ariblk.ttf"
	"--preload-file=${NFT_DATA}/configs.json@/configs.json"
	"--preload-file=${NFT_DATA}/default.txt@/default.txt"
	"--preload-file=${NFT_DATA}/imgui.ini@/imgui.ini"
	"--preload-file=${NFT_DATA}/data/cogollo@/data/cogollo")
