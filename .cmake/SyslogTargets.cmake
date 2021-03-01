add_library(Syslog::syslog INTERFACE IMPORTED)
# -- DISABLED: syslog is part of clib.
# set_property(TARGET Syslog::syslog PROPERTY INTERFACE_LINK_LIBRARIES "-lsyslog")
