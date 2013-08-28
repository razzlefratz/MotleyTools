#!/bin/bash

# ====================================================================
#
# --------------------------------------------------------------------

users="abarnes anazirudeen avasquez bwike cmaier dmarsh dpalmer gmiller gswaminathan jbrown jervin kahuna ktejani natallah pshread rduvall rrouhana shakimi smontgomery"

# ====================================================================
#
# --------------------------------------------------------------------

for user in ${users}; do
	echo ${user};
	~/newuser.sh ${user}
done

