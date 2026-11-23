#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class MatHang{
	private:
		int maMH;
		string tenMH;
		int soLuong;
		double giaNhap, giaXuat;
		static string donVi;
		static int stt;
	public:
		MatHang();
		void Nhap();
		void In();
		double ThanhTien();
		static void DoiDonVi(const string& dv) {
			donVi = dv;
		}
};
string MatHang::donVi = "chiec";
int MatHang::stt = 0; 
MatHang::MatHang(){
	maMH = 0;
	tenMH = "";
	soLuong = 0;
	giaNhap = giaXuat = 0.0;
	stt++;
}
void MatHang::Nhap(){
	getline(cin, tenMH);
	cin>> maMH >> soLuong >> giaNhap >> giaXuat;
	getchar();
}
double MatHang::ThanhTien(){
	return soLuong * giaXuat;
}
void MatHang::In(){
	cout<< stt << " "
		<< maMH << " "
		<< tenMH << " "
		<< donVi << " "
		<< soLuong << " "
		<< giaXuat << " "
		<< ThanhTien() << endl;
}

class KhachHang{
	private:
		string tenKH;
		string diaChi;
		string dienThoai;
	public:
		KhachHang();
		void Nhap();
		void In();
};
KhachHang::KhachHang(){
	tenKH = "";
	diaChi = "";
	dienThoai = "";
}
void KhachHang::Nhap(){
	getline(cin, tenKH);
	getchar();
	getline(cin, diaChi);
	getchar();
	getline(cin, dienThoai);
	getchar();
}
void KhachHang::In(){
	cout<< "Ban cho:" << tenKH
		<< "Dia chi:" << diaChi
		<< "Dien thoai:" << dienThoai << endl;
}

class HoaDon{
	private:
		string soHD;
		string ngay;
		KhachHang kh;
		int n;
		double thue;
		string hinhThuc;
	public:
		HoaDon();
		void Nhap();
		double TongTien();
		double TinhThue();
		double TongThanhToan();
		void In();
};
HoaDon::HoaDon(){
	
}

int main(){
	MatHang mh1, mh2, mh3;
	mh1.Nhap();
	mh2.Nhap();
	mh1.In();
	mh2.In();
	MatHang::DoiDonVi("thung");
	mh3.Nhap();
	m
	h3.In();
}
