cmake_minimum_required(VERSION 3.21)

project(smgc VERSION 1.0.0 LANGUAGES C CXX)

if(PROJECT_IS_TOP_LEVEL)
  if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
  endif()

  include(CheckIPOSupported)
  check_ipo_supported(RESULT ipo_ok)
  if(ipo_ok)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
  endif()
endif()

# --- glad ---
if(NOT TARGET glad)
  add_library(glad STATIC
    third_party/glad/src/glad.c
  )
  target_include_directories(glad PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include>
  )
  # Явно указываем язык линковки для glad
  set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)
endif()

# --- GLFW и OpenGL ---
find_package(glfw3 REQUIRED)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# --- GLM ---
find_package(glm REQUIRED)

if(NOT TARGET smpb::core)
  include(FetchContent)
  FetchContent_Declare(smpb
    GIT_REPOSITORY https://github.com/s1m-ila/SMPB.git
    GIT_TAG        main
  )
  FetchContent_MakeAvailable(smpb)
endif()

# --- smgc::display3D ---
add_library(smgc_display3D STATIC
  src/smgc/shaderClass.cpp
  src/smgc/VAO.cpp
  src/smgc/VBO.cpp
  src/smgc/EBO.cpp
  src/smgc/ObjectsBuffer.cpp
  src/smgc/paletts.cpp
  src/smgc/taskDefinitions.cpp
  src/smgc/ObjectsGenerator.cpp
  src/smgc/display3D.cpp
)
add_library(smgc::display3D ALIAS smgc_display3D)

target_include_directories(smgc_display3D PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_compile_features(smgc_display3D PUBLIC cxx_std_23)
set_target_properties(smgc_display3D PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(smgc_display3D
  PUBLIC
    smpb::core
    glad
    glfw
    glm::glm
  PRIVATE
    OpenGL::GL
)

# --- FILES ---
function(smgc_copy_files TARGET)
  set(SMGC_FILES
      "default.vert"
      "default.frag"
  )

  foreach(FILE ${SMGC_FILES})
      add_custom_command(
          TARGET ${TARGET} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/files/${FILE}"
          "$<TARGET_FILE_DIR:${TARGET}>/files/${FILE}"
          COMMENT "Copying file ${FILE} to build directory..."
      )
  endforeach()
endfunction()

option(SMGC_BUILD_EXAMPLE "Build smgc example" ${PROJECT_IS_TOP_LEVEL})
if(SMGC_BUILD_EXAMPLE)
  add_executable(smgc
    example/main.cpp
    example/Scene.cpp
  )
  target_link_libraries(smgc PRIVATE smgc::display3D)
  set_target_properties(smgc PROPERTIES CXX_EXTENSIONS OFF)

  include(GNUInstallDirs)
  install(TARGETS smgc RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

  smgc_copy_files(smgc)

  set(FILES
      "core.config"
  )

  foreach(FILE ${FILES})
      add_custom_command(
          TARGET smgc POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "${CMAKE_CURRENT_SOURCE_DIR}/files/${FILE}"
          "$<TARGET_FILE_DIR:smgc>/files/${FILE}"
          COMMENT "Copying file ${FILE} to build directory..."
      )
  endforeach()
endif()
