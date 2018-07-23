DRIVER_PATH = $(DEV)/0_driver

DRIVERSRC = 	$(DRIVER_PATH)/TLI4970.c \
				$(DRIVER_PATH)/LED.c \
				$(DRIVER_PATH)/MCP4726.c \
				$(DRIVER_PATH)/adcDriver.c \
				$(DRIVER_PATH)/pathSwitch.c \
				$(DRIVER_PATH)/bxCAN.c
				
DRIVERINC = 	$(DRIVER_PATH)/inc