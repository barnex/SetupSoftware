all:
	make -C FFTGrabber
	make -C Controller
	make -C CurrentSense

clean:
	make clean -C FFTGrabber
	make clean -C Controller
	make clean -C CurrentSense
