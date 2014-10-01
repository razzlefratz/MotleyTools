# ====================================================================
# math source files;
# --------------------------------------------------------------------

_abs.o: _abs.c _math.h
_atan.o: _atan.c _math.h
_ceil.o: _ceil.c _math.h
_cos.o: _cos.c _math.h
_cosh.o: _cosh.c _math.h
_dabs.o: _dabs.c _math.h
_dmod.o: _dmod.c _math.h
_dpow.o: _dpow.c _math.h
_dsgn.o: _dsgn.c _math.h
_e.o: _e.c _math.h
_exp.o: _exp.c _math.h
_fabs.o: _fabs.c _math.h
_floor.o: _floor.c _math.h
_fmod.o: _fmod.c _math.h
_iabs.o: _iabs.c _math.h
_ipow.o: _ipow.c _math.h
_labs.o: _labs.c _math.h
_log.o: _log.c _math.h
_log10.o: _log10.c _math.h
_sgn.o: _sgn.c _math.h
_sin.o: _sin.c _math.h
_sinh.o: _sinh.c _math.h
_sqrt.o: _sqrt.c _math.h

# ====================================================================
# files;
# --------------------------------------------------------------------

_math.h:
	touch ../math/${@}

