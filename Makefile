all:
	make -C Controller
	make -C CurrentSense
	make -C DumbScanner
	make -C FFTGrabber
	make -C FMRScanner
	make -C HPInterface
	make -C HittiteInterface
	make -C PiezoFMR
	make -C PiezoScanner
	make -C ScannerGUI

clean:
	make clean -C Controller
	make clean -C CurrentSense
	make clean -C DumbScanner
	make clean -C FFTGrabber
	make clean -C FMRScanner
	make clean -C HPInterface
	make clean -C HittiteInterface
	make clean -C PiezoFMR
	make clean -C PiezoScanner
	make clean -C ScannerGUI
