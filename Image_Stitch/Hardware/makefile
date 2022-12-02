#
# this file was created by a computer. trust it.
#

# compiler tools
XILINX_VITIS ?= /tools/Xilinx/Vitis/2020.2

HOST_CXX ?= arm-linux-gnueabihf-g++
RM = rm -f
RMDIR = rm -rf

VITIS_PLATFORM = zybo_gpio
VITIS_PLATFORM_DIR = /media/cole/XilinxShare/camera_design_vivado/platform3/zybo_gpio/export/zybo_gpio
VITIS_PLATFORM_PATH = $(VITIS_PLATFORM_DIR)/zybo_gpio.xpfm

# host compiler global settings
CXXFLAGS += -std=c++0x -DVITIS_PLATFORM=$(VITIS_PLATFORM) -D__USE_XOPEN2K8 -I/tools/Xilinx/Vivado/2020.2/include/ -I$(VITIS_PLATFORM_DIR)/sw/zybo_gpio/linux_domain/sysroot/cortexa9t2hf-neon-xilinx-linux-gnueabi/usr/include/xrt/ -O2 -g -Wall -c -fmessage-length=0 --sysroot=$(VITIS_PLATFORM_DIR)/sw/zybo_gpio/linux_domain/sysroot/cortexa9t2hf-neon-xilinx-linux-gnueabi
LDFLAGS += -lxilinxopencl -l opencv_imgproc -lopencv_calib3d -lopencv_features2d -lopencv_imgcodecs -l  opencv_core -lopencv_highgui -l opencv_imgcodecs -lpthread -lrt -ldl -lcrypt -lstdc++ -L$(VITIS_PLATFORM_DIR)/sw/zybo_gpio/linux_domain/sysroot/cortexa9t2hf-neon-xilinx-linux-gnueabi/usr/lib/ --sysroot=$(VITIS_PLATFORM_DIR)/sw/zybo_gpio/linux_domain/sysroot/cortexa9t2hf-neon-xilinx-linux-gnueabi

#
# host files
#

HOST_OBJECTS += src/image_thresholding-host.o
HOST_OBJECTS += src/myled.o

HOST_EXE = Image_Stitch

BUILD_SUBDIRS += src/

#
# primary build targets
#

.PHONY: all clean
all:  $(HOST_EXE)

clean:
	-$(RM) $(HOST_EXE) $(HOST_OBJECTS)

.PHONY: incremental
incremental: all


nothing:

#
# host rules
#

src/image_thresholding-host.o: ../src/image_thresholding-host.cpp ../../../../../../../tools/Xilinx/Vivado/2020.2/include/ap_int.h ../src/myled.h
	-@mkdir -p $(@D)
	$(HOST_CXX) $(CXXFLAGS) -o "$@" "$<"

src/myled.o: ../src/myled.c ../src/myled.h
	-@mkdir -p $(@D)
	$(HOST_CXX) $(CXXFLAGS) -o "$@" "$<"

$(HOST_EXE): $(HOST_OBJECTS)
	$(HOST_CXX) -o "$@" $(+) $(LDFLAGS)

