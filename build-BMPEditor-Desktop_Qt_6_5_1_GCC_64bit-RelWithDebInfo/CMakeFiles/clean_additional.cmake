# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "BMPEditor_autogen"
  "CMakeFiles/BMPEditor_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/BMPEditor_autogen.dir/ParseCache.txt"
  )
endif()
