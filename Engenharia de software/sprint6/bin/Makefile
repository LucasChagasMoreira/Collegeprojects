LIB_DIR = 'libVensim.so'
SO:
	g++ -c ../src/*.cpp -fPIC -g
	g++ *.o -shared -o libVensim.so -fpic -g 
	rm *.o

funcionalcomdll:
	g++ -c ../test/flows/*.cpp -fPIC -g
	g++ -c ../test/funcional/*.cpp -fPIC -g
	g++ *.o -o funcional -L. -lVensim -g
	rm *.o
unitariocomdll:
	g++ -c ../test/flows/*.cpp -fPIC -g
	g++ -c ../test/unit/*.cpp -fPIC -g
	g++ *.o -o unitario -L. -lVensim -g
	rm *.o
runtestescomdll:
	export LD_LIBRARY_PATH=:"/home/lucas/Documents/GitHub/Collegeprojects/Engenharia de software/sprint5/bin/libVensim.so"$LD_LIBRARY_PATHD
	./funcional
	./unitario
runtestessemdll:
	./functests_exe
	./unit_exe
	