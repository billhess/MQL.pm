

mql:
	if   [ `uname -s` = "SunOS" ]; then ${MAKE} -f Makefile.solaris; \
	elif [ `uname -s` = "HP-UX" ]; then ${MAKE} -f Makefile.hpux;    \
	elif [ `uname -s` = "AIX"   ]; then ${MAKE} -f Makefile.aix;     \
	elif [ `uname -s` = "IRIX64"]; then ${MAKE} -f Makefile.irix;    \
	fi

swig:
	if   [ `uname -s` = "SunOS" ]; then ${MAKE} -f Makefile.solaris swig; \
	elif [ `uname -s` = "HP-UX" ]; then ${MAKE} -f Makefile.hpux    swig; \
	elif [ `uname -s` = "AIX"   ]; then ${MAKE} -f Makefile.aix     swig; \
	elif [ `uname -s` = "IRIX64"]; then ${MAKE} -f Makefile.irix    swig; \
	fi

install:
	if   [ `uname -s` = "SunOS" ]; then ${MAKE} -f Makefile.solaris install; \
	elif [ `uname -s` = "HP-UX" ]; then ${MAKE} -f Makefile.hpux    install; \
	elif [ `uname -s` = "AIX"   ]; then ${MAKE} -f Makefile.aix     install; \
	elif [ `uname -s` = "IRIX64"]; then ${MAKE} -f Makefile.irix    install; \
	fi


clean:
	if   [ `uname -s` = "SunOS" ]; then ${MAKE} -f Makefile.solaris clean; \
	elif [ `uname -s` = "HP-UX" ]; then ${MAKE} -f Makefile.hpux    clean; \
	elif [ `uname -s` = "AIX"   ]; then ${MAKE} -f Makefile.aix     clean; \
	elif [ `uname -s` = "IRIX64"]; then ${MAKE} -f Makefile.irix    clean; \
	fi

