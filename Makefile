#
# Red Pitaya fast counter server.
# @author: Lukas Botsch <lukas.botsch@uni-leipzig.de>
#

APP=$(notdir $(CURDIR:%/=%))

# Installation directory. It is changed when using the main Makefile++++++
INSTALL_DIR ?= /opt/redpitaya

CNTSRV=rp-counter-server
SVC=redpitaya_counter.service
ARTIFACTS= $(CNTSRV)

all: $(CNTSRV)

$(CNTSRV):
	$(MAKE) -C src

install:
	mkdir -p $(INSTALL_DIR)/bin
	cp $(CNTSRV) $(INSTALL_DIR)/bin
	cp $(SVC) /etc/systemd/system/

clean:
	$(MAKE) -C src clean
