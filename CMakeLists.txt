cmake_minimum_required(VERSION 3.16)

project(smgcRunner LANGUAGES C CXX)   # <- добавил C

# Устанавливаем стандарт C++20
set(CMAKE_CXX_STANDARD 23)
# Говорим, что это обязательное требование (если не потянет — вылетит с ошибкой)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Отключаем расширения компилятора (чтобы код был чистым стандартом)
set(CMAKE_CXX_STANDARD_EXTENSIONS OFF)

# --- glad ---
add_library(glad STATIC
    third_party/glad/src/glad.c
)
target_include_directories(glad PUBLIC
    third_party/glad/include
)
# Явно указываем язык линковки для glad
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)

# --- GLFW и OpenGL ---
find_package(glfw3 REQUIRED)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

add_executable(smgcRunner
  main.cpp
  #AndroidFix.cpp
  
  Core/Core.h Core/Core.cpp
  Core/BaseTask.h Core/BaseTask.cpp
  Core/BaseComponent.h Core/BaseComponent.cpp
  Core/tools.h Core/tools.cpp
  Core/Config.h Core/Config.cpp
  
  SMGC/shaderClass.h SMGC/shaderClass.cpp
  SMGC/VAO.h SMGC/VAO.cpp
  SMGC/VBO.h SMGC/VBO.cpp
  SMGC/EBO.h SMGC/EBO.cpp
  SMGC/SMGC.h SMGC/SMGC.cpp
)

target_link_libraries(smgcRunner PRIVATE
    glad
    glfw
    OpenGL::GL
)

include(GNUInstallDirs)
install(TARGETS smgcRunner
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)