# --- Required interface definitions ---

# LIBTOOL needs bash
SHELL=/bin/bash

OBJ=o
LOBJ=lo

# Usage: $(call libname,base)
define libname
lib$(1).la
endef

# Usage: $(call binname,base)
define binname
$(1)
endef

# --- Private definitions ---

LD_VERSION_FLAGS=

# Usage: $(call libdepflags,$(basename obj))
# Usage: $(call fixdeps,$(basename obj))
ifeq ($(GENDEPS),1)
libdepflags=-MD -MF $(1).tdep -MP
fixdeps=sed -e 's/\.o:/.lo:/' < $(1).tdep > $(1).dep

else
libdepflags=
fixdeps=
endif

# --- Required rule definitions ---

#                       1   2        3
# Usage: $(call compile,src,includes,xflags)
define compile
	$(CXX) $(CXXFLAGS) $(3) \
		$(call depflags,$(basename $(call src_to_obj,$(1)))) \
		$(foreach I,$(2),-I$(I)) \
		$(CPPFLAGS) \
		-c $(1) -o $(call src_to_obj,$(1))
endef

#                         1   2        3
# Usage: $(call c_compile,src,includes,xflags)
define c_compile
	$(CC) $(CFLAGS) $(3) \
		$(call depflags,$(basename $(call c_src_to_obj,$(1)))) \
		$(foreach I,$(2),-I$(I)) \
		$(CPPFLAGS) \
		-c $(1) -o $(call c_src_to_obj,$(1))
endef

#                          1   2
# Usage: $(call libcompile,src,includes)
define libcompile
	$(LIBTOOL) --quiet --mode=compile \
		$(CXX) $(CXXFLAGS) \
		$(call libdepflags,$(basename $(call src_to_obj,$(1)))) \
		$(foreach I,$(2),-I$(I)) \
		$(CPPFLAGS) \
		-c $(1) -o $(call src_to_obj,$(1)); \
	$(call fixdeps,$(basename $(call src_to_obj,$(1))))
endef

#                          1   2
# Usage: $(call libcompile,src,includes)
define c_libcompile
	$(LIBTOOL) --quiet --mode=compile \
		$(CC) $(CFLAGS) \
		$(call libdepflags,$(basename $(call c_src_to_obj,$(1)))) \
		$(foreach I,$(2),-I$(I)) \
		$(CPPFLAGS) \
		-c $(1) -o $(call c_src_to_obj,$(1)); \
	$(call fixdeps,$(basename $(call src_to_obj,$(1))))
endef

#                        1    2
# Usage: $(call makeslib,objs,library)
define makeslib
	$(RM) $2
	$(AR) cru $(2) $(1)
	$(RANLIB) $(2)
endef

#                       1    2       3       4    5       6        7
# Usage: $(call makelib,objs,library,ldflags,libs,current,revision,age)
define makelib
	$(LIBTOOL) --mode=link \
		$(CXX) $(CXXFLAGS) $(LD_VERSION_FLAGS) \
		 -o $(2) $(1) $(3) $(4) \
		 $(RPATH) -version-info $(5):$(6):$(7) -no-undefined
endef

#                       1    2      3       4    5
# Usage: $(call makebin,objs,binary,ldflags,libs,xlinkflags)
define makebin
	$(LIBTOOL) --mode=link $(CXX) $(CXXFLAGS) $(5) $(1) -o $(2) $(3) $(4)
endef
