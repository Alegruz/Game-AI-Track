CC			= g++
CXXFLAGS	= -Wall -W -std=c++17
OBJS		= main.o Model.o LayerConv.o LayerReLU.o Layer.o Tensor3D.o Imagelib.o loadbmp.o

main: ${OBJS}
	${CC} ${CFLAGS} -o main ${OBJS}

main.o: main.cpp Tensor3D.h Imagelib.h
	${CC} ${CFLAGS} -c main.cpp

Model.o: Model.cpp Model.h Layer.h
	${CC} ${CFLAGS} -c Model.cpp

LayerConv.o: LayerConv.cpp LayerConv.h Layer.h
	${CC} ${CFLAGS} -c LayerConv.cpp

LayerReLU.o: LayerReLU.cpp LayerReLU.h Layer.h
	${CC} ${CFLAGS} -c LayerReLU.cpp

Layer.o: Layer.cpp Layer.h Tensor3D.h Imagelib.h
	${CC} ${CFLAGS} -c Layer.cpp

Tensor3D.o: Tensor3D.cpp Tensor3D.h Imagelib.h
	${CC} ${CFLAGS} -c Tensor3D.cpp

Imagelib.o: Imagelib.cpp Imagelib.h loadbmp.h
	${CC} ${CFLAGS} -c Imagelib.cpp

loadbmp.o: loadbmp.cpp loadbmp.h
	${CC} ${CFLAGS} -c loadbmp.cpp
