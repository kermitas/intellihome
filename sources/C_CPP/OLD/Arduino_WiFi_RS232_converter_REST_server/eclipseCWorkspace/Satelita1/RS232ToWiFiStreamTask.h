/*
 * RS232ToWiFiStreamTask.h
 *
 *  Created on: 21-05-2012
 *      Author: root
 */

#ifndef RS232TOWIFISTREAMTASK_H_
#define RS232TOWIFISTREAMTASK_H_

// =================================================

#include <Arduino.h>

// =================================================

#include "Runnable.h"
#include "DebugPrinter.h"

// =================================================

class RS232ToWiFiStreamTask: public Runnable
{
	public:

		RS232ToWiFiStreamTask();
		void run();

	protected:

		DebugPrinter dp;

		byte state;
			// 0 (logic point)
			//		if there is free space in incommingBuffer -> 1 [uwaga, ten zewnetrzny ktos kto zczyta bufor tak ze do konca dojedzie to musi odstawic go na sam poczatek]
			//		if there is NO free space in incommingBuffer -> 6
			// 1 (sending RECV command)
			//		if there were problem while sending this command -> 6
			//		after successful sending -> 2
			// 2 (waiting for 6 available bytes)
			//		if there was timeout -> 6
			//		all data ready -> 3
			// 3 (parsing header of RECV_ACK)
			//		if there is a problem while reading this command (no data in stream, bad command number, bad serial number, bad two reserved bytes, incomming data bigger than available space) -> 6
			//		if there is no incomming data or there will be incomming data -> 4
			// 4 (waiting for all available byes as stated in RECV_ACK and 2B of CRC)
			//		if there was timeout -> 6
			//		all data ready -> 5
			//	5 (reading data to incommingBuffer)
			//		if there is a problem while reading data (no data in stream, CRC does not match) -> 6
			//		if all data was read (and crc match) -> 6

			// 6 (logic point)
			//		if there is no data to send -> 0
			//		if there is data to send -> 7
			// 7 (sending SEND command)
			//		if there were problem while sending this command -> 0
			//		after successful sending -> 8
			// 8 (waiting for 5 available bytes)
			//		if there was timeout -> 0
			//		all data ready -> 9
			// 9 (reading and parsing SEND_ACK command)
			//		if there were problem while reading this command (no data in stream, bad command number, bad sn, bad 2 reserved bytes, bad info ack, bac CRC) -> 0
			//		after successful reading -> 0

		// pytania
		//	jak zrobic powrot do SEND jesli SEND_ACK powie, ze zle ack_info? albo przynajmniej jak to przekazac swiatu na zewnatrz?
		//  jak zrobic powrot do RECV jesli w RECV_ACK cos pojdzie nie tak (np. bedzie zle CRC?)

		// ---
};

// =================================================

#endif /* RS232TOWIFISTREAMTASK_H_ */