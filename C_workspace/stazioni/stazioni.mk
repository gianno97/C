##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Stazioni
ConfigurationName      :=Debug
WorkspacePath          :=E:/C/C_workspace
ProjectPath            :=E:/C/C_workspace/Stazioni
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Fabio2
Date                   :=21/08/2020
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
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
ObjectsFileList        :="Stazioni.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_main.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_libreria.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_Sperimentale_sperimentale_statistiche.c$(ObjectSuffix) 



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
	@$(MakeDirCommand) "$(ConfigurationName)"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "$(ConfigurationName)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_main.c$(ObjectSuffix): ../../../Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_main.c$(DependSuffix) -MM "../../../Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/main.c"
	$(CC) $(SourceSwitch) "E:/Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_main.c$(PreprocessSuffix): ../../../Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_main.c$(PreprocessSuffix) "../../../Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/main.c"

$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_libreria.c$(ObjectSuffix): ../../../Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/libreria.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_libreria.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_libreria.c$(DependSuffix) -MM "../../../Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/libreria.c"
	$(CC) $(SourceSwitch) "E:/Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/libreria.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_libreria.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_libreria.c$(PreprocessSuffix): ../../../Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/libreria.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_libreria.c$(PreprocessSuffix) "../../../Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/libreria.c"

$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_Sperimentale_sperimentale_statistiche.c$(ObjectSuffix): ../../../Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/Sperimentale/sperimentale_statistiche.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_Sperimentale_sperimentale_statistiche.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_Sperimentale_sperimentale_statistiche.c$(DependSuffix) -MM "../../../Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/Sperimentale/sperimentale_statistiche.c"
	$(CC) $(SourceSwitch) "E:/Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/Sperimentale/sperimentale_statistiche.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_Sperimentale_sperimentale_statistiche.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_Sperimentale_sperimentale_statistiche.c$(PreprocessSuffix): ../../../Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/Sperimentale/sperimentale_statistiche.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_up_Algoritmi_Nuova cartella_Progetti_Progetto sessione estiva 2016-2017_Progetto stazioni_Consegna_progetto_ASD_Sperimentale_sperimentale_statistiche.c$(PreprocessSuffix) "../../../Algoritmi/Nuova cartella/Progetti/Progetto sessione estiva 2016-2017/Progetto stazioni/Consegna_progetto_ASD/Sperimentale/sperimentale_statistiche.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


