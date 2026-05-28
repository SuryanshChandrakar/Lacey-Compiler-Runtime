


bool showstacks = false;
bool showops = false;
bool creep = false;

#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
using namespace std;


int opcode_count = 22;
string opcode_names[] = {"ADD", "SUB", "MULT", "DIV", "MOD",
                  "LT", "LE", "EQ", "GT", "GE", "NEQ",
                  "NOT", "AND", "OR",
                  "JMP", "JFALSE", "JTRUE",
                  "CALL", "RET",
                  "LOAD", "STO", "LIT"};
enum mnemonics {ADD, SUB, MULT, DIV, MOD,
                LT, LE, EQ, GT, GE, NEQ,
                NOT, AND, OR,
                JMP, JFALSE, JTRUE,
                CALL, RET,
                LOAD, STO, LIT};
int paramcount[] = {0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0,
                    0, 0, 0,
                    1, 1, 1,
                    3, 0,
                    2, 2, 1};


class Process {
	public:
		int jump_label;
		map<string, int> jump_label_to_index;
		vector<int> jump_lines;
		vector<vector<int> > OPS;

		int dstack_pointer;
		vector<int> data_stack;
		int pstack_pointer;
		vector<int> procedure_stack;
		int instruction_pointer;

		Process(vector<int> params) {
			instruction_pointer = 1;
			jump_label_to_index.clear();
			jump_label_to_index["EXIT:"] = 0;
			jump_label_to_index["0:"] = 0;
			jump_lines.clear();
			jump_lines.push_back(0);
			jump_label = 1;

			OPS.clear();
			int current_line = 1;
			vector<int> current_op(4,0);
			OPS.push_back(current_op); // dummy so the code lines start with 1

			data_stack.clear();
			dstack_pointer = 0;

			procedure_stack=params;
			pstack_pointer = params.size();
			ppush(0);
			ppush(0);
			ppush(0);

		}
		Process(string FileName, vector<int> params = vector<int>(0)) {
			LoadFromFile(FileName,params);
		}
		static string uppercase(string str) {
			for(int i = str.size()-1; i >= 0; --i)
				if(str[i] >= 'a' && str[i] <= 'z')
					str[i] = str[i]-'a'+'A';
			return str;
		}
		int base(int level_difference) {
			if(level_difference <= 0)
				return 0;
			int b1 = base(level_difference-1);
			return b1 + procedure_stack[pstack_pointer - b1 - 1];
		}


		int dpop() {
			return data_stack[--dstack_pointer];
		}
		void dpush(int val) {
			if(dstack_pointer >= data_stack.size()) {
				data_stack.push_back(val);
				dstack_pointer++;
			} else {
				data_stack[dstack_pointer++] = val;
			}
		}
		int ppop() {
			return procedure_stack[--pstack_pointer];
		}
		void ppush(int val) {
			if(pstack_pointer >= procedure_stack.size()) {
				procedure_stack.push_back(val);
				pstack_pointer++;
			} else {
				procedure_stack[pstack_pointer++] = val;
			}
		}


		bool LoadFromFile(string FileName, vector<int> params = vector<int>(0)) {
			instruction_pointer = 1;

			jump_label_to_index.clear();
			jump_label_to_index["EXIT:"] = 0;
			jump_label_to_index["0:"] = 0;
			jump_lines.clear();
			jump_lines.push_back(0);
			jump_label = 1;

			OPS.clear();
			int current_line = 1;
			vector<int> current_op(4,0);
			OPS.push_back(current_op); // dummy so the code lines start with 1

			data_stack.clear();
			dstack_pointer = 0;

			procedure_stack = params;
			pstack_pointer = params.size();
			ppush(0);
			ppush(0);
			ppush(0);

			ifstream prog(FileName.c_str());
			string opcode;
			while(prog.peek() != -1) {
				prog >> opcode;                                       // read opcode
				opcode = uppercase(opcode);
				if(opcode[opcode.size()-1] == ':') {     // if it's a jump label def
					if(jump_label_to_index.find(opcode) == jump_label_to_index.end()) {
						jump_label_to_index[opcode] = jump_label++;
						jump_lines.push_back(current_line);
					} else {
						if(jump_lines[jump_label_to_index[opcode]] == -2) {
							jump_lines[jump_label_to_index[opcode]] = current_line;
						} else {
							cerr << "Label \"" << opcode << "\" already defined\n";
							return false;
						}
					}
					continue;
				}

				for(int i = 0; i < opcode_count; i++) // else (no jump label -> opcode)
					if(opcode_names[i] == opcode) {
						current_op[0] = i;
						if(i == JMP || i == JFALSE || i == JTRUE || i == CALL) { // jumps
							prog >> opcode;
							opcode = uppercase(opcode);
							if(jump_label_to_index.find(opcode+":") == jump_label_to_index.end()) {
								jump_label_to_index[opcode+":"] = jump_label++;
								jump_lines.push_back(-2);
							}
							current_op[1] = jump_label_to_index[opcode+":"];
							if(i == CALL) {
								prog >> current_op[2];
								prog >> current_op[3];
							}
						} else {
							for(int j = 1; j <= paramcount[i]; j++)
								prog >> current_op[j];
						}
						OPS.push_back(current_op);
						goto opcode_found;
					}
				cerr << "unknown opcode \"" << opcode << "\"\n";
				return false;
				opcode_found:
				current_line++; // jump-label definitions have no line
			}

		for(int i = OPS.size()-1; i >= 0; --i)
			if(OPS[i][0] == JMP || OPS[i][0] == JFALSE || OPS[i][0] == JTRUE || OPS[i][0] == CALL) {
				OPS[i][1] = jump_lines[OPS[i][1]];
				if(OPS[i][1] == -2) {
					cerr << "jump label never defined (op number "<<i<<")\n";
					return false;
				}
			}
		return true;
		}

		void ShowDataStack(ostream& os) {
			if(dstack_pointer > 0) // print data stack
				os << data_stack[dstack_pointer-1];
			else
				os << "\"\"";
			for(int j = dstack_pointer-2; j >= 0; j--)
				os << ":" << data_stack[j];
		}
		void ShowProcedureStack(ostream &os) {
			int current_frame = pstack_pointer-1; // print procedure stack framewise
			while(procedure_stack[current_frame] > 0) {
				os << "  " << procedure_stack[current_frame--];
				for(int j = procedure_stack[current_frame]; j > 0; j--, current_frame--)
					os << ":" << procedure_stack[current_frame];
			}
			os << "  " << procedure_stack[current_frame];
			for(current_frame--; current_frame >= 0; current_frame--)
				os << ":" << procedure_stack[current_frame];
		}

		void RunProcess(int how_many_ops = -1) {
			int lval, rval, base_bak;
			for(int i = 0; (i < how_many_ops || how_many_ops < 0) && instruction_pointer > 0; i++) {

				if(showstacks) {
					cout << "  ";
					if(!showops)
						cout << instruction_pointer << "\t";
					ShowDataStack(cout);
					cout << "\t";
					ShowProcedureStack(cout);
					if(!creep || showops) cout << "\n";
				}
				if(showops) {
					cout << "  (" << instruction_pointer << ")\t" << opcode_names[OPS[instruction_pointer][0]];
					for(int j = 1; j <= paramcount[OPS[instruction_pointer][0]]; j++)
						cout << "\t" << OPS[instruction_pointer][j];
					if(!creep) cout << "\n";
				}
				if(creep)
					cin.ignore(1);

				switch(OPS[instruction_pointer][0]) {
					case ADD:
						lval = dpop();
						rval = dpop();
						dpush(rval + lval);
						break;
					case SUB:
						lval = dpop();
						rval = dpop();
						dpush(rval - lval);
						break;
					case MULT:
						lval = dpop();
						rval = dpop();
						dpush(rval * lval);
						break;
					case DIV:
						lval = dpop();
						rval = dpop();
						dpush(rval / lval);
						break;
					case MOD:
						lval = dpop();
						rval = dpop();
						dpush(rval % lval);
						break;

					case LT:
						lval = dpop();
						rval = dpop();
						dpush((rval < lval)?1:0);
						break;
					case LE:
						lval = dpop();
						rval = dpop();
						dpush((rval <= lval)?1:0);
						break;
					case EQ:
						lval = dpop();
						rval = dpop();
						dpush((rval == lval)?1:0);
						break;
					case GT:
						lval = dpop();
						rval = dpop();
						dpush((rval > lval)?1:0);
						break;
					case GE:
						lval = dpop();
						rval = dpop();
						dpush((rval >= lval)?1:0);
						break;
					case NEQ:
						lval = dpop();
						rval = dpop();
						dpush((rval != lval)?1:0);
						break;

					case NOT:
						lval = dpop();
						dpush((lval == 0)?1:0);
						break;
					case AND:
						lval = dpop();
						rval = dpop();
						dpush((rval == 1 && lval == 1)?1:0);
						break;
					case OR:
						lval = dpop();
						rval = dpop();
						dpush((rval == 1 || lval == 1)?1:0);
						break;

					case JMP:
						instruction_pointer = OPS[instruction_pointer][1]-1;
						break;
					case JFALSE:
						lval = dpop();
						if(lval == 0)
							instruction_pointer = OPS[instruction_pointer][1]-1;
						break;
					case JTRUE:
						lval = dpop();
						if(lval == 1)
							instruction_pointer = OPS[instruction_pointer][1]-1;
						break;

					case CALL:
						base_bak = base(OPS[instruction_pointer][2]);
						// allocate local variables
						for(int i = OPS[instruction_pointer][3]; i > 0; i--)
							ppush(0);
						ppush(instruction_pointer+1); // return address
						ppush(OPS[instruction_pointer][3]+2); // dynamic link
						ppush(base_bak + OPS[instruction_pointer][3] + 3); // static link
						instruction_pointer = OPS[instruction_pointer][1]-1;
						break;
					case RET:
						instruction_pointer = procedure_stack[pstack_pointer-3]-1;
						pstack_pointer -= procedure_stack[pstack_pointer-2]+1;
						break;

					case LOAD:
						dpush(procedure_stack[pstack_pointer - base(OPS[instruction_pointer][1]) - 3 - OPS[instruction_pointer][2]]);
						break;
					case STO:
						procedure_stack[pstack_pointer - base(OPS[instruction_pointer][1]) - 3 - OPS[instruction_pointer][2]] = dpop();
						break;
					case LIT:
						dpush(OPS[instruction_pointer][1]);
						break;
				}
				instruction_pointer++;
			}
		}
};


int main(int argc, char** argv) {
	vector<int> params;
	int i = 1;
	string argvi;
	for(; i < argc; i++) {
		argvi = argv[i];
		if(argvi == "-s" || argvi == "--show-stacks")
			showstacks = true;
		else if(argvi == "-o" || argvi == "--show-ops")
			showops = true;
		else if(argvi == "-c" || argvi == "--creep")
			creep = true;
		else if(argvi == "-h" || argvi == "--help" || argvi == "-help" || argvi == "--h") {
		cout << "\n +----------------------------------------------------------------------------------+\n"
		     << " | Virtual Machine for the example intermediate-code \"AM\" (abstract machine)        |\n"
		     << " +----------------------------------------------------------------------------------+\n"
		     << " +----------------------------------------------------------------------------------+\n\n";


			cout << " usage: " << argv[0] << " [options] <bps-file> [parameters for bps program]\n";
			cout << " where [options] can be\n";
			cout << "       -s --show-stacks   to show the stacks after every operation\n";
			cout << "       -o --show-ops      to show every operation before executing it\n";
			cout << "       -c --creep         to pause after every operation (note that\n";
			cout << "                          this option is disabled, if neither stacks\n";
			cout << "                          nor ops are shown)\n\n";
			cout << " the [parameters for bps program] must be integers and are put on the\n";
			cout << " stack of the main frame (the first parameter is pushed first, then the)\n";
			cout << " second and so on.\n";
			cout << " EXAMPLE: " << argv[0] << " -s -o -c fac_recursive.am 4 3\n";
			cout << " would start with the main frame 0:0:0:3:4\n\n";
			return 1;
		} else
			break;
	}
	if(!showstacks && !showops)
		creep = false;

	if(i >= argc) {
		cerr << " No am file specified.\n";
		return 1;
	}

	for(int j = argc - 1; j > i; --j)
		params.push_back(atoi(argv[j]));
	Process a(argv[i], params);
	a.RunProcess(-1);
	cout << "\n " << argv[i] << "(";
	if(argc > i+1)
		cout << argv[i+1];
	for(int j = i+2; j < argc; ++j)
		cout << "," << argv[j];
	cout << ") = (";

	for(int k = a.pstack_pointer-4; k > 0; --k)
		cout << a.procedure_stack[k] << ",";
	if(a.pstack_pointer >= 4)
		cout << a.procedure_stack[0];
	cout << ")\n\n";

	return 0;
}













