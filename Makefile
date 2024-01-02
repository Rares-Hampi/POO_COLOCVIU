SOURCES=main.cpp utilizator.cpp criptareandvalidare.cpp

ex: $(SOURCES)
	g++ -o aplicatie $(SOURCES)


