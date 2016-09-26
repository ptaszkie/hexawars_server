##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=hexawars_server
ConfigurationName      :=Debug
WorkspacePath          :=/home/quave/Pulpit/hexawars_server
ProjectPath            :=/home/quave/Pulpit/hexawars_server/hexawars_server
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Quave
Date                   :=26/09/16
CodeLitePath           :=/home/quave/.codelite
LinkerName             :=/usr/bin/clang++
SharedObjectLinkerName :=/usr/bin/clang++ -shared -fPIC
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="hexawars_server.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            := 
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)libs 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)mongocxx $(LibrarySwitch)bsoncxx $(LibrarySwitch)boost_system $(LibrarySwitch)pthread 
ArLibs                 :=  "libmongocxx" "libbsoncxx" "boost_system" "pthread" 
LibPath                := $(LibraryPathSwitch)libs 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/clang++
CC       := /usr/bin/clang
CXXFLAGS := -pedantic-errors -g -O0 -w -ansi -pedantic -W -std=c++14 -Wall $(Preprocessors)
CFLAGS   := -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_db.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_websocketsrv.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_gamesrv.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_msg.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_player.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/quave/Pulpit/hexawars_server/hexawars_server/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix)main.cpp

$(IntermediateDirectory)/src_db.cpp$(ObjectSuffix): src/db.cpp $(IntermediateDirectory)/src_db.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/quave/Pulpit/hexawars_server/hexawars_server/src/db.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_db.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_db.cpp$(DependSuffix): src/db.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_db.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_db.cpp$(DependSuffix) -MM src/db.cpp

$(IntermediateDirectory)/src_db.cpp$(PreprocessSuffix): src/db.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_db.cpp$(PreprocessSuffix)src/db.cpp

$(IntermediateDirectory)/src_websocketsrv.cpp$(ObjectSuffix): src/websocketsrv.cpp $(IntermediateDirectory)/src_websocketsrv.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/quave/Pulpit/hexawars_server/hexawars_server/src/websocketsrv.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_websocketsrv.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_websocketsrv.cpp$(DependSuffix): src/websocketsrv.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_websocketsrv.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_websocketsrv.cpp$(DependSuffix) -MM src/websocketsrv.cpp

$(IntermediateDirectory)/src_websocketsrv.cpp$(PreprocessSuffix): src/websocketsrv.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_websocketsrv.cpp$(PreprocessSuffix)src/websocketsrv.cpp

$(IntermediateDirectory)/src_gamesrv.cpp$(ObjectSuffix): src/gamesrv.cpp $(IntermediateDirectory)/src_gamesrv.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/quave/Pulpit/hexawars_server/hexawars_server/src/gamesrv.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_gamesrv.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_gamesrv.cpp$(DependSuffix): src/gamesrv.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_gamesrv.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_gamesrv.cpp$(DependSuffix) -MM src/gamesrv.cpp

$(IntermediateDirectory)/src_gamesrv.cpp$(PreprocessSuffix): src/gamesrv.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_gamesrv.cpp$(PreprocessSuffix)src/gamesrv.cpp

$(IntermediateDirectory)/src_msg.cpp$(ObjectSuffix): src/msg.cpp $(IntermediateDirectory)/src_msg.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/quave/Pulpit/hexawars_server/hexawars_server/src/msg.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_msg.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_msg.cpp$(DependSuffix): src/msg.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_msg.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_msg.cpp$(DependSuffix) -MM src/msg.cpp

$(IntermediateDirectory)/src_msg.cpp$(PreprocessSuffix): src/msg.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_msg.cpp$(PreprocessSuffix)src/msg.cpp

$(IntermediateDirectory)/src_player.cpp$(ObjectSuffix): src/player.cpp $(IntermediateDirectory)/src_player.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/quave/Pulpit/hexawars_server/hexawars_server/src/player.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_player.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_player.cpp$(DependSuffix): src/player.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_player.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_player.cpp$(DependSuffix) -MM src/player.cpp

$(IntermediateDirectory)/src_player.cpp$(PreprocessSuffix): src/player.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_player.cpp$(PreprocessSuffix)src/player.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


