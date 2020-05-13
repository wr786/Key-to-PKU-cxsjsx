#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

class Patient {
	public:
		int serious;
		int id;
		Patient(int i, int s): serious(s), id(i) {}
};

class PatientCmp {
public:
	bool operator() (const Patient& A, const Patient& B) const {
		if(A.serious != B.serious) return A.serious < B.serious;
		return A.id > B.id;
	}
};

int main() {
	int _t; cin >> _t;
	while(_t--) {
		int n; cin >> n;
		int k = 0;
		priority_queue<Patient, vector<Patient>, PatientCmp > doctor[3];
		for(int i=1; i<=n; i++) {
			string op; cin >> op;
			if(op == "IN") {
				int dr, ss; cin >> dr >> ss;
				doctor[dr-1].push(Patient(++k, ss));
			} else if (op == "OUT") {
				int dr; cin >> dr;
				if(doctor[dr-1].empty()) {
					cout << "EMPTY\n";
				} else {
					cout << doctor[dr-1].top().id << endl;
					doctor[dr-1].pop();
				}
			}
		}
	}
	return 0;
}