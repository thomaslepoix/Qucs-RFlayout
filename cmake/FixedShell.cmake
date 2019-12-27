# In a command such as add_test(), add_custom_target(), etc.
# The pattern `COMMAND <bin> <arg> <arg>` has some oddities, for example
# `2> /dev/null` does not work properly. Instead you can prefer this pattern
# `COMMAND ${FIXED_SHELL} "<bin> <arg> <arg>`
################################################################################

set( FIXED_SHELL ${CMAKE_COMMAND} -E env bash -c )

