##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Common
ConfigurationName      :=Debug
WorkspacePath          :=/home/lieven/workspace
ProjectPath            :=/home/lieven/workspace/Common
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Lieven
Date                   :=05/04/20
CodeLitePath           :=/home/lieven/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Common.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../ArduinoJson/src 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS := -std=c++11 -g -std=c++11 -fPIC  $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Uid.cpp$(ObjectSuffix) $(IntermediateDirectory)/CircBuf.cpp$(ObjectSuffix) $(IntermediateDirectory)/Json.cpp$(ObjectSuffix) $(IntermediateDirectory)/LinkedList.cpp$(ObjectSuffix) $(IntermediateDirectory)/Log.cpp$(ObjectSuffix) $(IntermediateDirectory)/Msgpack.cpp$(ObjectSuffix) $(IntermediateDirectory)/jsmn.c$(ObjectSuffix) $(IntermediateDirectory)/Sys.cpp$(ObjectSuffix) $(IntermediateDirectory)/BufferedByteStream.cpp$(ObjectSuffix) $(IntermediateDirectory)/Sema.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Config.cpp$(ObjectSuffix) $(IntermediateDirectory)/Register.cpp$(ObjectSuffix) $(IntermediateDirectory)/STM32_stubs.cpp$(ObjectSuffix) $(IntermediateDirectory)/printf.c$(ObjectSuffix) $(IntermediateDirectory)/Strpack.cpp$(ObjectSuffix) $(IntermediateDirectory)/RtosQueue.cpp$(ObjectSuffix) $(IntermediateDirectory)/Xdr.cpp$(ObjectSuffix) $(IntermediateDirectory)/Node.cpp$(ObjectSuffix) $(IntermediateDirectory)/Str.cpp$(ObjectSuffix) $(IntermediateDirectory)/Bytes.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/CborQueue.cpp$(ObjectSuffix) $(IntermediateDirectory)/PIC32_stubs.cpp$(ObjectSuffix) $(IntermediateDirectory)/Base64.cpp$(ObjectSuffix) $(IntermediateDirectory)/EventSource.cpp$(ObjectSuffix) $(IntermediateDirectory)/XdrQueue.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) ".build-debug"
	@echo rebuilt > ".build-debug/Common"

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Uid.cpp$(ObjectSuffix): Uid.cpp $(IntermediateDirectory)/Uid.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Uid.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Uid.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Uid.cpp$(DependSuffix): Uid.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Uid.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Uid.cpp$(DependSuffix) -MM Uid.cpp

$(IntermediateDirectory)/Uid.cpp$(PreprocessSuffix): Uid.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Uid.cpp$(PreprocessSuffix) Uid.cpp

$(IntermediateDirectory)/CircBuf.cpp$(ObjectSuffix): CircBuf.cpp $(IntermediateDirectory)/CircBuf.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "CircBuf.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CircBuf.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CircBuf.cpp$(DependSuffix): CircBuf.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CircBuf.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CircBuf.cpp$(DependSuffix) -MM CircBuf.cpp

$(IntermediateDirectory)/CircBuf.cpp$(PreprocessSuffix): CircBuf.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CircBuf.cpp$(PreprocessSuffix) CircBuf.cpp

$(IntermediateDirectory)/Json.cpp$(ObjectSuffix): Json.cpp $(IntermediateDirectory)/Json.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Json.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Json.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Json.cpp$(DependSuffix): Json.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Json.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Json.cpp$(DependSuffix) -MM Json.cpp

$(IntermediateDirectory)/Json.cpp$(PreprocessSuffix): Json.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Json.cpp$(PreprocessSuffix) Json.cpp

$(IntermediateDirectory)/LinkedList.cpp$(ObjectSuffix): LinkedList.cpp $(IntermediateDirectory)/LinkedList.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "LinkedList.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/LinkedList.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/LinkedList.cpp$(DependSuffix): LinkedList.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/LinkedList.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/LinkedList.cpp$(DependSuffix) -MM LinkedList.cpp

$(IntermediateDirectory)/LinkedList.cpp$(PreprocessSuffix): LinkedList.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/LinkedList.cpp$(PreprocessSuffix) LinkedList.cpp

$(IntermediateDirectory)/Log.cpp$(ObjectSuffix): Log.cpp $(IntermediateDirectory)/Log.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Log.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Log.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Log.cpp$(DependSuffix): Log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Log.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Log.cpp$(DependSuffix) -MM Log.cpp

$(IntermediateDirectory)/Log.cpp$(PreprocessSuffix): Log.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Log.cpp$(PreprocessSuffix) Log.cpp

$(IntermediateDirectory)/Msgpack.cpp$(ObjectSuffix): Msgpack.cpp $(IntermediateDirectory)/Msgpack.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Msgpack.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Msgpack.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Msgpack.cpp$(DependSuffix): Msgpack.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Msgpack.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Msgpack.cpp$(DependSuffix) -MM Msgpack.cpp

$(IntermediateDirectory)/Msgpack.cpp$(PreprocessSuffix): Msgpack.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Msgpack.cpp$(PreprocessSuffix) Msgpack.cpp

$(IntermediateDirectory)/jsmn.c$(ObjectSuffix): jsmn.c $(IntermediateDirectory)/jsmn.c$(DependSuffix)
	$(CC) $(SourceSwitch) "jsmn.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/jsmn.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/jsmn.c$(DependSuffix): jsmn.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/jsmn.c$(ObjectSuffix) -MF$(IntermediateDirectory)/jsmn.c$(DependSuffix) -MM jsmn.c

$(IntermediateDirectory)/jsmn.c$(PreprocessSuffix): jsmn.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/jsmn.c$(PreprocessSuffix) jsmn.c

$(IntermediateDirectory)/Sys.cpp$(ObjectSuffix): Sys.cpp $(IntermediateDirectory)/Sys.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Sys.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Sys.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Sys.cpp$(DependSuffix): Sys.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Sys.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Sys.cpp$(DependSuffix) -MM Sys.cpp

$(IntermediateDirectory)/Sys.cpp$(PreprocessSuffix): Sys.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Sys.cpp$(PreprocessSuffix) Sys.cpp

$(IntermediateDirectory)/BufferedByteStream.cpp$(ObjectSuffix): BufferedByteStream.cpp $(IntermediateDirectory)/BufferedByteStream.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "BufferedByteStream.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BufferedByteStream.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BufferedByteStream.cpp$(DependSuffix): BufferedByteStream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BufferedByteStream.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/BufferedByteStream.cpp$(DependSuffix) -MM BufferedByteStream.cpp

$(IntermediateDirectory)/BufferedByteStream.cpp$(PreprocessSuffix): BufferedByteStream.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BufferedByteStream.cpp$(PreprocessSuffix) BufferedByteStream.cpp

$(IntermediateDirectory)/Sema.cpp$(ObjectSuffix): Sema.cpp $(IntermediateDirectory)/Sema.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Sema.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Sema.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Sema.cpp$(DependSuffix): Sema.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Sema.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Sema.cpp$(DependSuffix) -MM Sema.cpp

$(IntermediateDirectory)/Sema.cpp$(PreprocessSuffix): Sema.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Sema.cpp$(PreprocessSuffix) Sema.cpp

$(IntermediateDirectory)/Config.cpp$(ObjectSuffix): Config.cpp $(IntermediateDirectory)/Config.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Config.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Config.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Config.cpp$(DependSuffix): Config.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Config.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Config.cpp$(DependSuffix) -MM Config.cpp

$(IntermediateDirectory)/Config.cpp$(PreprocessSuffix): Config.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Config.cpp$(PreprocessSuffix) Config.cpp

$(IntermediateDirectory)/Register.cpp$(ObjectSuffix): Register.cpp $(IntermediateDirectory)/Register.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Register.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Register.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Register.cpp$(DependSuffix): Register.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Register.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Register.cpp$(DependSuffix) -MM Register.cpp

$(IntermediateDirectory)/Register.cpp$(PreprocessSuffix): Register.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Register.cpp$(PreprocessSuffix) Register.cpp

$(IntermediateDirectory)/STM32_stubs.cpp$(ObjectSuffix): STM32_stubs.cpp $(IntermediateDirectory)/STM32_stubs.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "STM32_stubs.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/STM32_stubs.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/STM32_stubs.cpp$(DependSuffix): STM32_stubs.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/STM32_stubs.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/STM32_stubs.cpp$(DependSuffix) -MM STM32_stubs.cpp

$(IntermediateDirectory)/STM32_stubs.cpp$(PreprocessSuffix): STM32_stubs.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/STM32_stubs.cpp$(PreprocessSuffix) STM32_stubs.cpp

$(IntermediateDirectory)/printf.c$(ObjectSuffix): printf.c $(IntermediateDirectory)/printf.c$(DependSuffix)
	$(CC) $(SourceSwitch) "printf.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/printf.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/printf.c$(DependSuffix): printf.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/printf.c$(ObjectSuffix) -MF$(IntermediateDirectory)/printf.c$(DependSuffix) -MM printf.c

$(IntermediateDirectory)/printf.c$(PreprocessSuffix): printf.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/printf.c$(PreprocessSuffix) printf.c

$(IntermediateDirectory)/Strpack.cpp$(ObjectSuffix): Strpack.cpp $(IntermediateDirectory)/Strpack.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Strpack.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Strpack.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Strpack.cpp$(DependSuffix): Strpack.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Strpack.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Strpack.cpp$(DependSuffix) -MM Strpack.cpp

$(IntermediateDirectory)/Strpack.cpp$(PreprocessSuffix): Strpack.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Strpack.cpp$(PreprocessSuffix) Strpack.cpp

$(IntermediateDirectory)/RtosQueue.cpp$(ObjectSuffix): RtosQueue.cpp $(IntermediateDirectory)/RtosQueue.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "RtosQueue.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/RtosQueue.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/RtosQueue.cpp$(DependSuffix): RtosQueue.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/RtosQueue.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/RtosQueue.cpp$(DependSuffix) -MM RtosQueue.cpp

$(IntermediateDirectory)/RtosQueue.cpp$(PreprocessSuffix): RtosQueue.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/RtosQueue.cpp$(PreprocessSuffix) RtosQueue.cpp

$(IntermediateDirectory)/Xdr.cpp$(ObjectSuffix): Xdr.cpp $(IntermediateDirectory)/Xdr.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Xdr.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Xdr.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Xdr.cpp$(DependSuffix): Xdr.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Xdr.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Xdr.cpp$(DependSuffix) -MM Xdr.cpp

$(IntermediateDirectory)/Xdr.cpp$(PreprocessSuffix): Xdr.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Xdr.cpp$(PreprocessSuffix) Xdr.cpp

$(IntermediateDirectory)/Node.cpp$(ObjectSuffix): Node.cpp $(IntermediateDirectory)/Node.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Node.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Node.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Node.cpp$(DependSuffix): Node.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Node.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Node.cpp$(DependSuffix) -MM Node.cpp

$(IntermediateDirectory)/Node.cpp$(PreprocessSuffix): Node.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Node.cpp$(PreprocessSuffix) Node.cpp

$(IntermediateDirectory)/Str.cpp$(ObjectSuffix): Str.cpp $(IntermediateDirectory)/Str.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Str.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Str.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Str.cpp$(DependSuffix): Str.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Str.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Str.cpp$(DependSuffix) -MM Str.cpp

$(IntermediateDirectory)/Str.cpp$(PreprocessSuffix): Str.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Str.cpp$(PreprocessSuffix) Str.cpp

$(IntermediateDirectory)/Bytes.cpp$(ObjectSuffix): Bytes.cpp $(IntermediateDirectory)/Bytes.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Bytes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Bytes.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Bytes.cpp$(DependSuffix): Bytes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Bytes.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Bytes.cpp$(DependSuffix) -MM Bytes.cpp

$(IntermediateDirectory)/Bytes.cpp$(PreprocessSuffix): Bytes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Bytes.cpp$(PreprocessSuffix) Bytes.cpp

$(IntermediateDirectory)/CborQueue.cpp$(ObjectSuffix): CborQueue.cpp $(IntermediateDirectory)/CborQueue.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "CborQueue.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CborQueue.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CborQueue.cpp$(DependSuffix): CborQueue.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CborQueue.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CborQueue.cpp$(DependSuffix) -MM CborQueue.cpp

$(IntermediateDirectory)/CborQueue.cpp$(PreprocessSuffix): CborQueue.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CborQueue.cpp$(PreprocessSuffix) CborQueue.cpp

$(IntermediateDirectory)/PIC32_stubs.cpp$(ObjectSuffix): PIC32_stubs.cpp $(IntermediateDirectory)/PIC32_stubs.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "PIC32_stubs.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PIC32_stubs.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PIC32_stubs.cpp$(DependSuffix): PIC32_stubs.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PIC32_stubs.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PIC32_stubs.cpp$(DependSuffix) -MM PIC32_stubs.cpp

$(IntermediateDirectory)/PIC32_stubs.cpp$(PreprocessSuffix): PIC32_stubs.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PIC32_stubs.cpp$(PreprocessSuffix) PIC32_stubs.cpp

$(IntermediateDirectory)/Base64.cpp$(ObjectSuffix): Base64.cpp $(IntermediateDirectory)/Base64.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Base64.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Base64.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Base64.cpp$(DependSuffix): Base64.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Base64.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Base64.cpp$(DependSuffix) -MM Base64.cpp

$(IntermediateDirectory)/Base64.cpp$(PreprocessSuffix): Base64.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Base64.cpp$(PreprocessSuffix) Base64.cpp

$(IntermediateDirectory)/EventSource.cpp$(ObjectSuffix): EventSource.cpp $(IntermediateDirectory)/EventSource.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "EventSource.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/EventSource.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EventSource.cpp$(DependSuffix): EventSource.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/EventSource.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/EventSource.cpp$(DependSuffix) -MM EventSource.cpp

$(IntermediateDirectory)/EventSource.cpp$(PreprocessSuffix): EventSource.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/EventSource.cpp$(PreprocessSuffix) EventSource.cpp

$(IntermediateDirectory)/XdrQueue.cpp$(ObjectSuffix): XdrQueue.cpp $(IntermediateDirectory)/XdrQueue.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "XdrQueue.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/XdrQueue.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/XdrQueue.cpp$(DependSuffix): XdrQueue.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/XdrQueue.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/XdrQueue.cpp$(DependSuffix) -MM XdrQueue.cpp

$(IntermediateDirectory)/XdrQueue.cpp$(PreprocessSuffix): XdrQueue.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/XdrQueue.cpp$(PreprocessSuffix) XdrQueue.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


