# Install script for directory: C:/Users/chris/Documents/git/vst3sdk/public.sdk/samples/vst

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/vstsdk")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/chris/Documents/git/HelloWorldVST/public.sdk/samples/vst/InterAppAudio/cmake_install.cmake")
  include("C:/Users/chris/Documents/git/HelloWorldVST/public.sdk/samples/vst/adelay/cmake_install.cmake")
  include("C:/Users/chris/Documents/git/HelloWorldVST/public.sdk/samples/vst/again/cmake_install.cmake")
  include("C:/Users/chris/Documents/git/HelloWorldVST/public.sdk/samples/vst/again_aax/cmake_install.cmake")
  include("C:/Users/chris/Documents/git/HelloWorldVST/public.sdk/samples/vst/channelcontext/cmake_install.cmake")
  include("C:/Users/chris/Documents/git/HelloWorldVST/public.sdk/samples/vst/hostchecker/cmake_install.cmake")
  include("C:/Users/chris/Documents/git/HelloWorldVST/public.sdk/samples/vst/mda-vst3/cmake_install.cmake")
  include("C:/Users/chris/Documents/git/HelloWorldVST/public.sdk/samples/vst/note_expression_synth/cmake_install.cmake")
  include("C:/Users/chris/Documents/git/HelloWorldVST/public.sdk/samples/vst/note_expression_text/cmake_install.cmake")
  include("C:/Users/chris/Documents/git/HelloWorldVST/public.sdk/samples/vst/pitchnames/cmake_install.cmake")
  include("C:/Users/chris/Documents/git/HelloWorldVST/public.sdk/samples/vst/prefetchablesupport/cmake_install.cmake")
  include("C:/Users/chris/Documents/git/HelloWorldVST/public.sdk/samples/vst/programchange/cmake_install.cmake")

endif()

