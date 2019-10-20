//Daniel Pascual
//Cyclic Redundancy Check

#include <iostream>	// pour le cout et le cin
#include <conio.h>	// pour le _getch() et _getche()
#include <string>

using namespace std;

const int SIZE = 4 * 8 + 3;

string limitStringSize(const string &msg, int limit) {

	if (msg.size() > limit) {
		string result = "";
		for (int i = 0; i < limit; i++) {
			result += msg[i];
		}
		result += "0";
		return result;
	}

	else
		return msg;

}


//Send string bits to a binary array
void bitConversion(const string &msg, bool *bin) {
	unsigned int m,pos=0;

	for (int a = 0; a < msg.size(); a++) {//Loop chaque char du array
		m = 0x80;
		for (int i = 0; i < 8; i++) {//loop chaque bit du char

			if (msg[a] & m)
				bin[pos] = 1;
			else
				bin[pos] = 0;

			pos++;
			m >>= 1;//Deplacement pour comparer les bits
		}
	}
}

//string bitConversion(string msg) {
//	string res="";
//	char m;
//	for (int a = 0; a < msg.size(); a++) {
//		m = 0x80;
//		for (int i = 0; i < 8; i++) {
//
//			if (msg[a] & m)
//				res += "1";
//			else
//				res += "0";
//
//			m >>= 1;//Deplacement pour comparer les bits
//		}
//	}
//	return res;
//}

int BinToDec(unsigned int*bin) {
	int base = 1;
	unsigned int dec=0;
	for (int i = 4*8 + 2; i >= 0; i--) {
		if (bin[i] == '1')
			dec += base;
		base = base * 2;
	}

	return dec;
}

// function to convert decimal to binary 
void decToBinary(int n)
{
	// array to store binary number 
	int binaryNum[32];

	// counter for binary array 
	int i = 0;
	while (n > 0) {

		// storing remainder in binary array 
		binaryNum[i] = n % 2;
		n = n / 2;
		i++;
	}

	// printing binary array in reverse order 
	for (int j = i - 1; j >= 0; j--)
		cout << binaryNum[j];
}



//Affichage du choix du generateur
int choixGenerator() {
	//add wherex and gotoxy and erase
	bool repeat;
	unsigned int gen;

	cout << "Choissisez un generateur:" << endl
		<< "\t" << "1) 11" << endl
		<< "\t" << "2) 13"
		<< endl << "Choix:";
	//int x= wherex(), int y=wherey();
	do{
		//gotoxy();
		char choix;
		repeat = false;

		cin >> choix;
		
		switch (choix) {
		case '1': gen = 11; break;
		case '2': gen = 13; break;
		default: repeat=true;
		}
	} while (repeat == true);
	return gen;
}

string ConvertIntToString(const int &a) {
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}



//int CRC_Calcul(unsigned int *msg, unsigned int gen, unsigned int reste) {
//
//	unsigned int crc = 0;
//	unsigned int add = 1, sub = 0x80, subTmp = 0,  counter;
//	bool stop;
//
//	//add <<= 3;
//	//for (int i = 0; i < 3; i++) {
//	//	if(reste&add)
//	//	msg[4 * 8 + i] = 1;
//	//	else
//	//		msg[4 * 8 + i] = 0;
//	//	add >>= 1;
//	//}
//	//
//	//add = 1;
//
//	for (int i = 0; i < SIZE; i++) {
//
//		if (crc < gen) {
//			crc <<= 1;
//			if (msg[i] == 1)
//				crc |= add;
//
//		}
//		else {
//			
//			while (crc >= gen) {
//				
//				sub = 0x80;
//				
//				for(int a=0;a<8;a++){
//				if (gen&sub){
//					if (crc&sub)//soustraction normale
//						crc = crc ^ sub;
//					else//le crc cherche un binaire plus haut a donner 
//					{
//						subTmp = sub;//Might delete subTmp since after unrolling, I reroll
//						counter = 1;
//						bool stop = false;
//						while(stop==false){//CHECK Condition might be wrong
//							
//							subTmp <<= 1;
//							if (crc&subTmp) {
//				
//								while (counter > 0) {
//									crc = crc ^ subTmp;
//									subTmp >>= 1;
//									counter--;
//								}
//								
//							}
//							else
//								stop = true;
//						counter++;
//						}
//					}
//					
//				}
//				sub >>= 1;
//				}
//			}
//		}
//	}
//	return crc;
//}



//int CRC_Calcul(unsigned int *msg, unsigned int gen, unsigned int reste) {
//
//	unsigned int crc = 0;
//	unsigned int add = 1, sub = 0x80, counter=0;
//	bool stop=false;
//
//	do {//for (int i = 0; i < SIZE; i++) {
//
//		
//		if (crc < gen) {
//			crc <<= 1;
//			if (msg[counter] == 1)
//				crc |= add; 
//				
//			counter++;
//		}
//		else {
//			crc ^= gen;
//			
//			//while(crc>gen){
//			//	sub = 8;//0x80
//			//
//			//	for (int a = 0; a < 4; a++) {
//			//		if (gen&sub) 
//			//			crc = crc ^ sub;
//			//
//			//		sub >>= 1;
//			//	}
//			//}
//		}
//		if (counter == SIZE - 1)stop = true;
//	} while (stop==false);
//	return crc;
//}

int CRC_Calcul(bool *msg, const unsigned int &gen, unsigned int reste) {

	unsigned int crc = 0;
	unsigned int  sub = 0x80, counter = 0;
	bool stop = false;
	

	do {
		if (crc >= gen){
			crc ^= gen;
			if (crc >= gen)
				crc ^= gen;
		}
	
			crc <<= 1;
			if (msg[counter] == 1)
				crc |= 1;


			counter++;
	


	} while (counter < SIZE);
	
	return crc;
}

void showTrame(bool*trame) {
	for (int i = 0; i < SIZE; i++) {
		cout << trame[i];
	}
}

//affichage binaire du crc
void showCRC(const unsigned int &crc) {
	unsigned int bin = 0x80;
	for (int i = 0; i < 8; i++) {
		if (crc&bin)
			cout << "1";
		else cout << "0";

		bin >>= 1;
	}
}

//modification de la trame avec le CRC
void changeTrame(bool *trame, const unsigned int&crc) {
	//modification de la trame
	unsigned int bin = 8;
	for (int i = 3; i > 0; i--) {
		if (crc&bin)
			trame[SIZE - i] = 1;
		else
			trame[SIZE - i] = 0;
		bin >>= 1;
	}
}


void secondTrame(bool*trame2, const bool*trame, unsigned int gen) {
	char repeat;


	for (int i = 0; i < SIZE; i++) {
		trame2[i] = trame[i];
	}


	cin >> repeat;
	if (repeat == 'O' || repeat == 'o'){
		unsigned int nb,pos;

		cout <<"\n"<< "Combien voulez-vous en introduire?[Max 10]: " ;
		cin >> nb;
		for(int i=0;i<nb;i++){
			cout << "\n" << "Position de l'erreur #" << i << " [entre 0 et 34]:";
			cin >> pos;

			if(trame2[pos]==1)trame2[pos] = 0;
			else trame2[pos] = 1;
		}
	}

}


void compareMSG(const bool trame2[]) {
	bool error = false;

	for (int i = 0; i < 3; i++) {
		if (trame2[SIZE - i] != 0)error = true;
	}

	if (error == false) cout << "Aucune erreur";
	else cout << "Erreur introduite";

}

void main() {
	string msg;
	unsigned int crc, crc2, gen;
	bool trame[SIZE]{ 0 }, trame2[SIZE]{ 0 };
	
	
	cout << "Entrer les 4 chars: ";
	cin >> msg;
	msg = limitStringSize(msg, 4);

	bitConversion(msg, trame);

	cout << " Message a envoyer: " << msg << endl << " La trame: "; 
	showTrame(trame);

	cout << endl;
	
	gen = choixGenerator();
	
	crc = CRC_Calcul(trame, gen, 0);
	
	cout << endl << "Voici le reste obtenu de la première application du CRC: " << crc;
	showCRC(crc);
	
	changeTrame(trame, crc);
	cout << endl << "Voici la nouvelle trame: ";
	showTrame(trame);
	
	
	cout << endl << "Voulez-vous introduire des erreurs?[O/N]:";
	secondTrame(trame2, trame, gen);

	crc2 = CRC_Calcul(trame2, gen,0);
	
	
	cout << endl << "Voici le reste obtenu de la deuxième application du CRC: " << crc2 <<"  "; showCRC(crc2);
	cout << "\n";
	compareMSG(trame2);
	
	_getch();

}
