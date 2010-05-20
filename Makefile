all:
	g++ main.cpp -o client -lcxcore -lcv -lhighgui -lboost_system -lboost_thread
	g++ async_udp_echo_server.cpp -o server -lboost_system -lboost_thread

	
