#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libParseWebData.la

#######################################
# Build information for each library

# Sources for ParseWebData
libParseWebData_la_SOURCES = ParseWebData.cpp \
								ParseWebData_local.h \
								ParseMultipartFormData.h \
								ParseMultipartFormData.cpp 

# Linker options libTestProgram
libParseWebData_la_LDFLAGS = -version-info 0:0:0

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libParseWebData_la_CPPFLAGS = -I$(top_srcdir)/include

