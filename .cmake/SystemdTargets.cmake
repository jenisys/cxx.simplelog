add_library(Systemd::systemd INTERFACE IMPORTED)
set_property(
    TARGET Systemd::systemd PROPERTY INTERFACE_LINK_LIBRARIES "-lsystemd"
)
# -- HINT: Existance of systemd-library is NOT CHECKED.
