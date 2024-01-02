SOURCES=main.cpp user.cpp criptareandvalidare.cpp

ex: $(SOURCES)
	g++ -o aplicatie $(SOURCES)


