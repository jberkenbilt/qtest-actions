OUTPUT_DIR = build
BINS = ./test1

TARGETS = $(foreach B,$(BINS),./$(OUTPUT_DIR)/$(call binname,$(B)))

include autoconf.mk
BUILDRULES ?= libtool
include make/rules.mk

A := $(shell mkdir -p build)

default:: all

all:: $(TARGETS)

# -----

$(foreach B,$(BINS),$(eval \
  OBJS_$(B) = $(call src_to_obj,$(B).cc)))

$(foreach B,$(BINS),$(eval \
  $(OBJS_$(B)): ./$(OUTPUT_DIR)/%.$(OBJ): $(B).cc ; \
	$(call compile,$(B).cc,$(INCLUDES))))

$(foreach B,$(BINS),$(eval \
  ./$(OUTPUT_DIR)/$(call binname,$(B)): $(OBJS_$(B)) ; \
	$(call makebin,$(OBJS_$(B)),$$@,$(LDFLAGS),$(LIBS))))

clean::
	$(RM) -rf build
