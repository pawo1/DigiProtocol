
ifeq ($(OS),Windows_NT)
    EXE_SUFFIX = .exe
	RM = del /Q /F
	USBFLAGS = -lusb-1.0
	USBLIBS ?= -LC:\Libs\libusb
	USBINCLUDE ?= -IC:\Libs\libusb
else
    EXE_SUFFIX =
	RM = rm -rf
	USBFLAGS = -lusb-1.0
endif

CXX = g++

all: send receive

rebuild: remove all

send: send.cpp

	$(CXX) -o send$(EXE_SUFFIX) send.cpp $(USBINCLUDE) $(USBLIBS) $(USBFLAGS)

receive: receive.cpp

	$(CXX) -o receive$(EXE_SUFFIX) receive.cpp $(USBINCLUDE) $(USBLIBS) $(USBFLAGS)

remove:
	
	$(RM) send$(EXE_SUFFIX) receive$(EXE_SUFFIX)
