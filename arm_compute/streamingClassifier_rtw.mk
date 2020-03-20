###########################################################################
## Makefile generated for MATLAB file/project 'streamingClassifier'. 
## 
## Makefile     : streamingClassifier_rtw.mk
## Generated on : Fri Mar 20 02:42:32 2020
## MATLAB Coder version: 5.0 (R2020a)
## 
## Build Info:
## 
## Final product: .\streamingClassifier.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPILER_COMMAND_FILE   Compiler command listing model reference header paths
# CMD_FILE                Command file
# MODELLIB                Static library target

PRODUCT_NAME              = streamingClassifier
MAKEFILE                  = streamingClassifier_rtw.mk
MATLAB_ROOT               = C:\PROGRA~1\MATLAB\R2020a
MATLAB_BIN                = C:\PROGRA~1\MATLAB\R2020a\bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)\win64
MASTER_ANCHOR_DIR         = 
START_DIR                 = Q:\work\aircompressorclassification\arm_compute
TGT_FCN_LIB               = ISO_C++
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = .
override START_DIR        = .
COMPILER_COMMAND_FILE     = streamingClassifier_rtw_comp.rsp
CMD_FILE                  = streamingClassifier_rtw.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
NODEBUG                   = 1
MODELLIB                  = streamingClassifier.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Microsoft Visual C++ 2017 v15.0 | nmake (64-bit Windows)
# Supported Version(s):    15.0
# ToolchainInfo Version:   2020a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# NODEBUG
# cvarsdll
# cvarsmt
# conlibsmt
# ldebug
# conflags
# cflags

#-----------
# MACROS
#-----------

MW_EXTERNLIB_DIR    = $(MATLAB_ROOT)\extern\lib\win64\microsoft
MW_LIB_DIR          = $(MATLAB_ROOT)\lib\win64
CPU                 = AMD64
APPVER              = 5.02
CVARSFLAG           = $(cvarsmt)
CFLAGS_ADDITIONAL   = -D_CRT_SECURE_NO_WARNINGS
CPPFLAGS_ADDITIONAL = -EHs -D_CRT_SECURE_NO_WARNINGS
LIBS_TOOLCHAIN      = $(conlibs)

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Microsoft Visual C Compiler
CC = cl

# Linker: Microsoft Visual C Linker
LD = link

# C++ Compiler: Microsoft Visual C++ Compiler
CPP = cl

# C++ Linker: Microsoft Visual C++ Linker
CPP_LD = link

# Archiver: Microsoft Visual C/C++ Archiver
AR = lib

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)\mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: NMAKE Utility
MAKE = nmake


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -Zi
C_OUTPUT_FLAG       = -Fo
LDDEBUG             = /DEBUG
OUTPUT_FLAG         = -out:
CPPDEBUG            = -Zi
CPP_OUTPUT_FLAG     = -Fo
CPPLDDEBUG          = /DEBUG
OUTPUT_FLAG         = -out:
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = -out:
MEX_DEBUG           = -g
RM                  = @del
ECHO                = @echo
MV                  = @ren
RUN                 = @cmd /C

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = /nologo
CFLAGS               = $(cflags) $(CVARSFLAG) $(CFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPPFLAGS             = /TP $(cflags) $(CVARSFLAG) $(CPPFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPP_LDFLAGS          = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
CPP_SHAREDLIB_LDFLAGS  = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                         -dll -def:$(DEF_FILE)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                       -dll -def:$(DEF_FILE)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = .\streamingClassifier.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -DUSE_19_02_LIBRARY -DMODEL=streamingClassifier
DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=streamingClassifier

DEFINES = $(DEFINES_) $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = MWLSTMLayer.cpp MWSequenceInputLayer.cpp cnn_api.cpp MWCNNLayerImpl.cpp MWLSTMLayerImpl.cpp MWSequenceInputLayerImpl.cpp MWTargetNetworkImpl.cpp MWACLUtils.cpp $(START_DIR)\rt_nonfinite.cpp $(START_DIR)\rtGetNaN.cpp $(START_DIR)\rtGetInf.cpp $(START_DIR)\streamingClassifier_rtwutil.cpp $(START_DIR)\streamingClassifier_data.cpp $(START_DIR)\streamingClassifier_initialize.cpp $(START_DIR)\streamingClassifier_terminate.cpp $(START_DIR)\streamingClassifier.cpp $(START_DIR)\DeepLearningNetwork.cpp $(START_DIR)\matlabCodegenHandle.cpp $(START_DIR)\predictAndUpdateState.cpp $(START_DIR)\extractFeatures.cpp $(START_DIR)\sum.cpp $(START_DIR)\STFTCG.cpp $(START_DIR)\STFTSysObj.cpp $(START_DIR)\SystemProp.cpp $(START_DIR)\SystemCore.cpp $(START_DIR)\ProcessConstructorArguments.cpp $(START_DIR)\bsxfun.cpp $(START_DIR)\FFTImplementationCallback.cpp $(START_DIR)\AsyncBuffercg.cpp $(START_DIR)\AsyncBuffercgHelper.cpp $(START_DIR)\spectralCentroid.cpp $(START_DIR)\spectralCrest.cpp $(START_DIR)\spectralDecrease.cpp $(START_DIR)\spectralEntropy.cpp $(START_DIR)\spectralFlatness.cpp $(START_DIR)\spectralKurtosis.cpp $(START_DIR)\spectralRolloffPoint.cpp $(START_DIR)\spectralSkewness.cpp $(START_DIR)\spectralSlope.cpp $(START_DIR)\spectralSpread.cpp

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = MWLSTMLayer.obj MWSequenceInputLayer.obj cnn_api.obj MWCNNLayerImpl.obj MWLSTMLayerImpl.obj MWSequenceInputLayerImpl.obj MWTargetNetworkImpl.obj MWACLUtils.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj streamingClassifier_rtwutil.obj streamingClassifier_data.obj streamingClassifier_initialize.obj streamingClassifier_terminate.obj streamingClassifier.obj DeepLearningNetwork.obj matlabCodegenHandle.obj predictAndUpdateState.obj extractFeatures.obj sum.obj STFTCG.obj STFTSysObj.obj SystemProp.obj SystemCore.obj ProcessConstructorArguments.obj bsxfun.obj FFTImplementationCallback.obj AsyncBuffercg.obj AsyncBuffercgHelper.obj spectralCentroid.obj spectralCrest.obj spectralDecrease.obj spectralEntropy.obj spectralFlatness.obj spectralKurtosis.obj spectralRolloffPoint.obj spectralSkewness.obj spectralSlope.obj spectralSpread.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_ =  -std=c++11  -mfpu=neon  -fopenmp
CFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CFLAGS = $(CFLAGS) $(CFLAGS_) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_ =  -std=c++11  -mfpu=neon  -fopenmp
CPPFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CPPFLAGS = $(CPPFLAGS) $(CPPFLAGS_) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_ = -L"$(ARM_COMPUTELIB)/lib" -rdynamic -larm_compute -larm_compute_core -Wl,-rpath,"$(ARM_COMPUTELIB)/lib":-L"$(ARM_COMPUTELIB)/lib"  -fopenmp

CPP_LDFLAGS = $(CPP_LDFLAGS) $(CPP_LDFLAGS_)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_ = -L"$(ARM_COMPUTELIB)/lib" -rdynamic -larm_compute -larm_compute_core -Wl,-rpath,"$(ARM_COMPUTELIB)/lib":-L"$(ARM_COMPUTELIB)/lib"  -fopenmp

CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS) $(CPP_SHAREDLIB_LDFLAGS_)

#-----------
# Linker
#-----------

LDFLAGS_ = -L"$(ARM_COMPUTELIB)/lib" -rdynamic -larm_compute -larm_compute_core -Wl,-rpath,"$(ARM_COMPUTELIB)/lib":-L"$(ARM_COMPUTELIB)/lib"  -fopenmp

LDFLAGS = $(LDFLAGS) $(LDFLAGS_)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_ = -L"$(ARM_COMPUTELIB)/lib" -rdynamic -larm_compute -larm_compute_core -Wl,-rpath,"$(ARM_COMPUTELIB)/lib":-L"$(ARM_COMPUTELIB)/lib"  -fopenmp

SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS) $(SHAREDLIB_LDFLAGS_)

###########################################################################
## INLINED COMMANDS
###########################################################################


!include $(MATLAB_ROOT)\rtw\c\tools\vcdefs.mak


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute set_environment_variables


all : build
	@cmd /C "@echo ### Successfully generated all binary outputs."


build : set_environment_variables prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


set_environment_variables : 
	@set INCLUDE=$(INCLUDES);$(INCLUDE)
	@set LIB=$(LIB)


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@cmd /C "@echo ### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS) -out:$(PRODUCT) @$(CMD_FILE)
	@cmd /C "@echo ### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{Q:\work\aircompressorclassification}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{Q:\work\aircompressorclassification}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


rt_nonfinite.obj : $(START_DIR)\rt_nonfinite.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\rt_nonfinite.cpp


rtGetNaN.obj : $(START_DIR)\rtGetNaN.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\rtGetNaN.cpp


rtGetInf.obj : $(START_DIR)\rtGetInf.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\rtGetInf.cpp


streamingClassifier_rtwutil.obj : $(START_DIR)\streamingClassifier_rtwutil.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\streamingClassifier_rtwutil.cpp


streamingClassifier_data.obj : $(START_DIR)\streamingClassifier_data.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\streamingClassifier_data.cpp


streamingClassifier_initialize.obj : $(START_DIR)\streamingClassifier_initialize.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\streamingClassifier_initialize.cpp


streamingClassifier_terminate.obj : $(START_DIR)\streamingClassifier_terminate.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\streamingClassifier_terminate.cpp


streamingClassifier.obj : $(START_DIR)\streamingClassifier.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\streamingClassifier.cpp


DeepLearningNetwork.obj : $(START_DIR)\DeepLearningNetwork.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\DeepLearningNetwork.cpp


matlabCodegenHandle.obj : $(START_DIR)\matlabCodegenHandle.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\matlabCodegenHandle.cpp


predictAndUpdateState.obj : $(START_DIR)\predictAndUpdateState.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\predictAndUpdateState.cpp


extractFeatures.obj : $(START_DIR)\extractFeatures.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\extractFeatures.cpp


sum.obj : $(START_DIR)\sum.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\sum.cpp


STFTCG.obj : $(START_DIR)\STFTCG.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\STFTCG.cpp


STFTSysObj.obj : $(START_DIR)\STFTSysObj.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\STFTSysObj.cpp


SystemProp.obj : $(START_DIR)\SystemProp.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\SystemProp.cpp


SystemCore.obj : $(START_DIR)\SystemCore.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\SystemCore.cpp


ProcessConstructorArguments.obj : $(START_DIR)\ProcessConstructorArguments.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\ProcessConstructorArguments.cpp


bsxfun.obj : $(START_DIR)\bsxfun.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\bsxfun.cpp


FFTImplementationCallback.obj : $(START_DIR)\FFTImplementationCallback.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\FFTImplementationCallback.cpp


AsyncBuffercg.obj : $(START_DIR)\AsyncBuffercg.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\AsyncBuffercg.cpp


AsyncBuffercgHelper.obj : $(START_DIR)\AsyncBuffercgHelper.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\AsyncBuffercgHelper.cpp


spectralCentroid.obj : $(START_DIR)\spectralCentroid.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\spectralCentroid.cpp


spectralCrest.obj : $(START_DIR)\spectralCrest.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\spectralCrest.cpp


spectralDecrease.obj : $(START_DIR)\spectralDecrease.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\spectralDecrease.cpp


spectralEntropy.obj : $(START_DIR)\spectralEntropy.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\spectralEntropy.cpp


spectralFlatness.obj : $(START_DIR)\spectralFlatness.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\spectralFlatness.cpp


spectralKurtosis.obj : $(START_DIR)\spectralKurtosis.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\spectralKurtosis.cpp


spectralRolloffPoint.obj : $(START_DIR)\spectralRolloffPoint.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\spectralRolloffPoint.cpp


spectralSkewness.obj : $(START_DIR)\spectralSkewness.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\spectralSkewness.cpp


spectralSlope.obj : $(START_DIR)\spectralSlope.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\spectralSlope.cpp


spectralSpread.obj : $(START_DIR)\spectralSpread.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\spectralSpread.cpp


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(COMPILER_COMMAND_FILE) $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@cmd /C "@echo ### PRODUCT = $(PRODUCT)"
	@cmd /C "@echo ### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@cmd /C "@echo ### BUILD_TYPE = $(BUILD_TYPE)"
	@cmd /C "@echo ### INCLUDES = $(INCLUDES)"
	@cmd /C "@echo ### DEFINES = $(DEFINES)"
	@cmd /C "@echo ### ALL_SRCS = $(ALL_SRCS)"
	@cmd /C "@echo ### ALL_OBJS = $(ALL_OBJS)"
	@cmd /C "@echo ### LIBS = $(LIBS)"
	@cmd /C "@echo ### MODELREF_LIBS = $(MODELREF_LIBS)"
	@cmd /C "@echo ### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@cmd /C "@echo ### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@cmd /C "@echo ### CFLAGS = $(CFLAGS)"
	@cmd /C "@echo ### LDFLAGS = $(LDFLAGS)"
	@cmd /C "@echo ### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### CPPFLAGS = $(CPPFLAGS)"
	@cmd /C "@echo ### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@cmd /C "@echo ### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### ARFLAGS = $(ARFLAGS)"
	@cmd /C "@echo ### MEX_CFLAGS = $(MEX_CFLAGS)"
	@cmd /C "@echo ### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@cmd /C "@echo ### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@cmd /C "@echo ### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@cmd /C "@echo ### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@cmd /C "@echo ### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@cmd /C "@echo ### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	@if exist $(PRODUCT) $(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


