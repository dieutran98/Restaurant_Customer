#Restaurant
Restaurant: build/main_restaurant.o build/Customer.o build/queue.o ./build/Restaurant.o #build/Food.o
	g++ -pthread -o $@ $^


#Customer0
Customer_m0: build/Customer.o build/queue.o build/main_customer0.o
	g++ -pthread -o $@ $^


	
# .o file
./build/Customer.o: src/Customer.cpp include/Customer.h
	g++ -o $@ -c $<
./build/queue.o: src/queue.cpp include/queue.h
	g++ -o $@ -c $<
./build/Restaurant.o: src/Restaurant.cpp include/Restaurant.h 
	g++ -o $@ -c $<
build/main_restaurant.o: src/main_restaurant.cpp include/Restaurant.h
	g++ -pthread -o $@ -c $<
build/main_customer0.o: src/main_customer0.cpp include/Customer.h
	g++ -pthread -o $@ -c $<

#test make
Customer_test: test/build/Customer_test.o build/Customer.o build/queue.o
	g++ -o $@ $^
./test/build/Customer_test.o: test/src/Customer_test.cpp include/Customer.h
	g++ -o $@ -c $<
queue_test: test/build/queue_test.o build/Customer.o build/queue.o
	g++ -o $@ $^
./test/build/queue_test.o: test/src/queue_test.cpp include/Customer.h include/queue.h
	g++ -o $@ -c $<

#Send_test
send: test/build/send.o
	g++ -o $@ $<
test/build/send.o: test/src/send_test.cpp
	g++ -o $@ -c $<

#Recieve_test
recieve: test/build/recieve.o
	g++ -o $@ $<
test/build/recieve.o: test/src/recieve_test.cpp
	g++ -o $@ -c $<

clean:
	rm build/*.o
	rm test/build/*.o

static_check:
	cppcheck --enable=all --errorlist