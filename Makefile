CC=gcc
LDFLAGS= -lopencv_legacy -lopencv_highgui -lopencv_core -lopencv_ml -lopencv_video -lopencv_imgproc -lopencv_calib3d -lopencv_objdetect -L/usr/lib

CFLAGS = -O3 -I/usr/include/opencv -I/usr/include/opencv2

all: testp
