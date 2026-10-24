cmake_minimum_required(VERSION 3.16)

project(smgc LANGUAGES C CXX)   # <- добавил C

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Устанавливаем стандарт C++23
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

# --- GLM ---
find_package(glm REQUIRED)

include(FetchContent)
FetchContent_Declare(smpb
  GIT_REPOSITORY https://github.com/s1m-ila/SMPB.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(smpb)

add_executable(smgc
  main.cpp
  #AndroidFix.cpp
  
  SMGC/shaderClass.h SMGC/shaderClass.cpp
  SMGC/VAO.h SMGC/VAO.cpp
  SMGC/VBO.h SMGC/VBO.cpp
  SMGC/EBO.h SMGC/EBO.cpp
  SMGC/ObjectsBuffer.h SMGC/ObjectsBuffer.cpp
  SMGC/paletts.h SMGC/paletts.cpp
  SMGC/taskDefinitions.h SMGC/taskDefinitions.cpp
  SMGC/ObjectsGenerator.h SMGC/ObjectsGenerator.cpp
  SMGC/SMGC.h SMGC/SMGC.cpp

  Scene/Scene.h  Scene/Scene.cpp
)

# --- FILES ---
set(FILES
    "core.config"
    "SMGC/default.vert"
    "SMGC/default.frag"
)

foreach(FILE ${FILES})
    get_filename_component(FILENAME ${FILE} NAME)
    
    add_custom_command(
        TARGET smgc POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/${FILE}"
        "$<TARGET_FILE_DIR:smgc>/files/${FILENAME}"
        COMMENT "Copying file ${FILENAME} to build directory..."
    )
endforeach()

target_link_libraries(smgc PRIVATE
    smpb::core
    glad
    glfw
    OpenGL::GL
    glm::glm
)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_ok)
if(ipo_ok)
  set_property(TARGET smgc PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
endif()

include(GNUInstallDirs)
install(TARGETS smgc
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
