/*
 * ahbUart.cpp
 *
 *  Created on: Nov 3, 2016
 *      Author: jmgomez
 */


#include "ahbUart.hpp"

#include <iostream>

UartCommand::UartCommand(){
	this->data.empty();
	this->Length = 0;
	this->Write = false;
	this->Addr = 0;
}

UartCommand::UartCommand(UartCommand& uc){
	//this->data(uc.data);
	this->Length = uc.Length;
	this->Write = uc.Write;
	this->Addr = uc.Addr;
	this->data.empty();
	this->data.resize(uc.Length);
	copy(uc.data.begin(), uc.data.end(), this->data.begin());
}


UartCommand::UartCommand(string Dir, unsigned int Addr, const vector<int> &Data, unsigned int Length){

	if (!Dir.compare("Tx")){
		this->Length = Data.size();
		this->Write = true;
		this->Addr = Addr;
		this->data.empty();
		this->data.resize(Data.size());
		copy(Data.begin(), Data.end(), this->data.begin());
	}
	else{
		this->Length = Length;
		this->data.resize(this->Length);
		this->Write = true;
		this->Addr = Addr;
		cout << "Error";
	}
	cout << "Building " << Dir << " command to address " << this->Addr << " and size " << this->Length << endl;

};


UartCommand::~UartCommand(){
	this->Length = 0;
	this->Write = false;
	this->Addr = 0;
	this->data.clear();
};


/**
 * Create a packet with the command.
 * */
unsigned int UartCommand::build()
{
	//Size of the Command is Header (TypeCommand, Length), Address, Data => 1,4,-- in bytes.
	vector<int>::size_type cmdLength = 1 + sizeof(this->Addr) + this->data.size()*sizeof(int);
	this->cmd.empty();

	char header;
	header = (this->Write)?(0xC0 | this->Length): (0x80 | this->Length);
	this->cmd.push_back(header);
	// Split address if for bytes.
	char* addrData = static_cast<char*>(static_cast<void*>(&this->Addr));
	this->cmd.push_back(addrData[3]);
	this->cmd.push_back(addrData[2]);
	this->cmd.push_back(addrData[1]);
	this->cmd.push_back(addrData[0]);

	char* dataBytes;
	for(auto& elem : this->data){
		dataBytes = static_cast<char*>(static_cast<void*>(&elem));
		this->cmd.push_back(dataBytes[3]);
		this->cmd.push_back(dataBytes[2]);
		this->cmd.push_back(dataBytes[1]);
		this->cmd.push_back(dataBytes[0]);
	}

	return this->Length;
}

void UartCommand::print(){
	std::cout << "Command information:  " ;
	//cout.setf(ios::hex, ios::basefield);
	for(auto& elem : this->cmd){
		std::cout << hex << uppercase << static_cast<int>(elem) << '\t';
	}
	std::cout << std::endl;
}


