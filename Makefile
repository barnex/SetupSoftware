all:
	astyle --indent=tab --style=java */*.c */*.h */*.cpp || echo ""
	make -C Controller
	make -C CurrentSense
	make -C DumbScanner
	(cd FFTGrabber && ./make.bash)
	make -C FMRScanner
	make -C HPInterface
	make -C HittiteInterface
	make -C PiezoFMR
	make -C PiezoScanner
	make -C RigolInterface
	#(cd ScannerGUI && qmake && make)

clean:
	make clean -C Controller
	make clean -C CurrentSense
	make clean -C DumbScanner
	rm -rf FFTGrabber/FFTGrabber FFTGrabber/*.o
	make clean -C FMRScanner
	make clean -C HPInterface
	make clean -C HittiteInterface
	make clean -C PiezoFMR
	make clean -C PiezoScanner
	make clean -C RigolInterface
	make clean -C ScannerGUI
