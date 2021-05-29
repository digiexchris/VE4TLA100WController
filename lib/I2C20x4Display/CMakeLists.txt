idf_component_register(SRCS "I2C20x4Display.cpp"
                    INCLUDE_DIRS "." "../state" REQUIRES hd44780 pcf8574 PRIV_REQUIRES state pins)