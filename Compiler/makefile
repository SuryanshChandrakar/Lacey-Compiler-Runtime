all: version_1/bps1_to_am1 version_2/bps2_to_am1 version_3/bps3_to_am1

version_1/bps1_to_am1:
	make -C version_1
	
version_2/bps2_to_am1:
	make -C version_2
	
version_3/bps3_to_am1:
	make -C version_3

clean:
	make -C version_1 clean
	make -C version_2 clean
	make -C version_3 clean
