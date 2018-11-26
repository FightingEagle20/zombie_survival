cmake_minimum_required(VERSION 3.12)
project(zombie_survival C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c Textures.c Textures.h Player.c Player.h Globals.c Globals.h Start.c Start.h Finish.c Finish.h Timer.c Timer.h Entity.c Entity.h Map.c Map.h Zombie.c Zombie.h Pathfinding.c Pathfinding.h Weapon.c Weapon.h Projectiles.c Projectiles.h Loot.c Loot.h Game.c Game.h Menu.c Menu.h MenuElements.c MenuElements.h)
set(SDL2_INCLUDE_DIR C:/MinGW/include/SDL2)
set(SDL2_LIBRARY C:/MinGW/lib)

find_package(SDL2 REQUIRED)

add_executable(zombie_survival ${SOURCE_FILES})
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(zombie_survival ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf)
#-mwindows