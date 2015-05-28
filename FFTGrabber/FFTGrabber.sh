#! /bin/bash
# Filters out spurious alsa messages
FFTGrabber 5004 1 2> >(grep FFTGrabber)
