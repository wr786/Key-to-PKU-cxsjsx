class D: public B {
	private:
		int nDVal;
	public:
		void Print() {
			B::Print();
			cout << "nDVal=" << nDVal << endl;
		}
		void Fun() {
			cout << "D::Fun" << endl;
		}
		D (int n): nDVal(n), B(3*n) {}
};