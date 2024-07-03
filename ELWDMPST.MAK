###############################################################################
#####               This makefile generates ELWDMPST.DLL                   #####
###############################################################################
!include $(WGDEV)\src\gcrules.mak

DLLLIB =            \
     $(DLLLIB)      \
     wgserver.lib   \
     galgsbl.lib

OBJFILES =          \
     elwdmpst.obj     

elwdmpst.dll:       \
     $(GCBUILD)     \
     elwdmpst.h     \
     $(OBJFILES)    \
     $(DLLLIB)      \
     $(DEFILE)
     $(LINK) $(LIBCMD) @&&|
$(PRODLL) $(OBJFILES)
$(RUNDIR)\$&
$(RUNDIR)\$&
$(DLLLIB) $(LINKDLL)
$(DEFILE)
|
