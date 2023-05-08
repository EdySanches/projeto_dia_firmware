idf_component_register(
SRCS 
"core/src/main.c"
"core/src/led.c" 
"conn/src/wifi.c" 
"storage/src/nvs_handler.c"
"storage/src/spiffs_handler.c"
                    
INCLUDE_DIRS 
"."
"core/inc" 
"conn/inc" 
"storage/inc"
"sensor/inc")
