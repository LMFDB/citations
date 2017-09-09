#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#AC_CONFIG_MACRO_DIR(m4)

AC_PREREQ(2.57)
AC_INIT([bib2html],[2.1.6],[marchand@irisa.fr])
AC_CONFIG_AUX_DIR(cfg)

# Checks for programs.
AC_PROG_CXX
AC_PROG_RANLIB
AC_CHECK_TOOL(AR, ar crs, :)
AC_CHECK_PROG(HAVE_DOT, dot, YES, NO, ,)

AC_PROG_INSTALL
AC_PROG_MAKE_SET

########################################################################
# check for specific libraries
########################################################################

#-----------------------------------------------------------------------
# Check for -lm library
AC_CHECK_LIB(m,main)

########################################################################
# Extra checks
########################################################################
#-----------------------------------------------------------------------
# Get the OS name
OS=`uname -s`
AC_SUBST(OS,$OS)
#-----------------------------------------------------------------------
# Get the hostname
AC_SUBST(ac_hostname,$ac_hostname)
#-----------------------------------------------------------------------
# Get the compiler version
CXX_VERSION=`$CXX -dumpversion`
AC_SUBST(CXX_VERSION,$CXX_VERSION)

########################################################################
# check for compiler debug options
########################################################################
#-----------------------------------------------------------------------
# Remove -g option if it was fixed before automatically
CXXFLAGS=`echo $CXXFLAGS | sed -e "s;-g;;g"`

#-----------------------------------------------------------------------
# Manage the --enable-debug option
AC_MSG_CHECKING(whether to enable debugging)
AC_ARG_ENABLE(debug,
  AC_HELP_STRING([--enable-debug@<:@yes/no@:>@],
  [turn on debugging by adding -g compiler option [[default=no]] and add _g suffix to the build library names.]),enable_debug=yes, enable_debug=no)
if test "x$enable_debug" = "xyes"; then
  CXXFLAGS="$CXXFLAGS -g -Wno-deprecated"
  CPPFLAGS="$CPPFLAGS -DDEBUG"
  SUFFIX="_g"
  AC_MSG_RESULT(yes)
else
  CXXFLAGS="$CXXFLAGS"
  SUFFIX=""
  AC_MSG_RESULT(no)
fi


AC_SUBST(SUFFIX,$SUFFIX)

########################################################################
# Fix the name of the librairies
########################################################################

B2H_LIBNAME=$PACKAGE_TARNAME-$PACKAGE_VERSION$SUFFIX
AC_SUBST(B2H_LIBNAME,$B2H_LIBNAME)


########################################################################
# Add compiler options
########################################################################
#-----------------------------------------------------------------------
# Add systematically compiler options: -Wall -Wunused
CXXFLAGS="$CXXFLAGS -Wall -Wunused  -Wno-deprecated"
#-----------------------------------------------------------------------
# Add systematically compiler options: -Wall -Wunused
CPPFLAGS="$CPPFLAGS -D__${OS}_"
#-----------------------------------------------------------------------
# Set B2H home path
relpath=`dirname $0`
B2H_HOME=`(cd $relpath; pwd)` 
AC_SUBST(B2H_HOME)
#-----------------------------------------------------------------------
# Add systematically compiler options: -I$(B2H_DIR_INCLUDE)
#B2H_DIR_INCLUDE="$B2H_HOME/src"
CXXFLAGS="$CXXFLAGS  -I.."
#-----------------------------------------------------------------------
# Add systematically compiler options: -L$(B2H_LIB_PATH)
#B2H_LIB_PATH="$B2H_HOME/lib/$OS/$CXX_VERSION"
B2H_LIB_PATH="$B2H_HOME/lib"
LDFLAGS="$LDFLAGS -L$B2H_LIB_PATH"


########################################################################
# check for specific hardware
########################################################################

########################################################################
# Add all the ViSP libraries
########################################################################
# Is for the moment...
LIBS="-l$B2H_LIBNAME $LIBS"

########################################################################
# Create Makefiles
########################################################################
AC_SUBST_FILE(build_mk)
build_mk=$B2H_HOME/configs/build.mk
AC_SUBST_FILE(debug_mk)
debug_mk=$B2H_HOME/configs/debug.mk
AC_SUBST_FILE(directory_mk)
directory_mk=$B2H_HOME/configs/directory.mk
AC_SUBST_FILE(lib_mk)
lib_mk=$B2H_HOME/configs/lib.mk
AC_SUBST_FILE(bin_mk)
bin_mk=$B2H_HOME/configs/bin.mk
AC_SUBST_FILE(clean_mk)
clean_mk=$B2H_HOME/configs/clean.mk
AC_SUBST_FILE(uninstall_mk)
uninstall_mk=$B2H_HOME/configs/uninstall.mk

AC_CONFIG_FILES([
configs/build.mk
Makefile
src/Makefile
src/config/Makefile
src/database/Makefile
src/entry/Makefile
src/field/Makefile
src/tools/Makefile
src/main/Makefile
example/Makefile
example/bib/config.cnf
example/bib/html.cnf
example/bib/Makefile
example/tex/Makefile
example/tex/publi.tex
example/tex/em.tex
])
AC_OUTPUT

########################################################################
# Display compiler options
########################################################################
echo ""
echo "Building options:"
echo "Hostname     : $ac_hostname"
echo "Debugging on : $enable_debug"
echo "CXX          : $CXX"
echo "CXX version  : $CXX_VERSION"
echo "SUFFIX       : $SUFFIX"
echo "CXXFLAGS     : $CXXFLAGS"
echo "CPPFLAGS     : $CPPFLAGS"
echo "LDFLAGS      : $LDFLAGS"
echo "LIBS         : $LIBS"
