.SUFFIXES: .cpp .o
.PHONY: clean dep new cleanall local debug clear test

CXX = ccache g++ -m32

BOOST_INCLUDE = /usr/local/include/boost-1_70
BOOST_LIB_VER = -gcc11-mt-d-x32-1_70

OPT_CRYPT = -I../ShareLib \
            -I/usr/include/mysql \
            -I/usr/local/ssl/include \
            -I/usr/local/include/botan-1.10 \
            -I$(BOOST_INCLUDE) \
            -I/usr/local/include/curl

OPT_LDOBJ = -L../ShareLib \
            -L/usr/local/lib \
            -L/usr/local/apr/lib \
            -L/usr/lib/mysql \
            -lSharelib \
            -lmysqlclient \
            -lboost_thread$(BOOST_LIB_VER) \
            -lboost_system$(BOOST_LIB_VER) \
            -llog4cxx \
            -laprutil-1 \
            -lapr-1 \
            -lrt \
            -lstdc++ \
            -lexpat \
            -lz \
            -lpthread \
            -ljsoncpp \
            -lcurl

OPT_VER = -DLC_VER=\"$(LC_VER)\"

CXXFLAGS = -DDEVCONSOLE \
           -D_THREAD_SAFE \
           -O3 \
		   -gsplit-dwarf \
           -Wall \
           -Wno-write-strings \
           -Wno-char-subscripts \
		   -Wno-sign-compare \
		   -fdiagnostics-color=always \
           $(OPT_BIGENDIAN) \
           $(OPT_LANG) \
           $(OPT_DEBUG) \
           $(OPT_DEF) \
           $(OPT_TEST) \
           $(OPT_VER) \
           $(OPT_CRYPT)
