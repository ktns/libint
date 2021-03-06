
# Define LOCAL to compile directly in the source directory
ifndef LOCAL
  TOPDIR=../../..
  ifndef SRCDIR
    SRCDIR=$(shell pwd)
  endif
  -include $(TOPDIR)/src/bin/MakeVars
  vpath %.a $(libdir)
else
  SRCDIR=.
endif

NAME = libint
VERSION = 2

CXXFLAGS += -I. -I$(SRCDIR)

RANLIB = ranlib
OBJSUF = o
DEPSUF = d
CXXDEPENDSUF = none
CXXDEPENDFLAGS = -M

LIBCXXSRC = default_params.cc rr.cc dg.cc dgvertex.cc dgarc.cc gauss.cc \
oper.cc iter.cc policy.cc strategy.cc policy_spec.cc flop.cc \
prefactors.cc context.cc memory.cc tactic.cc codeblock.cc dims.cc code.cc \
iface.cc class_registry.cc algebra.cc graph_registry.cc drtree.cc task.cc \
extract.cc util.cc purgeable.cc buildtest.cc comp_deriv_gauss.cc
LIBCXXOBJ = $(LIBCXXSRC:%.cc=%.$(OBJSUF))
LIBCXXDEP = $(LIBCXXSRC:%.cc=%.$(DEPSUF))
LIBOBJ = $(LIBCXXOBJ)
LIBTARGET = libINT.a

LIBCXXINC = cgshellinfo.h cgshell_ordering.h

BUILDCXXSRC = build_libint.cc
BUILDCXXOBJ = $(BUILDCXXSRC:%.cc=%.$(OBJSUF))
BUILDCXXDEP = $(BUILDCXXSRC:%.cc=%.$(DEPSUF))

TESTCXXSRC = test.cc
TESTCXXOBJ = $(TESTCXXSRC:%.cc=%.$(OBJSUF))
TESTCXXDEP = $(TESTCXXSRC:%.cc=%.$(DEPSUF))

default:: build_libint

all:: default

build_libint: $(BUILDCXXOBJ) $(LIBTARGET)
	$(CXX) -o $@ $(LDFLAGS) $^ $(SYSLIBS) 

depend:: $(TESTCXXDEP) $(BUILDCXXDEP) $(LIBCXXDEP)

run_test:: test
	./test

test: $(TESTCXXOBJ) $(LIBTARGET)
	$(CXX) -o $@ $(LDFLAGS) $^ $(SYSLIBS) 

$(LIBTARGET): $(LIBOBJ)
	/bin/rm -f $@
	$(AR) $(ARFLAGS) $@ $(LIBOBJ)
	$(RANLIB) $@

%.eps: %.ps
	ps2epsi $^ $@

%.pdf: %.ps
	ps2pdf13 $^

%.ps: %.dot
	dot -Tps -o $@ $^

graph.dot: test
	./$^

install:: install_inc

install_inc:: $(LIBCXXINC)
	$(INSTALL) $(INSTALLDIROPT) $(DESTDIR)$(includedir)/$(NAME)$(VERSION)
	-$(INSTALL) $(INSTALLLIBOPT) $^ $(DESTDIR)$(includedir)/$(NAME)$(VERSION)

clean:: oclean targetclean dependclean miscclean

oclean::
	-rm -f *.$(OBJSUF)

targetclean::
	-rm -f $(LIBTARGET) test build_libint

dependclean::
	-rm -f *.$(DEPSUF)

miscclean::
	-rm -f *.dot

realclean:: clean

distclean:: realclean
	-rm -f cgshell_ordering.h

ifneq ($(CXXDEPENDSUF),none)
%.d: %.cc
	$(CXXDEPEND) $(CXXDEPENDFLAGS) -c $(CPPFLAGS) $(CXXFLAGS) $< > /dev/null
	sed 's/^$*.o/$*.$(OBJSUF) $*.d/g' < $(*F).$(CXXDEPENDSUF) > $(@F)
	/bin/rm -f $(*F).$(CXXDEPENDSUF)
else
%.d: %.cc
	$(CXXDEPEND) $(CXXDEPENDFLAGS) -c $(CPPFLAGS) $(CXXFLAGS) $< | sed 's/^$*.o/$*.$(OBJSUF) $*.d/g' > $(@F)
endif

-include $(LIBCXXDEP)
-include $(BUILDCXXDEP)
-include $(TESTCXXDEP)
        
