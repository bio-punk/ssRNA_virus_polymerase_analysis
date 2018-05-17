#include <iostream>
#include <fstream>
#include <string>
#include <array>

#include "fasta.h"

#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::array;
using std::vector;

int main(void)
{
	ifstream seqName("out.txt");
	ifstream db("base001.fasta");
	vector<fasta> base(71705);
	for (int i = 0; i < 71705; i++) {
		string name, seqs;
		db >> name >> seqs;
		name.erase(name.begin());
		fasta f(name, seqs);
		base[i] = f;
	}
	db.close();
	cout << "init\n";

	vector<fasta> newdb;
	for (int i = 0; i < 68249; i++) {
		string name;
		seqName >> name;
		for (int k = 0; k < 71705; k++) {
			if (name != base[k].name()) { continue; }
			bool nonHave = true;
			for (int w = newdb.size() - 1; w >= 0; w--) {
				if (newdb[w].name() == base[k].name()) { nonHave = false; break; }
			}
			if (nonHave) { newdb.push_back(base[k]); }
		}
		if (i % 1000 == 0) { cout << " find " << i << "/68249\n"; }
		for (int k = 0; k < 11; k++) { seqName >> name; }
	}
	seqName.close();

	ofstream outp("newdb.fasta");
	for (int i = 0; i < newdb.size(); i++) {
		outp << ">" << newdb[i].name() << endl << newdb[i].seq() << endl;
	}

}