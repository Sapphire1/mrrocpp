#!/bin/bash

function quitSig() {
    echo "***BASH*** Received SIGINT, going down"
}
trap 'quitSig' INT

if [ -x /usr/bin/color ]; then
		COLOR=/usr/bin/color;
else
		COLOR=true
fi

./messip_mgr &
MESSIP_PID=$!

export UI_HOST=`hostname -s`

sleep 0.5

PWD=`pwd`
DEFAULT_CONFIG="../../configs/default_file.cfg"
if [ ! -f ${DEFAULT_CONFIG} ]; then
	echo "default config file ${DEFAULT_CONFIG} missing"
else
	CONFIG=`cat ../../configs/default_file.cfg`
	CONFIG_FILE="../../${CONFIG}"
	if [ ! -f ${CONFIG_FILE} ]; then
		echo "config file ${CONFIG_FILE} missing"
		CONFIG=""
	fi
fi

if [ ${CONFIG} ]; then
	./configsrv ${PWD}/../ ../${CONFIG} &
else
	./configsrv ${PWD}/../ &
fi
CONFIGSRV_PID=$!

sleep 0.5

# debug: display PIDs
#echo CONFIGSRV_PID=${CONFIGSRV_PID}
#echo MESSIP_PID=${MESSIP_PID}

#function quitSig() {
#    echo "***BASH*** Received SIGINT, going down"
#}
#trap 'quitSig' INT

case `uname -s` in
		QNX)
				./ui;;
		Linux)
				./ui-qt-yoyek;;
		*)
				echo "OS not fully supported; defaults to UNIX"
				./ui-qt-yoyek;;
esac

<<<<<<< HEAD

#function quitSig() {
#    echo "***BASH*** Received SIGINT, going down"
#}
#trap 'quitSig' INT

=======
>>>>>>> 7bad1b6... configsrc: handle nonexisting default configuration file
echo "$(${COLOR} blue)Killing configsrv$(${COLOR} off)"
if ! kill ${CONFIGSRV_PID}; then
		echo "$(${COLOR} red) failed to kill configsrv$(${COLOR} off)"
fi
echo "$(${COLOR} blue)Killing messip_mgr$(${COLOR} off)"
if ! kill ${MESSIP_PID}; then
		echo "$(${COLOR} red) failed to kill messip_mgr$(${COLOR} off)"
fi


echo "$(${COLOR} blue)***BASH*** UI exited$(${COLOR} off)"
