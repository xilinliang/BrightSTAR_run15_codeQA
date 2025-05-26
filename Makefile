# Filename: Makefile
# Description: Makefile for building EG2 analysis tools
# Author: Latif Kabir < latif@jlab.org >
# Created: Wed Nov 15 01:00:17 2017 (-0500)
# URL: latifkabir.github.io

ifndef STARHOME
  $(error $$STARHOME environment variable not defined. source setup.[c]sh first)
endif

# directories
DIFFANA_DIR = diffAnalysis
# makefile name
MAKE_FILE = Makefile

####### Build rules
first: all

.PHONY: diff cons 

all: cons diff 
	@echo "done!"	
diff: lib
	$(MAKE) -C $(DIFFANA_DIR) -f $(MAKE_FILE)
	@cp -ur $(DIFFANA_DIR)/lib/*.so lib
cons:
	cons

####### Clean
clean: cleancons 

.PHONY: cleandiff 

cleandiff:
	$(MAKE) -C $(DIFFANA_DIR) -f $(MAKE_FILE) clean

cleancons:
	rm -r .${STAR_HOST_SYS}/*
