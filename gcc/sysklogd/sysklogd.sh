#!/bin/bash
# file: sysklogd/sysklogd.sh

exit

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -o klogd klogd.c
gcc -Wall -Wextra -Wno-unused-parameter -o syslogd syslogd.c

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c kmodsyms.c
gcc -Wall -Wextra -Wno-unused-parameter -c ksyms.c
gcc -Wall -Wextra -Wno-unused-parameter -c mysocket.c
gcc -Wall -Wextra -Wno-unused-parameter -c oops.c
gcc -Wall -Wextra -Wno-unused-parameter -c oops_test.c
gcc -Wall -Wextra -Wno-unused-parameter -c strfpri.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslog_decode.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslog_encode.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslog_facility_codes.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslog_facility_names.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslog_faclity_codes.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslog_lookup.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslog_severity_codes.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslog_severity_names.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_admin.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_broadcast.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_close_sockets.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_configure.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_enumerate.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_error.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_flag_names.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_gethost.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_index.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_inet_socket.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_merge.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_open_sockets.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_parse.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_print.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_queue.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_read_sockets.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_ready.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_scrub.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_start.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_state.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_stop.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_type_names.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_unix_socket.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_write.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslogd_write_host.c

