# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )
set(req state)

idf_component_register(SRCS "lpf.cpp" INCLUDE_DIRS "." REQUIRES ${req})
