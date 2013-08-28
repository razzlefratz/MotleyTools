#!/bin/bash
# =
#
# -
cd ~/.ssh
rm -f id_rsa id_rsa.pub
ssh-keygen -t rsa
mv id_rsa ${HOSTNAME}_rsa
mv id_rsa.pub ${HOSTNAME}_rsa.pub
chmod 0600 *_rsa *_rsa.pub
ln -fs ${HOSTNAME}_rsa id_rsa
