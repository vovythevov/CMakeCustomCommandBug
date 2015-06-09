cmake_minimum_required( VERSION 2.8.12 )

project( LibBug )
include_directories( ${LibBug_SOURCE_DIR} ${LibBug_BINARY_DIR} )

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

# 1 - Create very simple executable
add_executable(bar_generator bar_generator.cxx)
target_link_libraries(bar_generator ${QT_LIBRARIES})

# 2- Configure launcher for executable
get_property(bar_generator_EXECUTABLE TARGET bar_generator PROPERTY LOCATION)
if (WIN32)
  get_filename_component(QT_BIN_DIR ${QT_QMAKE_EXECUTABLE} DIRECTORY)
  set(launcher_path ${CMAKE_CURRENT_BINARY_DIR}/launcher.bat)
  configure_file(
    ${LibBug_SOURCE_DIR}/launcher.bat.in
    ${launcher_path}
    @ONLY
    )
endif()
set(bar_generator_EXECUTABLE ${launcher_path} ${bar_generator_EXECUTABLE}
    CACHE INTERNAL "Location of the wrapper executable" FORCE
)

# 3- Try to compile foo
set(sources
  foo.h
  )
set(moc_headers
  foo.h
  )

qt4_wrap_ui(ui_sources foo.ui)

set(output_header ${CMAKE_CURRENT_BINARY_DIR}/bar.h)
set_source_files_properties(${output_header} PROPERTIES GENERATED TRUE)
message("${bar_generator_EXECUTABLE} ${output_header}")
add_custom_command(OUTPUT ${output_header}
  COMMAND ${bar_generator_EXECUTABLE} ${output_header}
  DEPENDS ${bar_generator_EXECUTABLE}
  )

qt4_wrap_cpp(moc_sources ${moc_headers})

#add_library(foo
#  ${ui_sources}
#  ${sources}
#  ${moc_sources}
#  ${output_header}
#  ) # this order works

add_library(foo
  ${sources}
  ${ui_sources}
  ${output_header}
  ${moc_sources}
  ) # this does not work
