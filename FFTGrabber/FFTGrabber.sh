#! /bin/bash
# Filters out spurious alsa messages
FFTGrabber $@ 2> >(grep FFTGrabber)
