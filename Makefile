SOURCES=main.cpp user.cpp criptare_si_validare.cpp

ex: $(SOURCES)
	g++ -o aplicatie $(SOURCES)


