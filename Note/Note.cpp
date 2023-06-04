#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
//Ham check string1 va string 2 co giong nhau hay khong
bool checkstring(string s1, string s2) {
	if (s1.size() != s2.size()) {
		return false;
	}
	else {
		for (int i = 0; i < s2.size(); i++) {
			if (s1[i] != s2[i]) {
				return false;
			}
		}
		return true;
	}
}
//Ham kiem tra id co ton tai hay khong va cung tra vi vi tri neu tt
bool verify(vector<string>vt, string str,int &n) {
	for (int i = 0; i < vt.size(); i++) {
		string str1(vt[i].begin(), vt[i].begin() + 3);
		if (str1 == "Id:") {
			string str2(vt[i], 4, vt[i].size());
			if (checkstring(str2, str) == true) {
				n = i;
				return true;
			}
			if (checkstring(str2, str) == false && i == vt.size() - 1) {
				return false;
			}
		}
	}
}
class ntn {
private:
	int ngay;
	int thang;
	int nam;
public:
	ntn(){}
	friend istream& operator>>(istream& CIN, ntn& n) {
		cout << "Ngay: "; CIN >> n.ngay;
		cout << "Thang: "; CIN >> n.thang;
		cout << "Nam: "; CIN >> n.nam;
		return CIN;
	}
	int getNgay() {
		return ngay;
	}
	int getNam() {
		return nam;
	}
	int getThang() {
		return thang;
	}
	void setNgay(int ngay) {
		this->ngay = ngay;
	}
	void setThang(int thang) {
		this->thang = thang;
	}
	void setNam(int nam) {
		this->nam = nam;
	}
	friend ostream& operator<<(ostream& COUT, ntn& n) {
		cout << n.ngay << "/" << n.thang << "/" << n.nam << endl;
		return COUT;
	}
	~ntn() {
		ngay = thang = nam = 0;
	}
};
class Nganhang:public ntn {
private:
	string ten;
	int id;
	string password;
	ntn Ntn;
	long long tien;
public:
	Nganhang(){}
	friend istream& operator>>(istream& CIN, Nganhang& n) {
		cout << "Nhap id: "; CIN >> n.id;
		cout << "Nhap ten: ";
		CIN.ignore();
		getline(CIN, n.ten);
		cout << "Nhap ngay/thang/nam sinh: " << endl;
		cin >> n.Ntn;
		cout << "Nhap so tien trong tai khoan: ";
		cin >> n.tien;
		cout << "Nhap mat khau: "; CIN >> n.password;
		return CIN;
	}
	void setId(int id) {
		this->id = id;
	}
	int getId() {
		return id;
	}
	void setTen(string ten) {
		this->ten = ten;
	}
	string getTen() {
		return ten;
	}
	void setPassword(string password) {
		this->password = password;
	}
	string getPassword() {
		return password;
	}
	long long getTien() {
		return tien;
	}
	ntn getNtn() {
		return Ntn;
	}
	friend ostream& operator<<(ostream& COUT, Nganhang& n) {
		cout << "Id: " << n.id << endl;
		cout << "Tan: " << n.ten << endl;
		cout << "Ngay thang nam sinh: ";
		cout << n.Ntn;
		cout << "Tien trong tai khoan: "<<n.tien<<endl;
		cout << "Mat khau: " << n.password << endl;
		return COUT;
	}
	~Nganhang() {
		id = 0;
		ten = "";
		password = "";
	}
};
int main() {
	int k;
	do {
		cout << "1.Truy xuat thong tin khach hang." << endl;
		cout << "2.Nhap them thong tin." << endl;
		cout << "3.Tra cuu thong tin."<<endl;
		cout << "0.Thoat!" << endl;
		cout << "Chon muc thuc hien: ";
		cin >> k;
		if (k == 1) {
			fstream myfile;
			myfile.open("Bank.txt", ios::in);
			if (myfile.is_open()) {
				string str;
				while (getline(myfile, str)) {
					cout << str << endl;
				}
				myfile.close();
			}
			cout << "--------------*****--------------" << endl;
		}
		else if (k == 2) {
			Nganhang nh;
			int n;
			cout << "Nhap so luong tai khoan: ";
			cin >> n;
			vector<Nganhang>tk;
			for (int i = 0; i < n; i++) {
				cin >> nh;
				tk.push_back(nh);
			}
			fstream myfile;
			myfile.open("Bank.txt", ios::app);
			if (myfile.is_open()) {
				for (int i = 0; i < tk.size(); i++) {
					myfile << "Id: " << tk[i].getId() << endl;
					myfile << "Ten: " << tk[i].getTen() << endl;
					myfile << "Ngay/thang/nam sinh: " << tk[i].getNtn().getNgay() << "/" << tk[i].getNtn().getThang() << "/" << tk[i].getNtn().getNam() << endl;
					myfile << "So du: " << tk[i].getTien() << endl;
					myfile << "Mat khau: " << tk[i].getPassword() << endl;
				}
				myfile.close();
				cout << "--------------*****--------------" << endl;
			}
		}
		else if (k==3) {
			fstream myfile;
			vector<string> vt;
			myfile.open("Bank.txt", ios::in);
			cout << "Nhap vao id de tim kiem: ";
			string str;
			cin >> str;
			int n = 0;
			if (myfile.is_open()) {
				string str1;
				while (getline(myfile, str1)) {
					vt.push_back(str1);
				}
				if (verify(vt, str,n)== true) {
					for (int i = n; i <= n + 3; i++) {
						cout << vt[i] << endl;
					}
					cout << "--------------*****--------------" << endl;
				}
				else {
					cout << "Tai khoan khong ton tai!.\n";
					cout << "--------------*****--------------" << endl;
				}
			}
			myfile.close();
		}
	} while (k != 0);
}