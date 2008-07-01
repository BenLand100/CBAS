#
#  There exist several targets which are by default empty and which can be 
#  used for execution of your targets. These targets are usually executed 
#  before and after some main targets. They are: 
#
#     .build-pre:              called before 'build' target
#     .build-post:             called after 'build' target
#     .clean-pre:              called before 'clean' target
#     .clean-post:             called after 'clean' target
#     .clobber-pre:            called before 'clobber' target
#     .clobber-post:           called after 'clobber' target
#     .all-pre:                called before 'all' target
#     .all-post:               called after 'all' target
#     .help-pre:                called before 'help' target
#     .help-post:               called after 'help' target
#
#  Targets beginning with '.' are not intended to be called on their own.
#
#  Main targets can be executed directly, and they are:
#  
#     build                    build a specific configuration
#     clean                    remove built files from a configuration
#     clobber                  remove all built files
#     all                      build all configurations
#     help                     print help mesage
#  
#  Targets .build-impl, .clean-impl, .clobber-impl, .all-impl, and
#  .help-impl are implemented in nbproject/makefile-impl.mk.
#
# NOCDDL

# Environment 
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
WINDRES=/usr/local/cross-tools/bin/i386-mingw32-windres

# build
build: .build-pre .build-impl .build-post

.build-pre:
	ant -q -f ../CBAS_gui/build.xml compile
	rm -fr ../ClassPath
	mkdir ../ClassPath
	cp -R ../CBAS_gui/build/classes/* ../ClassPath
	make -C ../CBAS_lib/
	rm -f ../Lib/libcbas.dll
	cp ../CBAS_lib/dist/Debug/libcbas.dll ../Lib/
	${WINDRES} -o Resource.o Resource.rc
	cp ../CBAS_lib/jni.h ../CBAS_lib/jni_md.h ../CBAS_lib/Input.h ../CBAS_lib/Bitmap.h ../CBAS_lib/Color.h ../CBAS_lib/DebugWnd.h ../CBAS_lib/dll.h ../CBAS_lib/DTM.h ../CBAS_lib/Find.h ../CBAS_lib/Main.h ../CBAS_lib/Plugins.h ../CBAS_lib/Utils.h ../Includes/

.build-post:
	cp ./dist/Debug/CBAS.exe ../


# clean
clean: .clean-pre .clean-impl .clean-post

.clean-pre:
# Add your pre 'clean' code here...

.clean-post:
# Add your post 'clean' code here...


# clobber
clobber: .clobber-pre .clobber-impl .clobber-post

.clobber-pre:
# Add your pre 'clobber' code here...

.clobber-post:
# Add your post 'clobber' code here...


# all
all: .all-pre .all-impl .all-post

.all-pre:
# Add your pre 'all' code here...

.all-post:
# Add your post 'all' code here...


# help
help: .help-pre .help-impl .help-post

.help-pre:
# Add your pre 'help' code here...

.help-post:
# Add your post 'help' code here...



# include project implementation makefile
include nbproject/Makefile-impl.mk
