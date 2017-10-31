include Makefile.inc

SAMPLE_DATA=0001-sampleDataModule.bin

all: lib sampleCodeModule sampleDataModule dummy shell

lib:
	cd Lib; make
shell:
	cd Shell; make
dummy:
	cd Dummy; make


sampleCodeModule:
	cd SampleCodeModule; make

sampleDataModule:
	printf "This is sample data." >> $(SAMPLE_DATA) && dd if=/dev/zero bs=1 count=1 >> $(SAMPLE_DATA)

clean:
	cd SampleCodeModule; make clean
	cd Shell; make clean
	cd Lib; make clean
	rm -rf *.bin


.PHONY: sampleCodeModule dummy shell all clean 
