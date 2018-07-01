#
# Regular cron jobs for the libexadrums package
#
0 4	* * *	root	[ -x /usr/bin/libexadrums_maintenance ] && /usr/bin/libexadrums_maintenance
