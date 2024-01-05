SOURCES=main.cpp user.cpp criptare_si_validare.cpp flow.cpp step.cpp

ex: $(SOURCES)
	g++ -g -o aplicatie $(SOURCES)


