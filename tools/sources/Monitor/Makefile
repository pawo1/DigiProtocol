ifeq ($(OS) ,Windows_NT)
	
	SEP =\\

	OBJ = obj\\Release\\resource.o

    EXE_SUFFIX = .exe
	RM = del /Q /F
	RMDIR = rmdir /Q /S
	MKDIR1 = cmd /c if not exist bin\\Release md bin\\Release
	MKDIR2 = cmd /c if not exist $(OBJDIR) md $(OBJDIR)

	WINDRES = windres.exe

	USBFLAGS = -lusb-1.0
	USBLIBS ?= -LC:\\Libs\\libusb
	USBINCLUDE ?= -IC:\\Libs\\libusb
	wxDIR ?= C:\\wxWidgets-3.0.5
	dpDIR ?= C:\\Libs/DigiProtocol

	MONOLITH ?= 1	

	INC = -I$(wxDIR)\\include -I$(dpDIR) -I$(wxDIR)\\lib/gcc_lib\\mswu $(USBINCLUDE)	
	CFLAGS = -pipe -D__GNUWIN32__ -D__WXMSW__ -DwxUSE_UNICODE -mthreads
	LIBDIR ?= -L$(wxDIR)\\lib/gcc_lib $(USBLIBS)

	LIB = -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lcomctl32 -lwsock32 -lodbc32 
	LDFLAGS = -mthreads -s  -mwindows
	
	RESINC = -I$(wxDIR)\\lib\\gcc_lib\\mswu

	WXLIBS ?= -lwxmsw30u -lwxpng -lwxjpeg -lwxtiff -lwxzlib

	LIB := $(WXLIBS) $(LIB)

else

	SEP =/

    EXE_SUFFIX =
	RM = rm -rf
	RMDIR = rmdir
	MKDIR1 = mkdir -p bin/Release
	MKDIR2 = mkdir -p $(OBJDIR)


	USBFLAGS = -lusb-1.0
	dpDIR ?= /usr/include/

	INC = -I/usr/local/lib/wx/include/gtk3-unicode-static-3.0 -I/usr/local/include/wx-3.0 -I$(dpDIR)
	CFLAGS = -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -pthread
	LIBDIR ?= -L/usr/local/lib

	LIB = /usr/local/lib/libwx_gtk3u_xrc-3.0.a /usr/local/lib/libwx_gtk3u_qa-3.0.a /usr/local/lib/libwx_baseu_net-3.0.a /usr/local/lib/libwx_gtk3u_html-3.0.a /usr/local/lib/libwx_gtk3u_adv-3.0.a /usr/local/lib/libwx_gtk3u_core-3.0.a /usr/local/lib/libwx_baseu_xml-3.0.a /usr/local/lib/libwx_baseu-3.0.a -lgthread-2.0 -pthread -lX11 -lSM -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lpng -lexpat -lwxregexu-3.0 -lwxtiff-3.0 -lwxjpeg-3.0 -lz -ldl -lm  
	LDFLAGS = -pthread -s
endif

OBJDIR = obj$(SEP)Release

OBJ := $(OBJDIR)/ConfigReader.o $(OBJDIR)/GUIFrame.o $(OBJDIR)/ListenerThread.o $(OBJDIR)/MonitorAbout.o $(OBJDIR)/MonitorGUIApp.o $(OBJDIR)/MonitorGUIMain.o $(OBJ)


CXX = g++
LD = g++

CFLAGS := $(CFLAGS) -std=c++17 -Wall -O2

INC := $(INC) $(USBICNLUDE)
LIBDIR := $(LIBDIR) $(USBLIBS)
LIB := $(LIB) $(USBFLAGS)

OUT = bin/Release/Monitor$(EXE_SUFFIX)


main: release

all: release clean

rebuild: clean release

release: before out


before: 

	$(MKDIR1)
	$(MKDIR2)

out: before $(OBJ) $(DEP)	
	$(LD) $(LIBDIR) -o $(OUT) $(OBJ)  $(LDFLAGS) $(LIB)



$(OBJDIR)/ConfigReader.o: ConfigReader.cpp
	$(CXX) $(CFLAGS) $(INC) -c ConfigReader.cpp -o $(OBJDIR)/ConfigReader.o

$(OBJDIR)/GUIFrame.o: GUIFrame.cpp
	$(CXX) $(CFLAGS) $(INC) -c GUIFrame.cpp -o $(OBJDIR)/GUIFrame.o

$(OBJDIR)/ListenerThread.o: ListenerThread.cpp
	$(CXX) $(CFLAGS) $(INC) -c ListenerThread.cpp -o $(OBJDIR)/ListenerThread.o

$(OBJDIR)/MonitorAbout.o: MonitorAbout.cpp
	$(CXX) $(CFLAGS) $(INC) -c MonitorAbout.cpp -o $(OBJDIR)/MonitorAbout.o

$(OBJDIR)/MonitorGUIApp.o: MonitorGUIApp.cpp
	$(CXX) $(CFLAGS) $(INC) -c MonitorGUIApp.cpp -o $(OBJDIR)/MonitorGUIApp.o

$(OBJDIR)/MonitorGUIMain.o: MonitorGUIMain.cpp
	$(CXX) $(CFLAGS) $(INC) -c MonitorGUIMain.cpp -o $(OBJDIR)/MonitorGUIMain.o

$(OBJDIR)/resource.o: resource.rc
	$(WINDRES) -i resource.rc -J rc -o $(OBJDIR)/resource.o -O coff $(INC)

clean: 
	$(RM) $(OBJ)
	$(RMDIR) $(OBJDIR)

.PHONY: release clean before out rebuild
