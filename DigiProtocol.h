/*******************************************************************************
 *  DigiProtocol is Library designed for Communication with DigiSpark over USB.
 *  It’s based on DigiUSB library but adds protocol-frame.
 *  Copyright (C) 2021 Pawo (pandretix.pl)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *********************************************************************************/


#ifndef DIGIPROTOCOL_H
#define DIGIPROTOCOL_H

#include <string>
#include <libusb.h>
#include <chrono>
#include <thread>
#include <vector>


// device VID/PID
const int VID = 0x16c0;
const int PID = 0x05df;

// request definitions
enum dp_requests {
    DP_START_OF_TRANSMISSION = 0xAA,
    DP_SEND_ID = 0xBB,
    DP_BURN_ID = 0xDD,
    DP_SEND_STATUS = 0xAF,
    DP_STATUS_ALIVE = 0xFA,
    DP_REPEAT_MESSAGE = 0xCC,
    DP_WRONG_REQUEST = 0xEE,
    DP_WRONG_ID_FORMAT = 0xEA,
    DP_ID_TRANSMISSION = 0xDA,
    DP_BACKUP_TRANSMISSION = 0xDB,
    DP_CORRUPTED_ID = 0xDC,
    DP_NEW_DEVICE = 0xDE
};

// error list
enum dp_errors {
    DP_NO_ERROR = 0,
    DP_NO_DATA = 0,

    DP_ACCESS_ERROR = -1,

    DP_ERROR_NO_RESPONSE = -2,
    DP_ERROR_NO_DEVICE = -3,
    DP_ERROR_WRONG_PROTOCOL = -4,
    DP_ERROR_TIMEOUT = -5,
    DP_ERROR_CORRUPTED_DATA = -6,
    DP_ERROR_WRONG_SIZE = -7,
    DP_ERROR_WRONG_ID_LENGTH = -8,
    DP_EEPROM_WARNING = -9,
    DP_EEPROM_ERROR = -10,
    DP_ERROR_DEVICE_DISCONNECTED = -11,
    DP_ERROR_DEVICE_BUSY = -12
};


class DigiProtocol {


private:
    libusb_context* _context;
    libusb_device_handle* _devHandle;
    libusb_device** _deviceList;
	std::chrono::time_point<std::chrono::high_resolution_clock> _lastPing;
	int _lastStatus;
    int _errorStatus;
    int _timeDuration(std::chrono::time_point<std::chrono::high_resolution_clock> time_start);
    uint16_t _crc16Update(uint16_t crc, uint8_t byte);

    int _claimDevice();
    void _releaseDevice();
public:
    int _readByte(uint8_t &buffer, int timeout=1000);
    

    DigiProtocol(std::string ID="", int timeout=1000);
    ~DigiProtocol();
    int readMessage(std::string &message, int timeout=1000);
    int sendRequest(uint8_t request, int timeout=1000);
    int sendMessage(std::string message);
    int listDevices(std::vector<std::string> &IDlist, int timeout=1000);
    int error();
    bool isOpen(int timeout=1000);
	int readID(std::string &ID, int timeout=1000);
    int open(std::string ID="", int timeout=1000);
    void close();

};


inline DigiProtocol::DigiProtocol(std::string ID, int timeout) {
    _context = NULL;
    _devHandle = NULL;
    _deviceList = NULL;
    _errorStatus = DP_NO_ERROR;
	_lastPing = std::chrono::high_resolution_clock::now();

    libusb_init(&_context);

    _errorStatus = open(ID, timeout);
}

inline DigiProtocol::~DigiProtocol() {
    libusb_close(_devHandle);
    libusb_exit(_context);
}

inline int DigiProtocol::_timeDuration(std::chrono::time_point<std::chrono::high_resolution_clock> time_start) {
    std::chrono::time_point<std::chrono::high_resolution_clock>  time_finish = std::chrono::high_resolution_clock::now();
    return ( std::chrono::duration_cast<std::chrono::milliseconds>(time_finish - time_start).count() );
}

inline uint16_t DigiProtocol::_crc16Update(uint16_t crc, uint8_t byte) { // this function was taken from the library  util/crc16.h for compatibility with AVR code
    int i;
    crc ^= byte;
    for (i = 0; i < 8; ++i) {
        if (crc & 1)
            crc = (crc >> 1) ^ 0xA001;
        else
            crc = (crc >> 1);
    }
    return crc;
}

inline int DigiProtocol::readMessage(std::string &message, int timeout) {
    int r=0, data_size;
    uint8_t byte=0;
    uint16_t crc = 0;

    std::string buffer="";

    message = "";

    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    int time = _timeDuration(start);

    r = _claimDevice();

    while( r == DP_ERROR_DEVICE_BUSY && (time < timeout || timeout == 0) ) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        r = _claimDevice();

        time = _timeDuration(start);
    }

    if(r != DP_NO_ERROR) return r;

    while( byte != DP_START_OF_TRANSMISSION && (time < (timeout/2) || timeout == 0) ) {
        r = _readByte(byte, timeout - time);
        if(r <= 0)  std::this_thread::sleep_for(std::chrono::milliseconds(5));

        time = _timeDuration(start);
    }



    if(byte != DP_START_OF_TRANSMISSION) {
        if( _timeDuration(_lastPing) > 1000  ) { // ping no more than once every 250ms
			_lastPing = std::chrono::high_resolution_clock::now();
			if(isOpen(timeout/2)) {
				_lastStatus = DP_NO_DATA;
			} else {
				_lastStatus = DP_ERROR_NO_RESPONSE;
			}
		}
        _releaseDevice();
        return _lastStatus;

    }


     _readByte(byte, timeout - time);
     data_size = (int)byte;
     int x=0;



    while(x < data_size + 2 && (time < timeout || timeout == 0) ) {
        r = _readByte(byte, timeout - time);
        if(r <= 0)  std::this_thread::sleep_for(std::chrono::milliseconds(5));
        else {buffer += byte; x++;}

        time = _timeDuration(start);
    }


    if(time > timeout) {
        _releaseDevice();
        return DP_ERROR_TIMEOUT;
    }
    if(data_size + 2 != (int)buffer.length()) {
        _releaseDevice();
        return DP_ERROR_WRONG_SIZE;
    }

    //data_size = buffer[0];

    for(int x=0; x<data_size; x++) {
        crc = _crc16Update(crc, buffer[x]);
        message+= buffer[x];
    }

    crc = _crc16Update(crc, buffer[data_size]); // 1st byte of crc remaind
    crc = _crc16Update(crc, buffer[data_size+1]); // 2nd byte of crc remaind

    if(crc) {
        _releaseDevice();
        return DP_ERROR_CORRUPTED_DATA;
    }

    return message.length();
}

inline int DigiProtocol::readID(std::string &ID, int timeout) {

    sendRequest(DP_SEND_ID);

    int r=0;
    uint8_t byte=0;

    ID="";


    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    int time = _timeDuration(start);

        r = _claimDevice();

    while( r == DP_ERROR_DEVICE_BUSY && (time < timeout || timeout == 0) ) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        r = _claimDevice();

        time = _timeDuration(start);
    }

    if(r != DP_NO_ERROR) return r;


    while( ( byte != DP_ID_TRANSMISSION && byte != DP_BACKUP_TRANSMISSION && byte != DP_CORRUPTED_ID && byte != DP_NEW_DEVICE ) && (time < timeout || timeout == 0) ) {
        r = _readByte(byte, timeout - time);
        if(r <= 0)  std::this_thread::sleep_for(std::chrono::milliseconds(5));

        time = _timeDuration(start);
    }
    if(time > timeout) {
        _releaseDevice();
        return DP_ERROR_TIMEOUT;
    }
    if(byte == DP_CORRUPTED_ID) {
        _releaseDevice();
        return DP_EEPROM_ERROR;
    }
    if(byte == DP_NEW_DEVICE) {
        _releaseDevice();
        return DP_NEW_DEVICE;
    }
    if(byte == DP_BACKUP_TRANSMISSION) _errorStatus = DP_EEPROM_WARNING;

    r = readMessage(ID, timeout);
    if(r < 0) {
        _releaseDevice();
        return r;
    }

    _releaseDevice();
    return DP_NO_ERROR;
}

inline int DigiProtocol::_readByte(uint8_t &buffer, int timeout) {
    int _r=0;
    _r = libusb_control_transfer(_devHandle, (0x01<< 5) | 0x80, 0x01, 0, 0, &buffer, 1, timeout);
    return _r;
}

inline int DigiProtocol::sendRequest(uint8_t request, int timeout) {
    int _r=0;
    unsigned char buffer=0;
    _r = libusb_control_transfer(_devHandle, (0x01<< 5), 0x09, 0, request, &buffer, 1, timeout);

    return _r;
}

inline int DigiProtocol::sendMessage(std::string message) {

    uint16_t crc = 0;
    sendRequest(DP_START_OF_TRANSMISSION);
    sendRequest((int)message.length());
    for(int x=0; x<(int)message.length(); x++) {
        crc = _crc16Update(crc, message[x]);
        sendRequest(message[x]);
    }
    sendRequest((uint8_t)(crc & 0xFF));
    sendRequest((uint8_t)(crc >> 8));

    return DP_NO_ERROR;
}

inline int DigiProtocol::error() {
    int temp = _errorStatus;
    _errorStatus = 0;
    return temp;
}


inline bool DigiProtocol::isOpen(int timeout) {
    if(_devHandle == NULL) return false;

    int r=0;
    uint8_t byte=0;

    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    int time = _timeDuration(start);

    r = _claimDevice();

    while( r == DP_ERROR_DEVICE_BUSY && (time < timeout || timeout == 0) ) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        r = _claimDevice();

        time = _timeDuration(start);
    }

    if(r != DP_NO_ERROR ) return false;

    sendRequest(DP_SEND_STATUS, timeout);

    while( byte != DP_STATUS_ALIVE && time < timeout) {
        r = _readByte(byte, timeout - time);
        if(r <= 0)  std::this_thread::sleep_for(std::chrono::milliseconds(5));

        time = _timeDuration(start);
    }

    if(byte != DP_STATUS_ALIVE) {
        //close();
        return false;
    }

    return true;
}

inline void DigiProtocol::close() {
    libusb_close(_devHandle);
    _devHandle = NULL;
}

inline int DigiProtocol::open(std::string ID, int timeout) {
    int result=0;

    if(ID =="") {
        _devHandle = libusb_open_device_with_vid_pid(NULL, VID, PID);

    } else {

        int numberOfDevices = libusb_get_device_list(NULL, &_deviceList);
        if(numberOfDevices < 0) return DP_ACCESS_ERROR;

        for(int x=0; x<numberOfDevices; x++) {
            struct libusb_device_descriptor _desc;
            result = libusb_get_device_descriptor(_deviceList[x], &_desc);
            if(result < 0) return DP_ACCESS_ERROR;
            if(_desc.idVendor == VID && _desc.idProduct == PID) {
                libusb_open(_deviceList[x], &_devHandle);
                if(_devHandle == NULL) return DP_ACCESS_ERROR;

                std::string deviceID="";
                result = readID(deviceID, timeout);
                if( (result == DP_NEW_DEVICE && ID == "New Device without ID") || (result == DP_EEPROM_ERROR && ID == "Device with corrupted ID" ) ) {
                    libusb_free_device_list(_deviceList, 1);
                    return DP_NO_ERROR;
                }

                if( ( (ID.length() == 2 && ID == deviceID.substr(0, 2)) || ID == deviceID ) && result == DP_NO_ERROR ) {
                    libusb_free_device_list(_deviceList, 1);
                    return DP_NO_ERROR;
                    }

                if(result < 0)
                    _errorStatus = result;

                libusb_close(_devHandle);
            }
        }

        libusb_free_device_list(_deviceList, 1);
    }

    return  DP_ERROR_NO_DEVICE;

}

inline int DigiProtocol::listDevices(std::vector<std::string> &IDlist, int timeout) {

    close();

    libusb_context * _contextFunc = NULL;
    libusb_device ** _deviceListFunc = NULL;

    int result=0;
    std::string ID="";

    libusb_init(&_contextFunc);

    int numberOfDevices = libusb_get_device_list(NULL, &_deviceListFunc);
        if(numberOfDevices < 0) return DP_ACCESS_ERROR;

    for(int x=0; x<numberOfDevices; x++) {
        struct libusb_device_descriptor _desc;
        result = libusb_get_device_descriptor(_deviceListFunc[x], &_desc);
        if(result < 0) return DP_ACCESS_ERROR;
        if(_desc.idVendor == VID && _desc.idProduct == PID) {
            result = libusb_open(_deviceListFunc[x], &_devHandle);
            if(_devHandle == NULL) return DP_ACCESS_ERROR;

            DigiProtocol::_devHandle = _devHandle;
            result = DigiProtocol::readID(ID, timeout);
            if(result == DP_NEW_DEVICE) ID="New Device without ID";
            else if(result == DP_EEPROM_ERROR) ID="Device with corrupted ID";
            else if(result < 0) ID="ERROR";

            libusb_close(_devHandle);
            _devHandle = NULL;

            IDlist.push_back(ID);
        }

    }

    libusb_free_device_list(_deviceListFunc, 1);
    libusb_exit(_contextFunc);

    return DP_NO_ERROR;
}

inline int DigiProtocol::_claimDevice() {
    int r = libusb_claim_interface(_devHandle, 0);
    if(r == 0)
        return DP_NO_ERROR;

    return DP_ERROR_DEVICE_BUSY;
}

inline void DigiProtocol::_releaseDevice() {
    libusb_release_interface(_devHandle, 0);
}

#endif // DIGIPROTOCOL_H

