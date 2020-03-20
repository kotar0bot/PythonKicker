#pragma once
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <shellapi.h>
#include <cstdio>

#include <codecvt>
#pragma comment(lib, "shlwapi")
#include <shlwapi.h>
#include <atlstr.h>
#include <vector>
#include <sstream>
#include <msclr/marshal_cppstd.h>
#include <list>
#include <iterator>
#include <algorithm>

namespace PythonKicker {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	string PythonFileName;
	string PythonDirectoryName;

	/// <summary>
	/// MyForm の概要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ kickButton;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ selectButton;

	protected:

	protected:

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->kickButton = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->selectButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// kickButton
			// 
			this->kickButton->Location = System::Drawing::Point(41, 12);
			this->kickButton->Name = L"kickButton";
			this->kickButton->Size = System::Drawing::Size(75, 23);
			this->kickButton->TabIndex = 0;
			this->kickButton->Text = L"開始";
			this->kickButton->UseVisualStyleBackColor = true;
			this->kickButton->Click += gcnew System::EventHandler(this, &MyForm::kickButton_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(41, 41);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(887, 406);
			this->richTextBox1->TabIndex = 1;
			this->richTextBox1->Text = L"";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(191, 15);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(448, 19);
			this->textBox1->TabIndex = 2;
			// 
			// selectButton
			// 
			this->selectButton->Location = System::Drawing::Point(659, 12);
			this->selectButton->Name = L"selectButton";
			this->selectButton->Size = System::Drawing::Size(112, 22);
			this->selectButton->TabIndex = 3;
			this->selectButton->Text = L"Pythonファイル選択";
			this->selectButton->UseVisualStyleBackColor = true;
			this->selectButton->Click += gcnew System::EventHandler(this, &MyForm::selectButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1082, 531);
			this->Controls->Add(this->selectButton);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->kickButton);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	void strReplace(std::string& str, const std::string& from, const std::string& to) {

		std::string::size_type pos = 0;

		while (pos = str.find(from, pos), pos != std::string::npos) {

			str.replace(pos, from.length(), to);

			pos += to.length();
		}
	}

	std::wstring s2ws(const std::string& s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}

	private: System::Void kickButton_Click(System::Object^ sender, System::EventArgs^ e) {
		strReplace(PythonDirectoryName, "\\", "\\\\");
		string teststr =  "/c cd " + PythonDirectoryName + " ; python .\\\\" + PythonFileName + " > " + PythonDirectoryName + "test.txt -Encoding utf8";

		std::wstring stemp = s2ws(teststr);
		LPCWSTR result = stemp.c_str();

		ShellExecute(NULL, L"open", L"powershell.exe", result, L"", SW_HIDE);

		setlocale(LC_ALL, "");
		CString path = (PythonDirectoryName + "test.txt").c_str();

		while (!PathFileExists(path)){
			if (PathFileExists(path)) {
				break;
			}
		}

		ifstream file(path, std::ifstream::ate);
		size_t filesize = static_cast<size_t>(file.tellg());
		while (filesize <= 0) {
			ifstream file2(path, std::ifstream::ate);
			size_t filesize2 = static_cast<size_t>(file2.tellg());

			if (filesize2 > 0) {
				break;
			}
		}
		wifstream ifs(path);
		ifs.imbue(locale(locale::empty(), new codecvt_utf16<wchar_t, 0x10ffff, little_endian>));
		wstring str((istreambuf_iterator<wchar_t>(ifs)), istreambuf_iterator<wchar_t>());

		ifs >> str;
		String^ s1 = gcnew String(str.c_str());

		this->richTextBox1->Text = s1;
	}
	
	std::vector<std::string> split(string str, char del) {
		int first = 0;
		int last = str.find_first_of(del);

		vector<string> result;

		while (first < str.size()) {
			string subStr(str, first, last - first);

			result.push_back(subStr);

			first = last + 1;
			last = str.find_first_of(del, first);

			if (last == string::npos) {
				last = str.size();
			}
		}

		return result;
	}

	std::string replaceOtherStr(std::string& replacedStr, std::string from, std::string to) {
		const unsigned int pos = replacedStr.find(from);
		const int len = from.length();

		if (pos == std::string::npos || from.empty()) {
			return replacedStr;
		}

		return replacedStr.replace(pos, len, to);
	}

	private: System::Void selectButton_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ dlg = gcnew OpenFileDialog;
		if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::Cancel) return;
		String^ FileName = dlg->FileName;
		this->textBox1->Text = FileName;

		char del = '\\';
		string filename = msclr::interop::marshal_as<std::string>(FileName);
		vector<std::string> str = split(filename, del);
		int t = str.size() - 1;
		PythonFileName = str[t];
		PythonDirectoryName = replaceOtherStr(filename, str[t], "");
	}
};
}
