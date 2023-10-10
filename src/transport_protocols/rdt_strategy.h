#ifndef RDT_STRATEGY_H
#define RDT_STRATEGY_H

/* import libraries */
/******************************************/
#include "../utils/port_handler.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

/**
 * 策略模式
*/
class rdt_strategy
{
	protected:
		// attributes
		port_handler *p_handler;
		vector<int> window_size_analysis;
		int successful_sent;
		int total_sent;
	public:
		// constructor
		rdt_strategy(port_handler *p);
		virtual ~rdt_strategy() = default;
		void print_window_size_analysis();

		// interface methods
		virtual void implement() = 0;
};

#endif 
