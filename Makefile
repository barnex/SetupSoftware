all:
	make -C FFTGrabber
	make -C Controller

clean:
	make clean -C FFTGrabber
	make clean -C Controller
