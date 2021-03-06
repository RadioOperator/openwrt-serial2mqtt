#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)
# COMPONENT_ADD_INCLUDEDIRS=.
# CXXFLAGS +="-DESP32_IDF=1"
# Component makefile for extras/Common

# expected anyone using bmp driver includes it as 'Common/MQTT*.h'
INC_DIRS += $(Common_ROOT)
INC_DIRS +=  ../ArduinoJson/src

# args for passing into compile rule generation
Common_SRC_DIR =  $(Common_ROOT)
Common_CFLAGS=  -I../../ArduinoJson/src
Common_CXXFLAGS=  -fno-rtti -std=c++11 -fno-exceptions -I../ArduinoJson/src

$(eval $(call component_compile_rules,Common))

#ESP32 COMPONENT.MK
COMPONENT_SRCDIRS := .

COMPONENT_ADD_INCLUDEDIRS := . ../../ArduinoJson/src 
COMPONENT_PRIV_INCLUDEDIRS := ../../ArduinoJson/src ../ArduinoJson/src ../../../ArduinoJson/src
COMPONENT_ADD_LDFLAGS += -lpthread
